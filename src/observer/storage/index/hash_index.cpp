//
// Created by lianyu on 2022/11/6.
//

#include "hash_index.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <unordered_map>
#include "util/util.h"
#include "storage/colum/date_column.h"
#include "storage/colum/line_number.h"
static int ORDER_KEY_CACHE[6100000];

void HashIndex::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(data_, 0, sizeof(data_));
  for (int i = 0; i <HASH_INDEX_MAX_COUNT; i++) {
    data_[i].begin_num = 0xFFFFFFFF;
  }
}

void HashIndex::open_file(std::string file_name) {
  bzip3_uncompress_file(file_name.c_str(), data_);
//  std::string remove_file = file_name + ".bzp";
//  remove(remove_file.c_str());
//
//  std::ifstream in(file_name.c_str(), std::ios::in);
//  in.read((char *)data_, sizeof(data_));
//  in.close();
  int i = 0;
  for (; i < HASH_INDEX_MAX_COUNT; i++) {
    if (data_[i].begin_num == 0xFFFFFFFF) {
      break;
    } else {
      for (int iter = 0; iter < 256; iter++) {
        for (int value_count = 0; value_count < data_[i].offset[iter]; value_count++) {
          ORDER_KEY_CACHE[current_count_++] = data_[i].begin_num + iter;
          uint8_t line = value_count + 1;
          LineNumColumn::insert_from_order(&line, 0);
        }
      }
    }
  }
  current_small_page_num = i - 1;
}

void HashIndex::insert(int num) {
    ORDER_KEY_CACHE[current_count_] = num;
    while (1) {
      if (data_[current_small_page_num].begin_num == 0xFFFFFFFF) {
        data_[current_small_page_num].begin_num = num;
        data_[current_small_page_num].begin_index = current_count_;
      }
      int offset = num - data_[current_small_page_num].begin_num;
      if (offset < 256) {
        data_[current_small_page_num].offset[offset]++;
        current_count_++;
        break;
      } else {
        current_small_page_num++;
      }
    }
}

std::vector<RID> HashIndex::find(int search_key) {
  uint32_t num = search_key;
  std::vector<RID> rids;
  int small_page_num = find_small_page_num(num);
//  printf("find page beg = %d\n", data_[small_page_num].begin_num);
  while(small_page_num > 0 && data_[small_page_num].begin_num > num) {
    small_page_num--;
  }
//  printf("find page beg = %d\n", data_[small_page_num].begin_num);
  while(data_[small_page_num].begin_num <= num) {
//    printf("find page beg = %d\n", data_[small_page_num].begin_num);
    int target = num - data_[small_page_num].begin_num;
    if (target < 256) {
      int value_offset = data_[small_page_num].begin_index;
      for (int i = 0; i < target; i++) value_offset += data_[small_page_num].offset[i];
      for (int i = 0; i < data_[small_page_num].offset[target]; i++) {
        int value = value_offset + i;
        rids.push_back(RID(0, value));
      }
    }
    small_page_num++;
  }
  return rids;
}

int HashIndex::find_key(RID rid) {
  return ORDER_KEY_CACHE[rid.slot_num];
}

int HashIndex::find_small_page_num(int num) {
  int low = 0;
  int high = current_small_page_num;
  while(low < high) {
    int middle = (low + high) / 2;
    if(num == data_[middle].begin_num) {
       return middle;
    }
    if(num > data_[middle].begin_num) {
      low = middle + 1;
    }
    if(num < data_[middle].begin_num) {
      high = middle - 1;
    }
  }
  if (low > 0) low = low - 1;
  return low;
}

void HashIndex::flush_to_disk() {
  bzip3_compress_file(file_name_, data_, sizeof(data_));
}

static HashIndex *order_index = nullptr;
void HashIndex::set_hash_index(HashIndex *index)
{
  order_index = index;
}
HashIndex &HashIndex::instance()
{
  return *order_index;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
static std::unordered_map<uint16_t, std::vector<RID>> SHIP_DATE_CACHE;
static int max_page_num = 60000000;
static std::string date_file_name;
void HashDateIndex::open_file(std::string file_name) {
  date_file_name = file_name;
}

int HashDateIndex::index_size() {
  return SHIP_DATE_CACHE.size();
}

void HashDateIndex::add_sort_map(uint16_t date, int num) {
  SHIP_DATE_CACHE[date].push_back(RID(0, num % max_page_num));
}

std::vector<RID> HashDateIndex::find(uint16_t date){
  if (SHIP_DATE_CACHE.size() == 0) {
    DateColumn::delay_open_file(date_file_name);
  }
  return SHIP_DATE_CACHE[date];
}
