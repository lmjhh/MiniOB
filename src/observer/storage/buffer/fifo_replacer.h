//
// Created by lianyu on 2022/10/28.
//

#ifndef MINIDB_FIFO_REPLACER_H
#define MINIDB_FIFO_REPLACER_H

#include <list>
#include <unordered_set>
#include "replacer.h"
/**
 * 实现一个FIFO Replacer
 */
class FIFOReplacer : public Replacer {
public:
  /**
   * 创建 FIFO Replacer.
   * @param num_pages 可以管理的最大 Page 数量
   */
  explicit FIFOReplacer(int32_t num_pages);

  ~FIFOReplacer();

  RC victim(Frame **frame);

  RC insert(Frame *frame);

  RC remove(Frame *frame);

  int32_t size();

private:
  std::list<Frame *> list_;
  std::unordered_set<FrameID> used_;
  PageNum num_pages_;
};

#endif  // MINIDB_FIFO_REPLACER_H
