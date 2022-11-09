////
//// Created by lianyu on 2022/11/8.
////
//
//#include "lzw_compress.h"
//
///*
// * Definition for LZW coding
// *
// * vim: ts=4 sw=4 cindent nowrap
// */
//#include <cstdio>
//#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
//
//#define MAX_CODE 1000
//struct {
//  int suffix;
//  int parent;
//  int firstchild, nextsibling;
//} dictionary[MAX_CODE + 1];
//int next_code;
//int d_stack[MAX_CODE]; // stack for decoding a phrase
//
////#define input(f) ((int)BitsInput( f, 16))
////#define output(f, x) BitsOutput( f, (unsigned long)(x), 16)
//
//int DecodeString(int start, int code);
//void InitDictionary(void);
//void PrintDictionary(void)
//{//输出字典
//  int n;
//  int count;
//  for (n = 256; n < next_code; n++) {
//    count = DecodeString(0, n);
//    printf("%4d->", n);
//    while (0 < count--) printf("%c", (char)(d_stack[count]));
//    printf("\n");
//  }
//}
////Print out the dictionary that we build
//
//int DecodeString(int start, int code) {
//  //用来计算phrase_length的函数，并将编码后的字符倒序存入dstack
//  int count;//返回值定义为count
//  count = start;
//  while (0 <= code)
//  {
//    d_stack[count] = dictionary[code].suffix;//为解压缩而定义的堆栈
//    code = dictionary[code].parent;//找到母节点对应的长度，循环直到母节点长度的对应值为0
//    count++;
//  }
//  return count;
//}//the process of decoding
//
//void InitDictionary(void) {//初始化字典
//  int i;
//
//  for (i = 0; i < 256; i++) {
//    dictionary[i].suffix = i;//尾缀字符
//    dictionary[i].parent = -1;//母节点
//    dictionary[i].firstchild = -1;//孩子节点
//    dictionary[i].nextsibling = i + 1;//下一个兄弟节点
//  }
//  dictionary[255].nextsibling = -1;
//  next_code = 256;
//}
///*
// * Input: string represented by string_code in dictionary,
// * Output: the index of character+string in the dictionary
// * 		index = -1 if not found
// */
//int InDictionary(int character, int string_code) {
//  //查找词典中是否有字符串
//  int sibling;
//  if (0 > string_code)
//  {//如果前面没有前缀，那么直接返回刚读入进来的字符
//    return character;
//  }
//  sibling = dictionary[string_code].firstchild;
//  //让sibling的值等于输入为string_code的时候的first_child的值
//  while (-1 < sibling)
//  {
//    if (character == dictionary[sibling].suffix)
//      //如果现在输入的这个字符和某一个尾缀相同那么就返回此时sibling的值
//    {
//      return sibling;
//    }
//    sibling = dictionary[sibling].nextsibling;
//  }
//  return -1;
//}
//
//void AddToDictionary(int character, int string_code)
//{
//  int firstsibling, nextsibling;
//  if (0 > string_code)
//  {
//    return;
//  }
//  dictionary[next_code].suffix = character; //尾缀字符定义为character
//  dictionary[next_code].parent = string_code;//前缀为string_code
//  dictionary[next_code].nextsibling = -1;//没有nextsibling
//  dictionary[next_code].firstchild = -1;//没有firstchild
//  firstsibling = dictionary[string_code].firstchild;//查找string_code得到firstchild
//  if (-1 < firstsibling) {	// the parent has child
//    nextsibling = firstsibling;
//    while (-1 < dictionary[nextsibling].nextsibling)//一直循环到前缀为string_code的表的末尾
//    {
//      nextsibling = dictionary[nextsibling].nextsibling;//每循环一次，更新一次nextsibling的值
//    }
//    dictionary[nextsibling].nextsibling = next_code;
//  }
//  else {// no child before, modify it to be the first
//    dictionary[string_code].firstchild = next_code;
//  }
//  next_code++;
//}
//
//void LZWEncode(char *data, int length) {
//  int character;
//  int string_code;
//  int index;
//  unsigned long file_length;
//  InitDictionary();//初始化词典
//  string_code = -1;
//  for (int i = 0; i < length; i++) {
//    character = data[i];
//    index = InDictionary(character, string_code);//判断是否在字典中
//    if (0 <= index) {	// string+character in dictionary
//      string_code = index;
//    } else {//词典没有这个字符，需要在词典中创建一个新的
//      // string+character not in dictionary
//      output(bf, string_code);
//      if (MAX_CODE > next_code) {	// free space in the dictionary
//        // add string+character to the dictionary
//        AddToDictionary(character, string_code);
//      }
//      string_code = character;
//    }
//  }
//  output(bf, string_code);
//}
//void LZWDecode(BITFILE* bf, FILE* fp) {
//  int character = -1;//C:str(PW)的第一个字符
//  int new_code, last_code;//cw pw
//  int phrase_length;//每一次解码的长度
//  unsigned long file_length;//文件总长度
//  file_length = BitsInput(bf, 4 * 8);
//  if (-1 == file_length)
//  {
//    file_length = 0;
//  }
//  InitDictionary();//初始化解码词典
//  last_code = -1;
//  while (0 < file_length) {
//    new_code = input(bf);//此处为重定义的input的函数
//    if (new_code >= next_code)
//      //this is the case CSCSC(not in dict)
//    {
//      d_stack[0] = character;
//      phrase_length = DecodeString(1, last_code);
//    }
//    else//若不在字典中
//    {
//      phrase_length = DecodeString(0, new_code);
//    }
//    character = d_stack[phrase_length - 1];
//    while (0 < phrase_length) {//倒着写
//      phrase_length--;
//      fputc(d_stack[phrase_length], fp);
//      file_length--;
//    }
//    if (MAX_CODE > next_code) {	// add the new phrase to dictionary
//      AddToDictionary(character, last_code);
//    }
//    last_code = new_code;//更新last_code的值
//  }
//}
//int main(int argc, char** argv) {
//  FILE* fp;
//  BITFILE* bf;
//  if (4 > argc) { //输入的参数个数必须要大于等于三，不满足条件提醒
//    fprintf(stdout, "usage: \n%s <o> <ifile> <ofile>\n", argv[0]);
//    fprintf(stdout, "\t<o>: E or D reffers encode or decode\n");
//    fprintf(stdout, "\t<ifile>: input file name\n");
//    fprintf(stdout, "\t<ofile>: output file name\n");
//    return -1;
//  }
//  if ('E' == argv[1][0]) { // 编码
//    errno_t err = 0;
//    err = fopen_s(&fp, argv[2], "rb");//argv[2]输入的文件
//    bf = OpenBitFileOutput(argv[3]);//argv[3]输出的文件
//    if (err == 0 && NULL != bf) {
//      LZWEncode(fp, bf);
//      fclose(fp);
//      CloseBitFileOutput(bf);
//      fprintf(stdout, "encoding done\n");//完成编码过程
//    }
//  }
//  else if ('D' == argv[1][0]) {	// 解码
//    bf = OpenBitFileInput(argv[2]);//argv[2]输入的文件
//    errno_t err = 0;
//    err = fopen_s(&fp, argv[3], "wb");//argv[3]输出的文件
//    if (NULL != fp && NULL != bf) {
//      LZWDecode(bf, fp);
//      fclose(fp);
//      CloseBitFileInput(bf);
//      fprintf(stdout, "decoding done\n");//完成解码过程
//    }
//  }
//  else {	// otherwise
//    fprintf(stderr, "not supported operation\n");
//  }
//  return 0;
//}