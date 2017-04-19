#ifndef _MIN_MAX_HEAP_CPP_
#define _MIN_MAX_HEAP_CPP_

template <typename T>
static bool isLessThanEq(const Element<T> lhs, const Element<T> rhs){
  return (lhs.m_key <= rhs.m_key);
}

template <typename T>
static bool isGreaterThanEq(const Element<T> lhs, const Element<T> rhs){
  return (lhs.m_key >= rhs.m_key);
}

template <typename T>
Heap<T>::Heap(int capacity)
  :m_capacity(capacity), m_size(0), m_last(0) {
  m_array = new Element<T>[m_capacity+1];
}

template <typename T>
Heap<T>::~Heap() {
  delete m_array;
}

template <typename T>
void Heap<T>::bubbleUp(int emptyIndex, Element<T> e){
  if (isCeiling(emptyIndex)) {
    m_array[emptyIndex] = e;
    return;
  }

  if (m_compare(m_array[emptyIndex/2],e)) {
    m_array[emptyIndex] = e;
  }
  else {
    m_array[emptyIndex] = m_array[emptyIndex/2];
    bubbleUp(emptyIndex/2, e);
  }
}

/*
template <typename T>
void Heap<T>::trickleDown(int currIndex, Element<T> temp){
  Element<T> minChild;
  int minChildIndex;

  if (currIndex*2 > m_last){//at the bottom of heap
    m_array[currIndex] = temp;
    return;
  }

  else {

    if (currIndex*2 == m_last){
      minChild = m_array[m_last];
      minChildIndex = m_last;
    }

    else {

      if (m_array[currIndex*2] <= m_array[currIndex*2+1]){//pass left and right
        minChild = m_array[currIndex*2];
        minChildIndex = currIndex*2;
      }

      else {
        minChild = m_array[currIndex*2+1];
        minChildIndex = currIndex*2+1;
      }
    }
  }

  if (temp <= minChild) {//pass left and right
    m_array[currIndex] = temp;
    return;
  }

  m_array[currIndex] = minChild;
  trickleDown(minChildIndex, temp);
}
*/

template <typename T>
MinMaxHeap<T>::MinMaxHeap(int capacity){
  m_MinHeapPtr = new Heap<T>(capacity);
  m_MaxHeapPtr = new Heap<T>(capacity);

  m_MinHeapPtr->m_twin = m_MaxHeapPtr;
  m_MaxHeapPtr->m_twin = m_MinHeapPtr;

  m_MinHeapPtr->m_compare = &isLessThanEq;
  m_MaxHeapPtr->m_compare = &isGreaterThanEq;
}

/*
template <typename T>
MinMaxHeap<T>::MinMaxHeap(const MinMaxHeap<T>& other){

}


template <typename T>
MinMaxHeap<T>::~MinMaxHeap(){

}

template <typename T>
const MinMaxHeap<T>& MinMaxHeap<T>::operator=(const MinMaxHeap<T>& rhs){
}
*/

template <typename T>
int MinMaxHeap<T>::size(){
  return m_MinHeapPtr->m_size;
}


template <typename T>
void MinMaxHeap<T>::insert(const T& data){
  m_MinHeapPtr->m_size++;
  m_MinHeapPtr->m_last++;
  if (m_MinHeapPtr->m_size > m_MinHeapPtr->m_capacity){
    throw out_of_range("Heap is full.");
  }
  Element<T> newE;
  newE.m_key = data;

  m_MinHeapPtr->bubbleUp(m_MinHeapPtr->m_last, newE); 
}

  /*
template <typename T>
T MinMaxHeap<T>::deleteMin(){
    if (m_size == 0) {
    throw out_of_range("0 elements in min heap");
  }
  T tempTop = m_array[m_last];
  --m_last;
  --m_size;
  trickleDown(1, tempTop);
}

template <typename T>
T MinMaxHeap<T>::deleteMax(){

}
  */


template <typename T>
void MinMaxHeap<T>::dump(){
  cout << "size = " << m_MinHeapPtr->m_size << ", "
       << "capacity = " << m_MinHeapPtr->m_capacity << endl;

  for (int i = 1; i <= m_MinHeapPtr->m_last; i++){
    cout << "MinHeap[" << i << "] = "
         << m_MinHeapPtr->m_array[i].m_key << endl;
  }
}


/*
template <typename T>
void MinMaxHeap<T>::locateMin(int pos, T& data, int& index){

}

template <typename T>
void MinMaxHeap<T>::locateMax(int pos, T& data, int& index){

}
*/

#endif
