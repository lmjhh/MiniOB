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
// Created by lianyu on 2022/9/8.
//

#include <list>
#include <iostream>
#include <functional>
#include <thread>
#include <chrono>

#include "storage/index/bplus_tree.h"
#include "storage/default/disk_buffer_pool.h"
#include "rc.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "gtest/gtest.h"
#include "storage/trx/trx.h"

using namespace common;

// order must small real order
// if page is 8k, it is 400
#define ORDER 4
#define POOL_NUM 2

BplusTreeHandler *handler = nullptr;
const char *index_name = "test.btree";
int per_thread_write = 132;
int thread_count = 16;
RID rid, check_rid;

void init_bpm()
{
  BufferPoolManager *bmp = new BufferPoolManager();
  BufferPoolManager::set_instance(bmp);
}

template <typename... Args>
void launch_parallel_test(uint64_t num_threads, Args &&... args) {
  std::vector<std::thread> thread_group;
  // Launch a group of threads
  for (uint64_t thread_itr = 0; thread_itr < num_threads; ++thread_itr) {
    thread_group.push_back(std::thread(args..., thread_itr));
  }

  // Join the threads with the main thread
  for (uint64_t thread_itr = 0; thread_itr < num_threads; ++thread_itr) {
    thread_group[thread_itr].join();
  }
}

void order_insert() {
  RC rc = RC::SUCCESS;
  RID rid;
  Trx *trx = new Trx();
  for (int i = 0; i < per_thread_write * thread_count; i++) {
    rid.page_num = i / per_thread_write;
    rid.slot_num = i % per_thread_write;
    int insert_key = i;
    LOG_INFO("Insert %d. rid=%s", insert_key, rid.to_string().c_str());
    rc = handler->insert_entry((const char *)&insert_key, &rid, trx);
    ASSERT_EQ(RC::SUCCESS, rc);
  }
  delete trx;
}

void insert_util(BplusTreeHandler *btree, __attribute__((unused)) uint64_t thread_itr = 0) {
  RC rc = RC::SUCCESS;
  RID rid;
  Trx *trx = new Trx();
  for (int i = 0; i < per_thread_write; i++) {
    rid.page_num = thread_itr;
    rid.slot_num = i;
    int insert_key = thread_itr * per_thread_write + i;
    LOG_INFO("Insert %d. rid=%s", insert_key, rid.to_string().c_str());
    rc = handler->insert_entry((const char *)&insert_key, &rid, trx);
    ASSERT_EQ(RC::SUCCESS, rc);
  }
  delete trx;
}

void insert_and_read_util(BplusTreeHandler *btree, __attribute__((unused)) uint64_t thread_itr = 0) {
  RC rc = RC::SUCCESS;
  RID rid;
  Trx *trx = new Trx();
  for (int i = 0; i < per_thread_write; i++) {
    rid.page_num = thread_itr;
    rid.slot_num = i;
    int insert_key = thread_itr * per_thread_write + i;
    LOG_INFO("Insert %d. rid=%s", insert_key, rid.to_string().c_str());
    rc = handler->insert_entry((const char *)&insert_key, &rid, trx);
    ASSERT_EQ(RC::SUCCESS, rc);
    std::list<RID> rids;
    rids.clear();
    RC rc = handler->get_entry((const char *)&insert_key, 4, rids);
    ASSERT_EQ(RC::SUCCESS, rc);
    ASSERT_EQ(1, rids.size());
    check_rid = rids.front();
    ASSERT_EQ(rid.page_num, check_rid.page_num);
    ASSERT_EQ(rid.slot_num, check_rid.slot_num);
  }
  delete trx;
}

void delete_util(BplusTreeHandler *btree, __attribute__((unused)) uint64_t thread_itr = 0) {

  RC rc = RC::SUCCESS;
  RID rid;
  Trx *trx = new Trx();
  for (int i = 0; i < per_thread_write / 2; i++) {
    rid.page_num = thread_itr;
    rid.slot_num = i;
    int delete_key = thread_itr * per_thread_write + i;
    LOG_INFO("Delete %d. rid=%s", delete_key, rid.to_string().c_str());
    rc = handler->delete_entry((const char *)&delete_key, &rid, trx);
    ASSERT_EQ(RC::SUCCESS, rc);
  }
  delete trx;
}

