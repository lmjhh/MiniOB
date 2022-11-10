//
// Created by lianyu on 2022/11/10.
//

#ifndef UNTITLED_FILECOMPRESS_H
#define UNTITLED_FILECOMPRESS_H
/*利用库中的优先级队列实现哈夫曼树，最后基于哈夫曼树最终实现文件压缩。
描述：
    1.统计文件中字符出现的次数，利用优先级队列构建Haffman树，生成Huffman编码。
    构造过程可以使用priority_queue辅助，每次pq.top()都可以取出权值（频数）最小的节点。每取出两个最小权值的节点，就new出一个新的节点，左右孩子分别指向它们。然后把这个新节点push进优先队列。
    2.压缩：利用Haffman编码对文件进行压缩，即在压缩文件中按顺序存入每个字符的Haffman编码。
    3.将文件中出现的字符以及它们出现的次数写入配置文件中，以便后续压缩使用。
    4.解压缩：利用配置文件重构Haffman树，对文件进行减压缩。
*/
#pragma once
#include "HuffmanTree.h"
#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

//获取文件的大小
unsigned long getFileSize(const char *path)
{
  unsigned long filesize = -1;
  FILE *fp;
  fp = fopen(path, "r");
  if (fp == NULL)
  {
    return filesize;
  }
  fseek(fp, 0L, SEEK_END);
  filesize = ftell(fp);
  fclose(fp);
  return filesize;
}

struct CharInfo
{
  unsigned char _ch;   //字符 a
  unsigned int _count; //字符次数 45
  string _code;        //对应的哈夫曼编码 011100

  bool operator!=(const CharInfo &info)
  {
    return _count != info._count;
  }
  CharInfo operator+(const CharInfo &info)
  {
    CharInfo ret;
    ret._count = _count + info._count;
    return ret;
  }
  bool operator>(const CharInfo &info)
  {
    return _count > info._count;
  }
};

