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
  void deleteAt(int index);
  
private:
  void bubbleUp(int emptySlot, T n);
  void trickleDown(int currIndex, T replacement);
  
  bool isCeiling(int index){return index/2 == 0;}
  bool isFloor(int index){return index*2 > m_last;}

  int m_capacity;
  int m_size;
  T* m_heap;
  int m_last;
};

#endif

#include "MinHeap.cpp"

