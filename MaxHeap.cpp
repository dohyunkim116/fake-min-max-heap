template <class T>
MaxHeap<T>::MaxHeap(int capacity)
  :m_capacity(capacity), m_size(0), m_last(0) {
  m_heap = new T[m_capacity+1];
}

template <class T>
MaxHeap<T>::~MaxHeap() {
  delete m_heap;
}

template <class T>
int MaxHeap<T>::bubbleUp(int empty, T n){
  if (empty == 1){
    return empty;
  }
  if (m_heap[empty/2] >= n) {
    return empty;
  }
  else {
    m_heap[empty] = m_heap[empty/2];
    return bubbleUp(empty/2, n);
  }
}

template <class T>
void MaxHeap<T>::insert(T n){
  ++m_last;
  if (m_last > m_capacity)
    throw out_of_range("No room");
  int empty;
  if (m_heap[empty/2] < n) {
    empty = bubbleUp(m_last, n);
    m_heap[empty] = n;
  }
  else {
    m_heap[m_last] = n;
  }
  ++m_size;
}

template <class T>
void MaxHeap<T>::trickleDown(int currIndex, T temp){
  T maxChild;
  int maxChildIndex;

  if (currIndex*2 > m_last){//at the bottom of heap
    m_heap[currIndex] = temp;
    return;
  }

  else {

    if (currIndex*2 == m_last){
      maxChild = m_heap[m_last];
      maxChildIndex = m_last;
    }

    else {

      if (m_heap[currIndex*2] >= m_heap[currIndex*2+1]){
        maxChild = m_heap[currIndex*2];
        maxChildIndex = currIndex*2;
      }

      else {
        maxChild = m_heap[currIndex*2+1];
        maxChildIndex = currIndex*2+1;
      }
    }
  }

  if (temp >= maxChild) {
    m_heap[currIndex] = temp;
    return;
  }

  m_heap[currIndex] = maxChild;
  trickleDown(maxChildIndex, temp);
}

template <class T>
int MaxHeap<T>::deleteMax(){
  T tempTop = m_heap[m_last];
  --m_last;
  --m_size;
  trickleDown(1, tempTop);
}


template <class T>
void MaxHeap<T>::dump(){
  cout << "size = " << m_size << ", "
       << "capacity = " << m_capacity << endl;

  for (int i = 1; i <= m_last; i++){
    cout << "Heap[" << i << "] = "
         << m_heap[i] << endl;
  }
}
