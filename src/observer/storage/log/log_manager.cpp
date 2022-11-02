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

#include "log_manager.h"
#include <thread>
#include "common/log/log.h"

std::chrono::duration<long long int> LOG_TIMEOUT = std::chrono::seconds(1);

void LogManager::run_flush_thread()
{
  //开启一个后台线程刷日志
  flush_thread_ = new std::thread([&] {
    //每 LOG_TIMEOUT 刷一次，和 logbuffer 满的时候刷
    std::unique_lock<std::mutex> latch(latch_);
    // (2) When LOG_TIMEOUT is triggered.
    cv_.wait_for(latch, LOG_TIMEOUT, [&] {return need_flush_.load();});
    assert(flush_buffer_size_ == 0);
    if (log_buffer_offset_ > 0) {
      std::swap(log_buffer_, flush_buffer_);
      std::swap(log_buffer_offset_, flush_buffer_size_);
//      disk_manager_->WriteLog(flush_buffer_, flushBufferSize_);
      flush_buffer_size_ = 0;
      set_persistent_LSN(last_LSN_);
    }
    need_flush_ = false;
    appendCv_.notify_all();
  });
}

void LogManager::stop_flush_thread()
{
  flush(true);
  flush_thread_->join();
  assert(log_buffer_offset_ == 0 && flush_buffer_size_ == 0);
  delete flush_thread_;
}

LSN LogManager::append_log_record(LogRecord &log_record)
{
  std::unique_lock<std::mutex> latch(latch_);
  //LogBuffer满了唤醒日志线程
  if (log_buffer_offset_ + log_record.get_size() >= LOG_BUFFER_SIZE) {
    need_flush_ = true;
    cv_.notify_one();
    appendCv_.wait(latch, [&] {return log_buffer_offset_ + log_record.get_size() < LOG_BUFFER_SIZE;});
  }
  log_record.set_lsn(next_lsn_++);
  int write_len = log_record.serialize_to(log_buffer_ + log_buffer_offset_);
  log_buffer_offset_ += write_len;
  last_LSN_ = log_record.get_lsn();
  return last_LSN_;
}

void LogManager::flush(bool force) {
  std::unique_lock<std::mutex> latch(latch_);
  if (force) {
    need_flush_ = true;
    cv_.notify_one(); //let RunFlushThread wake up.
    appendCv_.wait(latch, [&] { return !need_flush_.load(); });
  } else {
    appendCv_.wait(latch); //组提交机制，等待超时或者写满Buffer的时候统一刷
  }
}


static LogManager *default_log_manager = nullptr;
void LogManager::set_instance(LogManager *logManager)
{
  if (default_log_manager != nullptr && logManager != nullptr) {
    LOG_ERROR("default log manager has been setted");
    abort();
  }
  default_log_manager = logManager;
}
LogManager &LogManager::instance()
{
  return *default_log_manager;
}