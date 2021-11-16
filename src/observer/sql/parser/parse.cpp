/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Longda on 2021/4/13.
//

#include <mutex>
#include "sql/parser/parse.h"
#include "rc.h"
#include "common/log/log.h"
#include <string.h>
#include<sstream>

RC parse(char *st, Query *sqln);

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name) {
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }
  relation_attr->attribute_name = strdup(attribute_name);
}
void relation_attr_init_for_number(RelAttr *relation_attr, const char *relation_name, int attribute_name){
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }  
  std::string str = std::to_string(attribute_name);
  const char *p = str.c_str();
  relation_attr->attribute_name = strdup(p);
}
void relation_attr_init_for_float(RelAttr *relation_attr, const char *relation_name, float attribute_name){
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }  
  std::ostringstream oss;
  oss << attribute_name;
  std::string str(oss.str());
  // std::string str = std::f(attribute_name);
  const char *p = str.c_str();
  relation_attr->attribute_name = strdup(p);
}

void relation_attr_destroy(RelAttr *relation_attr) {
  free(relation_attr->relation_name);
  free(relation_attr->attribute_name);
  relation_attr->relation_name = nullptr;
  relation_attr->attribute_name = nullptr;
  relation_attr->lsn = 0;
  std::cout << "relation_attr_destroy" << std::endl;
}

void mystrlwr(char *ps){
  while(*ps){
    if('A' <= *ps && *ps <= 'Z')
      *ps += 'a' - 'A'; 
      ps++;
  }
}

void poly_init(Poly *poly_tmp, const char *poly_name) {//在检测到attri时才将attri记录到poly的attributes里面
  std::cout << "paser: " << poly_name << std::endl;
  if (poly_name != nullptr) {
    poly_tmp->poly_attr.poly_name = strdup(poly_name);
    char *tmp_poly_name = strdup(poly_name);
    mystrlwr(tmp_poly_name);
    if(strcmp(tmp_poly_name, "avg") == 0) {poly_tmp->poly_attr.poly_type = POAVG;}
    if(strcmp(tmp_poly_name, "max") == 0) {poly_tmp->poly_attr.poly_type = POMAX;}
    if(strcmp(tmp_poly_name, "min") == 0) {poly_tmp->poly_attr.poly_type = POMIN;}
    if(strcmp(tmp_poly_name, "count") == 0) {poly_tmp->poly_attr.poly_type = POCOUNT;}
    poly_tmp->attr_num = 0;
  } else {
    poly_tmp->poly_attr.poly_name = nullptr;
  }

}

void poly_destroy(Poly *poly_tmp) {
  for (int k=0;k<poly_tmp->attr_num;k++){
    if(!&poly_tmp->attributes[k]){
      relation_attr_destroy(&poly_tmp->attributes[k]);
    }
  }
  free(poly_tmp->poly_attr.poly_name);
  poly_tmp->poly_attr.poly_name = nullptr;
  poly_tmp->attr_num = 0;
  poly_tmp->lsn = 0;
  std::cout << "poly_destroy" << std::endl;
}

