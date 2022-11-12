//
// Created by lianyu on 2022/11/9.
//

#include "quantity_column.h"
#include <fstream>
#include <sstream>
#include "defs.h"
#include "util//util.h"
const int QuantityColumnSize = 8; //一列多少bit
const int QuantityColumnCacheBytes = QuantityColumnSize * MAX_LINE_NUM / 8;

uint8_t QuantityColumnCache[MAX_LINE_NUM];

void QuantityColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(QuantityColumnCache, 0, sizeof(QuantityColumnCache));
}

void QuantityColumn::open_file(std::string file_name) {
  bzip3_uncompress_file(file_name.c_str(), QuantityColumnCache);

//  std::ifstream in(file_name.c_str(), std::ios::in);
//  in.read((char *)QuantityColumnCache, QuantityColumnCacheBytes);
//  in.close();
}

void QuantityColumn::to_string(std::ostream &os, int index, int line_num) {
  //直接用uint8会被当成字符
  int data = QuantityColumnCache[line_num];
  os << data;
}

void QuantityColumn::insert(void *data, int index) {
  uint8_t code = *(uint8_t *)data;
  QuantityColumnCache[current_line_num_++] = code;
}

void QuantityColumn::flush_to_disk() {
//  std::ofstream out(file_name_.c_str(), std::ios::out);
//  out.write((const char *) QuantityColumnCache, QuantityColumnCacheBytes);
//  out.close();
  bzip3_compress_file(file_name_, QuantityColumnCache, QuantityColumnCacheBytes);
}