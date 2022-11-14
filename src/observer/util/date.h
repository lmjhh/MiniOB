//
// Created by lianyu on 2022/11/14.
//

#ifndef MINIDB_DATE_H
#define MINIDB_DATE_H

//Date.h
#include <iostream>

class Date
{
public:
  int year;
  int month;
  int day;
  int leap(int);
  int md2d(int leap, int month, int day);
  Date(int y, int m, int d);
  Date();
  friend std::ostream& operator<<(std::ostream&, Date&);
  //某日期加上天数
  Date operator+(int days);
  //某日期减去天数
  Date operator-(int days);
  //两日期相差的天数
  int operator-(Date& b);
private:
  int y2d(int year)
  {
    return 365 + leap(year);
  }
};


#endif //MINIDB_DATE_H