void value_init_integer(Value *value, int v) {
  value->type = INTS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
  std::cerr<<"---value_init_int"<<std::endl;
}
void value_init_float(Value *value, float v) {
  value->type = FLOATS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
  std::cerr<<"---value_init_float"<<std::endl;
}
void value_init_null(Value *value, int v){
  value->type = NULLS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
  std::cerr<<"---value_init_NULL"<<std::endl;  
}
void value_init_string(Value *value, const char *v) {
  value->type = CHARS;
  value->data = strdup(v);
  std::cerr<<"---value_init_string"<<std::endl;
  std::cerr<<"---value->data:"<<value->data<<std::endl;
}
void value_init_date(Value *value, const char *v) {
  std::cerr<<"---value_init_date"<<std::endl;

  int year=0, month=0, day=0, valid=1, leap_year=0;
  char d[20] = ".-";
  char date[20];
  strcpy(date, v);
  char *p;
  p = strtok(date,d);
  int data_int = 0;
  if(p)
  {
    	for(int i=0; i<strlen(p); i++)
    	{
    		//cout<<p[i]<<endl;
    		data_int *=10;
    		data_int += p[i]-48;
		  }
      year = data_int;
	}
    p=strtok(NULL,d);
    if(p)
    {
    	if(strlen(p)==1)
    	{
    		data_int *=10;
    		data_int *=10;
    		data_int += p[0]-48;
		  }
		  else
		  {
			  data_int *=10;
    	  data_int += p[0]-48;
    	  data_int *=10;
    	  data_int += p[1]-48;
	  	}
      month = data_int % 100;
	  }
  p=strtok(NULL,d);
  if(p)
  {
    	if(strlen(p)==1)
    	{
    		data_int *=10;
    		data_int *=10;
    		data_int += p[0]-48;
		}
		else
		{
			data_int *=10;
    	data_int += p[0]-48;
    	data_int *=10;
    	data_int += p[1]-48;
		}
    day = data_int % 100;
	}
  if(year %4 ==0)
    leap_year=1;
  if(month > 12 || month < 1)
    valid=0;
  if(day > 31 || day < 1)
    valid = 0;
  if(month == 2 )
  {
    if(day>29)
      valid = 0;
    if(leap_year == 0 && day > 28)
      valid = 0;
  }
  if(month==4 || month==6 || month==9 || month==11)
  {
    if(day > 30)
      valid =0;
  }
  if(valid == 1){
    value->type = DATES;
    value->data = malloc(sizeof(int));
    memcpy(value->data, &data_int, sizeof(data_int));
  }
  else{
    value->type = UNDEFINED;
    value->data = malloc(sizeof(int));
    memcpy(value->data, &data_int, sizeof(data_int));
  }
  
}
void value_destroy(Value *value) {
  value->type = UNDEFINED;
  free(value->data);
  value->data = nullptr;
}

void condition_init(Condition *condition, CompOp comp, 
                    int left_is_attr, RelAttr *left_attr, Value *left_value,
                    int right_is_attr, RelAttr *right_attr, Value *right_value) {
  condition->comp = comp;
  condition->left_is_attr = left_is_attr;
  if (left_is_attr) {
    condition->left_attr = *left_attr;
  } else {
    condition->left_value = *left_value;
  }

  condition->right_is_attr = right_is_attr;
  if (right_is_attr) {
    condition->right_attr = *right_attr;
  } else {
    condition->right_value = *right_value;
  }
}

void condition_init_with_comp(Condition *condition, CompOp comp){
  condition->comp = comp;
} 

void condition_destroy(Condition *condition) {
  if (condition->left_is_attr) {
    relation_attr_destroy(&condition->left_attr);
  } else {
    value_destroy(&condition->left_value);
  }
  if (condition->right_is_attr) {
    relation_attr_destroy(&condition->right_attr);
  } else {
    value_destroy(&condition->right_value);
  }
  if (condition->left_sub_select != nullptr){
    selects_destroy(condition->left_sub_select);
  }
  condition->left_sub_select = nullptr;
  if (condition->right_sub_select != nullptr){
    selects_destroy(condition->right_sub_select);
  }
  condition->right_sub_select = nullptr;
}

void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length, int is_null_able) {
  attr_info->name = strdup(name);
  attr_info->type = type;
  attr_info->is_nullable = is_null_able;
  std::cerr<<"----type:"<<type<<std::endl;
  attr_info->length = length;
}
void attr_info_destroy(AttrInfo *attr_info) {
  free(attr_info->name);
  attr_info->name = nullptr;
}

void selects_init(Selects *selects, ...);

void selects_copy_with_other(Selects *selects, Selects *other){
  for(int i = 0; i < other->relation_num; i++){
    selects->relations[i] = strdup(other->relations[i]);
  }
  selects->relation_num = other->relation_num;

  for(int i = 0; i < other->attr_num; i++){
    selects->attributes[i] = other->attributes[i];
  }
  selects->attr_num = other->attr_num;

  for(int i = 0; i < other->poly_num; i++){
    selects->poly_list[i] = other->poly_list[i];
  }
  selects->poly_num = other->poly_num;

  for(int i = 0; i < other->condition_num; i++){
    selects->conditions[i] = other->conditions[i];
  }
  selects->condition_num = other->condition_num;

  selects_destroy(other);
}

