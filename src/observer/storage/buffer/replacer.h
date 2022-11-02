//
// Created by lianyu on 2022/10/22.
//

#ifndef MINIDB_REPLACER_H
#define MINIDB_REPLACER_H
#include "rc.h"
#include "defs.h"
#include "storage/buffer/frame.h"
/**
 * Replacer 抽象类，用于Page缓存替换
 */
class Replacer {
public:
  Replacer() = default;
  virtual ~Replacer() = default;

  /**
   * 实现淘汰算法.
   * @param[out]
   *
   */
  virtual RC victim(Frame **frame) = 0;

  virtual RC insert(Frame *frame) = 0;

  virtual RC remove(Frame *frame) = 0;

  /** @return 返回可以淘汰的总页数 */
  virtual int32_t size() = 0;
};

#endif  // MINIDB_REPLACER_H
