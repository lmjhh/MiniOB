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

#include "sql/operator/hash_index_scan_operator.h"
#include "storage/index/index.h"
#include "storage/index/hash_index.h"
HashIndexScanOperator::HashIndexScanOperator(const Table *table, int key) : table_(table), key_(key)
{
}

RC HashIndexScanOperator::open()
{
  if (nullptr == table_) {
    return RC::INTERNAL;
  }

  record_handler_ = table_->record_handler();
  tuple_.set_schema(table_, table_->table_meta().field_metas());
  rids_ = HashIndex::instance().find(key_);

  return RC::SUCCESS;
}

RC HashIndexScanOperator::next()
{
  if (current_index_ >= rids_.size()) {
    return RC::RECORD_EOF;
  }
  RID rid = rids_[current_index_++];
  rid_ = rid;
  return record_handler_->get_record(&rid, &current_record_);
}

RC HashIndexScanOperator::close()
{
  return RC::SUCCESS;
}

Tuple * HashIndexScanOperator::current_tuple()
{
  tuple_.set_record(&current_record_);
  return &tuple_;
}

RID HashIndexScanOperator::current_rid()
{
  return rid_;
}
