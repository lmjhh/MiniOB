//
// Created by lianyu on 2022/11/9.
//

#include "return_flag.h"

#include <fstream>
#include <sstream>
#include "defs.h"
#include "util//util.h"
const int ReturnFlagColumnSize = 8; //一列多少bit
const int ReturnFlagColumnCacheBytes = ReturnFlagColumnSize * MAX_LINE_NUM / 8;

uint8_t ReturnFlagColumnCache[MAX_LINE_NUM];

void ReturnFlagColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(ReturnFlagColumnCache, 0, sizeof(ReturnFlagColumnCache));
}

void ReturnFlagColumn::open_file(std::string file_name) {
  std::ifstream in(file_name.c_str(), std::ios::in);
  in.read((char *)ReturnFlagColumnCache, ReturnFlagColumnCacheBytes);
  in.close();
}

void ReturnFlagColumn::to_string(std::ostream &os, int index, int line_num) {
  char c = ReturnFlagColumnCache[line_num];
  char str[2] = {c, '\0'};
  os << str;
}

void ReturnFlagColumn::insert(void *data, int index) {
  uint8_t code = *(uint8_t *)data;
  ReturnFlagColumnCache[current_line_num_++] = code;
}

void ReturnFlagColumn::flush_to_disk() {
  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((char *) ReturnFlagColumnCache, ReturnFlagColumnCacheBytes);
  out.close();
}