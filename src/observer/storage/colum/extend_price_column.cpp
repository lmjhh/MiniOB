//
// Created by lianyu on 2022/11/9.
//

#include "extend_price_column.h"
#include <fstream>
#include <sstream>
#include "defs.h"
#include "util//util.h"
const int ExtendPriceColumnSize = 32; //一列多少bit
const int ExtendPriceColumnCacheBytes = ExtendPriceColumnSize * MAX_LINE_NUM / 8;

float ExtendPriceColumnCache[MAX_LINE_NUM];

void ExtendPriceColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(ExtendPriceColumnCache, 0, sizeof(ExtendPriceColumnCache));
}

void ExtendPriceColumn::open_file(std::string file_name) {
  std::ifstream in(file_name.c_str(), std::ios::in);
  in.read((char *)ExtendPriceColumnCache, ExtendPriceColumnCacheBytes);
  in.close();
}

void ExtendPriceColumn::to_string(std::ostream &os, int index, int line_num) {
  float v = ExtendPriceColumnCache[line_num];
  os << double2string(v);
}

void ExtendPriceColumn::insert(void *data, int index) {
  ExtendPriceColumnCache[current_line_num_++] = *(float *)data;
}

void ExtendPriceColumn::flush_to_disk() {
  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((const char *) ExtendPriceColumnCache, ExtendPriceColumnCacheBytes);
  out.close();
}