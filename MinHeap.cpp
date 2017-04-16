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
int MinHeap<T>::bubbleUp(int empty, int n){
  if (empty == 0){
    return empty+1;
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
void MinHeap<T>::dump(){
  cout << "size = " << m_size << ", "
       << "capacity = " << m_capacity << endl;

  for (int i = 1; i <= m_last; i++){
    cout << "Heap[" << i << "] = "
         << m_heap[i] << endl;
  }
}
