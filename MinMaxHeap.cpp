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
  delete [] m_array;
}

template <typename T>
void Heap<T>::copyHeap(const Heap<T>& other){
  m_array = new Element<T>[m_capacity+1];
  for (int i = 1; i <= m_size; ++i){
    m_array[i] = other.m_array[i];
  }
}

template <typename T>
Heap<T>::Heap(const Heap<T>& other)
  : m_capacity(other.m_capacity), m_size(other.m_size), m_last(other.m_last),
    m_compare(other.m_compare), m_twin(NULL) {
  copyHeap(other);
}

template <typename T>
int Heap<T>::bubbleUp(int emptyIndex, Element<T> e){
  if (isCeiling(emptyIndex)) {
    m_array[emptyIndex] = e;
    return emptyIndex;
  }

  if (m_compare(m_array[emptyIndex/2],e)) {
    m_array[emptyIndex] = e;
    return emptyIndex;
  }
  else {
    m_array[emptyIndex] = m_array[emptyIndex/2];
    int twinIndex = m_array[emptyIndex].m_twinIndex;
    m_twin->m_array[twinIndex].m_twinIndex = emptyIndex;
    return bubbleUp(emptyIndex/2, e);
  }
}

template <typename T>
void Heap<T>::trickleDown(int currIndex, Element<T> r){
  Element<T> minChild;
  int minChildIndex;

  if (isFloor(currIndex)){//at the bottom of heap
    m_array[currIndex] = r;
    int twinIndex = m_array[currIndex].m_twinIndex;
    m_twin->m_array[twinIndex].m_twinIndex = currIndex;
    return;
  }

  else {

    if (currIndex*2 == m_last){
      minChild = m_array[m_last];
      minChildIndex = m_last;
    }

    else {

      if (m_compare(m_array[currIndex*2],m_array[currIndex*2+1])){
        minChild = m_array[currIndex*2];
        minChildIndex = currIndex*2;
      }

      else {
        minChild = m_array[currIndex*2+1];
        minChildIndex = currIndex*2+1;
      }
    }
  }

  if (m_compare(r,minChild)) {
    m_array[currIndex] = r;
    int twinIndex = m_array[currIndex].m_twinIndex;
    m_twin->m_array[twinIndex].m_twinIndex = currIndex;
    return;
  }

  m_array[currIndex] = minChild;
  int twinIndex = m_array[currIndex].m_twinIndex;
  m_twin->m_array[twinIndex].m_twinIndex = currIndex;
  trickleDown(minChildIndex, r);
}

template <typename T>
MinMaxHeap<T>::MinMaxHeap(int capacity){
  m_MinHeapPtr = new Heap<T>(capacity);
  m_MaxHeapPtr = new Heap<T>(capacity);

  m_MinHeapPtr->m_twin = m_MaxHeapPtr;
  m_MaxHeapPtr->m_twin = m_MinHeapPtr;

  m_MinHeapPtr->m_compare = &isLessThanEq;
  m_MaxHeapPtr->m_compare = &isGreaterThanEq;
}

template <typename T>
MinMaxHeap<T>::~MinMaxHeap(){
  delete m_MinHeapPtr;
  m_MinHeapPtr = NULL;
  delete m_MaxHeapPtr;
  m_MaxHeapPtr = NULL;
}

template <typename T>
MinMaxHeap<T>::MinMaxHeap(const MinMaxHeap<T>& other){
  m_MinHeapPtr = new Heap<T>(*other.m_MinHeapPtr);
  m_MaxHeapPtr = new Heap<T>(*other.m_MaxHeapPtr);

  m_MinHeapPtr->m_twin = m_MaxHeapPtr;
  m_MaxHeapPtr->m_twin = m_MinHeapPtr;
}


