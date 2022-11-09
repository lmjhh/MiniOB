//
// Created by lianyu on 2022/11/9.
//

#include "comment_column.h"
#include <fstream>
#include <sstream>
#include "defs.h"
#include "util//util.h"
const int CommentColumnSize = 44 * 8; //一列多少bit
const int CommentColumnCacheBytes = CommentColumnSize * MAX_LINE_NUM / 8;

#pragma pack (6)
struct CommentNode {
  char data[44];
};
#pragma pack () /*取消指定对齐，恢复缺省对齐*/

CommentNode CommentColumnCache[MAX_LINE_NUM];

void CommentColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(CommentColumnCache, 0, sizeof(CommentColumnCache));
}

void CommentColumn::open_file(std::string file_name) {
  std::ifstream in(file_name.c_str(), std::ios::in);
  in.read((char *)CommentColumnCache, CommentColumnCacheBytes);
  in.close();
}

void CommentColumn::to_string(std::ostream &os, int index, int line_num) {
  os << CommentColumnCache[line_num].data;
}

void CommentColumn::insert(void *data, int index) {
  memcpy(CommentColumnCache[current_line_num_++].data, data, 44);
}

void CommentColumn::flush_to_disk() {
  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((const char *) CommentColumnCache, CommentColumnCacheBytes);
  out.close();
}