//
// Created by lianyu on 2022/11/8.
//

#ifndef MINIDB_HASH_DATE_INDEX_SCAN_OPERATOR_H
#define MINIDB_HASH_DATE_INDEX_SCAN_OPERATOR_H
#include "operator.h"

class HashDateIndexScanOperator : public Operator
{
public:
  HashDateIndexScanOperator(const Table *table, uint16_t key);

  virtual ~HashDateIndexScanOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;

  Tuple * current_tuple() override;
  RID current_rid() override;
private:
  const Table *table_ = nullptr;
  RecordFileHandler *record_handler_ = nullptr;
  Record current_record_;
  RowTuple tuple_;
  uint16_t key_;
  RID rid_;
  std::vector<RID> rids_;
  int current_index_ = 0;
};

#endif //MINIDB_HASH_DATE_INDEX_SCAN_OPERATOR_H
