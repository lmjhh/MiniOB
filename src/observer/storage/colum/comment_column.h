//
// Created by lianyu on 2022/11/9.
//

#ifndef MINIDB_COMMENT_COLUMN_H
#define MINIDB_COMMENT_COLUMN_H
#include "column.h"
class CommentColumn : public Column {
public:
  CommentColumn() = default;
  void create_file(std::string file_name) override;
  void open_file(std::string file_name) override;
  void to_string(std::ostream &os, int index, int line_num) override;
  void insert(void *data, int index) override;
  void flush_to_disk() override;
private:
  uint32_t current_data_ = 0;
};

#endif //MINIDB_COMMENT_COLUMN_H
