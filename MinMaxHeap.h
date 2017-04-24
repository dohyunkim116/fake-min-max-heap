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

//Create struct to allow templated typedef
template <typename T>
struct FunctionPtr {
  typedef bool (*compare_op)(const Element<T> lhs, const Element<T> rhs);
};


template <typename T>
class Heap{

  template <typename U>
  friend class MinMaxHeap;

 private:
  Heap(int capacity = 0);//constructor
  Heap(const Heap<T>& other);//copy constructor
  ~Heap();//destructor

  //overloaded assignment operator
  const Heap<T>& operator=(const Heap<T>& rhs);
  
  //used in insert, and deleteAt to stay as Heap
  int bubbleUp(int emptyIndex, Element<T> e);

  //used in deleteTop, and deleteAt to stay as Heap
  void trickleDown(int currIndex, Element<T> r);

  //used in deleteTop to delete twin element in twin Heap
  void deleteAt(int index);

  //used in deleteMin and deleteMax of MinMaxHeap class
  T deleteTop();
  
  //used in copy constructor and overloaded assignment operator
  void copyHeap(const Heap<T>& other);

  //check if we are currently at the top level of a heap
  bool isCeiling(int index){return index/2 == 0;}

  //check if we are currently at the bottom level of a heap
  bool isFloor(int index){return index*2 > m_last;}

  //update twin element of a twin heap when current heap 
  //is modified
  void updateTwinIndex(int index);

  //member variables
  int m_capacity;
  int m_size;
  Element<T>* m_array;//array of Element object
  int m_last;
  Heap* m_twin;//pointer to twin heap
  typename FunctionPtr<T>::compare_op m_compare;
};  


template <typename T>
class MinMaxHeap {
 public:
  MinMaxHeap(int capacity = 0);
  ~MinMaxHeap();
  MinMaxHeap(const MinMaxHeap<T>& other);
  const MinMaxHeap<T>& operator=(const MinMaxHeap<T>& rhs);
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


