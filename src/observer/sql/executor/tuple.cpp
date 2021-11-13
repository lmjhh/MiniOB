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
// Created by Wangyunlai on 2021/5/14.
//

#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "common/log/log.h"
#include <algorithm>

Tuple::Tuple(const Tuple &other) {
  LOG_PANIC("Copy constructor of tuple is not supported");
  exit(1);
}

Tuple::Tuple(Tuple &&other) noexcept : values_(std::move(other.values_)) {
}

Tuple & Tuple::operator=(Tuple &&other) noexcept {
  if (&other == this) {
    return *this;
  }

  values_.clear();
  values_.swap(other.values_);
  return *this;
}

Tuple::~Tuple() {
}

// add (Value && value)
void Tuple::add(TupleValue *value) {
  values_.emplace_back(value);
}
void Tuple::add(const std::vector<std::shared_ptr<TupleValue>> &other) {
  values_.insert(values_.end(), other.begin(), other.end());
}

void Tuple::add(const std::shared_ptr<TupleValue> &other) {
  values_.emplace_back(other);
}

void Tuple::add(int value) {
  add(new IntValue(value));
}

void Tuple::add(float value) {
  add(new FloatValue(value));
}

void Tuple::addDate(int value) {
  add(new DateValue(value));
}

void Tuple::add(const char *s, int len) {
  add(new StringValue(s, len));
}

void Tuple::clear(){
  values_.clear();
}

void Tuple::swapTuple(Tuple *A, Tuple *B){
    const std::vector<std::shared_ptr<TupleValue>> &values1 = A->values();
    const std::vector<std::shared_ptr<TupleValue>> &values2 = B->values();
    A->clear();
    B->clear();
    LOG_ERROR("准备交换");
    A->add(values2);
    B->add(values1);
}

////////////////////////////////////////////////////////////////////////////////

std::string TupleField::to_string() const {
  return std::string(table_name_) + "." + field_name_ + std::to_string(type_);
}

////////////////////////////////////////////////////////////////////////////////
void TupleSchema::from_table(const Table *table, TupleSchema &schema) {
  const char *table_name = table->name();
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = 0; i < field_num; i++) {
    const FieldMeta *field_meta = table_meta.field(i);
    if (field_meta->visible()) {
      schema.add(field_meta->type(), table_name, field_meta->name());
    }
  }
}

void TupleSchema::from_select(const char *table_name, const char *field_name, TupleSchema &schema, const TupleSchema &full_schema){
  const int size = full_schema.fields().size();
  for (int i = 0; i < size; i++) {
    const TupleField &field = full_schema.fields()[i];
    if(table_name == nullptr && field_name == nullptr){
      schema.add(field.type(), field.table_name(), field.field_name());
    }
    if(table_name == nullptr && field_name != nullptr){
      if (0 == strcmp(field.field_name(), field_name)) {
        schema.add(field.type(), field.table_name(), field.field_name());
      }
    }
    if(table_name != nullptr && field_name == nullptr){
      if (0 == strcmp(field.table_name(), table_name)) {
        schema.add(field.type(), field.table_name(), field.field_name());
      }
    }
    if(table_name != nullptr && field_name != nullptr){
      if (0 == strcmp(field.table_name(), table_name) && 0 == strcmp(field.field_name(), field_name)){
        schema.add(field.type(), field.table_name(), field.field_name());
      }
    }
  }
}

void TupleSchema::add(AttrType type, const char *table_name, const char *field_name) {
  fields_.emplace_back(type, table_name, field_name);
}

void TupleSchema::add_if_not_exists(AttrType type, const char *table_name, const char *field_name) {
  for (const auto &field: fields_) {
    if (0 == strcmp(field.table_name(), table_name) &&
        0 == strcmp(field.field_name(), field_name)) {
      return;
    }
  }

  add(type, table_name, field_name);
}

void TupleSchema::append(const TupleSchema &other) {
  fields_.reserve(fields_.size() + other.fields_.size());
  for (const auto &field: other.fields_) {
    fields_.emplace_back(field);
  }
}

int TupleSchema::index_of_field(const char *table_name, const char *field_name) const {
  const int size = fields_.size();
  for (int i = 0; i < size; i++) {
    const TupleField &field = fields_[i];
    if (0 == strcmp(field.table_name(), table_name) && 0 == strcmp(field.field_name(), field_name)) {
      return i;
    }
  }
  return -1;
}

void TupleSchema::print(std::ostream &os, bool isMoreTable) const {
  if (fields_.empty()) {
    os << "No schema";
    return;
  }

  // 判断有多张表还是只有一张表
  std::set<std::string> table_names;
  for (const auto &field: fields_) {
    table_names.insert(field.table_name());
  }


  for (std::vector<TupleField>::const_iterator iter = fields_.begin(), end = --fields_.end();
       iter != end; ++iter) {

    int is_func_field = 0;
    for(int i = 0; iter->field_name()[i]; i++){
      if(iter->field_name()[i] == '(') {
         is_func_field = 1;
         break;
      }
    }
    
    if ((table_names.size() > 1 || isMoreTable) && is_func_field == 0 ) {
      os << iter->table_name() << ".";
    }
    os << iter->field_name() << " | ";
  }

  int is_func_field = 0;
  for(int i = 0; fields_.back().field_name()[i]; i++){
    if(fields_.back().field_name()[i] == '(') {
        is_func_field = 1;
        break;
    }
  }

  if ((table_names.size() > 1 || isMoreTable ) && is_func_field == 0) {
    os << fields_.back().table_name() << ".";
  }
  os << fields_.back().field_name() << std::endl;
}

