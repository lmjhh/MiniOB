//
// Created by lianyu on 2022/11/10.
//

#ifndef UNTITLED_HUFFMANTREE_H
#define UNTITLED_HUFFMANTREE_H

#pragma once
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <class W>
struct HuffmanTreeNode
{
  HuffmanTreeNode(const W &weight)
          : _pLeft(NULL), _pRight(NULL), _pParent(NULL), _weight(weight)
  {
  }
  HuffmanTreeNode<W> *_pLeft;
  HuffmanTreeNode<W> *_pRight;
  HuffmanTreeNode<W> *_pParent;
  //权值
  W _weight;
};

template <class W>
class HuffmanTree
{
  typedef HuffmanTreeNode<W> *PNode;

private:
  //根节点
  PNode _pRoot;

public:
  HuffmanTree()
          : _pRoot(NULL)
  {
  }
  HuffmanTree(W *array, size_t size)
  {
    _CreateHuffmantree(array, size);
  }
  void _Destroy(PNode &pRoot)
  {
    //后序
    if (pRoot)
    {
      _Destroy(pRoot->_pLeft);
      _Destroy(pRoot->_pRight);
      delete pRoot;
      pRoot = NULL;
    }
  }
  ~HuffmanTree()
  {
    _Destroy(_pRoot);
  }
  PNode GetRoot()
  {
    return _pRoot;
  }

private:
  //构建哈夫曼树
  void _CreateHuffmantree(W *array, size_t size)
  {

    //小根堆
    struct PtrNodeCompare
    {
      bool operator()(PNode n1, PNode n2) //重载“（）”
      {
        return n1->_weight > n2->_weight;
      }
    };
    priority_queue<PNode, vector<PNode>, PtrNodeCompare> hp;

    for (size_t i = 0; i < size; ++i)
    {
      hp.push(new HuffmanTreeNode<W>(array[i])); // 数据入堆
    }
    //空堆
    if (hp.empty())
    {
      _pRoot = NULL;
    }

    while (hp.size() > 1) // 取两个出来只回收1个
    {
      PNode pLeft = hp.top();
      hp.pop();
      PNode pRight = hp.top();
      hp.pop();
      PNode pParent = new HuffmanTreeNode<W>(pLeft->_weight + pRight->_weight); //左加右的权值，作为新节点
      pParent->_pLeft = pLeft;
      pLeft->_pParent = pParent;

      pParent->_pRight = pRight;
      pRight->_pParent = pParent;
      hp.push(pParent);
    }
    _pRoot = hp.top(); // 根节点在堆顶
  }
};


#endif //UNTITLED_HUFFMANTREE_H
