//
// Created by lianyu on 2022/11/9.
//

#include "part_column.h"

#include <fstream>
#include <sstream>
#include "defs.h"
#include "util//util.h"
const int PartColumnSize = 32; //一列多少bit
const int PartColumnCacheBytes = PartColumnSize * MAX_LINE_NUM / 8;

uint32_t PartColumnCache[MAX_LINE_NUM];

void PartColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(PartColumnCache, 0, sizeof(PartColumnCache));
}

void PartColumn::open_file(std::string file_name) {

//  bzip3_uncompress_file(file_name.c_str());
//  std::string remove_file = file_name + ".bzp";
//  remove(remove_file.c_str());

  std::ifstream in(file_name.c_str(), std::ios::in);
  in.read((char *)PartColumnCache, PartColumnCacheBytes);
  in.close();
}

void PartColumn::to_string(std::ostream &os, int index, int line_num) {
  uint32_t data = PartColumnCache[line_num];
  if (index == 0) {
    data >>= 14;
  } else {
    data <<= 18;
    data >>= 18;
  }
  os << data;
}

void PartColumn::insert(void *data, int index) {
  uint32_t code = *(uint32_t *)data;
  if (index == 0) {
    PartColumnCache[current_line_num_] |= code;
    PartColumnCache[current_line_num_] <<= 14;
  } else {
    PartColumnCache[current_line_num_] |= code;
    current_line_num_++;
  }
}

void PartColumn::flush_to_disk() {
  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((const char *)PartColumnCache, PartColumnCacheBytes);
  out.close();
//  bzip3_compress_file(file_name_);
//  remove(file_name_.c_str());
}