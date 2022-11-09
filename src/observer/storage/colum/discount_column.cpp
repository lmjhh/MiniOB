//
// Created by lianyu on 2022/11/9.
//

#include "discount_column.h"
#include <fstream>
#include <sstream>
#include "defs.h"
#include "util//util.h"
const int DiscountColumnSize = 32; //一列多少bit
const int DiscountColumnCacheBytes = DiscountColumnSize * MAX_LINE_NUM / 8;

float DiscountColumnCache[MAX_LINE_NUM];

void DiscountColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(DiscountColumnCache, 0, sizeof(DiscountColumnCache));
}

void DiscountColumn::open_file(std::string file_name) {
  std::ifstream in(file_name.c_str(), std::ios::in);
  in.read((char *)DiscountColumnCache, DiscountColumnCacheBytes);
  in.close();
}

void DiscountColumn::to_string(std::ostream &os, int index, int line_num) {
  float v = DiscountColumnCache[line_num];
  os << double2string(v);
}

void DiscountColumn::insert(void *data, int index) {
  DiscountColumnCache[current_line_num_++] = *(float *)data;
}

void DiscountColumn::flush_to_disk() {
  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((const char *) DiscountColumnCache, DiscountColumnCacheBytes);
  out.close();
}