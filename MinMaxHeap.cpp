#ifndef _MIN_MAX_HEAP_CPP_
#define _MIN_MAX_HEAP_CPP_

//isLessThanEq: defines the behvaior of Min Heap
//pre: Two Element objects to compare.
//     First param is left hand side.
//     Second param is right hand side.
//post: true if m_key of lhs is less than equal to m_key of rhs
//      false o.w.
template <typename T>
static bool isLessThanEq(const Element<T> lhs, const Element<T> rhs){
  return (lhs.m_key <= rhs.m_key);
}

//isGreaterThanEq: defines the behvaior of Max Heap
//pre: Two Element objects to compare.
//     First param is left hand side.
//     Second param is right hand side.
//post: true if the m_key of lhs is greater than equal to m_key of rhs
//      false o.w.
template <typename T>
static bool isGreaterThanEq(const Element<T> lhs, const Element<T> rhs){
  return (lhs.m_key >= rhs.m_key);
}

//construct Heap object with given capacity
template <typename T>
Heap<T>::Heap(int capacity)
  :m_capacity(capacity), m_size(0) {

  //one bigger than given capacity because 
  //index 0 of an array holds nothing
  m_array = new Element<T>[m_capacity+1];
}

//destructor for a Heap object
template <typename T>
Heap<T>::~Heap() {
  delete [] m_array;
  m_array = NULL;
}

//helper function that is used in copy constructor
//and overloaded assignment operator of a Heap object
template <typename T>
void Heap<T>::copyHeap(const Heap<T>& other){
  m_array = new Element<T>[m_capacity+1];
  for (int i = 1; i <= m_size; ++i){
    m_array[i] = other.m_array[i];
  }
}

//copy constructor of a Heap object
//pre: other templated Heap object to be used
//     to construct a new Heap object
///post: new deep copy of Heap<T> other
template <typename T>
Heap<T>::Heap(const Heap<T>& other)
  : m_capacity(other.m_capacity), m_size(other.m_size),
    m_compare(other.m_compare), m_twin(NULL) {
  copyHeap(other);
}

//overload assignment operator of a heap
//pre: Heap object to be assigned.
//     templated Heap object for assigning.
//post: Heap object that is assigned is a 
//      deep copy of Heap<T> rhs
template <typename T>
const Heap<T>& Heap<T>::operator=(const Heap<T>& rhs){

  //checks for self assignment
  if (this == &rhs){
    return rhs;
  }

  this->~Heap();

  //update member variables
  m_capacity = rhs.m_capacity;
  m_size = rhs.m_size;
  m_compare = rhs.m_compare;

  copyHeap(rhs);
}

//updateTwinIndex: when an Element in one heap
//                 is moved, update its updated
//                 index in a twin element in
//                 a twin heap
//pre: Element changes its index after insert 
//     or delete operation of a heap.
//     Updated array index is passed as a param.
//post: Twin element has a correct array index of 
//      a updated index.
template <typename T>
void Heap<T>::updateTwinIndex(int index){
  int twinIndex = m_array[index].m_twinIndex;
  m_twin->m_array[twinIndex].m_twinIndex = index;
}

//bubbleUp: Carray an element up a level/levels of a heap
//          until heap regains correct ordering.
//pre: Insert or deleteAt is executed.
//     emptyIndex - index where bubbling occurs
//     Element e - 1) new element when insert
//               - 2) replacement element, which is a
//                    last element in an array when deleteAt
//during: If some element has been moved to a new position,
//        then its twin element is updated with a new position
//post: -Element e is in a correct position of a heap.
//      -Returns an index of where Element e is in an array
template <typename T>
int Heap<T>::bubbleUp(int emptyIndex, Element<T> e){

  //At the top of a heap
  if (isCeiling(emptyIndex)) {
    m_array[emptyIndex] = e;
    return emptyIndex;
  }

  //Heap order is correct
  if (m_compare(m_array[emptyIndex/2],e)) {
    m_array[emptyIndex] = e;
    return emptyIndex;
  }

  //Heap order is incorrect
  else {
    m_array[emptyIndex] = m_array[emptyIndex/2];
    updateTwinIndex(emptyIndex);
    return bubbleUp(emptyIndex/2, e);
  }
}

