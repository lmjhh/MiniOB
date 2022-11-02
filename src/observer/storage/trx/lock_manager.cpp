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

#include "lock_manager.h"

RC LockManager::lock_shared(Trx *trx, const RID &rid) {
  return lock(trx, rid, LockManager::LockMode::SHARED);
}
RC LockManager::lock_exclusive(Trx *trx, const RID &rid) {
  return lock(trx, rid, LockManager::LockMode::EXCLUSIVE);
}
RC LockManager::lock_upgrade(Trx *trx, const RID &rid) {
  return lock(trx, rid, LockManager::LockMode::UPGRADING);
}

RC LockManager::lock(Trx *trx, const RID &rid, LockMode mode) {
  // step 1
  if (trx->get_state() != Trx::State::GROWING) {
    trx->set_state(Trx::State::ABORTED);
    return RC::GENERIC_ERROR;
  }
  std::unique_lock<std::mutex> table_latch(mutex_);
  TrxList &trx_list = lock_table_[rid];
  std::unique_lock<std::mutex> trx_list_latch(trx_list.mutex_);
  table_latch.unlock();

  if (mode == LockMode::UPGRADING) {//step 2
    if (trx_list.has_upgrading_) {
      trx->set_state(Trx::State::ABORTED);
      return RC::GENERIC_ERROR;
    }
    auto it = find_if(trx_list.locks_.begin(), trx_list.locks_.end(),
        [trx](const TrxItem &item) {return item.trx_id_ == trx->get_trx_id();});
    if (it == trx_list.locks_.end() || it->mode_ != LockMode::SHARED || !it->granted_) {
      trx->set_state(Trx::State::ABORTED);
      return RC::GENERIC_ERROR;
    }
    trx_list.locks_.erase(it);
    assert(trx->get_shared_lockset()->erase(rid) == 1);
  }
  //step 3
  bool can_grant = trx_list.check_can_grant(mode);
  //死锁检测
  if (!can_grant && trx_list.locks_.back().trx_id_ < trx->get_trx_id()) {
    trx->set_state(Trx::State::ABORTED);
    return RC::GENERIC_ERROR;
  }
  trx_list.insert(trx,rid,mode,can_grant,&trx_list_latch);
  return RC::SUCCESS;
}


RC LockManager::unlock(Trx *trx, const RID &rid) {
  if (strict_2PL_) {//step1
    if (trx->get_state() != Trx::State::COMMITTED && trx->get_state() != Trx::State::ABORTED) {
      trx->set_state(Trx::State::ABORTED);
      return RC::GENERIC_ERROR;
    }
  } else if (trx->get_state() == Trx::State::GROWING) {
    trx->set_state(Trx::State::SHRINKING);
  }
  std::unique_lock<std::mutex> table_latch(mutex_);
  TrxList &trx_list = lock_table_[rid];
  std::unique_lock<std::mutex> trx_list_latch(trx_list.mutex_);
  //step 2 remove trx_list and trx->lockset
  auto it = find_if(trx_list.locks_.begin(), trx_list.locks_.end(),
      [trx](const TrxItem &item) {return item.trx_id_ == trx->get_trx_id();});
  assert(it != trx_list.locks_.end());
  auto lockSet = it->mode_ == LockMode::SHARED ? trx->get_shared_lockset() : trx->get_exclusive_lockset();
  assert(lockSet->erase(rid) == 1);
  trx_list.locks_.erase(it);
  if (trx_list.locks_.empty()) {
    lock_table_.erase(rid);
    return RC::SUCCESS;
  }
  table_latch.unlock();
  //step 3 check can grant other
  for (auto &tx : trx_list.locks_) {
    if (tx.granted_)
      break;
    tx.grant(); //grant blocking one
    if (tx.mode_ == LockMode::SHARED) {continue;}
    if (tx.mode_ == LockMode::UPGRADING) {
      trx_list.has_upgrading_ = false;
      tx.mode_ = LockMode::EXCLUSIVE;
    }
    break;
  }
  return RC::SUCCESS;
}

static LockManager *default_lock_manager = nullptr;
void LockManager::set_instance(LockManager *lockManager)
{
  if (default_lock_manager != nullptr && lockManager != nullptr) {
    LOG_ERROR("default lock manager has been setted");
    abort();
  }
  default_lock_manager = lockManager;
}
LockManager &LockManager::instance()
{
  return *default_lock_manager;
}