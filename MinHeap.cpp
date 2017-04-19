#ifndef _MIN_HEAP_CPP_
#define _MIN_HEAP_CPP_

template <class T>
MinHeap<T>::MinHeap(int capacity)
  :m_capacity(capacity), m_size(0), m_last(0) {
  m_heap = new T[m_capacity+1];
}

template <class T>
MinHeap<T>::~MinHeap() {
  delete [] m_heap;
}

template <class T>
void MinHeap<T>::bubbleUp(int emptySlot, T n){
  if (isCeiling(emptySlot)) {
    m_heap[emptySlot] = n;
    return;
  }
  
  if (m_heap[emptySlot/2] <= n) {
    m_heap[emptySlot] = n;
  }
  else {
    m_heap[emptySlot] = m_heap[emptySlot/2];
    bubbleUp(emptySlot/2, n);
  }
}

template <class T>
void MinHeap<T>::insert(T n){
  ++m_last;
  ++m_size;
  if (m_size > m_capacity)
    throw out_of_range("No room");
  bubbleUp(m_last,n);
}

template <class T>
void MinHeap<T>::trickleDown(int currIndex, T replacement){ 
  T minChild;
  int minChildIndex;
  
  if (isFloor(currIndex)){
    m_heap[currIndex] = replacement;
    return;
  }

  else {

    if (currIndex*2 == m_last){
      minChild = m_heap[m_last];
      minChildIndex = m_last;
    }

    else {

      if (m_heap[currIndex*2] <= m_heap[currIndex*2+1]){
	minChild = m_heap[currIndex*2];
	minChildIndex = currIndex*2;
      }

      else {
	minChild = m_heap[currIndex*2+1];
	minChildIndex = currIndex*2+1;
      }
    }  
  }

  if (replacement <= minChild) {
    m_heap[currIndex] = replacement;
    return;
  }

  m_heap[currIndex] = minChild;  
  trickleDown(minChildIndex, replacement);
}

template <class T>
int MinHeap<T>::deleteMin(){
  if (m_size == 0) {
    throw out_of_range("0 elements in min heap");
  }
  T replacement = m_heap[m_last];
  --m_last;
  --m_size;
  trickleDown(1, replacement);
}


template <class T>
void MinHeap<T>::deleteAt(int index){
  if (m_size == 0){
    throw out_of_range("0 elements in min heap");
  }
  T replacement = m_heap[m_last];
  --m_last;
  --m_size;
  
  if (index == m_last+1){
    return;
  }

  if (isCeiling(index)){
    trickleDown(index, replacement);
  }
  else if (isFloor(index)){
    bubbleUp(index, replacement);
  }
  else if (m_heap[index/2] > replacement){
    bubbleUp(index, replacement);
  }
  else {
    trickleDown(index, replacement);
  }
}



template <class T>
void MinHeap<T>::dump(){
  cout << "size = " << m_size << ", "
       << "capacity = " << m_capacity << endl;

  for (int i = 1; i <= m_last; i++){
    cout << "Heap[" << i << "] = "
         << m_heap[i] << endl;
  }
}

#endif