//trickleDown: Carry an element down heap level/levels until
//             correct heap ordering is achieved.
//pre: deleteTop or deleteAt is executed
//     Element<T> r - replacement element, which is a last element
//                    in an array
//     currIndex - current index where replacement element resides
//                 in an array
template <typename T>
void Heap<T>::trickleDown(int currIndex, Element<T> r){
  Element<T> compChild;//child element to compare to parent
  int compChildIndex;

  //at the bottom of a heap
  if (isFloor(currIndex)){
    m_array[currIndex] = r;
    updateTwinIndex(currIndex);
    return;
  }

  //There is a room for r to trickle down a heap, so
  //find child key to compare to a parent key
  else {

    //left child is the last elment 
    if (currIndex*2 == m_size){
      compChild = m_array[m_size];
      compChildIndex = m_size;
    }

    else {

      //m_array[currIndex*2] <= m_array[currIndex*2+1] if Min Heap
      //m_array[currIndex*2] >= m_array[currIndex*2+1] if Max Heap
      if (m_compare(m_array[currIndex*2],m_array[currIndex*2+1])){
        compChild = m_array[currIndex*2];
        compChildIndex = currIndex*2;
      }

      else {
        compChild = m_array[currIndex*2+1];
        compChildIndex = currIndex*2+1;
      }
    }
  }

  //r is in correct index, so put it in
  //a array in index, currIndex.
  if (m_compare(r,compChild)) {
    m_array[currIndex] = r;
    updateTwinIndex(currIndex);
    return;
  }

  //r is not in correct index, so move
  //compChild to currIndex and trickle down r
  m_array[currIndex] = compChild;
  updateTwinIndex(currIndex);
  trickleDown(compChildIndex, r);
}

//MinMaxHeap object constructor
template <typename T>
MinMaxHeap<T>::MinMaxHeap(int capacity){
  m_MinHeapPtr = new Heap<T>(capacity);
  m_MaxHeapPtr = new Heap<T>(capacity);

  m_MinHeapPtr->m_twin = m_MaxHeapPtr;
  m_MaxHeapPtr->m_twin = m_MinHeapPtr;

  m_MinHeapPtr->m_compare = &isLessThanEq;
  m_MaxHeapPtr->m_compare = &isGreaterThanEq;
}

//destructor for MinMaxHeap
template <typename T>
MinMaxHeap<T>::~MinMaxHeap(){
  delete m_MinHeapPtr;
  m_MinHeapPtr = NULL;
  delete m_MaxHeapPtr;
  m_MaxHeapPtr = NULL;
}

//copy constructor for MinMaxHeap
template <typename T>
MinMaxHeap<T>::MinMaxHeap(const MinMaxHeap<T>& other){
  m_MinHeapPtr = new Heap<T>(*other.m_MinHeapPtr);
  m_MaxHeapPtr = new Heap<T>(*other.m_MaxHeapPtr);

  m_MinHeapPtr->m_twin = m_MaxHeapPtr;
  m_MaxHeapPtr->m_twin = m_MinHeapPtr;
}

//overloaded assignment operator for MinMaxHeap
template <typename T>
const MinMaxHeap<T>& MinMaxHeap<T>::operator=(const MinMaxHeap<T>& rhs){
  
  //checks for self assignment
  if (this == &rhs){
    return rhs;
  }

  //use overloaded assignment operator of Heap
  *m_MinHeapPtr = *rhs.m_MinHeapPtr;
  *m_MaxHeapPtr = *rhs.m_MaxHeapPtr;

  //Note: no need to update m_twin of MinHeap and MaxHeap
}


//size: returns size of a MinMaxHeap
//pre: Min Heap object
template <typename T>
int MinMaxHeap<T>::size(){
  return m_MinHeapPtr->m_size;
}

//insert: insert given data
//pre: MinMaxHeap object with m_capacity > 0
//post: data is in MinMaxHeap
template <typename T>
void MinMaxHeap<T>::insert(const T& data){
  if (m_MinHeapPtr->m_size+1 > m_MinHeapPtr->m_capacity){
    throw out_of_range("Heap is full.");
  }

  //create Element object to be inserted into 
  //Min Heap and Max Heap
  Element<T> minElement, maxElement;
  minElement.m_key = data;
  maxElement.m_key = data;
  
  //insert Element into Min Heap
  m_MinHeapPtr->m_size++;
  int minIndex = m_MinHeapPtr->bubbleUp(m_MinHeapPtr->m_size, 
					minElement);

  //update m_twinIndex of twin element in Max Heap
  maxElement.m_twinIndex = minIndex;
  
  //insert Element into Max Heap
  m_MaxHeapPtr->m_size++;
  int maxIndex = m_MaxHeapPtr->bubbleUp(m_MaxHeapPtr->m_size,
					maxElement);


  //update m_twinIndex of twin element in Min Heap
  m_MaxHeapPtr->m_twin->m_array[minIndex].m_twinIndex = maxIndex;
}

