//
// Created by lianyu on 2022/11/9.
//

#include "line_number.h"

#include <fstream>
#include <sstream>
#include "defs.h"
#include "util//util.h"
const int LineNumColumnSize = 8; //一列多少bit
const int LineNumColumnCacheBytes = LineNumColumnSize * MAX_LINE_NUM / 8;

uint8_t LineNumColumnCache[MAX_LINE_NUM];

void LineNumColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(LineNumColumnCache, 0, sizeof(LineNumColumnCache));
}

void LineNumColumn::open_file(std::string file_name) {
  bzip3_uncompress_file(file_name.c_str(), LineNumColumnCache);

//  std::ifstream in(file_name.c_str(), std::ios::in);
//  in.read((char *)LineNumColumnCache, LineNumColumnCacheBytes);
//  in.close();
}

void LineNumColumn::to_string(std::ostream &os, int index, int line_num) {
  //直接用uint8会被当成字符
  int data = LineNumColumnCache[line_num];
  os << data;
}

void LineNumColumn::insert(void *data, int index) {
  uint8_t code = *(uint8_t *)data;
  LineNumColumnCache[current_line_num_++] = code;
}

void LineNumColumn::flush_to_disk() {
//  std::ofstream out(file_name_.c_str(), std::ios::out);
//  out.write((const char *) LineNumColumnCache, LineNumColumnCacheBytes);
//  out.close();
  bzip3_compress_file(file_name_, LineNumColumnCache, LineNumColumnCacheBytes);
}