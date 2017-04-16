#ifndef _MIN_HEAP_H_
#define _MIN_HEAP_H_

#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class MinHeap{
public:
  MinHeap(int capacity = 0);
  ~MinHeap();
  void insert(T n);
  int deleteMin();
  void dump();
  int size() {return m_size;}
  
private:
  int bubbleUp(int empty, T n);
  void trickleDown(int currIndex);

  int m_capacity;
  int m_size;
  T* m_heap;
  int m_last;
};

#include "MinHeap.cpp"

#endif

