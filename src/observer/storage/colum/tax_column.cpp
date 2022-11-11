//
// Created by lianyu on 2022/11/9.
//

#include "tax_column.h"
#include <fstream>
#include <sstream>
#include "defs.h"
#include "util//util.h"
const int TaxColumnSize = 4; //一列多少bit
const int TaxColumnCacheBytes = TaxColumnSize * MAX_LINE_NUM / 8;

uint8_t TaxColumnCache[MAX_LINE_NUM];

void TaxColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(TaxColumnCache, 0, TaxColumnCacheBytes);
}

void TaxColumn::open_file(std::string file_name) {
//  bzip3_uncompress_file(file_name.c_str());
//  std::string remove_file = file_name + ".bzp";
//  remove(remove_file.c_str());

  std::ifstream in(file_name.c_str(), std::ios::in);
  in.read((char *)TaxColumnCache, TaxColumnCacheBytes);
  in.close();
}

void TaxColumn::to_string(std::ostream &os, int index, int line_num) {
  uint8_t value = TaxColumnCache[line_num/2];
  if (line_num % 2 == 0) {
    value = value >> 4;
  } else {
    value = value << 4;
    value = value >> 4;
  }
  float f_v = value;
  os << double2string(f_v/100.0);
}

void TaxColumn::insert(void *data, int index) {
  float f_value = *(float *)data;
  f_value *= 100;
  uint8_t i_value = f_value;
  if (current_line_num_ % 2 == 0) {
    TaxColumnCache[current_line_num_/2] |= i_value << 4;
  } else {
    TaxColumnCache[current_line_num_/2] |= i_value;
  }
  current_line_num_++;
}

void TaxColumn::flush_to_disk() {
  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((const char *) TaxColumnCache, TaxColumnCacheBytes);
  out.close();
//  bzip3_compress_file(file_name_);
//  remove(file_name_.c_str());
}