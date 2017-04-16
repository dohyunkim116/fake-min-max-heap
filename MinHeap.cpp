template <class T>
MinHeap<T>::MinHeap(int capacity)
  :m_capacity(capacity), m_size(0), m_last(0) {
  m_heap = new T[m_capacity+1];
}

template <class T>
MinHeap<T>::~MinHeap() {
  delete m_heap;
}

template <class T>
int MinHeap<T>::bubbleUp(int empty, T n){
  if (empty == 1){
    return empty;
  }
  if (m_heap[empty/2] <= n) {
    return empty;
  }
  else {
    m_heap[empty] = m_heap[empty/2];
    return bubbleUp(empty/2, n);
  }
}

template <class T>
void MinHeap<T>::insert(T n){
  ++m_last;
  if (m_last > m_capacity)
    throw out_of_range("No room");
  int empty;
  if (m_heap[empty/2] > n) {
    empty = bubbleUp(m_last, n);
    m_heap[empty] = n;
  }
  else {
    m_heap[m_last] = n;
  }
  ++m_size;
}

template <class T>
void MinHeap<T>::trickleDown(int currIndex, T temp){ 
  T minChild;
  int minChildIndex;
  
  if (currIndex*2 > m_last){//at the bottom of heap
    m_heap[currIndex] = temp;
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

  if (temp <= minChild) {
    m_heap[currIndex] = temp;
    return;
  }

  m_heap[currIndex] = minChild;  
  trickleDown(minChildIndex, temp);
}

template <class T>
int MinHeap<T>::deleteMin(){
  if (m_size == 0) {
    throw out_of_range("0 elements in min heap");
  }
  T tempTop = m_heap[m_last];
  --m_last;
  --m_size;
  trickleDown(1, tempTop);
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
