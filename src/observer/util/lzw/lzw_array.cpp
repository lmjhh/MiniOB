#include "lzw_array.h"

DictElement dictionaryArray[4095];

// add prefix + character to the dictionary
void dictionaryArrayAdd(int prefix, int character, int value) {
    dictionaryArray[value].prefix = prefix;
    dictionaryArray[value].character = character;
}

int dictionaryArrayPrefix(int value) {
    return dictionaryArray[value].prefix;
}

int dictionaryArrayCharacter(int value) {
    return dictionaryArray[value].character;
}
