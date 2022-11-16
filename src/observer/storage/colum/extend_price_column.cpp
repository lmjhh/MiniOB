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
#include "util/zpaq_compress.h"
const int PartKeyMaxNum = 200000;
const int ExtendPriceColumnCacheINTBytes = 16 * PartKeyMaxNum / 8;
const int ExtendPriceColumnCacheFLOBytes = 8 * PartKeyMaxNum / 8;

uint16_t ExtendPriceColumnINTCache[PartKeyMaxNum];
uint8_t ExtendPriceColumnFLOCache[PartKeyMaxNum];

void ExtendPriceColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(ExtendPriceColumnINTCache, 0, sizeof(ExtendPriceColumnINTCache));
  memset(ExtendPriceColumnFLOCache, 0, sizeof(ExtendPriceColumnFLOCache));
}

void ExtendPriceColumn::open_file(std::string file_name) {
  file_name_ = file_name;
}

void ExtendPriceColumn::delay_open_file() {
  zpaq_uncompress(file_name_.c_str());
  std::string remove_file = file_name_ + ".zpaq";
  remove(remove_file.c_str());

  std::ifstream in(file_name_.c_str(), std::ios::in);
  in.read((char *)ExtendPriceColumnINTCache, ExtendPriceColumnCacheINTBytes);
  in.read((char *)ExtendPriceColumnFLOCache, ExtendPriceColumnCacheFLOBytes);
  in.close();
  current_line_num_ = 1;
}

void ExtendPriceColumn::to_string(std::ostream &os, int index, int line_num) {
  if (current_line_num_ == 0) {
    delay_open_file();
  }
  uint8_t flo_v = ExtendPriceColumnFLOCache[line_num - 1];
  int flag = 0;
  if (flo_v >= 128) flag = 1;
  flo_v <<= 1;
  flo_v >>= 1;
  uint32_t int_v = ExtendPriceColumnINTCache[line_num - 1];
  float v = (int_v * 2 + flag) * 100 + flo_v;
  v = v * index;
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
  ExtendPriceColumnFLOCache[index - 1] |= flo_v;
  if (int_v % 2 == 1) {
    ExtendPriceColumnFLOCache[index - 1] |= (1 << 7);
  }
  int_v >>= 1;
  ExtendPriceColumnINTCache[index - 1] |= int_v;
}

void ExtendPriceColumn::flush_to_disk() {
  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((const char *) ExtendPriceColumnINTCache, ExtendPriceColumnCacheINTBytes);
  out.write((const char *) ExtendPriceColumnFLOCache, ExtendPriceColumnCacheFLOBytes);
  out.close();
  zpaq_compress(file_name_);
  remove(file_name_.c_str());
}