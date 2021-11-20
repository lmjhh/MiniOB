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
// Created by Wangyunlai on 2021/5/7.
//

#include <stddef.h>
#include "condition_filter.h"
#include "record_manager.h"
#include "common/log/log.h"
#include "storage/common/table.h"

using namespace common;

ConditionFilter::~ConditionFilter()
{}

DefaultConditionFilter::DefaultConditionFilter()
{
  left_.is_attr = false;
  left_.attr_index = 0;
  left_.value = nullptr;

  right_.is_attr = false;
  left_.attr_index = 0;
  right_.value = nullptr;
}
DefaultConditionFilter::~DefaultConditionFilter()
{}

RC DefaultConditionFilter::init(const ConDesc &left, const ConDesc &right, AttrType left_attr_type, AttrType right_attr_type, CompOp comp_op)
{
  if (left_attr_type < CHARS || left_attr_type > NULLS) {
    LOG_ERROR("Invalid condition with unsupported attribute type: %d", left_attr_type);
    return RC::INVALID_ARGUMENT;
  }

  if (right_attr_type < CHARS || right_attr_type > NULLS) {
    LOG_ERROR("Invalid condition with unsupported attribute type: %d", right_attr_type);
    return RC::INVALID_ARGUMENT;
  }


  if (comp_op < EQUAL_TO || comp_op > OP_NO_IS) {
    LOG_ERROR("Invalid condition with unsupported compare operation: %d", comp_op);
    return RC::INVALID_ARGUMENT;
  }

  left_ = left;
  right_ = right;
  left_attr_type_ = left_attr_type;
  right_attr_type_ = right_attr_type;
  comp_op_ = comp_op;
  return RC::SUCCESS;
}