/////////////////////////////////////////////////////////////////////////////
TupleSet::TupleSet(TupleSet &&other) : tuples_(std::move(other.tuples_)), schema_(other.schema_){
  other.schema_.clear();
}

TupleSet &TupleSet::operator=(TupleSet &&other) {
  if (this == &other) {
    return *this;
  }

  schema_.clear();
  schema_.append(other.schema_);
  other.schema_.clear();

  tuples_.clear();
  tuples_.swap(other.tuples_);
  return *this;
}

void TupleSet::add(Tuple &&tuple) {
  tuples_.emplace_back(std::move(tuple));
}

void TupleSet::clear() {
  tuples_.clear();
  schema_.clear();
}

void TupleSet::print(std::ostream &os, bool isMoreTable) const {
  if (schema_.fields().empty()) {
    LOG_WARN("Got empty schema");
    return;
  }
  schema_.print(os, isMoreTable);

  for (const Tuple &item : tuples_) {
    const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
    for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
          iter != end; ++iter) {
      (*iter)->to_string(os);
      os << " | ";
    }
    values.back()->to_string(os);
    os << std::endl;
  }
}

bool isNumber(const std::string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

RC TupleSet::order_by_field_and_type(const RelAttr *attributes, const OrderType *order_types, size_t size) {

  /* 检查是否合法 */
   for(int i = size - 1; i >= 0; i--){
      if(attributes[i].relation_name == nullptr){
        TupleField field = schema().field(0);
        size_t vaule_index = schema().index_of_field(field.table_name(), attributes[i].attribute_name);
        buble_sort(vaule_index, order_types[i]);
      }else {
        size_t vaule_index = schema().index_of_field(attributes[i].relation_name, attributes[i].attribute_name);
        buble_sort(vaule_index, order_types[i]);
      }
   }
   return RC::SUCCESS;

} 

void TupleSet::buble_sort(int index, OrderType type){
  for (int i = 0; i < size() - 1; i++) {
    for(int j = 0; j < size() - 1 - i; j++){
        if(compareTupleWithIndex(get(j),get(j + 1),index, type)){
            std::swap(tuples_[j], tuples_[j + 1]);
        }
    }
  }
}


bool TupleSet::compareTupleWithIndex(const Tuple &tuple1, const Tuple &tuple2, int index, OrderType type){
  const std::vector<std::shared_ptr<TupleValue>> &values1 = tuple1.values();
  const std::vector<std::shared_ptr<TupleValue>> &values2 = tuple2.values();
  int cmp_result = (*values1[index]).compare(*values2[index]);
  switch (type)
  {
    case OrderType::BYDESC:{
      if(cmp_result < 0){
        return true;
      }else{
        return false;
      }
    }
    break;
    default:{
      if(cmp_result <= 0){
        return false;
      }else{
        return true;
      }    
    }
    break;
  }
}

bool isnum(const std::string& s)
{
        std::stringstream sin(s);
        double t;
        char p;
        if(!(sin >> t))
          return false;
        if(sin >> p)
          return false;
        else
          return true;
}

bool isChar(std::string s){
  if (s[0] == '\'' or  s[0] == '\"')
    return true;
  else
    return false;
}


void TupleSet::set_schema(const TupleSchema &schema) {
  schema_ = schema;
}

const TupleSchema &TupleSet::get_schema() const {
  return schema_;
}

bool TupleSet::is_empty() const {
  return tuples_.empty();
}

int TupleSet::size() const {
  return tuples_.size();
}

const Tuple &TupleSet::get(int index) const {
  return tuples_[index];
}

const std::vector<Tuple> &TupleSet::tuples() const {
  return tuples_;
}

/////////////////////////////////////////////////////////////////////////////
TupleRecordConverter::TupleRecordConverter(Table *table, TupleSet &tuple_set) :
      table_(table), tuple_set_(tuple_set){
}

void TupleRecordConverter::add_record(const char *record) {
  const TupleSchema &schema = tuple_set_.schema();
  Tuple tuple;
  const TableMeta &table_meta = table_->table_meta();
  for (const TupleField &field : schema.fields()) {
    const FieldMeta *field_meta = table_meta.field(field.field_name());
    assert(field_meta != nullptr);
    switch (field_meta->type()) {
      case DATES: {
        int value = *(int*)(record + field_meta->offset());
        tuple.addDate(value);
      }
      break;
      case INTS: {
        int value = *(int*)(record + field_meta->offset());
        tuple.add(value);
      }
      break;
      case FLOATS: {
        float value = *(float *)(record + field_meta->offset());
        tuple.add(value);
      }
        break;
      case CHARS: {
        const char *s = record + field_meta->offset();  // 现在当做Cstring来处理
        tuple.add(s, strlen(s));
      }
      break;
      default: {
        LOG_PANIC("Unsupported field type. type=%d", field_meta->type());
      }
    }
  }

  tuple_set_.add(std::move(tuple));
}


