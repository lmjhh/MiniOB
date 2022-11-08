//
// Created by lianyu on 2022/11/8.
//

#ifndef MINIDB_LZW_ALOGRITHMS_H
#define MINIDB_LZW_ALOGRITHMS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function declarations
void compress(FILE *inputFile, FILE *outputFile);
void decompress(FILE *inputFile, FILE *outputFile);
int decode(int code, FILE * outputFile);

#endif //MINIDB_LZW_ALOGRITHMS_H
