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

#include "util/lzw_compress.h"
static int ORDER_KEY_CACHE[6100000];

HashIndex::HashIndex(std::string file_name, int page_max_num) : page_max_num_(page_max_num) {
  file_name_ = file_name;
//  std::string file_name_lzw = file_name + ".lzw";
//  lzw(1, (char *)file_name_lzw.c_str()); //尝试解压
  file_desc_ = open(file_name.c_str(), O_RDWR | O_CREAT | O_EXCL, 0000400 | 0000200);
  if (file_desc_ < 0) { //已经存在
    file_desc_ = open(file_name.c_str(), O_RDWR);
    if (file_desc_ < 0) {
      printf("open failed %s %d %s\n", file_name.c_str(), file_desc_, strerror(errno));
    }
    if (lseek(file_desc_, 0, SEEK_SET) < 0) {
      printf("open seek failed\n");
    }
    size_t read_size = 0;
    read_size = read(file_desc_, data_, sizeof(data_));
    if (read_size != sizeof(data_)) {
      printf("open_read failed %s\n", strerror(errno));
    }
    int i = 0;
    for (; i < HASH_INDEX_MAX_COUNT; i++) {
      if (data_[i].begin_num == 0xFFFFFFFF) {
        break;
      } else {
        for (int iter = 0; iter < 256; iter++) {
          for (int value_count = 0; value_count < data_[i].offset[iter]; value_count++) {
            ORDER_KEY_CACHE[current_count_++] = data_[i].begin_num + iter;
          }
        }
      }
    }
    current_small_page_num = i - 1;
  } else {
    if (lseek(file_desc_, 0, SEEK_SET) < 0) {
      printf("open seek failed\n");
    }
    memset(data_, 0, sizeof(data_));
    for (int i = 0; i <HASH_INDEX_MAX_COUNT; i++) {
      data_[i].begin_num = 0xFFFFFFFF;
    }
  }
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
        rids.push_back(RID(value / page_max_num_ + 1, value % page_max_num_));
      }
    }
    small_page_num++;
  }
  return rids;
}

int HashIndex::find_key(RID rid) {
  return ORDER_KEY_CACHE[(rid.page_num - 1) * page_max_num_ + rid.slot_num];
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

  if (lseek(file_desc_, 0, SEEK_SET) < 0) {
    printf("seek failed\n");
  }
  if (write(file_desc_, data_, sizeof(data_)) != sizeof(data_)) {
    printf("write failed\n");
  }
  if (close(file_desc_) < 0) {
    printf("close failed\n");
  }

//  std::string lzw_file_name = file_name_;
//  lzw(0, (char *)lzw_file_name.c_str());
//  remove(file_name_.c_str());
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
static int max_page_num;
void HashDateIndex::set_max_page_num(int num) {
  max_page_num = num;
}

void HashDateIndex::add_sort_map(uint16_t date, int num) {
  SHIP_DATE_CACHE[date].push_back(RID(num / max_page_num + 1, num % max_page_num));
}

std::vector<RID> HashDateIndex::find(uint16_t date){
  return SHIP_DATE_CACHE[date];
}
