//
// Created by lianyu on 2022/11/8.
//

#ifndef MINIDB_LZW_COMPRESS_H
#define MINIDB_LZW_COMPRESS_H

int lzw_compress (void (*dst)(int,void*), void *dstctx, int (*src)(void*), void *srcctx, int maxbits);
int lzw_decompress (void (*dst)(int,void*), void *dstctx, int (*src)(void*), void *srcctx);

#endif //MINIDB_LZW_COMPRESS_H
