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
// Created by lianyu on 2022/9/14.
//

#ifndef __OBSERVER_STORAGE_TRX_LOCK_MANAGER_H_
#define __OBSERVER_STORAGE_TRX_LOCK_MANAGER_H_

#include <mutex>
#include <condition_variable>
#include <list>

#include "storage/trx/trx.h"
#include "storage/common/record_manager.h"

class LockManager {
public:
  enum class LockMode : int {
    SHARED = 0,
    EXCLUSIVE,
    UPGRADING
  };
  struct TrxItem {
    TrxItem(uint32_t tid, LockMode mode, bool granted) :
          trx_id_(tid), mode_(mode), granted_(granted) {}

    void wait() {
      std::unique_lock<std::mutex> ul(mutex_);
      cv_.wait(ul, [this] { return this->granted_; });
    }

    void grant() {
      std::lock_guard<std::mutex> lg(mutex_);
      granted_ = true;
      cv_.notify_one();
    }

    std::mutex mutex_;
    std::condition_variable cv_;
    uint32_t trx_id_;
    LockMode mode_;
    bool granted_;
  };

  struct TrxList {
    bool check_can_grant(LockMode mode) { //protect by mutex outside
      if (locks_.empty()) return true;
      const auto &last = locks_.back();
      if (mode == LockMode::SHARED) {
        return last.granted_ && last.mode_ == LockMode::SHARED;
      }
      return false;
    }

    void insert(Trx* trx, const RID &rid, LockMode mode, bool granted, std::unique_lock<std::mutex> *lock) {
      bool upgrading_mode = (mode == LockMode::UPGRADING);
      if (upgrading_mode && granted) mode = LockMode::EXCLUSIVE;
      locks_.emplace_back(trx->get_trx_id(), mode, granted);
      auto &last = locks_.back();
      if (!granted) {
        has_upgrading_ |= upgrading_mode;
        lock->unlock();
        last.wait();
      }
      if (mode == LockMode::SHARED) {
        trx->get_shared_lockset()->insert(rid);
      } else {
        trx->get_exclusive_lockset()->insert(rid);
      }
    }

    std::mutex mutex_;
    std::list<TrxItem> locks_;
    bool has_upgrading_;
  };

public:
  LockManager(bool strict_2PL) : strict_2PL_(strict_2PL){};

  /**
   * lock:
   * mode: 共享锁、排他锁、升级锁
   */
  RC lock_shared(Trx *trx, const RID &rid);
  RC lock_exclusive(Trx *trx, const RID &rid);
  RC lock_upgrade(Trx *trx, const RID &rid);
  /**
   * unlock:
   * 释放事务持有的锁
  */
  RC unlock(Trx *trx, const RID &rid);

  static void set_instance(LockManager *lockManager);
  static LockManager &instance();
private:

  bool strict_2PL_;
  std::mutex mutex_;
  std::unordered_map<RID,TrxList> lock_table_;

  RC lock(Trx *trx, const RID &rid, LockMode mode);
};


#endif  // __OBSERVER_STORAGE_TRX_LOCK_MANAGER_H_
