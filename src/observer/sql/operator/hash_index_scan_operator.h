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
// Created by Wangyunlai on 2022/07/08.
//

#pragma once

#include "sql/operator/operator.h"
#include "sql/expr/tuple.h"

class HashIndexScanOperator : public Operator
{
public:
  HashIndexScanOperator(const Table *table, int key);

  virtual ~HashIndexScanOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;

  Tuple * current_tuple() override;
private:
  const Table *table_ = nullptr;
  RecordFileHandler *record_handler_ = nullptr;
  Record current_record_;
  RowTuple tuple_;
  int key_;
  std::vector<RID> rids_;
  int current_index_ = 0;
};
