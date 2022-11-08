//
// Created by lianyu on 2022/11/8.
//

#include "lzw_compress.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./lzw/lzw_algorithms.h" // LZW compression

FILE *inputFile;
FILE *outputFile;

int lzw(int type, char *file_name) {
  // do we have correct # of arguments?
  if (type == 0) { // compression
    inputFile = fopen(file_name, "r"); // read from the input file (HTML)
    outputFile = fopen(strcat(file_name, ".lzw"), "w+b"); // binary write to output file

    if (outputFile == NULL || inputFile == NULL) {
      printf("Can't open files\n'"); return 0;
    }

    compress(inputFile, outputFile);
  } else { // decompression
    inputFile = fopen(file_name, "rb"); // binary read from the input file
    if (inputFile == NULL) {
      return 0;
    }

    char temp[20]; int length = strlen(file_name)-4;
    strncpy(temp, file_name, length);
    temp[length] = '\0';
    outputFile = fopen(temp, "w"); // write to output file (HTML)

    decompress(inputFile, outputFile);
  }

  fclose(inputFile); fclose(outputFile); // close handles

  return 0;
}