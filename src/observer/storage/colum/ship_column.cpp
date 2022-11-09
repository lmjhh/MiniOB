//
// Created by lianyu on 2022/11/9.
//

#include "ship_column.h"

#include <fstream>
#include <sstream>
#include "defs.h"
#include "util//util.h"
const int ShipColumnSize = 8; //一列多少bit
const int ShipColumnCacheBytes = ShipColumnSize * MAX_LINE_NUM / 8;

uint8_t ShipColumnCache[MAX_LINE_NUM];

void ShipColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(ShipColumnCache, 0, sizeof(ShipColumnCache));
}

void ShipColumn::open_file(std::string file_name) {
  std::ifstream in(file_name.c_str(), std::ios::in);
  in.read((char *)ShipColumnCache, ShipColumnCacheBytes);
  in.close();
}

void ShipColumn::to_string(std::ostream &os, int index, int line_num) {
  uint8_t code = 0;
  if (index == 0) code = ShipColumnCache[line_num] >> 4;
  else {
    code = ShipColumnCache[line_num] << 4;
    code = code >> 4;
  }
  os << ship_code_to_str(code);
}

void ShipColumn::insert(void *data, int index) {
  uint8_t code = *(uint8_t *)data;
  if (index == 0) {
    ShipColumnCache[current_line_num_] = code;
  } else {
    ShipColumnCache[current_line_num_] = ShipColumnCache[current_line_num_] << 4;
    ShipColumnCache[current_line_num_] = ShipColumnCache[current_line_num_] | code;
  }
  if (index == 1) current_line_num_++;
}

void ShipColumn::flush_to_disk() {
  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((const char *)ShipColumnCache, ShipColumnCacheBytes);
  out.close();
}