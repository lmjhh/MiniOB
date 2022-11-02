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
// Created by Wangyunlai on 2021/5/24.
//

#ifndef __OBSERVER_STORAGE_TRX_TRX_H_
#define __OBSERVER_STORAGE_TRX_TRX_H_

#include <stddef.h>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <mutex>
#include "sql/parser/parse.h"
#include "storage/common/record_manager.h"
#include "rc.h"

class Table;
class LockManager;

class Operation {
public:
  enum class Type : int {
    READ,
    INSERT,
    UPDATE,
    DELETE,
    UNDEFINED,
  };

public:
  Operation(Type type, const RID &rid) : type_(type), page_num_(rid.page_num), slot_num_(rid.slot_num)
  {}

  Type type() const
  {
    return type_;
  }
  PageNum page_num() const
  {
    return page_num_;
  }
  SlotNum slot_num() const
  {
    return slot_num_;
  }

private:
  Type type_;
  PageNum page_num_;
  SlotNum slot_num_;
};
class OperationHasher {
public:
  size_t operator()(const Operation &op) const
  {
    return (((size_t)op.page_num()) << 32) | (op.slot_num());
  }
};

class OperationEqualer {
public:
  bool operator()(const Operation &op1, const Operation &op2) const
  {
    return op1.page_num() == op2.page_num() && op1.slot_num() == op2.slot_num();
  }
};

/**
 * 这里是一个简单的事务实现，可以支持提交/回滚。但是没有对并发访问做控制
 * 可以在这个基础上做备份恢复，当然也可以重写
 */
class Trx {
public:
  enum class State { GROWING, SHRINKING, COMMITTED, ABORTED };

  static int32_t next_trx_id();
  static const char *trx_field_name();
  static AttrType trx_field_type();
  static int trx_field_len();

public:
  Trx();
  ~Trx();

public:
  RC insert_record(Table *table, Record *record);
  RC delete_record(Table *table, Record *record);

  RC begin();
  RC commit();
  RC rollback();

  RC commit_insert(Table *table, Record &record);
  RC rollback_delete(Table *table, Record &record);

  bool is_visible(Table *table, const Record *record);

  void init_trx_info(Table *table, Record &record);

  void set_is_auto_commit(bool is_auto_commit) { is_auto_commit_ = is_auto_commit; }
  bool is_auto_commit() { return  is_auto_commit_; }

  /**
   * 获取事务 tid
   */
  inline int32_t get_trx_id() const { return trx_id_; }
  /**
   * 事务状态相关
   */
  inline State get_state() { return state_; }
  inline void set_state(State state) { state_ = state; }

  /**
   * 仅用于B+树，保存当前事务访问索引持有的页
   * @param frame
   */
  inline void add_into_page_set(Frame *frame) {
    page_set_->push_back(frame);
  }
  inline std::shared_ptr<std::deque<Frame *>> get_page_set() { return page_set_; }

  inline std::shared_ptr<std::unordered_set<RID>> get_shared_lockset() {
    return shared_lock_set_;
  }

  inline std::shared_ptr<std::unordered_set<RID>> get_exclusive_lockset() {
    return exclusive_lock_set_;
  }

  inline LSN get_prev_LSN() { return prev_lsn_; }

  inline void set_prev_LSN(LSN prev_lsn) { prev_lsn_ = prev_lsn; }

private:
  void set_record_trx_id(Table *table, Record &record, int32_t trx_id, bool deleted) const;
  static void get_record_trx_id(Table *table, const Record &record, int32_t &trx_id, bool &deleted);

private:
  using OperationSet = std::unordered_set<Operation, OperationHasher, OperationEqualer>;

  Operation *find_operation(Table *table, const RID &rid);
  void insert_operation(Table *table, Operation::Type type, const RID &rid);
  void delete_operation(Table *table, const RID &rid);

private:
  void start_if_not_started();

private:

  bool is_auto_commit_ = true;
  /**
   * 事务状态：初始化为GROWING状态
   */
  State state_ = State::GROWING;
  int32_t trx_id_ = 0;
  LSN prev_lsn_ = 0;
  std::unordered_map<Table *, OperationSet> operations_;

  /**
   * 此事务获得共享锁的rid集合
   */
  std::shared_ptr<std::unordered_set<RID>> shared_lock_set_;
  /**
   * 此事务获得排他锁的rid集合
   */
  std::shared_ptr<std::unordered_set<RID>> exclusive_lock_set_;

  // 用于B+索引的并发安全
  std::shared_ptr<std::deque<Frame *>> page_set_;
};

#endif  // __OBSERVER_STORAGE_TRX_TRX_H_
