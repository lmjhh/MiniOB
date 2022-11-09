//
// Created by lianyu on 2022/11/8.
//

#include "hash_date_index_scan_operator.h"

#include "storage/index/index.h"
#include "storage/index/hash_index.h"

HashDateIndexScanOperator::HashDateIndexScanOperator(const Table *table, uint16_t key) : table_(table), key_(key)
{
}

RC HashDateIndexScanOperator::open()
{
  if (nullptr == table_) {
    return RC::INTERNAL;
  }

  record_handler_ = table_->record_handler();
  tuple_.set_schema(table_, table_->table_meta().field_metas());
  rids_ = HashDateIndex::find(key_);
  return RC::SUCCESS;
}

RC HashDateIndexScanOperator::next()
{
  if (current_index_ >= rids_.size()) {
    return RC::RECORD_EOF;
  }
  RID rid = rids_[current_index_++];
  rid_ = rid;
  return RC::SUCCESS;
}

RC HashDateIndexScanOperator::close()
{
  return RC::SUCCESS;
}

Tuple * HashDateIndexScanOperator::current_tuple()
{
  tuple_.set_record(&current_record_);
  return &tuple_;
}

RID HashDateIndexScanOperator::current_rid()
{
  return rid_;
}