class FileCompressAndUnCompress
{
  typedef HuffmanTreeNode<CharInfo> Node;
  struct TmpInfo
  {
    unsigned char _ch;   //字符
    unsigned int _count; //次数
  };

protected:
  CharInfo _infos[256];

public:
  //构造函数
  FileCompressAndUnCompress()
  {
    for (size_t i = 0; i < 256; ++i)
    {
      _infos[i]._ch = i;
      _infos[i]._count = 0;
    }
  }
  //获取哈夫曼编码
  void GenerateHuffmanCode(Node *root, string code)
  {
    if (root == NULL)
      return;
    //前序遍历生成编码
    if (root->_pLeft == NULL && root->_pRight == NULL)
    {
      _infos[(unsigned char)root->_weight._ch]._code = code; // 码值
      return;
    }
    GenerateHuffmanCode(root->_pLeft, code + '0');
    GenerateHuffmanCode(root->_pRight, code + '1');
  }
  void Compress(const char *file) // file:要压缩的文件
  {
    //获取文件的大小
    unsigned long fileSize = getFileSize(file);
    // 1.统计字符出现的次数
    FILE *fout = fopen(file, "rb");
    assert(fout);
    char ch = fgetc(fout);
    while (feof(fout) == 0) //文件结束，则返回值为1，否则为0
    {
      _infos[(unsigned char)ch]._count++; // 计算对应字符出现的频率
      ch = fgetc(fout);
    }
    // 2.生成Huffmantree 及code
    // 2.1 生成Huffmantree， 构建哈夫曼树
    HuffmanTree<CharInfo> tree(_infos, 256);

    string compressfile = file;
    compressfile += ".huffman";
    FILE *fin = fopen(compressfile.c_str(), "wb"); //打开压缩文件
    assert(fin);

    string code;
    //  2.2 根据哈夫曼树每个字符对应的code
    GenerateHuffmanCode(tree.GetRoot(), code);
    // 2.3 将码表写入压缩文件中
    int writeNum = 0;
    int objSize = sizeof(TmpInfo);
    for (size_t i = 0; i < 256; ++i)
    {
      if (_infos[i]._count > 0)
      {
        TmpInfo info;
        info._ch = _infos[i]._ch;
        info._count = _infos[i]._count;
//        printf("codec ch:%u, cout:%u\n", (unsigned char)info._ch, info._count);
        fwrite(&info, objSize, 1, fin);
        writeNum++;
      }
    }
    //把info._count = -1写进去作为数据字典的结束标志位
    TmpInfo info;
    info._count = -1;
    printf("code objSize:%d\n", objSize);
    fwrite(&info, objSize, 1, fin);

    // 3.开始压缩文件
    int writeCount = 0;
    int readCount = 0;
    //文件指针回到开头
    fseek(fout, 0, SEEK_SET); //文件指针、偏移量、参照位置
    ch = fgetc(fout);
    readCount++;
    unsigned char value = 0;
    size_t pos = 0;
    while (feof(fout) == 0) // 一个个字符读取
    {
      // 读取数据，查找对应编码
      string &code = _infos[(unsigned char)ch]._code; // 查找对应的编码
//      printf("code[%d]:%u:%s\n", readCount, (unsigned char)ch, code.c_str());
      // 根据对应的编码，修改对应的value值
      for (size_t i = 0; i < code.size(); ++i)
      {
        if (code[i] == '1')
        {
          value |= (1 << pos);
        }
        else if (code[i] != '0')
        {
          assert(false);
          printf("assert(false); ??????????");
        }
        ++pos;
        if (pos == 8)
        {
          writeCount++;
          // 够8个bit就存储一次，不用担心code是否全部读完
          fputc(value, fin);
          value = 0;
          pos = 0;
        }
      }
      readCount++;
      ch = fgetc(fout);
    }
    //最后可能不够8bit，也存储进去
    if (pos > 0)
    {
      writeCount++;
      fputc(value, fin); //写入压缩文件（fin）
    }
    printf("码表的大小:%d字节\n", objSize * (writeNum + 1));
    printf("压缩后的文件大小:%d字节\n", writeCount);
    unsigned long totalSize = writeCount + objSize * (writeNum + 1);
    printf("压缩后总文件大小:%lu字节, 原始文件大小:%lu字节, 压缩率:%0.2f\n",
           totalSize, fileSize, (float)(totalSize * 1.0 / fileSize));
    fclose(fout);
    fclose(fin);
  }
  void Uncompress(const char *file) //要解压缩的文件
  {
    string uncompressfile = file;
    //找到最后一个'.'
    size_t pos = uncompressfile.rfind('.');
    assert(pos != string::npos);
    //删除掉".huffman"后缀
    uncompressfile.erase(pos);
    // uncompressfile += ".unhuffman";
    FILE *fin = fopen(uncompressfile.c_str(), "wb"); //打开解压缩文件
    assert(fin);
    FILE *fout = fopen(file, "rb"); //打开压缩文件
    assert(fout);

    // 读入码表
    TmpInfo info;
    int cycleNum = 1;
    int objSize = sizeof(TmpInfo);
    fread(&info, objSize, 1, fout);

    while (info._count != -1) //-1为结束标志
    {
      _infos[(unsigned char)info._ch]._ch = info._ch;
      _infos[(unsigned char)info._ch]._count = info._count;

      fread(&info, objSize, 1, fout);
      cycleNum++;
    }

    //根据码表重建huaffman树
    HuffmanTree<CharInfo> tree(_infos, 256); //参数：数组，256个，无效值（出现0次）
    Node *root = tree.GetRoot();
    Node *cur = root;
    unsigned int n = root->_weight._count; //所有叶子节点的和（源文件字符的个数）
    char ch = fgetc(fout);                 //从fout(压缩文件)读字符
    int readCount = 0;

    while (ch != EOF || n > 0)
    {
      for (size_t i = 0; i < 8; ++i)
      {
        if ((ch & (1 << i)) == 0)
          cur = cur->_pLeft; // 往左边找
        else
          cur = cur->_pRight; // 往右边找
        if (cur->_pLeft == NULL && cur->_pRight == NULL)
        {
          // cout << cur->_weight._ch;
          //找到对应的字符，写入解压缩文件
          fputc(cur->_weight._ch, fin);
          cur = root;
          if (--n == 0)
            break;
        }
      }
      ch = fgetc(fout);
    }
    printf("解压缩完成\n");
    fclose(fin);
    fclose(fout);
  }
};

#endif //UNTITLED_FILECOMPRESS_H
