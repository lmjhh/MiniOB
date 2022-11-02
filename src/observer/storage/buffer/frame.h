//
// Created by lianyu on 2022/10/29.
//

#ifndef MINIDB_FRAME_H
#define MINIDB_FRAME_H
#include "defs.h"
#include <pthread.h>
#include <string>

struct Page {
  PageNum page_num;
  char data[PAGE_DATA_SIZE];
};

class DiskBufferPool;
class BufferPool;

class FrameID
{
public:
  FrameID(int file_desc, PageNum page_num) :
        file_desc_(file_desc), page_num_(page_num)
  {}
  bool equal_to(const FrameID &other) const
  {
    return file_desc_ == other.file_desc_ && page_num_ == other.page_num_;
  }

  bool operator== (const FrameID &other) const
  {
    return this->equal_to(other);
  }

  int file_desc() const { return file_desc_; }
  PageNum page_num() const { return page_num_; }

private:
  int32_t file_desc_;
  PageNum page_num_;
};

template <> struct std::hash<FrameID> {
  size_t operator()(const FrameID &obj) const {
    return hash<int64_t>()(((uint64_t)obj.page_num()) << 32 | obj.file_desc());
  }
};

class Frame
{
public:
  void clear_page()
  {
    memset(&page_, 0, sizeof(page_));
  }

  PageNum page_num() const
  {
    return page_.page_num;
  }

  void set_page_num(PageNum page_num)
  {
    page_.page_num = page_num;
  }

  /**
   * 标记指定页面为“脏”页。如果修改了页面的内容，则应调用此函数，
   * 以便该页面被淘汰出缓冲区时系统将新的页面数据写入磁盘文件
   */
  void mark_dirty() {
    dirty_ = true;
  }

  char *data() {
    return page_.data;
  }

  int file_desc() const
  {
    return file_desc_;
  }

  void set_file_desc(int fd)
  {
    file_desc_ = fd;
  }
  bool can_purge()
  {
    return pin_count_ <= 0;
  }
  //读写锁相关
  void w_unlatch()
  {
    pthread_rwlock_unlock(&rwlock_);
  }
  void w_latch()
  {
    pthread_rwlock_wrlock(&rwlock_);
  }
  void r_unlatch()
  {
    pthread_rwlock_unlock(&rwlock_);
  }
  void r_latch() {
    pthread_rwlock_rdlock(&rwlock_);
  }

private:
  friend class DiskBufferPool;
  friend class BufferPool;
  bool          dirty_     = false;
  unsigned int  pin_count_ = 0;
  unsigned long acc_time_  = 0;
  int           file_desc_ = -1;
  Page          page_;

  //加读写锁
  pthread_rwlock_t rwlock_ = PTHREAD_RWLOCK_INITIALIZER;
};




#endif  // MINIDB_FRAME_H
