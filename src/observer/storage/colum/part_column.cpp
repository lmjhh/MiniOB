//
// Created by lianyu on 2022/11/9.
//

#include "part_column.h"

#include <fstream>
#include <sstream>
#include "defs.h"
#include "util//util.h"
#include "util/zpaq_compress.h"
#include <vector>
#include <set>
const int PartColumnCacheBytes = 8 * MAX_LINE_NUM / 8;
const int SupperColumnCacheBytes = 16 * MAX_LINE_NUM / 8;

uint8_t PartColumnCache[MAX_LINE_NUM];
uint16_t SupperColumnCache[MAX_LINE_NUM];

std::vector<std::vector<int>>  supperkey_to_park;
std::vector<std::set<int>> supperkey_to_set;

void PartColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(PartColumnCache, 0, sizeof(PartColumnCache));
  memset(SupperColumnCache, 0, sizeof(SupperColumnCache));
  for (int i = 0; i < 10000; i++) {
    supperkey_to_park.push_back(std::vector<int>());
    supperkey_to_set.push_back(std::set<int>());
  }
}

void PartColumn::open_file(std::string file_name) {
  file_name_ = file_name;
  for (int i = 0; i < 10000; i++) {
    supperkey_to_park.push_back(std::vector<int>());
  }
}

void PartColumn::delay_open_file() {
  std::string suppkey_file = file_name_ + "supper";
  zpaq_uncompress(suppkey_file);
  std::string remove_file = suppkey_file + ".zpaq";
  remove(remove_file.c_str());


  std::ifstream su_in(suppkey_file.c_str(), std::ios::in);
  for (int i = 0; i < 10000; i++) {
    uint8_t supper_size;
    su_in.read((char *)&supper_size, 1);
    for (uint8_t j = 0; j < supper_size; j++) {
      int part_key;
      su_in.read((char *)&part_key, 4);
      supperkey_to_park[i].push_back(part_key);
    }
  }
  su_in.close();


  zpaq_uncompress(file_name_.c_str());
  remove_file = file_name_ + ".zpaq";
  remove(remove_file.c_str());

  std::ifstream in(file_name_.c_str(), std::ios::in);
  in.read((char *)PartColumnCache, PartColumnCacheBytes);
  in.read((char *)SupperColumnCache, SupperColumnCacheBytes);
  in.close();
  current_line_num_ = 1;
}

void PartColumn::to_string(std::ostream &os, int index, int line_num) {
  if (current_line_num_ == 0) {
    delay_open_file();
  }
  if (index == 0) {
    os << supperkey_to_park[SupperColumnCache[line_num] - 1][PartColumnCache[line_num]];
  } else {
    os << SupperColumnCache[line_num];
  }
}

void PartColumn::insert(void *data, int index) {
  uint32_t code = *(uint32_t *)data;
  if (index == 0) {
    current_data_ = code;
  } else {
    SupperColumnCache[current_line_num_] = code;
    int part_key = current_data_;
    if (supperkey_to_set[code - 1].find(part_key) == supperkey_to_set[code - 1].end()) {
      supperkey_to_set[code - 1].insert(part_key);
      supperkey_to_park[code - 1].push_back(part_key);
    }
    for (int i = 0; i < supperkey_to_park[code - 1].size(); i++) {
      if (supperkey_to_park[code - 1][i] == part_key) {
        PartColumnCache[current_line_num_] = i;
        break;
      }
    }
    current_line_num_++;
    if (current_line_num_ == 6001215) {
      std::ofstream out(file_name_.c_str(), std::ios::out);
      out.write((const char *)PartColumnCache, PartColumnCacheBytes);
      out.close();

      std::string file2 = file_name_ + "2";
      std::ofstream out2(file2.c_str(), std::ios::out);
      out2.write((const char *)SupperColumnCache, SupperColumnCacheBytes);
      out2.close();
    }
  }
}

uint32_t PartColumn::get_partkey(int line_num) {
  if (line_num == -1) {
//    printf("%d %d %d\n", SupperColumnCache[current_line_num_ - 1], PartColumnCache[current_line_num_ - 1], supperkey_to_park[SupperColumnCache[current_line_num_ - 1] - 1][PartColumnCache[current_line_num_ - 1]]);
    return supperkey_to_park[SupperColumnCache[current_line_num_ - 1] - 1][PartColumnCache[current_line_num_ - 1]];
  } else {
//    printf("%d %d %d\n", SupperColumnCache[line_num], PartColumnCache[line_num], supperkey_to_park[SupperColumnCache[line_num] - 1][PartColumnCache[line_num]]);
//    for (int i = 0; i < supperkey_to_park[SupperColumnCache[line_num] - 1].size(); i++) {
//      printf("%d ", supperkey_to_park[SupperColumnCache[line_num] - 1][i]);
//    }
//    printf("%d\n");
    return supperkey_to_park[SupperColumnCache[line_num] - 1][PartColumnCache[line_num]];
  }
}

void PartColumn::flush_to_disk() {
  std::string suppkey_file = file_name_ + "supper";
  std::ofstream su_out(suppkey_file.c_str(), std::ios::out);
  for (int i = 0; i < 10000; i++) {
    uint8_t supper_size = supperkey_to_park[i].size();
    su_out.write((char *)&supper_size, 1);
    for (uint8_t j = 0; j < supper_size; j++) {
      int part_key = supperkey_to_park[i][j];
      su_out.write((char *)&part_key, 4);
    }
  }
  su_out.close();
  zpaq_compress(suppkey_file);
  remove(suppkey_file.c_str());


  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((const char *)PartColumnCache, PartColumnCacheBytes);
  out.write((const char *)SupperColumnCache, SupperColumnCacheBytes);
  out.close();

  zpaq_compress(file_name_);
  remove(file_name_.c_str());
}