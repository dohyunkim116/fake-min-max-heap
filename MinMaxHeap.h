#ifndef _MIN_MAX_HEAP_H_
#define _MIN_MAX_HEAP_H_

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;


template <typename T>
struct Element {
  T m_key;
  int m_twinIndex;
};

template <typename T>
struct FunctionPtr {
  typedef bool (*compare_op)(const Element<T> lhs, const Element<T> rhs);
};

template <typename T>
class Heap{

  template <typename U>
  friend class MinMaxHeap;

 private:
  Heap(int capacity = 0);
  Heap(const Heap<T>& other);
  ~Heap();
  //const Heap& operator=(const Heap& rhs);
  int bubbleUp(int emptyIndex, Element<T> e);
  void trickleDown(int currIndex, Element<T> r);
  void deleteAt(int index);
  T deleteTop();
  
  void copyHeap(const Heap<T>& other);
  bool isCeiling(int index){return index/2 == 0;}
  bool isFloor(int index){return index*2 > m_last;}


  int m_capacity;
  int m_size;
  Element<T>* m_array;
  int m_last;
  Heap* m_twin;
  typename FunctionPtr<T>::compare_op m_compare;
};  

template <typename T>
class MinMaxHeap {
 public:
  MinMaxHeap(int capacity = 0);
  ~MinMaxHeap();
  MinMaxHeap(const MinMaxHeap<T>& other);
  //const MinMaxHeap<T>& operator=(cost MinMaxHeap<T>& rhs);
  int size();
  void insert(const T& data);
  T deleteMin();
  T deleteMax();
  void dump();
  void locateMin(int pos, T& data, int& index);
  void locateMax(int pos, T& data, int& index);

 private:
  Heap<T>* m_MinHeapPtr;
  Heap<T>* m_MaxHeapPtr;
};

template <typename T>
static bool isLessThanEq(const Element<T> lhs, const Element<T> rhs);

template <typename T>
static bool isGreaterThanEq(const Element<T> lhs, const Element<T> rhs);


#endif

#include "MinMaxHeap.cpp"


