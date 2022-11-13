//
// Created by lianyu on 2022/11/6.
//

#ifndef MINIDB_HASH_INDEX_H
#define MINIDB_HASH_INDEX_H

#include "stdint.h"
#include "defs.h"
#include <fstream>
#include "storage/record/record.h"
#include <vector>

#define HASH_INDEX_MAX_COUNT (23450)
struct SmallHeader {
  uint32_t begin_num;
  uint32_t begin_index;
  uint8_t offset[256]; //begin
};

class HashIndex {
public:
  HashIndex() = default;
  void create_file(std::string file_name);
  void open_file(std::string file_name);
  void insert(int num);
  std::vector<RID> find(int search_key);
  int find_key(RID rid);
  void flush_to_disk();
public:
  static void set_hash_index(HashIndex *index);
  static HashIndex &instance();

private:
  int find_small_page_num(int num);

  SmallHeader data_[HASH_INDEX_MAX_COUNT];
  int page_max_num_;
  int current_count_ = 0;
  int current_small_page_num = 0;
  int file_desc_;
  std::string file_name_;
};

class HashDateIndex {
public:
  HashDateIndex() = default;
public:
  static void open_file(std::string file_name);
  static void add_sort_map(uint16_t date, int num);
  static std::vector<RID> find(uint16_t date);
  static int index_size();
};

#endif //MINIDB_HASH_INDEX_H