void selects_append_attribute(Selects *selects, RelAttr *rel_attr) {
  if(rel_attr->relation_name != nullptr){
    LOG_ERROR("attr %s.%s",rel_attr->relation_name,rel_attr->attribute_name);
  }else{
    LOG_ERROR("attr %s",rel_attr->attribute_name);
  }
  if(selects->lsn < 0 or selects->lsn > MAX_NUM) selects->lsn = 0;
  rel_attr->lsn = selects->lsn++;
  LOG_ERROR("attr lsn = %d",rel_attr->lsn);
  selects->attributes[selects->attr_num++] = *rel_attr;
}
void selects_append_relation(Selects *selects, const char *relation_name) {
  selects->relations[selects->relation_num++] = strdup(relation_name);
}

void selects_append_conditions(Selects *selects, Condition conditions[], size_t start, size_t end) {
  // assert((end - start)) <= sizeof(selects->conditions)/sizeof(selects->conditions[0]));
  int index = 0;
  for (size_t i = start; i < end; i++) {
    selects->conditions[index++] = conditions[i];
  }
  selects->condition_num = end - start;
}

void selects_append_poly(Selects *selects, Poly *rel_po) {
  if(selects->lsn < 0 or selects->lsn > MAX_NUM) selects->lsn = 0;
  rel_po->lsn = selects->lsn++;
  selects->poly_list[selects->poly_num] = *rel_po;
  rel_po->attr_num = 0;
  selects->poly_num++;
  // std::cout << "selects->poly_num" << selects->poly_num << std::endl;
}
void selects_append_poly_attribute(Selects *selects, RelAttr *rel_attr, int is_attr) {
  if (selects->poly_list[selects->poly_num-1].attr_num < 0 or selects->poly_list[selects->poly_num-1].attr_num > MAX_NUM){
    selects->poly_list[selects->poly_num-1].attr_num = 0;
  }
  if(rel_attr->relation_name != nullptr){
    LOG_ERROR("poly attr %s.%s",rel_attr->relation_name,rel_attr->attribute_name);
  }else{
    LOG_ERROR("poly attr %s",rel_attr->attribute_name);
  }
  selects->poly_list[selects->poly_num-1].attributes[selects->poly_list[selects->poly_num-1].attr_num] = *rel_attr;
  selects->poly_list[selects->poly_num-1].isAttr = is_attr;
  selects->poly_list[selects->poly_num-1].attr_num++;
}

void selects_append_orderbyAttr(Selects *selects, RelAttr *attr, OrderType type){
  if(selects->order_by.attr_num < 0 || selects->order_by.attr_num > MAX_NUM){
      selects->order_by.attr_num = 0;
  }
  selects->order_by.attributes[selects->order_by.attr_num] = *attr;
  selects->order_by.order_type[selects->order_by.attr_num] = type;
  selects->order_by.attr_num++;
}

void selects_append_groupbyAttr(Selects *selects, RelAttr *attr, OrderType type){
  if(selects->group_by.attr_num < 0 || selects->group_by.attr_num > MAX_NUM){
      selects->group_by.attr_num = 0;
  }
  if(attr->relation_name != nullptr){
    LOG_ERROR("group_by %s.%s",attr->relation_name,attr->attribute_name);
  }else{
    LOG_ERROR("group_by %s",attr->attribute_name);
  }
  selects->group_by.attributes[selects->group_by.attr_num] = *attr;
  selects->group_by.order_type[selects->group_by.attr_num] = type;
  selects->group_by.attr_num++;
}

void selects_destroy(Selects *selects) {
  for (size_t i = 0; i < selects->attr_num; i++) {
    relation_attr_destroy(&selects->attributes[i]);
  }
  selects->attr_num = 0;
  selects->lsn = 0;

  for (size_t i = 0; i < selects->relation_num; i++) {
    free(selects->relations[i]);
    selects->relations[i] = NULL;
  }
  selects->relation_num = 0;

  for (size_t i = 0; i < selects->condition_num; i++) {
    condition_destroy(&selects->conditions[i]);
  }
  selects->condition_num = 0;

  for (size_t i = 0; i < selects->poly_num; i++) {
    poly_destroy(&selects->poly_list[i]);
  }
  selects->poly_num = 0;

  for (size_t i = 0; i < selects->order_by.attr_num; i++) {
    relation_attr_destroy(&selects->order_by.attributes[i]);
    selects->order_by.order_type[i] = BYASC;
  }

  selects->group_by.attr_num = 0;
  for (size_t i = 0; i < selects->group_by.attr_num; i++) {
    relation_attr_destroy(&selects->group_by.attributes[i]);
    selects->group_by.order_type[i] = BYASC;
  }
  selects->group_by.attr_num = 0;
}


