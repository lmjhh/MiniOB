//
// Created by lianyu on 2022/11/8.
//

#ifndef MINIDB_COLUM_H
#define MINIDB_COLUM_H
#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>

class Column {
public:
  Column() {}
  ~Column() = default;
  virtual void create_file(std::string file_name) = 0;
  virtual void open_file(std::string file_name) = 0;
  //会有列间编码
  virtual void to_string(std::ostream &os, int index, int line_num) = 0;
  virtual void insert(void *data, int index) = 0;
  virtual void flush_to_disk() = 0;

  int size_;
  std::string file_name_;
  int current_line_num_ = 0;
};


#endif //MINIDB_COLUM_H
