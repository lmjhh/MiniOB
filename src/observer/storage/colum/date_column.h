//
// Created by lianyu on 2022/11/8.
//

#ifndef MINIDB_DATE_COLUMN_H
#define MINIDB_DATE_COLUMN_H
#include <bitset>
#include "column.h"

class DateColumn : public Column {
public:
  DateColumn() = default;
  void create_file(std::string file_name) override;
  void open_file(std::string file_name) override;
  void to_string(std::ostream &os, int index, int line_num) override;
  void insert(void *data, int index) override;
  void flush_to_disk() override;
private:
  uint32_t current_data_ = 0;
};

#endif //MINIDB_DATE_COLUMN_H