void inserts_init(Inserts *inserts, const char *relation_name) {
  inserts->relation_name = strdup(relation_name);
}

void inserts_append_tuple(Inserts *inserts, Value values[], size_t value_num) {
  assert(value_num <= sizeof(inserts->tuples[0].values)/sizeof(inserts->tuples[0].values[0]));
  if(inserts->tuple_num < 0 || inserts->tuple_num > MAX_NUM) inserts->tuple_num = 0;
  for (size_t i = 0; i < value_num; i++) {
    inserts->tuples[inserts->tuple_num].values[i] = values[i];
  }
  inserts->tuples[inserts->tuple_num].value_num = value_num;
  inserts->tuple_num++;
}

void inserts_destroy(Inserts *inserts) {
  free(inserts->relation_name);
  inserts->relation_name = nullptr;
  for (size_t j = 0; j < inserts->tuple_num; j++){
    for (size_t i = 0; i < inserts->tuples[j].value_num; i++) {
      value_destroy(&inserts->tuples[j].values[i]);
    }
    inserts->tuples[j].value_num = 0;
  }
  inserts->tuple_num = 0;
}

void deletes_init_relation(Deletes *deletes, const char *relation_name) {
  deletes->relation_name = strdup(relation_name);
}

void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num) {
  assert(condition_num <= sizeof(deletes->conditions)/sizeof(deletes->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    deletes->conditions[i] = conditions[i];
  }
  deletes->condition_num = condition_num;
}
void deletes_destroy(Deletes *deletes) {
  for (size_t i = 0; i < deletes->condition_num; i++) {
    condition_destroy(&deletes->conditions[i]);
  }
  deletes->condition_num = 0;
  free(deletes->relation_name);
  deletes->relation_name = nullptr;
}

void updates_init(Updates *updates, const char *relation_name, const char *attribute_name,
                  Value *value, Condition conditions[], size_t condition_num) {
  updates->relation_name = strdup(relation_name);
  updates->attribute_name = strdup(attribute_name);
  updates->value = *value;

  assert(condition_num <= sizeof(updates->conditions)/sizeof(updates->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    updates->conditions[i] = conditions[i];
  }
  updates->condition_num = condition_num;
}

void updates_destroy(Updates *updates) {
  free(updates->relation_name);
  free(updates->attribute_name);
  updates->relation_name = nullptr;
  updates->attribute_name = nullptr;

  value_destroy(&updates->value);

  for (size_t i = 0; i < updates->condition_num; i++) {
    condition_destroy(&updates->conditions[i]);
  }
  updates->condition_num = 0;
}

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info) {
  create_table->attributes[create_table->attribute_count++] = *attr_info;
}
void create_table_init_name(CreateTable *create_table, const char *relation_name) {
  create_table->relation_name = strdup(relation_name);
}
void create_table_destroy(CreateTable *create_table) {
  for (size_t i = 0; i < create_table->attribute_count; i++) {
    attr_info_destroy(&create_table->attributes[i]);
  }
  create_table->attribute_count = 0;
  free(create_table->relation_name);
  create_table->relation_name = nullptr;
}

void drop_table_init(DropTable *drop_table, const char *relation_name) {
  drop_table->relation_name = strdup(relation_name);
}
void drop_table_destroy(DropTable *drop_table) {
  free(drop_table->relation_name);
  drop_table->relation_name = nullptr;
}

void create_index_init(CreateIndex *create_index, const char *index_name, const char *relation_name, int is_unique) {
  create_index->index_name = strdup(index_name);
  create_index->relation_name = strdup(relation_name);
  create_index->is_unique = is_unique;
}

void create_index_append_attribute(CreateIndex *create_index, const char *attr_name){
  if(create_index->attribute_count < 0 || create_index->attribute_count > MAX_NUM) create_index->attribute_count = 0;
  create_index->attribute_names[create_index->attribute_count++] = strdup(attr_name);
}

void create_index_destroy(CreateIndex *create_index) {
  free(create_index->index_name);
  free(create_index->relation_name);
  
  for(int i = 0; i < create_index->attribute_count; i++){
    free(create_index->attribute_names[i]);
  }
  create_index->attribute_count = 0;
  create_index->index_name = nullptr;
  create_index->relation_name = nullptr;
}

void create_unique_index_destroy(CreateIndex *create_index) {
  free(create_index->index_name);
  free(create_index->relation_name);

  create_index->index_name = nullptr;
  create_index->relation_name = nullptr;
}

void drop_index_init(DropIndex *drop_index, const char *index_name) {
  drop_index->index_name = strdup(index_name);
}
void drop_index_destroy(DropIndex *drop_index) {
  free((char *)drop_index->index_name);
  drop_index->index_name = nullptr;
}

void desc_table_init(DescTable *desc_table, const char *relation_name) {
  desc_table->relation_name = strdup(relation_name);
}

void desc_table_destroy(DescTable *desc_table) {
  free((char *)desc_table->relation_name);
  desc_table->relation_name = nullptr;
}

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name) {
  load_data->relation_name = strdup(relation_name);

  if (file_name[0] == '\'' || file_name[0] == '\"') {
    file_name++;
  }
  char *dup_file_name = strdup(file_name);
  int len = strlen(dup_file_name);
  if (dup_file_name[len - 1] == '\'' || dup_file_name[len - 1] == '\"') {
    dup_file_name[len - 1] = 0;
  }
  load_data->file_name = dup_file_name;
}

