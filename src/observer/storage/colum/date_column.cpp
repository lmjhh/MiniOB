//
// Created by lianyu on 2022/11/8.
//


#include "date_column.h"
#include <fstream>
#include <sstream>
#include "defs.h"
#include "storage/index/hash_index.h"
#include "util//util.h"
const int DateColumnCacheBytes = 32 * MAX_LINE_NUM / 8;
const int DateColumnCacheOverBytes = 4 * MAX_LINE_NUM / 8;
uint32_t DateColumnCache[MAX_LINE_NUM];
uint8_t DateColumnCacheOver[MAX_LINE_NUM];

void DateColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(DateColumnCache, 0, sizeof(DateColumnCache));
  memset(DateColumnCacheOver, 0, sizeof(DateColumnCacheOver));
}

void DateColumn::open_file(std::string file_name) {
  std::ifstream in(file_name.c_str(), std::ios::in);
  in.read((char *)DateColumnCache, DateColumnCacheBytes);
  in.read((char *)DateColumnCacheOver, DateColumnCacheOverBytes);
  for (int i = 0; i < MAX_LINE_NUM; i++){
    uint32_t t = DateColumnCache[i];
    uint16_t v = t >> 20;
    HashDateIndex::add_sort_map(v, i);
  }
  in.close();
}

void DateColumn::to_string(std::ostream &os, int index, int line_num) {
  uint16_t t = 0;
  if (index == 0) {
    t = DateColumnCache[line_num] >> 20;
  } else if (index == 1) {
    uint32_t o = DateColumnCache[line_num] << 12;
    t = o >> 20;
  } else if (index == 2) {
    uint32_t o = DateColumnCache[line_num] << 24;
    t = o >> 20;
    if (line_num % 2 == 0) {
      t |= DateColumnCacheOver[line_num/2] >> 4;
    } else {
      uint8_t f = DateColumnCacheOver[line_num/2] << 4;
      f = f >> 4;
      t |= f;
    }
  }
  os << to_date_str(t);
}

void DateColumn::insert(void *data, int index) {
  uint16_t date = *(uint16_t *)data;
  date = date << 4;
  date = date >> 4;
  if (index == 0) {
    DateColumnCache[current_line_num_] |= date;
    DateColumnCache[current_line_num_] <<= 12;
  } else if (index == 1) {
    DateColumnCache[current_line_num_] |= date;
    DateColumnCache[current_line_num_] <<= 8;
  } else {
    DateColumnCache[current_line_num_] |= date >> 4;
    uint8_t t = date;
    t <<= 4;
    t >>= 4;
    DateColumnCacheOver[current_line_num_ / 2] |= t;
    if (current_line_num_ % 2 == 0) {
      DateColumnCacheOver[current_line_num_ / 2] <<= 4;
    }
    current_line_num_++;
  }
}

void DateColumn::flush_to_disk() {
  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((const char *)DateColumnCache, DateColumnCacheBytes);
  out.write((const char *)DateColumnCacheOver, DateColumnCacheOverBytes);
  out.close();
}