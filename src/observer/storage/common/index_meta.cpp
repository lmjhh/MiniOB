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
// Created by wangyunlai.wyl on 2021/5/18.
//

#include "storage/common/index_meta.h"
#include "storage/common/field_meta.h"
#include "storage/common/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "rc.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_COUNT("count");
const static Json::StaticString FIELD_UNIQUE("unique");
const static Json::StaticString FIELD_FIELD_NAMES("field_names");

RC IndexMeta::init(const char *name, const FieldMeta *fields[], int fields_count, int is_unique) {
  if (nullptr == name || common::is_blank(name)) {
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  fields_ = (const char **) malloc(MAX_NUM * sizeof(char *));
  for(int i = 0; i < fields_count; i++){
    //倒序的要转成正序
    fields_[fields_count - i - 1] = fields[i]->name();
  }
  is_unique_ = is_unique;
  fields_count_ = fields_count;

  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const {
  json_value[FIELD_NAME] = name_;
  json_value[FIELD_COUNT] = fields_count_;
  json_value[FIELD_UNIQUE] = is_unique_;
  for(int i = 0; i < fields_count_; i++)
    json_value[FIELD_FIELD_NAMES].append(fields_[i]);
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index) {
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &is_unique = json_value[FIELD_UNIQUE];
  const Json::Value &fields_count = json_value[FIELD_COUNT];
  const Json::Value &field_values = json_value[FIELD_FIELD_NAMES];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  if (!fields_count.isInt()) {
    LOG_ERROR("Index name is not a int. json value=%s", fields_count.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  if (!is_unique.isInt()) {
    LOG_ERROR("Index name is not a int. json value=%s", is_unique.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  if (!field_values.isArray()) {
    LOG_ERROR("Field name of index [%s] is not a array. json value=%s",
              name_value.asCString(), field_values.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  const FieldMeta *fields[MAX_NUM];
  for(int i = 0; i < fields_count.asInt(); i++){
    fields[i] = table.field(field_values[i].asCString());
    // LOG_ERROR("从磁盘中读取索引列 %s",field[i]->name());
    if (nullptr == fields[i]) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_values[i].asCString());
      return RC::SCHEMA_FIELD_MISSING;
    }
  }

  return index.init(name_value.asCString(), fields,fields_count.asInt(), is_unique.asInt());
}

const char *IndexMeta::name() const {
  return name_.c_str();
}

const char **IndexMeta::fields() const {
  return fields_;
}

const int IndexMeta::fields_count() const{
  return fields_count_;
}

const int IndexMeta::is_unique() const {
  return is_unique_;
}

void IndexMeta::desc(std::ostream &os) const {
  os << "index name=" << name_;
  for(int i = 0; i < fields_count_; i++)
    os  << ", field=" << fields_[i];
}