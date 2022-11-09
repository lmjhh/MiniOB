//
// Created by lianyu on 2022/11/9.
//

#include "line_status.h"
#include <fstream>
#include <sstream>
#include "defs.h"
#include "util//util.h"
const int LineStatusColumnSize = 8; //一列多少bit
const int LineStatusColumnCacheBytes = LineStatusColumnSize * MAX_LINE_NUM / 8;

char LineStatusColumnCache[MAX_LINE_NUM];

void LineStatusColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(LineStatusColumnCache, 0, sizeof(LineStatusColumnCache));
}

void LineStatusColumn::open_file(std::string file_name) {
  std::ifstream in(file_name.c_str(), std::ios::in);
  in.read((char *)LineStatusColumnCache, LineStatusColumnCacheBytes);
  in.close();
}

void LineStatusColumn::to_string(std::ostream &os, int index, int line_num) {
  char str[2] = {LineStatusColumnCache[line_num], '\0'};
  os << str;
}

void LineStatusColumn::insert(void *data, int index) {
  uint8_t code = *(uint8_t *)data;
  LineStatusColumnCache[current_line_num_++] = code;
}

void LineStatusColumn::flush_to_disk() {
  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((const char *) LineStatusColumnCache, LineStatusColumnCacheBytes);
  out.close();
}