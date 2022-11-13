
#include "zpaq_compress.h"
#include "./zpaq/zpaq.h"
void zpaq_compress(std::string file_name) {
  std::string zpaq_file_name = file_name + ".zpaq";
  const char *argv[5] = {"./", "a", zpaq_file_name.c_str(), file_name.c_str(), "-m5"};
  exec(5, argv);
}
void zpaq_uncompress(std::string file_name) {
  std::string zpaq_file_name = file_name + ".zpaq";
  const char *argv[5] = {"./", "x", zpaq_file_name.c_str(), file_name.c_str(), "-m5"};
  exec(5, argv);
}