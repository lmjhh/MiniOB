//
// Created by lianyu on 2022/11/8.
//

#ifndef MINIDB_LZW_ARRAY_H
#define MINIDB_LZW_ARRAY_H

typedef struct{
  int prefix; // prefix for byte > 255
  int character; // the last byte of the string
} DictElement;

void dictionaryArrayAdd(int prefix, int character, int value);
int dictionaryArrayPrefix(int value);
int dictionaryArrayCharacter(int value);

#endif //MINIDB_LZW_ARRAY_H
