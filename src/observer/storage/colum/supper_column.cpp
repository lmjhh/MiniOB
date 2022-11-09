//
// Created by lianyu on 2022/11/9.
//

#include "supper_column.h"

#include <fstream>
#include <sstream>
#include "defs.h"
#include "util//util.h"
const int SupperColumnSize = 32; //一列多少bit
const int SupperColumnCacheBytes = SupperColumnSize * MAX_LINE_NUM / 8;

uint32_t SupperColumnCache[MAX_LINE_NUM];

void SupperColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(SupperColumnCache, 0, sizeof(SupperColumnCache));
}

void SupperColumn::open_file(std::string file_name) {
  std::ifstream in(file_name.c_str(), std::ios::in);
  in.read((char *)SupperColumnCache, SupperColumnCacheBytes);
  in.close();
}

void SupperColumn::to_string(std::ostream &os, int index, int line_num) {
  //用无符号的都会被转成字符
  os << (int)SupperColumnCache[line_num];
}

void SupperColumn::insert(void *data, int index) {
  uint32_t code = *(uint32_t *)data;
  SupperColumnCache[current_line_num_++] = code;
}

void SupperColumn::flush_to_disk() {
  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((const char *) SupperColumnCache, SupperColumnCacheBytes);
  out.close();
}