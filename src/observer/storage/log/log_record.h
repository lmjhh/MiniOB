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
// Created by lianyu on 2022/10/12.
//

/**
 * 对每一次的写操作，都需要记录日志。每一条日志需要包含一个 Head (5 field, 20 bytes)
 *-------------------------------------------------------------
 * | size | | LSN | prevLSN | trxID | logType |
 *-------------------------------------------------------------
 * insert 操作的日志
 *-------------------------------------------------------------
 * | HEADER | record_rid | record_size | record_data(char[] array) |
 *-------------------------------------------------------------
 * delete 操作的日志(包含 markdelete, rollbackdelete, applydelete)
 *-------------------------------------------------------------
 * | HEADER | record_rid | record_size | record_data(char[] array) |
 *-------------------------------------------------------------
 * update 操作的日志
 *------------------------------------------------------------------------------
 * | HEADER | record_rid | record_size | old_record_data | record_size | new_record_data |
 *------------------------------------------------------------------------------
 * new Page 操作的日志
 *-------------------------------------------------------------
 * | HEADER | prev_page_id |
 *-------------------------------------------------------------
 */

#ifndef MINIDB_LOG_RECORD_H
#define MINIDB_LOG_RECORD_H

#include "storage/common/record.h"

struct LogRecordHeader {
  int32_t size_;
  int32_t lsn_;
  int32_t prev_lsn_;
  int32_t trx_id_;
  int32_t type_;

  bool operator==(const LogRecordHeader &other) const
  {
    return lsn_ == other.lsn_ && prev_lsn_ == other.prev_lsn_ && trx_id_ == other.trx_id_ && type_ == other.type_ && size_ == other.size_;
  }
};

struct LogInsertRecord {
  RID rid_;
  int32_t record_size_;
  char *record_data_;

  bool operator==(const LogInsertRecord &other) const
  {
    return (rid_ == other.rid_) &&
           (record_size_ == other.record_size_) && (memcmp(record_data_, other.record_data_, record_size_) == 0);
  }
};

struct LogDeleteRecord {
  RID rid_;
  int32_t record_size_;
  char *record_data_;

  bool operator==(const LogDeleteRecord &other) const
  {
    return (rid_ == other.rid_) &&
           (record_size_ == other.record_size_) && (memcmp(record_data_, other.record_data_, record_size_) == 0);
  }
};

struct LogUpdateRecord {
  RID rid_;
  int32_t record_size_;
  char *old_record_data_;
  char *new_record_data_;
  bool operator==(const LogUpdateRecord &other) const
  {
    return (rid_ == other.rid_) &&
           (record_size_ == other.record_size_) &&
           (memcmp(old_record_data_, other.old_record_data_, record_size_) == 0) &&
           (memcmp(new_record_data_, other.new_record_data_, record_size_) == 0);
  }
};


union LogRecords {
  LogInsertRecord ins;
  LogDeleteRecord del;
  LogUpdateRecord upd;
  char *errors;
};

class LogRecord {

public:
  enum Type {
    INVALID = 0,
    INSERT,
    MARKDELETE,
    APPLYDELETE,
    ROLLBACKDELETE,
    UPDATE,
    BEGIN,
    COMMIT,
    ABORT,
    NEWPAGE,
  };

  LogRecord(Type type, int32_t lsn, int32_t  prev_lsn, int32_t trx_id, int data_len = 0, Record *rec = nullptr);
  ~LogRecord();

  inline LogRecordHeader &get_hdr() { return  hdr_; }

  inline RID &get_delete_rid() { return log_record_.del.rid_; }

//  inline Record &get_inserte_record() { return log_record_.ins.record_data_; }

  inline RID &get_insert_rid() { return log_record_.ins.rid_; }

  inline PageNum get_new_page_record() { return prev_page_id_; }

  inline int32_t get_size() { return hdr_.size_; }

  inline LSN get_lsn() { return hdr_.lsn_; }

  inline void set_lsn(LSN lsn) { hdr_.lsn_ = lsn; }

  inline int32_t get_trx_id() { return hdr_.trx_id_; }

  inline LSN get_prev_lsn() { return hdr_.prev_lsn_; }

  inline int32_t &get_log_record_type() { return hdr_.type_; }

  int serialize_to(char *address);

  const static int HEADER_SIZE = 20;

private:

  LogRecordHeader hdr_;
  LogRecords log_record_;

  PageNum prev_page_id_ = 0;
};

#endif  // MINIDB_LOG_RECORD_H
