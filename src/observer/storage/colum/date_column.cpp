//
// Created by lianyu on 2022/11/8.
//


#include "date_column.h"
#include <fstream>
#include <sstream>
#include "defs.h"
#include "storage/index/hash_index.h"
const int DateColumnSize = 32; //一列30bit
const int DateColumnCacheBytes = DateColumnSize * MAX_LINE_NUM / 8;
//std::bitset<DateColumnSize> DateColumnCache[MAX_LINE_NUM];
uint32_t DateColumnCache[MAX_LINE_NUM];

void DateColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(DateColumnCache, 0, sizeof(DateColumnCache));
}

void DateColumn::open_file(std::string file_name) {
  std::ifstream in(file_name.c_str(), std::ios::binary);
  in.read((char *)DateColumnCache, DateColumnCacheBytes);
  for (int i = 0; i < MAX_LINE_NUM; i++) {
    if (DateColumnCache[i] != 0) {
      uint16_t date = DateColumnCache[i] >> 18;
      HashDateIndex::add_sort_map(date, i);
    }
  }
//  for (int i = 0; i < MAX_LINE_NUM; i++) {
//    for (int j = 0; j < DateColumnSize;) {
//      char temp = 0;
//      in.read(&temp, sizeof(char));
//      for (int k = 0; k < 8; k++) {
//        bool flag = (bool) ((temp >> k) & 1);
//        if (flag)
//          DateColumnCache[i].set(j + k);
//      }
//      j = j + 8;
//    }
//  }
  in.close();
}

void DateColumn::to_string(std::ostream &os, int index, int line_num) {
  uint32_t data = DateColumnCache[line_num];
  data = data << 2; //清空前置0
  uint32_t y, m, d;
  y = (data >> 29) + 1992;
  if (index == 0) {
    m = data; m = m << 3; m = m >> 28;
    d = data; d = d << 7; d = d >> 27;
  } else if (index == 1) {
    m = data; m = m << 12; m = m >> 28;
    d = data; d = d << 16; d = d >> 27;
  } else if (index == 2) {
    m = data; m = m << 21; m = m >> 28;
    d = data; d = d << 25; d = d >> 27;
  }
  char yearStr[5], monthStr[3], dayStr[3];
  sprintf(yearStr, "%d", y); //年。
  sprintf(monthStr, "%d", m); //月。
  if (monthStr[1] == '\0') {
    monthStr[2] = '\0';
    monthStr[1] = monthStr[0];
    monthStr[0] = '0';
  }
  sprintf(dayStr, "%d", d); //日
  if (dayStr[1] == '\0') {
    dayStr[2] = '\0';
    dayStr[1] = dayStr[0];
    dayStr[0] = '0';
  }
  char result[11];
  sprintf(result, "%s-%s-%s", yearStr, monthStr, dayStr);
  os << result;
}

void DateColumn::insert(void *data, int index) {
  uint16_t date = *(uint16_t *)data;
  if (index == 0) {
//    std::bitset<16> bit_date(date);
//    printf("one date %s\n", bit_date.to_string().c_str());
    current_data_ = 0;
    date = date << 4;
    date = date >> 4; //只保存相对1992的偏移
    current_data_ = current_data_ | date;
    current_data_ = current_data_ << 9; //写入one_date
//    std::bitset<32> bit_write(current_data_);
//    printf("one date %s\n", bit_write.to_string().c_str());
  } else if (index == 1) {
//    std::bitset<16> bit_date(date);
//    printf("one date %s\n", bit_date.to_string().c_str());
    date = date << 7; date = date >> 7; //只保留9位
    current_data_ = current_data_ | date; current_data_ = current_data_ << 9; //写入two_date
//    std::bitset<32> bit_write(current_data_);
//    printf("one date %s\n", bit_write.to_string().c_str());
  } else if (index == 2) {
//    std::bitset<16> bit_date(date);
//    printf("one date %s\n", bit_date.to_string().c_str());
    date = date << 7; date = date >> 7; //只保留9位
    current_data_ = current_data_ | date;                 //写入thr_date
    DateColumnCache[current_line_num_++] = current_data_;
  }
}

void DateColumn::flush_to_disk() {
  std::ofstream out(file_name_.c_str(), std::ios::binary);
  out.write((char *)DateColumnCache, DateColumnCacheBytes);
  out.close();
}