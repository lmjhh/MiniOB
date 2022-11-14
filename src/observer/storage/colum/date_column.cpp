//
// Created by lianyu on 2022/11/8.
//


#include "date_column.h"
#include <fstream>
#include <sstream>
#include "defs.h"
#include "storage/index/hash_index.h"
#include "util/zpaq_compress.h"
#include "util/util.h"
const int DateColumnSize = 48; //一列36bit
const int DateColumnCacheBytes = DateColumnSize * MAX_LINE_NUM / 8;

#pragma pack (6)
struct DateCacheNode
{
  int16_t data[3];
};
#pragma pack () /*取消指定对齐，恢复缺省对齐*/

DateCacheNode DateColumnCache[MAX_LINE_NUM];

void DateColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(DateColumnCache, 0, sizeof(DateColumnCache));
}

void DateColumn::open_file(std::string file_name) {
  file_name_ = file_name;
}

void DateColumn::delay_open_file(std::string file_name) {
  zpaq_uncompress(file_name);
  std::string copress_name = file_name +".zpaq";
  remove(copress_name.c_str());

  std::ifstream in(file_name.c_str(), std::ios::in);
  in.read((char *)DateColumnCache, DateColumnCacheBytes);
  for (int i = 0; i < MAX_LINE_NUM; i++){
    HashDateIndex::add_sort_map(DateColumnCache[i].data[0], i);
  }
  in.close();
}

void DateColumn::to_string(std::ostream &os, int index, int line_num) {
  if (HashDateIndex::index_size() == 0) {
    DateColumn::delay_open_file(file_name_);
  }
  if (index != 0) {
    uint16_t cur_date = DateColumnCache[line_num].data[index] + DateColumnCache[line_num].data[0];
    os << to_date_str(cur_date);
  } else {
    os << to_date_str(DateColumnCache[line_num].data[index]);
  }
}

void DateColumn::insert(void *data, int index) {
  uint16_t date = *(uint16_t *)data;
  if(index != 0) {
    DateColumnCache[current_line_num_].data[index] = date - DateColumnCache[current_line_num_].data[0];
  } else {
    DateColumnCache[current_line_num_].data[index] = date;
  }
  if (index == 2) current_line_num_++;
}

void DateColumn::flush_to_disk() {
  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((const char *)DateColumnCache, DateColumnCacheBytes);
  out.close();
  zpaq_compress(file_name_);
  remove(file_name_.c_str());
}