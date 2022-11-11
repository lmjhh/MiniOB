//
// Created by lianyu on 2022/11/9.
//

#include "discount_column.h"
#include <fstream>
#include <sstream>
#include "defs.h"
#include "util//util.h"
const int DiscountColumnSize = 4; //一列多少bit
const int DiscountColumnCacheBytes = DiscountColumnSize * MAX_LINE_NUM / 8;

uint8_t DiscountColumnCache[MAX_LINE_NUM];

void DiscountColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(DiscountColumnCache, 0, sizeof(DiscountColumnCache));
}

void DiscountColumn::open_file(std::string file_name) {
//  bzip3_uncompress_file(file_name.c_str());
//  std::string remove_file = file_name + ".bzp";
//  remove(remove_file.c_str());

  std::ifstream in(file_name.c_str(), std::ios::in);
  in.read((char *)DiscountColumnCache, DiscountColumnCacheBytes);
  in.close();
}

void DiscountColumn::to_string(std::ostream &os, int index, int line_num) {
  uint8_t value = DiscountColumnCache[line_num/2];
  if (line_num % 2 == 0) {
    value = value >> 4;
  } else {
    value = value << 4;
    value = value >> 4;
  }
  float f_v = value;
  os << double2string(f_v/100.0);
}

void DiscountColumn::insert(void *data, int index) {
  float f_value = *(float *)data;
  f_value *= 100;
  uint8_t i_value = f_value;
  if (current_line_num_ % 2 == 0) {
    DiscountColumnCache[current_line_num_/2] |= i_value << 4;
  } else {
    DiscountColumnCache[current_line_num_/2] |= i_value;
  }
  current_line_num_++;
}

void DiscountColumn::flush_to_disk() {
  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((const char *) DiscountColumnCache, DiscountColumnCacheBytes);
  out.close();
//  bzip3_compress_file(file_name_);
//  remove(file_name_.c_str());
}