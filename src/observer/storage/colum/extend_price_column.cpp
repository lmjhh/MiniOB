//
// Created by lianyu on 2022/11/9.
//

#include "extend_price_column.h"
#include <fstream>
#include <sstream>
#include "defs.h"
#include "util//util.h"
#include <iomanip>
#include <algorithm>
const int ExtendPriceColumnSize = 24; //一列多少bit
const int ExtendPriceColumnCacheINTBytes = 16 * MAX_LINE_NUM / 8;
const int ExtendPriceColumnCacheFLOBytes = 8 * MAX_LINE_NUM / 8;

uint16_t ExtendPriceColumnINTCache[MAX_LINE_NUM];
uint8_t ExtendPriceColumnFLOCache[MAX_LINE_NUM];

void ExtendPriceColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(ExtendPriceColumnINTCache, 0, sizeof(ExtendPriceColumnINTCache));
  memset(ExtendPriceColumnFLOCache, 0, sizeof(ExtendPriceColumnFLOCache));
}

void ExtendPriceColumn::open_file(std::string file_name) {
//  bzip3_uncompress_file(file_name.c_str());
//  std::string remove_file = file_name + ".bzp";
//  remove(remove_file.c_str());

  std::ifstream in(file_name.c_str(), std::ios::in);
  in.read((char *)ExtendPriceColumnINTCache, ExtendPriceColumnCacheINTBytes);
  in.read((char *)ExtendPriceColumnFLOCache, ExtendPriceColumnCacheFLOBytes);
  in.close();
}

void ExtendPriceColumn::to_string(std::ostream &os, int index, int line_num) {
  uint8_t flo_v = ExtendPriceColumnFLOCache[line_num];
  int flag = 0;
  if (flo_v >= 128) flag = 1;
  flo_v <<= 1;
  flo_v >>= 1;
  uint32_t int_v = ExtendPriceColumnINTCache[line_num];
  float v = (int_v * 2 + flag) * 100 + flo_v;
  os << double2string(v/100);
}

void ExtendPriceColumn::insert(void *data, int index) {
  char buf[256];
  snprintf(buf, sizeof(buf), "%.2f", *(float *)data);
  std::string str(buf);
  str.erase(std::remove(str.begin(), str.end(), '.'), str.end());
  uint32_t int_v = atoi(str.c_str());
  uint8_t flo_v = int_v % 100;
  int_v /= 100;
  ExtendPriceColumnFLOCache[current_line_num_] |= flo_v;
  if (int_v % 2 == 1) {
    ExtendPriceColumnFLOCache[current_line_num_] |= (1 << 7);
  }
  int_v >>= 1;
  ExtendPriceColumnINTCache[current_line_num_] |= int_v;
  current_line_num_++;
}

void ExtendPriceColumn::flush_to_disk() {
  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((const char *) ExtendPriceColumnINTCache, ExtendPriceColumnCacheINTBytes);
  out.write((const char *) ExtendPriceColumnFLOCache, ExtendPriceColumnCacheFLOBytes);
  out.close();
//  bzip3_compress_file(file_name_);
//  remove(file_name_.c_str());
}