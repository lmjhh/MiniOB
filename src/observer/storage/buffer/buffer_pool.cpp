//
// Created by lianyu on 2022/10/22.
//

#include "buffer_pool.h"
#include "fifo_replacer.h"
#include "common/log/log.h"

/////////////////////////////////////////////////////////////////////////////////

BufferPool::BufferPool(int32_t pool_size)
  : pool_size_(pool_size)
{
  frames_ = new Frame[pool_size];
  replacer_ = new FIFOReplacer(pool_size);
  page_table_ = new std::unordered_map<FrameID, Frame *>();
  for (size_t i = 0; i < pool_size; ++i) {
    free_list_.emplace_back(&frames_[i]);
  }
}

RC BufferPool::allocate_page(int file_desc, Frame **frame)
{
  std::lock_guard<std::mutex> lck(latch_);
  //1. 找到一个可以用的页
  Frame *allocated_frame = nullptr;
  RC rc = get_victim_page(&allocated_frame);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  PageNum page_num = DiskManager::instance().allocate_new_page(file_desc);
  //2. 如果是个脏页，需要落盘和记录日志
  if (allocated_frame->dirty_) {
    DiskManager::instance().write_page(allocated_frame->file_desc(), allocated_frame->page_num(), &allocated_frame->page_);
  }
  //3. 移除索引
  page_table_->erase(FrameID( allocated_frame->file_desc(), allocated_frame->page_num()));
  page_table_->insert(std::pair<FrameID, Frame *>(FrameID(file_desc, page_num), allocated_frame));

  //4. 更新Frame信息
  allocated_frame->clear_page();
  allocated_frame->set_page_num(page_num);
  allocated_frame->set_file_desc(file_desc);
  allocated_frame->dirty_ = false;
  allocated_frame->pin_count_ = 1;

  *frame = allocated_frame;
  return  rc;
}

RC BufferPool::get_this_page(int file_desc, PageNum page_num, Frame **frame)
{
  std::lock_guard<std::mutex> lck(latch_);
  RC rc = RC::SUCCESS;
  //1 已经在内存中，直接返回
  auto it = page_table_->find(FrameID(file_desc, page_num));
  if (it != page_table_->end()) {
    it->second->pin_count_++;
    *frame = it->second;
    //如果在可淘汰的列表中，需要移除
    replacer_->remove(it->second);
    return rc;
  }
  //2 不在内存中，需要从磁盘读
  //2.1 找到一个可用的页
  Frame *allocated_frame = nullptr;
  rc = get_victim_page(&allocated_frame);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  //2.2 如果是个脏页，需要落盘和记录日志
  if (allocated_frame->dirty_) {
    DiskManager::instance().write_page(allocated_frame->file_desc_, allocated_frame->page_num(), &allocated_frame->page_);
  }
  //2.3 移除索引,并把新的页ID加入索引
  page_table_->erase(FrameID( allocated_frame->file_desc(), allocated_frame->page_num()));
  page_table_->insert(std::pair<FrameID, Frame *>(FrameID(file_desc, page_num), allocated_frame));
  //2.4 从磁盘读数据到内存中
  DiskManager::instance().read_page(file_desc, page_num, &allocated_frame->page_);
  //2.5 更新Frame信息
  allocated_frame->set_file_desc(file_desc);
  allocated_frame->set_page_num(page_num);
  allocated_frame->dirty_ = false;
  allocated_frame->pin_count_ = 1;
  return RC::SUCCESS;
}

RC BufferPool::get_victim_page(Frame **frame) {
  if (free_list_.empty()) {
    if (replacer_->size() == 0) {
      return RC::BUFFERPOOL_NOBUF;
    }
    RC rc = replacer_->victim(frame);
    return rc;
  } else {
    Frame *target = free_list_.front();
    free_list_.pop_front();
    *frame = target;
  }
  return RC::SUCCESS;
}

RC BufferPool::unpin_page(Frame *frame) {
  std::lock_guard<std::mutex> lck(latch_);
  assert(frame->pin_count_ >= 1);
  if (--frame->pin_count_ == 0) {
    replacer_->insert(frame);
  }
  return RC::SUCCESS;
}

RC BufferPool::flush_page(Frame *frame)
{
  std::lock_guard<std::mutex> lck(latch_);
  PageNum page_num = frame->page_num();
  auto it = page_table_->find(FrameID(frame->file_desc(), frame->page_num()));
  if (it == page_table_->end()) {
    return RC::IOERR_WRITE;
  }
  RC rc = DiskManager::instance().write_page(frame->file_desc(), page_num, &frame->page_);
  frame->dirty_ = false;
  return rc;
}

RC BufferPool::dispose_page(int file_desc, PageNum page_num)
{
  auto iter = page_table_->find(FrameID(file_desc, page_num));
  if (iter != page_table_->end()) {
    if (iter->second->dirty_) {
      flush_page(iter->second);
    }
    free_list_.push_back(iter->second);
    return DiskManager::instance().dispose_page(file_desc, page_num);
  }
  return RC::BUFFERPOOL_INVALID_PAGE_NUM;
}

/**
 * BufferPool Manager
 */

MemBufferPoolManager::MemBufferPoolManager(int32_t pool_num)
                  : pool_num_(pool_num){
  buffer_pools_.push_back(new BufferPool(128));
}

RC MemBufferPoolManager::create_file(const char *file_name, int &space_id)
{
  return DiskManager::instance().create_data_file(file_name, space_id);
}

RC MemBufferPoolManager::open_file(const char *file_name, int &file_id)
{
  RC rc = DiskManager::instance().open_data_file(file_name, file_id);
  if (rc != RC::SUCCESS) return rc;

  return rc;
}

RC MemBufferPoolManager::close_file(int file_desc){
  return DiskManager::instance().close_file(file_desc);
}

RC MemBufferPoolManager::allocate_page(int file_id, Frame **frame)
{
  return buffer_pools_.front()->allocate_page(file_id, frame);
}

RC MemBufferPoolManager::unpin_page(Frame *frame)
{
  return buffer_pools_.front()->unpin_page(frame);
}

RC MemBufferPoolManager::get_this_page(int file_id, PageNum page_num, Frame **frame)
{
  return buffer_pools_.front()->get_this_page(file_id, page_num, frame);
}

RC MemBufferPoolManager::flush_page(Frame &frame)
{
  return buffer_pools_.front()->flush_page(frame);
}

RC MemBufferPoolManager::flush_all_pages(int file_desc) {
  return RC::SUCCESS;
}

RC MemBufferPoolManager::dispose_page(int file_desc, PageNum page_num)
{
  return buffer_pools_.front()->dispose_page(file_desc, page_num);
}

static MemBufferPoolManager *default_bpm = nullptr;
void MemBufferPoolManager::set_instance(MemBufferPoolManager *bpm)
{
  if (default_bpm != nullptr && bpm != nullptr) {
    LOG_ERROR("default buffer pool manager has been setted");
    abort();
  }
  default_bpm = bpm;
}
MemBufferPoolManager &MemBufferPoolManager::instance()
{
  return *default_bpm;
}