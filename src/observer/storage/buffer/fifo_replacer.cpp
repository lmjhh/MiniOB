//
// Created by lianyu on 2022/10/28.
//

#include "fifo_replacer.h"
FIFOReplacer::FIFOReplacer(int32_t num_pages) : num_pages_(num_pages){

}

FIFOReplacer::~FIFOReplacer()
{

}

RC FIFOReplacer::victim(Frame **frame)
{
  Frame *first_frame = list_.front();
  list_.remove(first_frame);
  used_.erase(FrameID(first_frame->file_desc(), first_frame->page_num()));
  *frame = first_frame;
 return RC::SUCCESS;
}

RC FIFOReplacer::insert(Frame *frame)
{
  list_.push_back(frame);
  used_.insert(FrameID(frame->file_desc(), frame->page_num()));
  return RC::SUCCESS;
}

RC FIFOReplacer::remove(Frame *frame)
{
  auto iter = used_.find(FrameID(frame->file_desc(), frame->page_num()));
  if (iter != used_.end()) {
    list_.remove(frame);
    used_.erase(iter);
  }
  return RC::SUCCESS;
}

int32_t FIFOReplacer::size()
{
  return list_.size();
}