/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by wangyunlai on 2022/9/28
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <vector>
#include "util/util.h"
#include "FileCompress.h"
#include "lzw_compress.h"
#include "util/bzip3/libbz3.c"

std::string double2string(double v)
{
  char buf[256];
  snprintf(buf, sizeof(buf), "%.2f", v);
  size_t len = strlen(buf);
  while (buf[len - 1] == '0') {
    len--;
      
  }
  if (buf[len - 1] == '.') {
    len--;
  }

  return std::string(buf, len);
}

//////////////////////////////////日期编码
DateNum to_date_data (char *str) {
  int y, m, d;
  sscanf(str, "%d-%d-%d", &y, &m, &d);
  return d + m * 32 + (y - 1992) * 512;
}

std::string to_date_str (DateNum data) {
  uint16_t d = (data << 11); d = d >> 11;
  uint16_t m = (data >> 5);  m = m << 12; m = m >> 12;
  uint16_t y = (data >> 9);  y += 1992;
  char yearStr[5], monthStr[3], dayStr[3];
  sprintf(yearStr, "%d", y); //年。
  sprintf(monthStr, "%d", m); //月。
  if (monthStr[1] == '\0') {
    monthStr[2] = '\0';
    monthStr[1] = monthStr[0];
    monthStr[0] = '0';
  }
  sprintf(dayStr, "%d", d); //日
  if (dayStr[1] == '\0') {
    dayStr[2] = '\0';
    dayStr[1] = dayStr[0];
    dayStr[0] = '0';
  }
  char result[11];
  sprintf(result, "%s-%s-%s", yearStr, monthStr, dayStr);
  return std::string(result);
}

///////////////////////////////////
static std::unordered_map<std::string, uint8_t> SHIP_MAP = {
        {"RAIL", 0}, {"SHIP", 1}, {"REG AIR", 2},
        {"AIR", 3}, {"FOB", 4}, {"MAIL", 5},
        {"TRUCK", 6},
        {"TAKE BACK RETURN", 7},
        {"DELIVER IN PERSON", 8},
        {"NONE", 9},
        {"COLLECT COD", 10}

};
static std::vector<std::string> SHIP_ARRAY = {
        "RAIL", "SHIP", "REG AIR", "AIR", "FOB", "MAIL", "TRUCK", "TAKE BACK RETURN", "DELIVER IN PERSON", "NONE", "COLLECT COD"
};

uint8_t str_to_ship_code(char *str) {
  return SHIP_MAP[std::string(str)];
}

std::string ship_code_to_str(uint8_t code) {
  return SHIP_ARRAY[code];
}

void huffman_compress_file(const char *file_name) {
  FileCompressAndUnCompress fc;
  fc.Compress(file_name); // 压缩文件
}
void huffman_uncompress_file(const char *file_name) {
  FileCompressAndUnCompress fc;
  fc.Uncompress(file_name); // 解压缩文件
}


typedef struct {
  unsigned char buffer [65536];
  int checksum, head, tail;
  size_t byte_count;
} streamer;

FILE *in, *out;

static int read_buff (void *ctx)
{
  streamer *stream = (streamer *)ctx;
  int value;

  if (stream->head == stream->tail)
    stream->tail = (stream->head = 0) + fread (stream->buffer, 1, sizeof (stream->buffer), in);

  if (stream->head < stream->tail) {
    value = stream->buffer [stream->head++];
    stream->checksum = stream->checksum * 3 + (unsigned char) value;
    stream->byte_count++;
  }
  else
    value = EOF;

  return value;
}

static void write_buff (int value, void *ctx)
{
  streamer *stream = (streamer *)ctx;

  if (value == EOF) {
    fwrite (stream->buffer, 1, stream->head, out);
    return;
  }

  stream->buffer [stream->head++] = value;

  if (stream->head == sizeof (stream->buffer)) {
    fwrite (stream->buffer, 1, stream->head, out);
    stream->head = 0;
  }

  stream->checksum = stream->checksum * 3 + (unsigned char) value;
  stream->byte_count++;
}

