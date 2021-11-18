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
// Created by Wangyunlai on 2021/5/14.
//

#ifndef __OBSERVER_SQL_EXECUTOR_VALUE_H_
#define __OBSERVER_SQL_EXECUTOR_VALUE_H_

#include <string.h>
#include <stdlib.h>
#include <string>
#include <ostream>
// #include "storage/default/disk_buffer_pool.h"

class TupleValue {
public:
  TupleValue() = default;
  virtual ~TupleValue() = default;

  virtual void to_string(std::ostream &os) const = 0;
  virtual int compare(const TupleValue &other) const = 0;
  virtual bool isNull() const = 0;
  virtual float getValue() const = 0;
private:
};

class IntValue : public TupleValue {
public:
  explicit IntValue(int value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    if(value_ == OB_INT_MIN) os<<"NULL";
    else os << value_;
  }

  int compare(const TupleValue &other) const override {
    const IntValue & int_other = (const IntValue &)other;
    return value_ - int_other.value_;
  }

  bool isNull() const override{
    if(value_ == OB_INT_MIN) return true;
    return false; 
  }

  float getValue() const override{
    return value_*1.0;
  }

private:
  int value_;
};

class FloatValue : public TupleValue {
public:
  explicit FloatValue(float value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    if(value_ - OB_FLT_MIN < 0.0000001) os<<"NULL";
    else {

      char fomatValueStr[256];
      snprintf(fomatValueStr, sizeof(fomatValueStr), "%.2f", value_);
      
      if (NULL != strchr(fomatValueStr, '.')){
        int length = strlen(fomatValueStr);
        for (int i = length - 1; i > 0; i--) {
          if ('\0' == fomatValueStr[i]) {
            continue;
          }else if ('0' == fomatValueStr[i]) {
            fomatValueStr[i] = '\0';
          }else if ('.' == fomatValueStr[i]) {
            fomatValueStr[i] = '\0';
            break;
          }else{
            break;
          }
        }
      }
      os << fomatValueStr;
    }
  }

  int compare(const TupleValue &other) const override {
    const FloatValue & float_other = (const FloatValue &)other;
    float result = value_ - float_other.value_;
    if (result > 0.00001) { // 浮点数没有考虑精度问题
      return 1;
    }
    if (result < 0) {
      return -1;
    }
    return 0;
  }

  bool isNull() const override{
    if(value_ - OB_FLT_MIN < 0.0000001) return true;
    return false; 
  }

  float getValue() const override{
    return value_*1.0;
  }

private:
  float value_;

};

class StringValue : public TupleValue {
public:
  StringValue(const char *value, int len) : value_(value, len){
  }
  explicit StringValue(const char *value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
      if(value_ == "NUL") os << "NULL";
      else os << value_;
  }

  int compare(const TupleValue &other) const override {
    const StringValue &string_other = (const StringValue &)other;
    return strcmp(value_.c_str(), string_other.value_.c_str());
  }

  bool isNull() const override{
    if(value_ == "NUL") return true;
    return false; 
  }

  float getValue() const override{
    return 0.0;
  }

private:
  std::string value_;
};

class DateValue : public TupleValue {

public:
  explicit DateValue(int value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    if(value_ == 0) os<<"NULL";
    else{
      char date[20];
      int value = value_;
      int a=0;
      a = value % 10;
      date[9] = (char)(48+a);
      value /= 10;
      a = value % 10;
      date[8] = (char)(48+a);
      date[7] = '-';
      value /= 10;
      a = value % 10; 
      date[6] = (char)(48+a);
      value /= 10;
      a = value % 10;
      date[5] = (char)(48+a);
      date[4] = '-';
      value /= 10;
      a = value % 10;
      date[3] = (char)(48+a);
      value /= 10;
      a = value % 10;
      date[2] = (char)(48+a);
      value /= 10;
      a = value % 10;
      date[1] = (char)(48+a);
      value /= 10;
      a = value % 10;
      date[0] = (char)(48+a);
      date[10] = '\0';
      os << date;
    }
  }

  int compare(const TupleValue &other) const override {
    const DateValue & date_other = (const DateValue &)other;
    return value_ - date_other.value_;
  }

  bool isNull() const override{
    if(value_ == 0) return true;
    return false; 
  }

  float getValue() const override{
    return value_*1.0;
  }

  private:
    int value_;
};


class TextValue : public TupleValue {

public:
  explicit TextValue(int value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    if(value_ == 0) os<<"NULL";
    else{
      int a = 1, b=1;
      a = a << 12;
      b = b << 22;
      int offset = value_ % a;
      int page_num = (value_ % b) / a;
      int file_id = value_ >> 22;

      // DiskBufferPool *disk_buffer_pool = theGlobalDiskBufferPool();
      // RC ret = RC::SUCCESS;
      // BPPageHandle page_handle;
      // if ((ret = disk_buffer_pool->get_this_page(file_id, page_num, &page_handle)) != RC::SUCCESS) {
      //   return;
      // }
      // char *data;
      // ret = disk_buffer_pool->get_data(&page_handle, &data);
      // if (ret != RC::SUCCESS) {
      //   return;
      // }

      // char text[4096];
      // memcpy(text, data, offset);
      // os << text;
      
    }
  }

  int compare(const TupleValue &other) const override {
    return 0;
  }

  bool isNull() const override{
    if(value_ == 0) return true;
    return false; 
  }

  float getValue() const override{
    return value_*1.0;
  }

  private:
    int value_;
};

#endif //__OBSERVER_SQL_EXECUTOR_VALUE_H_
