//
// Created by lianyu on 2022/10/28.
//

#ifndef MINIDB_DISK_MANAGER_H
#define MINIDB_DISK_MANAGER_H
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "rc.h"
#include "defs.h"
#include "storage/buffer/frame.h"
#include "common/lang/bitmap.h"

struct SYS_INFO {
  int max_space_id; //每个文件对应一个 space_id
};

/**
 * diskfile的文件第一个页面，存放一些元数据信息，包括了后面每页的分配信息。
 * TODO 1. 当前的做法，只能分配比较少的页面，你可以扩展一下，支持更多的页面或无限多的页面吗？
 *         可以参考Linux ext(n)和Windows NTFS等文件系统
 *      2. 当前使用bitmap存放页面分配情况，但是这种方法在页面非常多的时候，查找空闲页面的
 *         效率非常低，你有办法优化吗？
 */
struct DiskDataFileHeader {
  int32_t page_count;        //! 当前文件一共有多少个页面
  int32_t allocated_pages;   //! 已经分配了多少个页面
  char    bitmap[0];         //! 页面分配位图, 第0个页面(就是当前页面)，总是1
  /**
   * 能够分配的最大的页面个数，即bitmap的字节数 乘以8
   */
  static const int MAX_PAGE_NUM = (PAGE_DATA_SIZE - sizeof(page_count) - sizeof(allocated_pages)) * 8;
};

class DiskDataFile {
public:
  DiskDataFile() = default;
  DiskDataFileHeader * file_header_ = nullptr;
  int                  file_desc_ = -1;
  std::string          file_name_;
  Page                 page_;
};

class DiskFileIterator
{
public:
  DiskFileIterator();
  ~DiskFileIterator();

  RC init(int file_desc, PageNum start_page = 0);
  bool has_next();
  PageNum next();
  RC reset();
private:
  common::Bitmap bitmap_;
  PageNum  current_page_num_ = -1;
};

class DiskManager {
public:
  DiskManager();
  ~DiskManager();
  RC create_data_file(const char *file_name, int &space_id);
  RC open_data_file(const char *file_name, int &file_desc);
  RC dispose_page(int file_desc, int page_num);
  RC close_file(int file_desc);

  RC get_disk_data_file(int file_desc, DiskDataFile &disk_data_file);


  RC write_page(int file_desc, PageNum page_num, const void *page_data);
  RC read_page(int file_desc, PageNum page_num, void *page_data);
  PageNum allocate_new_page(int file_desc);

public:
  static void set_instance(DiskManager *disk_manager);
  static DiskManager &instance();

private:
  SYS_INFO sys_info_;
  std::unordered_map<std::string, DiskDataFile *> opened_files_name_;
  std::unordered_map<int, DiskDataFile *> opened_files_fd_;
};
#endif  // MINIDB_DISK_MANAGER_H
