//
// Created by lianyu on 2022/11/8.
//

#ifndef MINIDB_LZW_DICTIONARY_H
#define MINIDB_LZW_DICTIONARY_H

// the "string" in the dictionary consists of the last byte of the string and an index to a prefix for that string
struct DictNode {
  int value; // the position in the list
  int prefix; // prefix for byte > 255
  int character; // the last byte of the string
  struct DictNode *next;
};

void dictionaryInit();
void appendNode(struct DictNode *node);
void dictionaryDestroy();
int dictionaryLookup(int prefix, int character);
int dictionaryPrefix(int value);
int dictionaryCharacter(int value);
void dictionaryAdd(int prefix, int character, int value);

#endif //MINIDB_LZW_DICTIONARY_H
