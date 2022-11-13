//
// Created by lianyu on 2022/11/9.
//

#include "comment_column.h"
#include "common/lang/string.h"
#include <fstream>
#include <sstream>
#include "defs.h"
#include "util/util.h"
#include "numeric"
#include <vector>
#include <unordered_map>
const int CommentColumnSize = 44 * 8; //一列多少bit
const int CommentColumnCacheBytes = CommentColumnSize * MAX_LINE_NUM / 8;

uint8_t CommentColumnValueCache[CommentColumnCacheBytes];
int CommentColumnValueOffset[MAX_LINE_NUM];

static std::unordered_map<char, uint8_t> chars_map = {
        {'a', 0},  {'b', 1},  {'c', 2},  {'d', 3},  {'e', 4},  {'f', 5},  {'g', 6},  {'h', 7},
        {'i', 8},  {'j', 9},  {'k', 10}, {'l', 11}, {'m', 12}, {'n', 13}, {'o', 14}, {'p', 15},
        {'q', 16}, {'r', 17}, {'s', 18}, {'t', 19}, {'u', 20}, {'v', 21}, {'w', 22}, {'x', 23},
        {'y', 24}, {'z', 25}, {'T', 26}, {'?', 27}, {';', 28}, {':', 29}, {'.', 30}, {'-', 31},
        {',', 32}, {'!', 33}, {' ', 34}
};

static std::unordered_map<std::string, uint8_t> words_map = {
        {"are", 35}, {"about", 36}, {"above", 37}, {"account", 38}, {"accord", 39}, {"across", 40}, {"after", 41}, {"affix", 42}, {"against", 43}, {"along", 44}, {"among", 45},
        {"beans", 46}, {"blithely", 47}, {"boost", 48}, {"bold", 49},
        {"care", 50}, {"cajole", 51},
        {"deposit", 52}, {"depend", 53}, {"dolphin", 54},
        {"even", 55}, {"express", 56}, {"excuses", 57},
        {"final", 58}, {"fluff", 59}, {"foxes", 60}, {"furio", 61},
        {"haggle", 62},
        {"ironic", 63}, {"ideas", 64},  {"instruct", 65},
        {"nag", 66},
        {"of", 67},
        {"pack", 68}, {"pint", 69}, {"pla", 70},
        {"quick", 71},
        {"req", 72}, {"reg", 73},
        {"sleep", 74}, {"slyly", 75}, {"silent", 76} ,{"special", 77}, {"steal", 78},
        {"the", 79}, {"to", 80},
        {"unusual", 81}, {"use", 82},
        {"wake", 83},

        {"side", 84}, {"fully", 85}, {"usly", 86}, {"ular", 87}

};

static std::vector<std::string> u8_to_str = {
        "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","T","?",";",":",".","-",",","!"," ",
        "are", "about", "above", "account", "accord", "across", "after", "affix", "against", "along", "among",
        "beans", "blithely", "boost", "bold",
        "care", "cajole",
        "deposit", "depend", "dolphin",
        "even", "express", "excuses",
        "final", "fluff", "foxes" ,"furio",
        "haggle",
        "ironic", "ideas", "instruct",
        "nag",
        "of",
        "pack", "pint", "pla",
        "quick",
        "req", "reg",
        "sleep", "slyly", "silent", "special", "steal",
        "the", "to",
        "unusual", "use",
        "wake",
        "side", "fully", "usly", "ular"

};

void CommentColumn::create_file(std::string file_name) {
  file_name_ = file_name;
  memset(CommentColumnValueCache, 0, sizeof(CommentColumnValueCache));
}

void CommentColumn::open_file(std::string file_name) {

//  bzip3_uncompress_file(file_name.c_str(), CommentColumnValueCache);

  for(int i = 35; i < u8_to_str.size(); i++) {
    if (words_map[u8_to_str[i]] != i) {
      printf ("%d\n",i);
    }
  }

  lzw_uncompress_file(file_name.c_str());
  std::string remove_file = file_name + ".lzw";
  remove(remove_file.c_str());

  std::ifstream in(file_name.c_str(), std::ios::in);
  in.read((char *) (&current_offset_), 4);
  in.read((char *) CommentColumnValueCache + 4 , current_offset_);
  in.close();

//  current_offset_ = *(uint32_t *)CommentColumnValueCache;

  for (int i = 4; i < current_offset_ + 4; i++) {
    if (CommentColumnValueCache[i] >= 128) {
      CommentColumnValueCache[i] -= 128; //还原字符
      CommentColumnValueOffset[total_data_++] = i + 1;
    }
  }
}

void CommentColumn::to_string(std::ostream &os, int index, int line_num) {
  std::string result;
  int begin_index = 4;
  if (line_num > 0) begin_index = CommentColumnValueOffset[line_num - 1];
  for (int i = begin_index; i < CommentColumnValueOffset[line_num]; i++) {
    result += u8_to_str[CommentColumnValueCache[i]];
  }
  os << result;
}

void CommentColumn::insert(void *data, int index) {
  int data_len = strlen((char *)data);
  char *data_str = (char *)data;
  std::string sub_str;
  for (int i = 0; i < data_len; i++) {
    if (data_str[i] == ' ') {
      CommentColumnValueCache[current_offset_++] = chars_map[' '];
      sub_str = "";
    } else {
      sub_str += data_str[i];
//      printf("%s\n", sub_str.c_str());
      if (words_map.find(sub_str) != words_map.end()) {
        CommentColumnValueCache[++current_offset_ - sub_str.length()] = words_map[sub_str];
        current_offset_ =  current_offset_ - sub_str.length() + 1;
      } else if (chars_map.find(data_str[i]) != chars_map.end()){
        CommentColumnValueCache[current_offset_++] = chars_map[data_str[i]];
      }
    }
  }
  CommentColumnValueCache[current_offset_ - 1] += 128;
}

void CommentColumn::flush_to_disk() {
  memcpy(CommentColumnValueCache, &current_offset_, 4);

//  bzip3_compress_file(file_name_, CommentColumnValueCache, current_offset_);

  std::ofstream out(file_name_.c_str(), std::ios::out);
  out.write((const char *) CommentColumnValueCache, current_offset_);
  out.close();

  lzw_compress_file(file_name_);
  remove(file_name_.c_str());
}