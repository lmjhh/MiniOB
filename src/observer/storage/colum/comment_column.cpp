//
// Created by lianyu on 2022/11/9.
//

#include "comment_column.h"
#include <fstream>
#include <sstream>
#include "defs.h"
#include "util//util.h"
#include "numeric"

const int CommentColumnSize = 44 * 8; //一列多少bit
const int CommentColumnCacheBytes = CommentColumnSize * MAX_LINE_NUM / 8;

char CommentColumnValueCache[CommentColumnCacheBytes];
uint8_t CommentColumnLengthCache[MAX_LINE_NUM];

void CommentColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(CommentColumnValueCache, 0, sizeof(CommentColumnValueCache));
  memset(CommentColumnLengthCache, 0, sizeof(CommentColumnLengthCache));
}

void CommentColumn::open_file(std::string file_name) {
  std::ifstream in(file_name.c_str(), std::ios::in);
  in.read((char *) (&total_data_), 4);
  in.read((char *) (&current_offset_), 4);
  in.read((char *) CommentColumnLengthCache, total_data_);
  in.read((char *) CommentColumnValueCache, current_offset_);
  in.close();
}

void CommentColumn::to_string(std::ostream &os, int index, int line_num) {
  char data[44];
  uint32_t offset = std::accumulate(CommentColumnLengthCache, CommentColumnLengthCache + line_num, 0);
  memcpy(data, CommentColumnValueCache + offset, CommentColumnLengthCache[line_num]);
  data[43] = '\0';
  os << data;
}

void CommentColumn::insert(void *data, int index) {
  uint8_t len = strlen((char *) data);
  memcpy(CommentColumnLengthCache + total_data_, &len, 1);
  memcpy(CommentColumnValueCache + current_offset_, data, len);
  total_data_ += 1;
  current_offset_ += len;
}

void CommentColumn::flush_to_disk() {
  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((const char *) &total_data_, 4);
  out.write((const char *) &current_offset_, 4);
  out.write((const char *) CommentColumnLengthCache, total_data_);
  out.write((const char *) CommentColumnValueCache, current_offset_);
  out.close();
}