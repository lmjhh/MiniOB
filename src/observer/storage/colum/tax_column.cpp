//
// Created by lianyu on 2022/11/9.
//

#include "tax_column.h"
#include <fstream>
#include <sstream>
#include "defs.h"
#include "util//util.h"
const int TaxColumnSize = 32; //一列多少bit
const int TaxColumnCacheBytes = TaxColumnSize * MAX_LINE_NUM / 8;

float TaxColumnCache[MAX_LINE_NUM];

void TaxColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(TaxColumnCache, 0, sizeof(TaxColumnCache));
}

void TaxColumn::open_file(std::string file_name) {
  std::ifstream in(file_name.c_str(), std::ios::in);
  in.read((char *)TaxColumnCache, TaxColumnCacheBytes);
  in.close();
}

void TaxColumn::to_string(std::ostream &os, int index, int line_num) {
  float v = TaxColumnCache[line_num];
  os << double2string(v);
}

void TaxColumn::insert(void *data, int index) {
  TaxColumnCache[current_line_num_++] = *(float *)data;
}

void TaxColumn::flush_to_disk() {
  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((const char *) TaxColumnCache, TaxColumnCacheBytes);
  out.close();
}