void delete_and_read_util(BplusTreeHandler *btree, __attribute__((unused)) uint64_t thread_itr = 0) {
  RC rc = RC::SUCCESS;
  RID rid;
  Trx *trx = new Trx();
  for (int i = 0; i < per_thread_write / 2; i++) {
    rid.page_num = thread_itr;
    rid.slot_num = i;
    int delete_key = thread_itr * per_thread_write + i;
    LOG_INFO("Delete %d. rid=%s", delete_key, rid.to_string().c_str());
    rc = handler->delete_entry((const char *)&delete_key, &rid, trx);
    ASSERT_EQ(RC::SUCCESS, rc);
    std::list<RID> rids;
    rids.clear();
    RC rc = handler->get_entry((const char *)&delete_key, 4, rids);
    ASSERT_EQ(RC::SUCCESS, rc);
    ASSERT_EQ(0, rids.size());
  }
  delete trx;
}


TEST(test_bplus_concurrent, insert_test) {
  LoggerFactory::init_default("concurrent_insert.log");
  const char *index_name = "concurrent_insert.btree";
  ::remove(index_name);
  handler = new BplusTreeHandler();
  handler->create(index_name, INTS, sizeof(int), ORDER, ORDER);
  //开始并行写
  launch_parallel_test(thread_count, insert_util, handler);
  handler->print_tree();
  ASSERT_EQ(true, handler->validate_tree());
  //检查是否正确
  std::list<RID> rids;
  for (int i = 0; i < per_thread_write * thread_count; i++) {
    rid.page_num = i / per_thread_write;
    rid.slot_num = i % per_thread_write;
    rids.clear();
    RC rc = handler->get_entry((const char *)&i, 4, rids);
    ASSERT_EQ(RC::SUCCESS, rc);
    ASSERT_EQ(1, rids.size());
    check_rid = rids.front();
    ASSERT_EQ(rid.page_num, check_rid.page_num);
    ASSERT_EQ(rid.slot_num, check_rid.slot_num);
  }
  handler->close();
}


TEST(test_bplus_concurrent, insert_and_read_test) {
  LoggerFactory::init_default("concurrent_insert_and_read.log");
  const char *index_name = "concurrent_insert_and_read.btree";
  ::remove(index_name);
  handler = new BplusTreeHandler();
  handler->create(index_name, INTS, sizeof(int), ORDER, ORDER);
  //开始并行写
  launch_parallel_test(thread_count, insert_and_read_util, handler);
  handler->print_tree();
  ASSERT_EQ(true, handler->validate_tree());
}

TEST(test_bplus_concurrent, delete_test) {
  LoggerFactory::init_default("concurrentInsert.log");
  const char *index_name = "concurrentDelete.btree";
  ::remove(index_name);
  handler = new BplusTreeHandler();
  handler->create(index_name, INTS, sizeof(int), ORDER, ORDER);

  //单线程插入
  order_insert();
  handler->print_tree();
  ASSERT_EQ(true, handler->validate_tree());
  //并行删除
  launch_parallel_test(thread_count, delete_util, handler);
  handler->print_tree();
  ASSERT_EQ(true, handler->validate_tree());

  std::list<RID> rids;
  for (int i = 0; i < per_thread_write * thread_count; i++) {
    rid.page_num = i / per_thread_write;
    rid.slot_num = i % per_thread_write;
    rids.clear();
    if (i % per_thread_write < (per_thread_write / 2)) {
      RC rc = handler->get_entry((const char *)&i, 4, rids);
      ASSERT_EQ(RC::SUCCESS, rc);
      ASSERT_EQ(0, rids.size());
    } else {
      RC rc = handler->get_entry((const char *)&i, 4, rids);
      ASSERT_EQ(RC::SUCCESS, rc);
      ASSERT_EQ(1, rids.size());
      check_rid = rids.front();
      ASSERT_EQ(rid.page_num, check_rid.page_num);
      ASSERT_EQ(rid.slot_num, check_rid.slot_num);
    }
  }
  handler->close();
}

TEST(test_bplus_concurrent, delete_and_read_test) {
  LoggerFactory::init_default("concurrent_delete_and_read.log");
  const char *index_name = "concurrent_delete_and_read.btree";
  ::remove(index_name);
  handler = new BplusTreeHandler();
  handler->create(index_name, INTS, sizeof(int), ORDER, ORDER);
  //单线程插入
  order_insert();
  handler->print_tree();
  ASSERT_EQ(true, handler->validate_tree());
  //开始并行读和删除
  launch_parallel_test(thread_count, delete_and_read_util, handler);
  handler->print_tree();
  ASSERT_EQ(true, handler->validate_tree());
}

int main(int argc, char **argv)
{
  // 分析gtest程序的命令行参数
  testing::InitGoogleTest(&argc, argv);

  // 调用RUN_ALL_TESTS()运行所有测试用例
  // main函数返回RUN_ALL_TESTS()的运行结果

  init_bpm();
  int rc = RUN_ALL_TESTS();

  return rc;
}