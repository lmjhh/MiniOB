//
// Created by lianyu on 2022/11/9.
//

#include "return_flag.h"

#include <fstream>
#include <sstream>
#include <bitset>
#include "defs.h"
#include "util/util.h"
#include "util/zpaq_compress.h"
const int ReturnFlagColumnSize = 1; //一列多少bit
const int ReturnFlagColumnCacheBytes = ReturnFlagColumnSize * MAX_LINE_NUM / 8;

char ReturnFlagColumnCache[MAX_LINE_NUM/8];
char LineStatusColumnCache[MAX_LINE_NUM/8];

void ReturnFlagColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(ReturnFlagColumnCache, 0, ReturnFlagColumnCacheBytes);
  memset(LineStatusColumnCache, 0, ReturnFlagColumnCacheBytes);
}

void ReturnFlagColumn::open_file(std::string file_name) {
  file_name_ = file_name;
}

void ReturnFlagColumn::delay_open_file() {
  zpaq_uncompress(file_name_);
  std::string copress_name = file_name_ +".zpaq";
  remove(copress_name.c_str());

  std::ifstream in(file_name_.c_str(), std::ios::in);
  in.read((char *)ReturnFlagColumnCache, ReturnFlagColumnCacheBytes);
  in.read((char *)LineStatusColumnCache, ReturnFlagColumnCacheBytes);
  in.read((char *)&N_F_size, 4);
  for (int i = 0; i < N_F_size; i++) {
    uint32_t tmp;
    in.read((char *)&tmp, 4);
    N_F_lines.insert(tmp);
  }
  in.close();
}

void ReturnFlagColumn::to_string(std::ostream &os, int index, int line_num) {
  if (N_F_size == 0) {
    delay_open_file();
  }
  if (N_F_lines.find(line_num) != N_F_lines.end()) {
    if (index == 0) {
      char str[2] = {'N', '\0'};
      os << str;
    } else {
      char str[2] = {'F', '\0'};
      os << str;
    }
    return;
  }
  if (index == 0) {
    std::bitset<8> bits(LineStatusColumnCache[line_num / 8]);
    if (bits[line_num % 8] == 0) {
      char str[2] = {'N', '\0'};
      os << str;
      return;
    }
    bits = ReturnFlagColumnCache[line_num / 8];
    if (bits[line_num % 8] != 0) {
      char str[2] = {'A', '\0'};
      os << str;
    } else {
      char str[2] = {'R', '\0'};
      os << str;
    }
  } else {
    std::bitset<8> bits(LineStatusColumnCache[line_num / 8]);
    if (bits[line_num % 8] == 0) {
      char str[2] = {'O', '\0'};
      os << str;
    } else {
      char str[2] = {'F', '\0'};
      os << str;
    }
  }
}

void ReturnFlagColumn::insert(void *data, int index) {
  uint8_t code = *(uint8_t *)data;
  if (index == 0) {
    if (code - 'A' == 0) {
      ReturnFlagColumnCache[current_line_num_ / 8] |= (1 << (current_line_num_ % 8));
    }
    last_char = code;
  } else if (index == 1) {
    if (code - 'F' == 0) {
      LineStatusColumnCache[current_line_num_ / 8] |= (1 << (current_line_num_ % 8));

      if (last_char == 'N') {
        N_F_size++;
        N_F_lines.insert(current_line_num_);
      }
    }
    current_line_num_++;
  }
}

void ReturnFlagColumn::flush_to_disk() {
  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((char *) ReturnFlagColumnCache, ReturnFlagColumnCacheBytes);
  out.write((char *) LineStatusColumnCache, ReturnFlagColumnCacheBytes);
  out.write((char *) &N_F_size, 4);
  for (auto iter : N_F_lines) {
    out.write((char *) &iter, 4);
  }
  out.close();
  zpaq_compress(file_name_);
  remove(file_name_.c_str());
}