void lzw_compress_file(std::string file_name) {
  int maxbits = 16, error = 0;
  streamer reader, writer;
  std::string out_file_name = file_name + ".lzw";
  in = fopen( file_name.c_str() , "r" );
  out = fopen( out_file_name.c_str() , "w" );

  memset(&reader, 0, sizeof(reader));
  memset(&writer, 0, sizeof(writer));
  reader.checksum = writer.checksum = -1;

  if (lzw_compress(write_buff, &writer, read_buff, &reader, maxbits)) {
    fprintf(stderr, "lzw_compress() returned non-zero!\n");
  }

  write_buff(EOF, &writer);

  if (reader.byte_count) {
    fprintf(stderr, "source checksum = %x, ratio = %.2f%%\n", reader.checksum,
            writer.byte_count * 100.0 / reader.byte_count);
  }
  fclose(in);
  fclose(out);
}

void lzw_uncompress_file(std::string file_name) {
  int verbose = 0, error = 0;
  streamer reader, writer;

  std::string in_file_name = file_name + ".lzw";
  in = fopen( in_file_name.c_str() , "r" );
  out = fopen( file_name.c_str() , "w" );

  memset(&reader, 0, sizeof(reader));
  memset(&writer, 0, sizeof(writer));
  reader.checksum = writer.checksum = -1;

  if (lzw_decompress(write_buff, &writer, read_buff, &reader)) {
    fprintf(stderr, "lzw_decompress() returned non-zero!\n");
  }

  write_buff(EOF, &writer);

  if (verbose && writer.byte_count) {
    fprintf(stderr, "output checksum = %x, ratio = %.2f%%\n", writer.checksum,
            reader.byte_count * 100.0 / writer.byte_count);
  }
  fclose(in);
  fclose(out);
}


void bzip3_compress_file(std::string file_name, void *buf, size_t buf_size) {
  // Compress the file:
  size_t out_size = bz3_bound(buf_size);
  uint8_t * outbuf = (uint8_t *)malloc(out_size);
  int bzerr = bz3_compress(buf_size + 16, (const uint8_t *)buf, outbuf, buf_size, &out_size);
  if (bzerr != BZ3_OK) {
    printf("bz3_compress() failed with error code %d", bzerr);
  }
  std::string out_name = file_name + ".bzp";
  FILE *bzp_out = fopen(out_name.c_str() , "wb" );
  /* XXX: Doesn't preserve endianess. We should write the `size_t` value manually with known endianess. */
  fwrite(&buf_size, 1, sizeof(size_t), bzp_out);
  fwrite(outbuf, 1, out_size, bzp_out);

  fclose(bzp_out);
}
void bzip3_uncompress_file(std::string file_name) {
  std::string in_name = file_name + ".bzp";
  FILE *bzp_in = fopen(in_name.c_str() , "rb" );
  fseek(bzp_in, 0, SEEK_END);
  size_t size = ftell(bzp_in);
  fseek(bzp_in, 0, SEEK_SET);
  uint8_t *buffer = (uint8_t *)malloc(size);
  fread(buffer, 1, size, bzp_in);
  fclose(bzp_in);

  // Decompress the file:
  size_t orig_size = *(size_t *)buffer;
  uint8_t * outbuf = (uint8_t *)malloc(orig_size);
  int bzerr = bz3_decompress(buffer + sizeof(size_t), outbuf, size - sizeof(size_t), &orig_size);
  if (bzerr != BZ3_OK) {
    printf("bz3_decompress() failed with error code %d", bzerr);
  }

  FILE *bzp_out = fopen(file_name.c_str(), "wb");
  fwrite(outbuf, 1, orig_size, bzp_out);
  fclose(bzp_out);
}