/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by wangyunlai on 2022/9/28
//

#pragma once
#include <string>
typedef uint16_t DateNum;

std::string double2string(double v);

DateNum to_date_data (char *str);
std::string to_date_str (DateNum data);

uint8_t str_to_ship_code(char *str);
std::string ship_code_to_str(uint8_t code);

void huffman_compress_file(const char *file_name);
void huffman_uncompress_file(const char *file_name);

void lzw_compress_file(std::string file_name);
void lzw_uncompress_file(std::string file_name);

void bzip3_compress_file(std::string file_name, void* buf, size_t buf_size);
void bzip3_uncompress_file(std::string file_name);