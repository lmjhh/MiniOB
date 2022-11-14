//
// Created by lianyu on 2022/11/14.
//

#include "date.h"

//Date.cpp
#include "date.h"
#include <iostream>
using namespace std;
const int day_tab[2][12] = { {31,28,31,30,31,30,31,31,30,31,30,31},
                             {31,29,31,30,31,30,31,31,30,31,30,31} };

int Date::leap(int y)
{
  return (y % 4 == 0 && y % 100 != 0 || y % 400 == 0);
}

int Date::md2d(int leap, int month, int day)
{
  for (int i = month-2; i >= 0; i--)
  {
    day += day_tab[leap][i];
  }
  return day;
}

Date::Date(int y, int m, int d)
{
  year = y; month = m; day = d;
}

Date::Date()
{
  cout << "年:";
  cin >> year;
  cout << "月:";
  cin >> month;
  cout << "日:";
  cin >> day;
}

Date Date::operator+(int days)
{
  days += md2d(leap(year), month, day);
  //0<days<=365+leap
  int y = year;
  while (days > y2d(y))
  {
    days -= y2d(y);
    y++;
  }
  while (days <= 0)
  {
    y--;
    days += y2d(y);
  }
  //d2md
  int m = 1;
  int d1;
  while ((d1 = days - day_tab[leap(y)][m - 1]) > 0)
  {
    days = d1;
    m++;
  }
  Date dt(y, m, days);
  return dt;
}

Date Date::operator-(int days)
{
  return *this + (-days);
}

int Date::operator-(Date& b)
{
  int d1 = md2d(leap(year), month, day);
  int d2 = md2d(leap(b.year), b.month, b.day);
  int ds = d1 - d2;
  int y1 = year;
  int y2 = b.year;
  while (y1 > y2)
  {
    y1--;
    ds += y2d(y1);
  }
  while (y1 < y2)
  {
    ds -= y2d(y1);
    y1++;
  }
  return ds;
}

ostream& operator<<(ostream& os, Date& d)
{
  os << d.year << "年" << d.month << "月" << d.day << "日";
  return os;
}
