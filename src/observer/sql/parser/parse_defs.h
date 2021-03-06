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
// Created by wangyunlai.wyl on 2021/6/7.
//

#ifndef __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
#define __OBSERVER_SQL_PARSER_PARSE_DEFS_H__

#include <stddef.h>
#include <string.h>

#define MAX_NUM 20
#define MAX_REL_NAME 20
#define MAX_ATTR_NAME 20
#define MAX_ERROR_MESSAGE 20
#define MAX_DATA 50
#define OB_FLT_MIN 1.17549435e-38F
#define OB_INT_MIN -2147483648
#define MAX_EXP_NODE_NUM 25
#define MAX_EXP_TMP_NUM 5
//属性结构体
typedef struct {
  char *relation_name;   // relation name (may be NULL) 表名
  char *attribute_name;  // attribute name              属性名
  size_t lsn;
} RelAttr;

typedef enum {
  EQUAL_TO,     //"="     0
  LESS_EQUAL,   //"<="    1
  NOT_EQUAL,    //"<>"    2
  LESS_THAN,    //"<"     3
  GREAT_EQUAL,  //">="    4
  GREAT_THAN,   //">"     5
  OP_IS,                     //针对NULL的比较
  OP_NO_IS,                  //针对NULL的比较
  OP_IN,
  OP_NO_IN,
  NO_OP
} CompOp;

//属性值类型
typedef enum { UNDEFINED, CHARS, INTS, DATES, TEXTS, FLOATS, NULLS} AttrType;

typedef enum { BYASC, BYDESC } OrderType;

typedef enum { POCOUNT, POAVG, POMAX, POMIN } PolyType;

//属性值
typedef struct _Value {
  AttrType type;  // type of value
  void *data;     // value
} Value;

typedef struct _Selects Selects;

// 不知道咋存储expression，还没定义出来......
typedef union {
  Value value;
  RelAttr attr;
  char* op;
} NodeType;

typedef struct {
  int type; //1是value, 2是attr, 3是符号
  NodeType v;
} ExpNode;

typedef struct {
  ExpNode expnodes[MAX_EXP_NODE_NUM]; // 算数表达式的后缀表达式
  int exp_num;
  size_t lsn;
  char* exp_name;
} Exp;


typedef struct _Condition {
  int left_is_attr;    // TRUE if left-hand side is an attribute
                       // 1时，操作符左边是属性名，0时，是属性值
  Value left_value;    // left-hand side value if left_is_attr = FALSE
  RelAttr left_attr;   // left-hand side attribute
  CompOp comp;         // comparison operator
  Exp *left_exp;

  int right_is_attr;   // TRUE if right-hand side is an attribute
                       // 1时，操作符右边是属性名，0时，是属性值
  RelAttr right_attr;  // right-hand side attribute if right_is_attr = TRUE 右边的属性
  Value right_value;   // right-hand side value if right_is_attr = FALSE

  int is_left_sub;
  Selects *left_sub_select;
  int is_right_sub;
  Selects *right_sub_select;

  Exp *right_exp;
  
} Condition;



typedef struct {
  char*     poly_name; // 标志聚合函数的名字
  PolyType  poly_type;
} PolyAttr;

// 聚合函数
typedef struct {
  RelAttr   attributes[10];    // attrs in Select clause
  size_t    attr_num;
  PolyAttr  poly_attr;              // 标志聚合函数的名字
  int       isAttr;                  // 值还是类型
  int       lsn;
} Poly;



// Order By
typedef struct {
  RelAttr   attributes[5];    //保存所有要排序的列
  size_t    attr_num;               //列的个数
  OrderType order_type[5];    //对应升序还是降序
} OrderBy;

// GropuBy
typedef struct {
  RelAttr   attributes[5];    //保存所有要排序的列
  size_t    attr_num;               //列的个数
  OrderType order_type[5];    //对应升序还是降序
} GroupBy;

// struct of select
struct _Selects{
  size_t    attr_num;               // Length of attrs in Select clause
  RelAttr   attributes[MAX_NUM];    // attrs in Select clause
  size_t    relation_num;           // Length of relations in Fro clause
  char *    relations[MAX_NUM];     // relations in From clause
  size_t    condition_num;          // Length of conditions in Where clause
  Condition conditions[MAX_NUM];    // conditions in Where clause
  size_t    poly_num;               // Length of attrs in poly
  Poly      poly_list[10];     //每扫描到一个poly 就记录下来是什么poly 以及涉及到的attri
  OrderBy   order_by;               // 需要排序的列集合
  GroupBy   group_by;
  size_t    lsn;                    //用来排序 group by poly 和 attr
  Exp       exp_list[8];
  size_t    exp_num; 
};

typedef struct {
   size_t value_num;       // Length of values
   Value values[MAX_NUM];  // values to insert 
} InsertsTuple;

// struct of insert
typedef struct {
  char *relation_name;    // Relation to insert into
  size_t tuple_num;       // Length of tuples
  InsertsTuple tuples[MAX_NUM];  // tuples to insert
} Inserts;

