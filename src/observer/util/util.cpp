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

#include <string.h>
#include "util/util.h"

std::string double2string(double v)
{
  char buf[256];
  snprintf(buf, sizeof(buf), "%.2f", v);
  size_t len = strlen(buf);
  while (buf[len - 1] == '0') {
    len--;
      
  }
  if (buf[len - 1] == '.') {
    len--;
  }

  return std::string(buf, len);
}


DateNum to_date_data (char *str) {
  int y, m, d;
  sscanf(str, "%d-%d-%d", &y, &m, &d);
  return d + m * 32 + (y - 1980) * 512;
}

std::string to_date_str (DateNum data) {
  uint16_t d = (data << 11); d = d >> 11;
  uint16_t m = (data >> 5);  m = m << 12; m = m >> 12;
  uint16_t y = (data >> 9);  y += 1980;
  char yearStr[5], monthStr[3], dayStr[3];
  sprintf(yearStr, "%d", y); //年。
  sprintf(monthStr, "%d", m); //月。
  if (monthStr[1] == '\0') {
    monthStr[2] = '\0';
    monthStr[1] = monthStr[0];
    monthStr[0] = '0';
  }
  sprintf(dayStr, "%d", d); //日
  if (dayStr[1] == '\0') {
    dayStr[2] = '\0';
    dayStr[1] = dayStr[0];
    dayStr[0] = '0';
  }
  char result[11];
  sprintf(result, "%s-%s-%s", yearStr, monthStr, dayStr);
  return std::string(result);
}