void load_data_destroy(LoadData *load_data) {
  free((char *)load_data->relation_name);
  free((char *)load_data->file_name);
  load_data->relation_name = nullptr;
  load_data->file_name = nullptr;
}

void query_init(Query *query) {
  query->flag = SCF_ERROR;
  memset(&query->sstr, 0, sizeof(query->sstr));
}

Query *query_create() {
  Query *query = (Query *)malloc(sizeof(Query));
  if (nullptr == query) {
    LOG_ERROR("Failed to alloc memroy for query. size=%ld", sizeof(Query));
    return nullptr;
  }

  query_init(query);
  return query;
}

void query_reset(Query *query) {
  switch (query->flag) {
    case SCF_SELECT: {
      selects_destroy(&query->sstr.selection);
    }
    break;
    case SCF_INSERT: {
      inserts_destroy(&query->sstr.insertion);
    }
    break;
    case SCF_DELETE: {
      deletes_destroy(&query->sstr.deletion);
    }
    break;
    case SCF_UPDATE: {
      updates_destroy(&query->sstr.update);
    }
    break;
    case SCF_CREATE_TABLE: {
      create_table_destroy(&query->sstr.create_table);
    }
    break;
    case SCF_DROP_TABLE: {
      drop_table_destroy(&query->sstr.drop_table);
    }
    break;
    case SCF_CREATE_INDEX: {
      create_index_destroy(&query->sstr.create_index);
    }
    break;
    case SCF_CREATE_UNIQUE_INDEX: {
      create_unique_index_destroy(&query->sstr.create_index);
    }
    break;
    case SCF_DROP_INDEX: {
      drop_index_destroy(&query->sstr.drop_index);
    }
    break;
    case SCF_SYNC: {

    }
    break;
    case SCF_SHOW_TABLES:
    break;

    case SCF_DESC_TABLE: {
      desc_table_destroy(&query->sstr.desc_table);
    }
    break;

    case SCF_LOAD_DATA: {
      load_data_destroy(&query->sstr.load_data);
    }
    break;
    case SCF_BEGIN:
    case SCF_COMMIT:
    case SCF_ROLLBACK:
    case SCF_HELP:
    case SCF_EXIT:
    case SCF_ERROR:
    break;
  }
}

void query_destroy(Query *query) {
  query_reset(query);
  free(query);
}
#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

////////////////////////////////////////////////////////////////////////////////

extern "C" int sql_parse(const char *st, Query  *sqls);

RC parse(const char *st, Query *sqln) {
  sql_parse(st, sqln);

  if (sqln->flag == SCF_ERROR)
    return SQL_SYNTAX;
  else
    return SUCCESS;
}