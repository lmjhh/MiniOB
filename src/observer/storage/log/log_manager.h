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

#ifndef MINIDB_LOG_MANAGER_H
#define MINIDB_LOG_MANAGER_H

#include "log_record.h"

const uint32_t LOG_BUFFER_SIZE = 1<<10;

class LogManager {
public:
  LogManager()
      : next_lsn_(0), persistent_lsn_(-1) {

    log_buffer_ = new char[LOG_BUFFER_SIZE];
    flush_buffer_ = new char[LOG_BUFFER_SIZE];
  }

  ~LogManager() {
    delete[] log_buffer_;
    delete[] flush_buffer_;
    log_buffer_ = nullptr;
    flush_buffer_ = nullptr;
  }

  void run_flush_thread();
  void stop_flush_thread();
  void flush(bool force);
  // 插入一条RECODRD到 Logbuffer 返回 LSN
  LSN append_log_record(LogRecord &log_record);

  inline LSN get_persistent_LSN() { return persistent_lsn_; }
  inline void set_persistent_LSN(LSN lsn) { persistent_lsn_ = lsn; }
  inline char *get_log_buffer() { return log_buffer_; }

public:
  static void set_instance(LogManager *logManager);
  static LogManager &instance();

private:
  // 保证LSN是顺序递增
  std::atomic<LSN> next_lsn_;
  // log records before & include persistent_lsn_ have been written to disk
  std::atomic<LSN> persistent_lsn_;

  char *log_buffer_;
  char *flush_buffer_;

  // 共享变量 latch
  std::mutex latch_;
  // flush 线程
  std::thread *flush_thread_;
  // 通知 flush thread
  std::condition_variable cv_;


  int32_t log_buffer_offset_ = 0;
  int32_t flush_buffer_size_ = 0;
  std::atomic<bool> need_flush_; //组提交
  LSN last_LSN_ = -1; // Append以后会更新, 在flush的时候使用
  std::condition_variable appendCv_; // 通知 append thread
};

#endif  // MINIDB_LOG_MANAGER_H