// struct of delete
typedef struct {
  char *relation_name;            // Relation to delete from
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Deletes;

// struct of update
typedef struct {
  char *relation_name;            // Relation to update
  char *attribute_name;           // Attribute to update
  Value value;                    // update value
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Updates;

typedef struct {
  char *name;     // Attribute name
  AttrType type;  // Type of attribute
  size_t length;  // Length of attribute
  int is_nullable;//是否可以为空
} AttrInfo;

// struct of craete_table
typedef struct {
  char *relation_name;           // Relation name
  size_t attribute_count;        // Length of attribute
  AttrInfo attributes[MAX_NUM];  // attributes
} CreateTable;

// struct of drop_table
typedef struct {
  char *relation_name;  // Relation name
} DropTable;

// struct of create_index
typedef struct {
  int   is_unique;                // 是否是唯一索引
  char *index_name;               // Index name
  char *relation_name;            // Relation name
  char *attribute_names[MAX_NUM];  // Attribute name Array
  size_t attribute_count;
} CreateIndex;

// struct of  drop_index
typedef struct {
  const char *index_name;  // Index name
} DropIndex;

typedef struct {
  const char *relation_name;
} DescTable;

typedef struct {
  const char *relation_name;
  const char *file_name;
} LoadData;

union Queries {
  Selects selection;
  Inserts insertion;
  Deletes deletion;
  Updates update;
  CreateTable create_table;
  DropTable drop_table;
  CreateIndex create_index;
  DropIndex drop_index;
  DescTable desc_table;
  LoadData load_data;
  char *errors;
};

// 修改yacc中相关数字编码为宏定义
enum SqlCommandFlag {
  SCF_ERROR = 0,
  SCF_SELECT,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_CREATE_UNIQUE_INDEX,
  SCF_DROP_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_DESC_TABLE,
  SCF_BEGIN,
  SCF_COMMIT,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT
};
// struct of flag and sql_struct
typedef struct Query {
  enum SqlCommandFlag flag;
  union Queries sstr;
} Query;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name);
void relation_attr_destroy(RelAttr *relation_attr);
void relation_attr_init_for_number(RelAttr *relation_attr, const char *relation_name, int attribute_name);
void relation_attr_init_for_float(RelAttr *relation_attr, const char *relation_name, float attribute_name);

void value_init_integer(Value *value, int v);
void value_init_float(Value *value, float v);
void value_init_string(Value *value, const char *v);
void value_init_date(Value *value, const char *v);
void value_init_null(Value *value, int v);
void value_destroy(Value *value);

void condition_init(Condition *condition, CompOp comp, int left_is_attr, RelAttr *left_attr, Value *left_value,
    int right_is_attr, RelAttr *right_attr, Value *right_value);
void condition_init_with_comp(Condition *condition, CompOp comp);
void condition_destroy(Condition *condition);
void exp_destroy(Exp *exp);
void condition_init_exp(Condition *condition, CompOp comp, int left_is_attr, RelAttr *left_attr, Value *left_value, Exp *left_exp,
    int right_is_attr, RelAttr *right_attr, Value *right_value, Exp *right_exp);

void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length, int is_null_able);
void attr_info_destroy(AttrInfo *attr_info);

void selects_init(Selects *selects, ...);
void selects_append_attribute(Selects *selects, RelAttr *rel_attr);
void selects_append_relation(Selects *selects, const char *relation_name);
void selects_append_conditions(Selects *selects, Condition conditions[], size_t start, size_t end);
void selects_swap_with_other(Selects *selects, Selects *other);
void selects_destroy(Selects *selects);
void push_to_exp(Exp *exp, ExpNode *expnode);
void expnode_init(ExpNode *expnode, int type, Value *value, RelAttr *attr, char *op);
void exp_swap_with_other(Exp *exp, Exp *other);
void selects_append_exp(Selects *selects, Exp *exp);
void set_exp_name(Exp *exp, const char *name);

void poly_init(Poly *poly_tmp, const char *poly_name);
void poly_destroy(Poly *poly_tmp);

void selects_append_poly(Selects *selects, Poly *rel_po);
void selects_append_poly_attribute(Selects *selects, RelAttr *rel_attr, int is_attr);


void selects_append_orderbyAttr(Selects *selects, RelAttr *attr, OrderType type);
void selects_append_groupbyAttr(Selects *selects, RelAttr *attr, OrderType type);

void inserts_init(Inserts *inserts, const char *relation_name);
void inserts_append_tuple(Inserts *inserts, Value values[], size_t value_num);
void inserts_destroy(Inserts *inserts);

void deletes_init_relation(Deletes *deletes, const char *relation_name);
void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num);
void deletes_destroy(Deletes *deletes);

void updates_init(Updates *updates, const char *relation_name, const char *attribute_name, Value *value,
    Condition conditions[], size_t condition_num);
void updates_destroy(Updates *updates);

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info);
void create_table_init_name(CreateTable *create_table, const char *relation_name);
void create_table_destroy(CreateTable *create_table);

void drop_table_init(DropTable *drop_table, const char *relation_name);
void drop_table_destroy(DropTable *drop_table);

void create_index_init(CreateIndex *create_index, const char *index_name, const char *relation_name, int is_unique);
void create_index_append_attribute(CreateIndex *create_index, const char *attr_name);

void create_index_destroy(CreateIndex *create_index);

void drop_index_init(DropIndex *drop_index, const char *index_name);
void drop_index_destroy(DropIndex *drop_index);

void desc_table_init(DescTable *desc_table, const char *relation_name);
void desc_table_destroy(DescTable *desc_table);

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name);
void load_data_destroy(LoadData *load_data);

void query_init(Query *query);
Query *query_create();  // create and init
void query_reset(Query *query);
void query_destroy(Query *query);  // reset and delete

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // __OBSERVER_SQL_PARSER_PARSE_DEFS_H__