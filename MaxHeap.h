#ifndef _MAX_HEAP_H_
#define _MAX_HEAP_H_

#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class MaxHeap{
public:
  MaxHeap(int capacity = 0);
  ~MaxHeap();
  void insert(T n);
  int deleteMax();
  void dump();
  int size() {return m_size;}
  
private:
  int bubbleUp(int empty, T n);
  void trickleDown(int currIndex, T temp);

  int m_capacity;
  int m_size;
  T* m_heap;
  int m_last;
};

#include "MaxHeap.cpp"

#endif