//deleteAt: delete an element in an array 
//          at a given index
//pre: -index of an element to be deleted
//     -deleteTop is executed
//post: An elment at a given index in a heap is
//      removed
template <typename T>
void Heap<T>::deleteAt(int index){

  Element<T> replacement = m_array[m_size];
  --m_size;

  //element to be removed is the last element
  //of an array
  if (index == m_size+1){
    return;
  }

  //checks if a given index is top level of a heap
  if (isCeiling(index)){
    trickleDown(index, replacement);
  }

  //checks if a given index is a bottom level of a heap
  else if (isFloor(index)){
    int newIndex = bubbleUp(index, replacement);
    updateTwinIndex(newIndex);
  }

  //checks if a key of replacement element is:
  //1) Min Heap: less than equal to parent key
  //2) Max Heap: greater than equal to parent key
  else if (m_compare(replacement,m_array[index/2])){
    int newIndex = bubbleUp(index, replacement);
    updateTwinIndex(newIndex);
  }
  
  //otherwise, must trickleDown
  else {
    trickleDown(index, replacement);
  }
}
//deleteTop: delete top level element of a calling heap
//pre: - calling heap must have > 0 elements
//     - deleteMax or deleteMin of MinMaxHeap class is 
//       executed
//post: - Either minimum or maximum elment of a heap is removed
//        as well as corresponding twin element in twin heap is
//        removed.
//      - Removed top element's key is returned.
template <typename T>
T Heap<T>::deleteTop(){
  if (m_size == 0) {
    throw out_of_range("0 elements in MinMaxHeap");
  }
  Element<T> replacement = m_array[m_size];
  Element<T> top = m_array[1];
  --m_size;
  trickleDown(1, replacement);
  m_twin->deleteAt(top.m_twinIndex);
  return top.m_key;
}

//deleteMin: delete minimum element of MinMaxHeap
//pre: At least 1 element in a min heap
//post: - Minimum element is removed from a min heap, thus
//        from MinMaxHeap as well.
//      - Removed minimum element's key is returned.
template <typename T>
T MinMaxHeap<T>::deleteMin(){
  return m_MinHeapPtr->deleteTop();
}

//deleteMax: delete maximum element of MinMaxHeap
//pre: At least 1 element in a max heap
//post: - Maxium element is removed from a max heap, thus
//        from MinMaxHeap as well.
//      - Removed maximum element's key is returned.
template <typename T>
T MinMaxHeap<T>::deleteMax(){
  return m_MaxHeapPtr->deleteTop();
}

//dump: prints out internals of Min and Max Heap
//      of a MinMaxHeap
//pre: MinMaxHeap object
template <typename T>
void MinMaxHeap<T>::dump(){

  cout << "\n... MinMaxHeap::dump() ..." << endl;

  cout << "\n------------Min Heap------------" << endl;
  cout << "size = " << m_MinHeapPtr->m_size << ", "
       << "capacity = " << m_MinHeapPtr->m_capacity << endl;

  for (int i = 1; i <= m_MinHeapPtr->m_size; i++){
    cout << "Heap[" << i << "] = "
         << '(' << m_MinHeapPtr->m_array[i].m_key << ','
	 << m_MinHeapPtr->m_array[i].m_twinIndex << ")\n";
  }

  cout << "\n------------Max Heap------------" << endl;
  cout << "size = " << m_MaxHeapPtr->m_size << ", "
       << "capacity = " << m_MaxHeapPtr->m_capacity << endl;

  for (int i = 1; i <= m_MaxHeapPtr->m_size; i++){
    cout << "Heap[" << i << "] = "
         << '(' << m_MaxHeapPtr->m_array[i].m_key << ','
	 << m_MaxHeapPtr->m_array[i].m_twinIndex << ")\n";
  }
  cout << "--------------------------------\n" << endl;
}

//locateMin: retrieve key and index of an elment at a given
//           position of a Min Heap
//pre: 0 < pos < m_size of Min Heap
//     data passed by reference to retrieve the key
//     index passed by reference to retrieve the index
template <typename T>
void MinMaxHeap<T>::locateMin(int pos, T& data, int& index){
  if (pos > m_MinHeapPtr->m_size || pos < 1) {
    throw out_of_range("Position is out of bounds.");
  }
  data = m_MinHeapPtr->m_array[pos].m_key;
  index = m_MinHeapPtr->m_array[pos].m_twinIndex;
}

//locateMax: retrieve key and index of an elment at a given
//           position of a Max Heap
//pre: 0 < pos < m_size of Max Heap
//     data passed by reference to retrieve the key
//     index passed by reference to retrieve the index
template <typename T>
void MinMaxHeap<T>::locateMax(int pos, T& data, int& index){
  if (pos > m_MaxHeapPtr->m_size || pos < 1) {
    throw out_of_range("Position is out of bounds.");
  }
  data = m_MaxHeapPtr->m_array[pos].m_key;
  index = m_MaxHeapPtr->m_array[pos].m_twinIndex;
}


#endif
