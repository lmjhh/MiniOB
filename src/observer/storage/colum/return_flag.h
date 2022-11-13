//
// Created by lianyu on 2022/11/9.
//

#ifndef MINIDB_RETURN_FLAG_H
#define MINIDB_RETURN_FLAG_H

#include "column.h"
#include <unordered_set>
class ReturnFlagColumn : public Column {
public:
  ReturnFlagColumn() = default;
  void create_file(std::string file_name) override;
  void open_file(std::string file_name) override;
  void to_string(std::ostream &os, int index, int line_num) override;
  void insert(void *data, int index) override;
  void flush_to_disk() override;
  void delay_open_file();
private:
  char last_char;
  uint32_t N_F_size = 0;
  std::unordered_set<uint32_t> N_F_lines;
};

#endif //MINIDB_RETURN_FLAG_H