//template <typename T>
//const MinMaxHeap<T>& MinMaxHeap<T>::operator=(const MinMaxHeap<T>& rhs){
//}



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
  Element<T> minElement, maxElement;
  minElement.m_key = data;
  maxElement.m_key = data;

  int minIndex = m_MinHeapPtr->bubbleUp(m_MinHeapPtr->m_last, 
					minElement);
  maxElement.m_twinIndex = minIndex;

  m_MaxHeapPtr->m_size++;
  m_MaxHeapPtr->m_last++;
  int maxIndex = m_MaxHeapPtr->bubbleUp(m_MaxHeapPtr->m_last,
					maxElement);
  m_MaxHeapPtr->m_twin->m_array[minIndex].m_twinIndex = maxIndex;
}

template <typename T>
void Heap<T>::deleteAt(int index){
  Element<T> replacement = m_array[m_last];
  --m_last;
  --m_size;

  if (index == m_last+1){
    return;
  }

  if (isCeiling(index)){
    trickleDown(index, replacement);
  }
  else if (isFloor(index)){
    int newIndex = bubbleUp(index, replacement);
    int twinIndex = m_array[newIndex].m_twinIndex;
    m_twin->m_array[twinIndex].m_twinIndex = newIndex;
  }
  else if (m_compare(replacement,m_array[index/2])){
    int newIndex = bubbleUp(index, replacement);
    int twinIndex = m_array[newIndex].m_twinIndex;
    m_twin->m_array[twinIndex].m_twinIndex = newIndex;
  }
  else {
    trickleDown(index, replacement);
  }
}

template <typename T>
T Heap<T>::deleteTop(){
  if (m_size == 0) {
    throw out_of_range("0 elements in MinMaxHeap");
  }
  Element<T> replacement = m_array[m_last];
  Element<T> top = m_array[1];
  --m_last;
  --m_size;
  trickleDown(1, replacement);
  m_twin->deleteAt(top.m_twinIndex);
  return top.m_key;
}

template <typename T>
T MinMaxHeap<T>::deleteMin(){
  return m_MinHeapPtr->deleteTop();
}

template <typename T>
T MinMaxHeap<T>::deleteMax(){
  return m_MaxHeapPtr->deleteTop();
}


template <typename T>
void MinMaxHeap<T>::dump(){

  cout << "\n... MinMaxHeap::dump() ..." << endl;

  cout << "\n------------Min Heap------------" << endl;
  cout << "size = " << m_MinHeapPtr->m_size << ", "
       << "capacity = " << m_MinHeapPtr->m_capacity << endl;

  for (int i = 1; i <= m_MinHeapPtr->m_last; i++){
    cout << "Heap[" << i << "] = "
         << '(' << m_MinHeapPtr->m_array[i].m_key << ','
	 << m_MinHeapPtr->m_array[i].m_twinIndex << ")\n";
  }

  cout << "\n------------Max Heap------------" << endl;
  cout << "size = " << m_MaxHeapPtr->m_size << ", "
       << "capacity = " << m_MaxHeapPtr->m_capacity << endl;

  for (int i = 1; i <= m_MaxHeapPtr->m_last; i++){
    cout << "Heap[" << i << "] = "
         << '(' << m_MaxHeapPtr->m_array[i].m_key << ','
	 << m_MaxHeapPtr->m_array[i].m_twinIndex << ")\n";
  }
  cout << "--------------------------------\n" << endl;
}


template <typename T>
void MinMaxHeap<T>::locateMin(int pos, T& data, int& index){
  if (pos > m_MinHeapPtr->m_size || pos < 1) {
    throw out_of_range("Position is out of bounds.");
  }
  data = m_MinHeapPtr->m_array[pos].m_key;
  index = m_MinHeapPtr->m_array[pos].m_twinIndex;
}

template <typename T>
void MinMaxHeap<T>::locateMax(int pos, T& data, int& index){
  if (pos > m_MaxHeapPtr->m_size || pos < 1) {
    throw out_of_range("Position is out of bounds.");
  }
  data = m_MaxHeapPtr->m_array[pos].m_key;
  index = m_MaxHeapPtr->m_array[pos].m_twinIndex;
}


#endif
