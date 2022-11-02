//
// Created by lianyu on 2022/10/22.
//

#ifndef MINIDB_BUFFER_POOL_H
#define MINIDB_BUFFER_POOL_H

#include <list>
#include <unordered_map>

#include "replacer.h"
#include "storage/buffer/frame.h"
#include "storage/log/log_manager.h"
#include "storage/disk/disk_manager.h"
#include "common/log/log.h"

class BufferPool {

public:
  BufferPool(int32_t pool_size);

  /**
   * 在指定文件中分配一个新的页面，并将其放入缓冲区，返回页面句柄指针。
   * 分配页面时，如果文件中有空闲页，就直接分配一个空闲页；
   * 如果文件中没有空闲页，则使用淘汰算法淘汰一页。
   */
  RC allocate_page(int file_desc, Frame **frame);

  /**
   * 根据文件ID和页号获取指定页面到缓冲区，返回页面句柄指针。
   */
  RC get_this_page(int file_desc, PageNum page_num, Frame **frame);

  /**
   * 用替换算法淘汰一个页面
   */
  RC get_victim_page(Frame **frame);

  RC unpin_page(Frame *frame);

  RC flush_page(Frame *frame);

  RC dispose_page(int file_desc, PageNum page_num);

private:
  int32_t pool_size_;
  Frame *frames_;
  std::unordered_map<FrameID, Frame *> *page_table_;
  std::list<Frame *> free_list_;
  Replacer *replacer_;
  std::mutex latch_;
};

//TODO:目前只会有一个pool,针对buffer_pool的优化待实现
/**
 * 创建多个buffer_pool管理
 * 方案1.一个DB对应一个buffer_pool
 * 方案2.同类Page对应一个buffer_pool
 *
 */
class MemBufferPoolManager {
public:
  /**
   * @param pool_size buffer pool 数量
   * @param disk_manager 磁盘管理
   * @param log_manager 日志管理
   */
  MemBufferPoolManager(int32_t pool_num_);

  RC create_file(const char *file_name, int &space_id);
  RC open_file(const char *file_name, int &file_id);
  RC close_file(int file_desc);
  RC allocate_page(int file_id, Frame **frame);
  RC get_this_page(int file_id, PageNum page_num, Frame **frame);
  RC unpin_page(Frame *frame);
  RC flush_page(Frame &frame);
  RC flush_all_pages(int file_desc);
  RC dispose_page(int file_desc, PageNum page_num);
public:
  static void set_instance(MemBufferPoolManager *bpm);
  static MemBufferPoolManager &instance();

private:
  int32_t pool_num_;
  std::vector<BufferPool *> buffer_pools_;
};

#endif  // MINIDB_BUFFER_POOL_H
