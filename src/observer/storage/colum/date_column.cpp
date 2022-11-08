//
// Created by lianyu on 2022/11/8.
//


#include "date_column.h"
#include <fstream>
#include <sstream>
#include "defs.h"
#include "storage/index/hash_index.h"
#include "util//util.h"
const int DateColumnSize = 48; //一列36bit
const int DateColumnCacheBytes = DateColumnSize * MAX_LINE_NUM / 8;

#pragma pack (6)
struct DateCacheNode
{
  uint16_t data[3];
};
#pragma pack () /*取消指定对齐，恢复缺省对齐*/

DateCacheNode DateColumnCache[MAX_LINE_NUM];

void DateColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(DateColumnCache, 0, sizeof(DateColumnCache));
}

void DateColumn::open_file(std::string file_name) {
  std::ifstream in(file_name.c_str(), std::ios::in);
  in.read((char *)DateColumnCache, DateColumnCacheBytes);
//  for (int i = 0; i < MAX_LINE_NUM; i++) {
//    if (DateColumnCache[i].data_[0] != 0) {
//      uint16_t date = 0;
//      if (i % 2 == 0 ){ //0的是从第一个开始
//        date = date | DateColumnCache[i].data_[0];
//        date = date << 8;
//        date = date | DateColumnCache[i].data_[1];
//        date = date >> 4;
//      } else {
//        date = date | DateColumnCache[i - 1].data_[4];
//        date = date << 8;
//        date = date | DateColumnCache[i].data_[0];
//        date = date << 4;
//        date = date >> 4;
//      }
//      HashDateIndex::add_sort_map(date, i);
//    }
//  }
  for (int i = 0; i < MAX_LINE_NUM; i++){
    HashDateIndex::add_sort_map(DateColumnCache[i].data[0], i);
  }
  in.close();
}

void DateColumn::to_string(std::ostream &os, int index, int line_num) {
//  uint8_t y = 0, m = 0, d = 0;
//  if (line_num % 2 == 0) {
//    if (index == 0) {
//      y = DateColumnCache[line_num].data_[0] >> 5 + 1992;
//      m = DateColumnCache[line_num].data_[0] << 4; m = m >> 4;
//      d = DateColumnCache[line_num].data_[0] << 7; d = d >> 3;
//      d = d | (DateColumnCache[line_num].data_[1] >> 4);
//    } else if (index == 1) {
//      y = DateColumnCache[line_num].data_[1] << 4; y = y >> 5 + 1992;
//      m = DateColumnCache[line_num].data_[1] << 7; m = m >> 5;
////      m = m | (DateColumnCache[line_num].data_[2] )
//    } else if (index == 2) {
//    }
//  }
//  char yearStr[5], monthStr[3], dayStr[3];
//  sprintf(yearStr, "%d", y); //年。
//  sprintf(monthStr, "%d", m); //月。
//  if (monthStr[1] == '\0') {
//    monthStr[2] = '\0';
//    monthStr[1] = monthStr[0];
//    monthStr[0] = '0';
//  }
//  sprintf(dayStr, "%d", d); //日
//  if (dayStr[1] == '\0') {
//    dayStr[2] = '\0';
//    dayStr[1] = dayStr[0];
//    dayStr[0] = '0';
//  }
//  char result[11];
//  sprintf(result, "%s-%s-%s", yearStr, monthStr, dayStr);
  os << to_date_str(DateColumnCache[line_num].data[index]);
}

void DateColumn::insert(void *data, int index) {
  uint16_t date = *(uint16_t *)data;
  DateColumnCache[current_line_num_].data[index] = date;
  if (index == 2) current_line_num_++;
//  if (index == 0) {
////    std::bitset<16> bit_date(date);
////    printf("one date %s\n", bit_date.to_string().c_str());
//    current_data_ = 0;
//    date = date << 4;
//    date = date >> 4; //只保存相对1992的偏移
//    current_data_ = current_data_ | date;
//    current_data_ = current_data_ << 9; //写入one_date
////    std::bitset<32> bit_write(current_data_);
////    printf("one date %s\n", bit_write.to_string().c_str());
//  } else if (index == 1) {
////    std::bitset<16> bit_date(date);
////    printf("one date %s\n", bit_date.to_string().c_str());
//    //这里可能有大于第一列的数据 把多余的2个bit弄成差
//    uint16_t copy = date; copy = copy << 4; copy = copy >> 13;
//    uint16_t first_year = current_data_ >> 18;
//    uint32_t flag = 1;
//    flag = flag << 22;
//    current_data_ = current_data_ | flag;
//
//    date = date << 7; date = date >> 7; //只保留9位
//    current_data_ = current_data_ | date; current_data_ = current_data_ << 9; //写入two_date
////    std::bitset<32> bit_write(current_data_);
////    printf("one date %s\n", bit_write.to_string().c_str());
//  } else if (index == 2) {
////    std::bitset<16> bit_date(date);
////    printf("one date %s\n", bit_date.to_string().c_str());
//    date = date << 7; date = date >> 7; //只保留9位
//    current_data_ = current_data_ | date;                 //写入thr_date
//
//    uint16_t copy = date; copy = copy << 4; copy = copy >> 13;
//    uint32_t first_year = current_data_ << 2; first_year = current_data_ >> 29;
//    uint32_t flag = 1;
//    flag = flag << 21;
//    current_data_ = current_data_ | flag;
//
//    DateColumnCache[current_line_num_++] = current_data_;
//
//  }
}

void DateColumn::flush_to_disk() {
  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((const char *)DateColumnCache, DateColumnCacheBytes);
  out.close();
}