RC DefaultConditionFilter::init(Table &table, const Condition &condition)
{
  const TableMeta &table_meta = table.table_meta();
  ConDesc left;
  ConDesc right;

  left.attr_index = 0;
  right.attr_index = 0;

  AttrType type_left = UNDEFINED;
  AttrType type_right = UNDEFINED;

  if (1 == condition.left_is_attr) {
    left.is_attr = 1;
    const FieldMeta *field_left = table_meta.field(condition.left_attr.attribute_name);
    if (nullptr == field_left) {
      LOG_WARN("No such field in condition. %s.%s", table.name(), condition.left_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    left.attr_lengths[left.attr_index] = field_left->len();
    left.attr_offsets[left.attr_index] = field_left->offset();

    left.value = nullptr;

    type_left = field_left->type();
    left.attr_index++;

  } else if(0 == condition.left_is_attr) {
    left.is_attr = 0;
    left.value = condition.left_value.data;  // 校验type 或者转换类型
    type_left = condition.left_value.type;

    left.attr_index = 0;
  } else if(2 == condition.left_is_attr) { //是个表达式
    if(exp_is_only_value(condition.left_exp)){
      left.is_attr = 0;
      float result;
      bool is_compute = compute_exp(condition.left_exp, &result);
      LOG_ERROR("左边计算结果 %f",result);
      if(is_compute == false) return RC::GENERIC_ERROR;
      Value value;
      value_init_float(&value, result);
      left.value = value.data;
      type_left = value.type;
      left.attr_index = 0;
    }else {
      LOG_ERROR("输入带属性的表达式");
      left.is_attr = 2;
      for(int i = 0; i < condition.left_exp -> exp_num; i++){
        left.exp = condition.left_exp;
        if(condition.left_exp->expnodes[i].type == 2){
          const FieldMeta *field_left = table_meta.field(condition.left_exp->expnodes[i].v.attr.attribute_name);
          if (nullptr == field_left) {
            LOG_WARN("No such field in condition. %s.%s", table.name(), condition.left_exp->expnodes[i].v.attr.attribute_name);
            return RC::SCHEMA_FIELD_MISSING;
          }
          left.attr_lengths[left.attr_index] = field_left->len();
          left.attr_offsets[left.attr_index] = field_left->offset();
          left.attr_types[left.attr_index] = field_left->type();

          LOG_ERROR("左边表达式属性名 %s",condition.left_exp->expnodes[i].v.attr.attribute_name);
          LOG_ERROR("左边表达式属性类型 %d, 偏移量 %d", field_left->type(), field_left->offset());
          left.value = nullptr;

          type_left = field_left->type();
          left.attr_index++;
        }
      }
      if(left.exp->exp_num == 1){
        left.is_attr = 1;
      }else{
        type_left = FLOATS;
      }
    }
    LOG_ERROR("左边表达式Condition构建成功");
  }

  if (1 == condition.right_is_attr) {
    right.is_attr = 1;
    const FieldMeta *field_right = table_meta.field(condition.right_attr.attribute_name);
    if (nullptr == field_right) {
      LOG_WARN("No such field in condition. %s.%s", table.name(), condition.right_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    right.attr_lengths[right.attr_index] = field_right->len();
    right.attr_offsets[right.attr_index] = field_right->offset();

    type_right = field_right->type();

    right.value = nullptr;
    right.attr_index++;
  } else if(0 == condition.right_is_attr){
    right.is_attr = 0;
    right.value = condition.right_value.data;
    type_right = condition.right_value.type;

    right.attr_index=0;
  } else if(2 == condition.right_is_attr) { //是个表达式
    if(exp_is_only_value(condition.right_exp)){
      right.is_attr = 0;
      float result;
      bool is_compute = compute_exp(condition.right_exp, &result);
      LOG_ERROR("右边计算结果 %f",result);
      if(is_compute == false) return RC::GENERIC_ERROR;
      Value value;
      value_init_float(&value, result);
      right.value = value.data;
      type_right = value.type;
      right.attr_index = 0;
    }else {
      for(int i = 0; i < condition.right_exp -> exp_num; i++){
        right.is_attr = 2;
        right.exp = condition.right_exp;
        if(condition.right_exp->expnodes[i].type == 2){
          const FieldMeta *field_right = table_meta.field(condition.right_exp->expnodes[i].v.attr.attribute_name);
          if (nullptr == field_right) {
            LOG_WARN("No such field in condition. %s.%s", table.name(), condition.right_exp->expnodes[i].v.attr.attribute_name);
            return RC::SCHEMA_FIELD_MISSING;
          }
          right.attr_lengths[right.attr_index] = field_right->len();
          right.attr_offsets[right.attr_index] = field_right->offset();
          right.attr_types[right.attr_index] = field_right->type();

          right.value = nullptr;

          type_right = field_right->type();
          right.attr_index++;
        }
      }
      if(right.exp->exp_num == 1){
        right.is_attr = 1;
      }else{
        type_right = FLOATS;
      }
    }
  }

  if(type_left != type_right 
      && type_left != NULLS && type_right != NULLS
      && (type_left == FLOATS && type_right == INTS) 
      && (type_left == INTS && type_right == FLOATS) ) {
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }

  return init(left, right, type_left, type_right,condition.comp);
}

bool DefaultConditionFilter::filter(const Record &rec) const
{
  char *left_value = nullptr;
  char *right_value = nullptr;

  if (left_.is_attr == 1) {  // value
    left_value = (char *)(rec.data + left_.attr_offsets[left_.attr_index - 1]);
  } else if(left_.is_attr == 0){
    left_value = (char *)left_.value;
  } else if (left_.is_attr == 2){
    LOG_ERROR("开始生成左边表达式Filter");
    Exp tmpExp = *left_.exp;
    int current_index = 0;
    for(int i = 0; i < tmpExp.exp_num; i++){
      if(tmpExp.expnodes[i].type == 2){
        LOG_ERROR("当前属性类型 %d", left_.attr_types[current_index]);
        if(left_.attr_types[current_index] == FLOATS){
          float record_value = *(float *)(rec.data + left_.attr_offsets[current_index++]);
          LOG_ERROR("从record中读到value = %f",record_value);
          Value value;
          value_init_float(&value, record_value);
          tmpExp.expnodes[i].type = 1;
          tmpExp.expnodes[i].v.value = value;    
        }  
        if(left_.attr_types[current_index] == INTS){
          int record_value = *(int *)(rec.data + left_.attr_offsets[current_index++]);
          LOG_ERROR("从record中读到value = %d",record_value);
          Value value;
          value_init_integer(&value, record_value);
          tmpExp.expnodes[i].type = 1;
          tmpExp.expnodes[i].v.value = value;   
        }     
      }
    }
    float result;
    bool is_compute = compute_exp(&tmpExp, &result);
    LOG_ERROR("左边计算结果 %f",result);
    if(is_compute == false) return false;
    left_value = (char *)&result;
  }
  

  if (right_.is_attr == 1) {
    right_value = (char *)(rec.data + right_.attr_offsets[right_.attr_index - 1]);
  } else if(right_.is_attr == 0){
    right_value = (char *)right_.value;
  } else if (right_.is_attr == 2){
    LOG_ERROR("开始生成右边表达式Filter");
    Exp tmpExp = *right_.exp;
    for(int i = 0; i < tmpExp.exp_num; i++){
      int current_index = 0;
      if(tmpExp.expnodes[i].type == 2){
        LOG_ERROR("当前属性类型 %d", right_.attr_types[current_index]);
        if(right_.attr_types[current_index] == FLOATS){
          float record_value = *(float *)(rec.data + right_.attr_offsets[current_index++]);
          LOG_ERROR("从record中读到value = %f",record_value);
          Value value;
          value_init_float(&value, record_value);
          tmpExp.expnodes[i].type = 1;
          tmpExp.expnodes[i].v.value = value;    
        }  
        if(right_.attr_types[current_index] == INTS){
          int record_value = *(int *)(rec.data + right_.attr_offsets[current_index++]);
          LOG_ERROR("从record中读到value = %d",record_value);
          Value value;
          value_init_integer(&value, record_value);
          tmpExp.expnodes[i].type = 1;
          tmpExp.expnodes[i].v.value = value;   
        }     
      }
    }
    float result;
    bool is_compute = compute_exp(&tmpExp, &result);
    LOG_ERROR("右边计算结果 %f",result);
    if(is_compute == false) return false;
    right_value = (char *)&result;
  }


  if(left_attr_type_ != right_attr_type_ && (left_attr_type_ == NULLS || right_attr_type_ == NULLS)){
    //如果左边或右边是值，和NULL比较 直接返回 false
    if(left_attr_type_ != NULLS && !left_.is_attr) {
      if(comp_op_ == OP_NO_IS) return true; 
      return false;
    }
    if(right_attr_type_ != NULLS && !right_.is_attr) {
      if(comp_op_ == OP_NO_IS) return true; 
      return false;
    }
    //如果左边或右边是属性，和NULL比较需判断
    if(left_attr_type_ != NULLS){
      switch (left_attr_type_)
      {
      case CHARS:{
        LOG_ERROR("左边是属性：%s 右边是NULL", left_value);
        int result = strcmp(left_value, "NUL");
        if(result == 0 && comp_op_ == OP_IS) return true;
        else if(result != 0 && comp_op_ == OP_NO_IS) return true;
        else return false;
      }
      case TEXTS:{
        LOG_ERROR("左边是属性：%s 右边是NULL", left_value);
        int result = strcmp(left_value, "NUL");
        if(result == 0 && comp_op_ == OP_IS) return true;
        else if(result != 0 && comp_op_ == OP_NO_IS) return true;
        else return false;
      }
      case DATES:{
        LOG_ERROR("左边是属性：%d 右边是NULL", *(int *)left_value);
        int left = *(int *)left_value;
        if(left == 0 && comp_op_ == OP_IS) return true;
        else if(left != 0 && comp_op_ == OP_NO_IS) return true;
        else return false;
      }
      case INTS:{
        LOG_ERROR("左边是属性：%d 右边是NULL", *(int *)left_value);
        int left = *(int *)left_value;
        if(left == OB_INT_MIN && comp_op_ == OP_IS) return true;
        else if(left != OB_INT_MIN && comp_op_ == OP_NO_IS) return true;
        else return false;
      }
      case FLOATS:{
        LOG_ERROR("左边是属性：%f 右边是NULL", *(float *)left_value);
        float left = *(float *)left_value;
        if(left - OB_FLT_MIN < 0.00001 && comp_op_ == OP_IS) return true;
        else if(left - OB_FLT_MIN > 0.00001 && comp_op_ == OP_NO_IS) return true;
        else return false;
      }   
      default:
        break;
      }
    }
    if(right_attr_type_ != NULLS){
      switch (right_attr_type_)
      {
      case CHARS:{
        int result = strcmp(right_value, "NUL");
        if(result == 0 && comp_op_ == OP_IS) return true;
        else if(result != 0 && comp_op_ == OP_NO_IS) return true;
        else return false;
      }
      case TEXTS:{
        int result = strcmp(right_value, "NUL");
        if(result == 0 && comp_op_ == OP_IS) return true;
        else if(result != 0 && comp_op_ == OP_NO_IS) return true;
        else return false;
      }
      case DATES:{
        int right = *(int *)right_value;
        if(right == 0 && comp_op_ == OP_IS) return true;
        else if(right != 0 && comp_op_ == OP_NO_IS) return true;
        else return false;
      }
      case INTS:{
        int right = *(int *)right_value;
        if(right == OB_INT_MIN && comp_op_ == OP_IS) return true;
        else if(right != OB_INT_MIN && comp_op_ == OP_NO_IS) return true;
        else return false;
      }
      case FLOATS:{
        float right = *(float *)right_value;
        if(right - OB_FLT_MIN < 0.00001 && comp_op_ == OP_IS) return true;
        else if(right - OB_FLT_MIN > 0.00001 && comp_op_ == OP_NO_IS) return true;
        else return false;
      }   
      default:
        break;
      }      
    }
  }

  
  int cmp_result = 0;
  switch (left_attr_type_) {
    case CHARS: {  // 字符串都是定长的，直接比较
      // 按照C字符串风格来定
      cmp_result = strcmp(left_value, right_value);
    } break;
    case TEXTS: {  // 字符串都是定长的，直接比较
      // 按照C字符串风格来定
      cmp_result = strcmp(left_value, right_value);
    } break;
    case DATES: {
      // 没有考虑大小端问题
      // 对int和float，要考虑字节对齐问题,有些平台下直接转换可能会跪
      int left = *(int *)left_value;
      int right = *(int *)right_value;
      cmp_result = left - right;
    } break;
    case INTS: {
      // 没有考虑大小端问题
      // 对int和float，要考虑字节对齐问题,有些平台下直接转换可能会跪
      if(right_attr_type_ == INTS){
        int left = *(int *)left_value;
        int right = *(int *)right_value;
        cmp_result = left - right;
      }
      if(right_attr_type_ == FLOATS){
        float left = *(int *)left_value * 1.0;
        float right = *(float *)right_value;  
        if(left - right < 0.00001 && left - right >= 0) cmp_result = 0;
        else if(left - right > 0.00001) cmp_result = 1;
        else if(left - right < 0.00001) cmp_result = -1;     
      }
    } break;
    case FLOATS: {
      if(right_attr_type_ == FLOATS){
        float left = *(float *)left_value;
        float right = *(float *)right_value;
        if(left - right < 0.00001 && left - right >= 0) cmp_result = 0;
        else if(left - right > 0.00001) cmp_result = 1;
        else if(left - right < 0.00001) cmp_result = -1;
      }
      if(right_attr_type_ == INTS){
        float left = *(float *)left_value;
        float right = *(int *)right_value * 1.0;
        if(left - right < 0.00001 && left - right >= 0) cmp_result = 0;
        else if(left - right > 0.00001) cmp_result = 1;
        else if(left - right < 0.00001) cmp_result = -1;       
      }
    } break;
    case NULLS: {
      int left = *(int *)left_value;
      int right = *(int *)right_value;
      cmp_result = left - right;
      if(cmp_result == 0 && comp_op_ == OP_IS) return true;
      else if(cmp_result != 0 && comp_op_ == OP_NO_IS) return true;
      else return false;
    } break;
    default: {
    }
  }

  switch (comp_op_) {
    case EQUAL_TO:
      return 0 == cmp_result;
    case LESS_EQUAL:
      return cmp_result <= 0;
    case NOT_EQUAL:
      return cmp_result != 0;
    case LESS_THAN:
      return cmp_result < 0;
    case GREAT_EQUAL:
      return cmp_result >= 0;
    case GREAT_THAN:
      return cmp_result > 0;
    case OP_NO_IS:
      return cmp_result != 0;
    case OP_IS:
      return 0 == cmp_result;

    default:
      break;
  }

  LOG_PANIC("Never should print this.");
  return cmp_result;  // should not go here
}

CompositeConditionFilter::~CompositeConditionFilter()
{
  if (memory_owner_) {
    delete[] filters_;
    filters_ = nullptr;
  }
}

RC CompositeConditionFilter::init(const ConditionFilter *filters[], int filter_num, bool own_memory)
{
  filters_ = filters;
  filter_num_ = filter_num;
  memory_owner_ = own_memory;
  return RC::SUCCESS;
}
RC CompositeConditionFilter::init(const ConditionFilter *filters[], int filter_num)
{
  return init(filters, filter_num, false);
}

RC CompositeConditionFilter::init(Table &table, const Condition *conditions, int condition_num)
{
  if (condition_num == 0) {
    return RC::SUCCESS;
  }
  if (conditions == nullptr) {
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;
  ConditionFilter **condition_filters = new ConditionFilter *[condition_num];
  for (int i = 0; i < condition_num; i++) {
    DefaultConditionFilter *default_condition_filter = new DefaultConditionFilter();
    rc = default_condition_filter->init(table, conditions[i]);
    if (rc != RC::SUCCESS) {
      delete default_condition_filter;
      for (int j = i - 1; j >= 0; j--) {
        delete condition_filters[j];
        condition_filters[j] = nullptr;
      }
      delete[] condition_filters;
      condition_filters = nullptr;
      return rc;
    }
    condition_filters[i] = default_condition_filter;
  }
  return init((const ConditionFilter **)condition_filters, condition_num, true);
}

bool CompositeConditionFilter::filter(const Record &rec) const
{
  for (int i = 0; i < filter_num_; i++) {
    if (!filters_[i]->filter(rec)) {
      return false;
    }
  }
  return true;
}



/* 表达式相关函数 */
bool exp_is_only_value(Exp * exp){
  for(int i=0; i< exp->exp_num; i++){
    if(exp->expnodes[i].type == 2){
      return false;
    }
  }
  return true;
}

bool operate(float a, char theta, float b, float &r) { //计算二元表达式的值
	if (theta == '+')
		r = a + b;
	else if (theta == '-')
		r = a - b;
	else if (theta == '*')
		r = a * b;
	else {
		if ((b - 0.0 < 1e-8 && b > 0.0) || (0.0 - b < 1e-8 && b < 0))  //如果除数为0，返回错误信息
			return false;
		else {
			r = a / b;
    }
	}
	return true;
}


// 传入表达式，返回结果到result
bool compute_exp(Exp* exp, float *result){
  // 此表达式只会有两种节点，value&&op
  std::cerr << "开始表达式计算 一共 " << exp->exp_num << "个表达式" << std::endl;
  float a, b, r;
  std::stack<float> OPND;
  for(int i=0; i< exp->exp_num; i++){
    if (exp->expnodes[i].type == 1){
      // 压入数字栈
      float v;
      if(exp->expnodes[i].v.value.type == FLOATS){
        v = *(float *)exp->expnodes[i].v.value.data;
        std::cerr << v << std::endl;
      }else if(exp->expnodes[i].v.value.type == INTS){
        v = *(int *)exp->expnodes[i].v.value.data * 1.0;
        std::cerr << v << std::endl;
      }
      OPND.push(v);
    }
    if (exp->expnodes[i].type == 3){
      if (strcmp(exp->expnodes[i].v.op, "u")==0){
        // 单目运算符，只取出一个操作数
        b = OPND.top();
        OPND.pop();
        if(operate(0.0, '-', b, r)){
          OPND.push(r);
        }
        else{
          //计算错误，按照null处理
          return false;
        }
        continue;
      }
      //是运算符，则取两个数字出来计算
      b = OPND.top();
      OPND.pop();
      a = OPND.top();
      OPND.pop();
      if(operate(a, *exp->expnodes[i].v.op, b, r)){
        OPND.push(r);
      }
      else{
        //计算错误，按照null处理
        return false;
      }
    }
  }
  *result = OPND.top();
  return true;
}