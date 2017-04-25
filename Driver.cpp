#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdexcept>
#include "MinMaxHeap.h"
#include <set>
using namespace std ;

//sanityCheck: provided by Dr. Chang
template <typename T>
void sanityCheck(MinMaxHeap<T>& H) {
  int n = H.size() ;
  T minKey, maxKey, leftKey, rightKey ;
  int minPos, maxPos, pos ;
   
  bool passed=true ;

  cout << "Sanity Check minHeap...\n" ;

  for (int i=1 ; i<=n ; i++) {
    H.locateMin(i,minKey,maxPos) ; 
    H.locateMax(maxPos,maxKey,minPos) ; 
      
    if (minKey != maxKey) {
      passed = false ;
      cout << "Key mismatch at i = " << i << ": "
	   << "minKey = " << minKey << ", " 
	   << "minPos = " << minPos << ", " 
	   << "maxKey = " << maxKey << ", " 
	   << "maxPos = " << maxPos 
	   << endl ;
    }

    if (minPos != i) {
      passed = false ;
      cout << "Position mismatch at i = " << i << ": "
	   << "minKey = " << minKey << ", " 
	   << "minPos = " << minPos << ", " 
	   << "maxKey = " << maxKey << ", " 
	   << "maxPos = " << maxPos 
	   << endl ;
    }

    if (2*i <= n) {  // has left child
      H.locateMin(2*i,leftKey,pos) ;
      if (leftKey < minKey) {  // left child smaller than root 
	passed = false ;
	cout << "Bad heap condition at i = " << i << ": "
	     << "root key = " << minKey << ", " 
	     << "left key = " << leftKey 
	     << endl ;
      }
    }  

    if (2*i+1 <= n) {  // has right child
      H.locateMin(2*i+1,rightKey,pos) ;
      if (rightKey < minKey) {  // right child smaller than root 
	passed = false ;
	cout << "Bad heap condition at i = " << i << ": "
	     << "root key = " << minKey << ", " 
	     << "right key = " << rightKey 
	     << endl ;
      }
    }  

  }  // end of for (...)


  cout << "Sanity Check maxHeap...\n" ;

  for (int i=1 ; i<=n ; i++) {
    H.locateMax(i,maxKey,minPos) ; 
    H.locateMin(minPos,minKey,maxPos) ; 
      
    if (minKey != maxKey) {
      passed = false ;
      cout << "Key mismatch at i = " << i << ": "
	   << "minKey = " << minKey << ", " 
	   << "minPos = " << minPos << ", " 
	   << "maxKey = " << maxKey << ", " 
	   << "maxPos = " << maxPos 
	   << endl ;
    }

    if (maxPos != i) {
      passed = false ;
      cout << "Position mismatch at i = " << i << ": "
	   << "minKey = " << minKey << ", " 
	   << "minPos = " << minPos << ", " 
	   << "maxKey = " << maxKey << ", " 
	   << "maxPos = " << maxPos 
	   << endl ;
    }

    if (2*i <= n) {  // has left child
      H.locateMax(2*i,leftKey,pos) ;
      if (leftKey > maxKey) {  // left child bigger than root 
	passed = false ;
	cout << "Bad heap condition at i = " << i << ": "
	     << "root key = " << maxKey << ", " 
	     << "left key = " << leftKey 
	     << endl ;
      }
    }  

    if (2*i+1 <= n) {  // has right child
      H.locateMax(2*i+1,rightKey,pos) ;
      if (rightKey > maxKey) {  // right child bigger than root 
	passed = false ;
	cout << "Bad heap condition at i = " << i << ": "
	     << "root key = " << maxKey << ", " 
	     << "right key = " << rightKey 
	     << endl ;
      }
    }  
  }  // end of for (...)


  if (passed) {
    cout << "Passed sanityCheck().\n" ;
  } else {
    cout << "*** Failed sanityCheck().\n" ;
  }
}

//checkAgainstSet (for MinHeap): provided by Dr. Chang
template <typename T>
void checkAgainstSet(MinMaxHeap<T>& H, multiset<T>& origS) {
  multiset<T> S ;  
  typename multiset<T>::iterator it ;

  int n = H.size() ;
  int pos ;
  int key ;

  bool passed = true ;

  S = origS ;  // make copy

  if ( n != S.size() ) {
    passed = false ;
    cout << "Heap and multiset sizes do not match!\n" ;
    cout << "   Heap size = " << n << endl ;
    cout << "   Set size  = " << S.size() << endl ;
  }


  for (int i=1 ; i <= n ; i++) {
    H.locateMin(i,key,pos) ;
    it = S.find(key) ;
    if (it == S.end()) {
      passed = false ;
      cout << "Key " << key << " in the min-heap but not in the multiset.\n" ;
    } else {
      S.erase(it) ;
    }
  }

  if (S.size() > 0) {
    cout << "There are " << S.size() 
	 << " items in multiset that not in the min-heap.\n" ;
    for (it=S.begin() ; it != S.end() ; it++) {
      cout << *it << " " ;
    }
    cout << endl ;
  }


  S = origS ;  // start over

  for (int i=1 ; i <= n ; i++) {
    H.locateMax(i,key,pos) ;
    it = S.find(key) ;
    if (it == S.end()) {
      passed = false ;
      cout << "Key " << key << " in the max-heap but not in the multiset.\n" ;
    } else {
      S.erase(it) ;
    }
  }

  if (S.size() > 0) {
    cout << "There are " << S.size() 
	 << " items in multiset that not in the max-heap.\n" ;
    for (it=S.begin() ; it != S.end() ; it++) {
      cout << *it << " " ;
    }
    cout << endl ;
  }

  if (passed) {
    cout << "Passed check against multiset\n" ;
  } else {
    cout << "***Failed check against multiset\n" ;
  }

}

//checkAgainstSet(for MaxHeap): provided by Dr. Chang
template <typename T>
void checkAgainstSet(MinMaxHeap<T>& H, multiset<T,greater<T> >& origS) {
  multiset<T,greater<T> > S ;  
  typename multiset<T,greater<T> >::iterator it ;

  int n = H.size() ;
  int pos ;
  int key ;

  bool passed = true ;

  S = origS ;  // make copy

  if ( n != S.size() ) {
    passed = false ;
    cout << "Heap and multiset sizes do not match!\n" ;
    cout << "   Heap size = " << n << endl ;
    cout << "   Set size  = " << S.size() << endl ;
  }


  for (int i=1 ; i <= n ; i++) {
    H.locateMin(i,key,pos) ;
    it = S.find(key) ;
    if (it == S.end()) {
      passed = false ;
      cout << "Key " << key << " in the min-heap but not in the multiset.\n" ;
    } else {
      S.erase(it) ;
    }
  }

  if (S.size() > 0) {
    cout << "There are " << S.size() 
	 << " items in multiset that not in the min-heap.\n" ;
    for (it=S.begin() ; it != S.end() ; it++) {
      cout << *it << " " ;
    }
    cout << endl ;
  }


  S = origS ;  // start over

  for (int i=1 ; i <= n ; i++) {
    H.locateMax(i,key,pos) ;
    it = S.find(key) ;
    if (it == S.end()) {
      passed = false ;
      cout << "Key " << key << " in the max-heap but not in the multiset.\n" ;
    } else {
      S.erase(it) ;
    }
  }

  if (S.size() > 0) {
    cout << "There are " << S.size() 
	 << " items in multiset that not in the max-heap.\n" ;
    for (it=S.begin() ; it != S.end() ; it++) {
      cout << *it << " " ;
    }
    cout << endl ;
  }

  if (passed) {
    cout << "Passed check against multiset\n" ;
  } else {
    cout << "***Failed check against multiset\n" ;
  }

}

//NoCopyString class provided by Dr. Chang
class NoCopyString {
 public:
  NoCopyString() ;
  NoCopyString(const char *) ;

  bool operator<  (const NoCopyString& other) const ;
  bool operator<= (const NoCopyString& other) const ;
  bool operator== (const NoCopyString& other) const ;
  bool operator!= (const NoCopyString& other) const ;
  bool operator>  (const NoCopyString& other) const ;
  bool operator>= (const NoCopyString& other) const ;

  const char *m_str ;

} ;


std::ostream& operator<< (std::ostream& sout, const NoCopyString& s) ;


NoCopyString::NoCopyString() {
  m_str = NULL ;
}

NoCopyString::NoCopyString(const char *str) {
  m_str = str ;
}

bool NoCopyString::operator<  (const NoCopyString& other) const {
  if (strcmp(m_str, other.m_str) <  0) return true ;
  return false ;
}

bool NoCopyString::operator<= (const NoCopyString& other) const {
  if (strcmp(m_str, other.m_str) <= 0) return true ;
  return false ;
}

bool NoCopyString::operator== (const NoCopyString& other) const {
  if (strcmp(m_str, other.m_str) == 0) return true ;
  return false ;
}

bool NoCopyString::operator!= (const NoCopyString& other) const {
  if (strcmp(m_str, other.m_str) != 0) return true ;
  return false ;
}

bool NoCopyString::operator>= (const NoCopyString& other) const {
  if (strcmp(m_str, other.m_str) >= 0) return true ;
  return false ;
}

bool NoCopyString::operator>  (const NoCopyString& other) const {
  if (strcmp(m_str, other.m_str) >  0) return true ;
  return false ;
}


std::ostream& operator<< (std::ostream& sout, const NoCopyString& s) {
  sout << s.m_str ;
  return sout ;
}


int main() {
  cout << "**********************************" << endl;
  cout << "** Test 1 provided by Dr. Chang **" << endl;
  cout << "**********************************" << endl;

  MinMaxHeap<int> H1(25) ;
  H1.insert(5) ;
  H1.insert(10) ;
  H1.insert(7) ;
  H1.insert(9) ;
  H1.insert(6) ;
  H1.insert(2) ;
  H1.insert(16) ;
  H1.insert(12) ;
  H1.insert(11) ;

  cout << "Initial MinMax Heap\n" ;
  H1.dump() ;

  H1.insert(8); 
  cout << "After inserting 8\n" ;
  H1.dump() ;

  sanityCheck(H1) ;

  int answer1 ;
  answer1 = H1.deleteMin() ;
  cout << "\n\nMin item " << answer1 << " removed from MinMax Heap\n" ;

  H1.dump() ;
  sanityCheck(H1) ;

  answer1 = H1.deleteMax() ;
  cout << "\n\nMax item " << answer1 << " removed from MinMax Heap\n" ;

  H1.dump() ;
  sanityCheck(H1) ;
  cout << endl;

  cout << "**********************************" << endl;
  cout << "** Test 2 provided by Dr. Chang **" << endl;
  cout << "**********************************" << endl;

  MinMaxHeap<string> H2(25) ;
  H2.insert("jkl") ;
  H2.insert("yz_") ;
  H2.insert("abc") ;
  H2.insert("mno") ;
  H2.insert("vwx") ;
  H2.insert("pqr") ;
  H2.insert("ghi") ;
  H2.insert("def") ;
  H2.insert("stu") ;

  H2.dump() ;
  sanityCheck(H2) ;

  string answer2 ;
  answer2 = H2.deleteMin() ;
  cout << "Min item " << answer2 << " removed from MinMax Heap\n" ;

  answer2 = H2.deleteMax() ;
  cout << "Max item " << answer2 << " removed from MinMax Heap\n" ;

  H2.dump() ;
  sanityCheck(H2) ;
  cout << endl;

  cout << "**********************************" << endl;
  cout << "** Test 3 provided by Dr. Chang **" << endl;
  cout << "**********************************" << endl;
  
  MinMaxHeap<NoCopyString> H3(9) ;

  const char* myData[9] = {
    "jkl", "yz_", "abc",
    "mno", "vwx", "pqr",
    "ghi", "def", "stu" 
  } ;

  H3.insert(myData[0]) ;
  H3.insert(myData[1]) ;
  H3.insert(myData[2]) ;
  H3.insert(myData[3]) ;
  H3.insert(myData[4]) ;
  H3.insert(myData[5]) ;
  H3.insert(myData[6]) ;
  H3.insert(myData[7]) ;
  H3.insert(myData[8]) ;

  H3.dump() ;
  sanityCheck(H3) ;

  NoCopyString answer3 ;
  answer3 = H3.deleteMin() ;
  cout << "Min item " << answer3 << " removed from MinMax Heap\n" ;

  answer3 = H3.deleteMax() ;
  cout << "Max item " << answer3 << " removed from MinMax Heap\n" ;

  H3.dump() ;
  sanityCheck(H3) ;
  cout << endl;

  cout << "********************************************************\n"
       << "** Test A: Checks for out-of-range exception handling **\n"  
       << "********************************************************\n";
    
  MinMaxHeap<int> Q1(1);
  MinMaxHeap<string> Q2(1);

  cout << "(a) MinMaxHeap<int> object with capcity 1:" << endl;
  cout << "\nDump empty heap..." << endl;
  Q1.dump();

  cout << "Delete Min..." << endl;
  try {
    Q1.deleteMin();
  }
  catch (out_of_range e){
    cout << e.what() << endl;
  }
  cout << "Delete Max..." << endl;
  try {
    Q1.deleteMax();
  }
  catch (out_of_range e){
    cout << e.what() << endl;
  }
  cout << "\nDump heap after deletes..." << endl;
  Q1.dump();
  
  cout << "Insert 1...\n";
  Q1.insert(1);
  cout << "Insert 2...\n";
  try {
    Q1.insert(2);
  }
  catch (out_of_range e){
    cout << e.what() << endl;
  }
  cout << "\nDump heap after inserts..." << endl;
  Q1.dump();
  cout << endl;

  cout << "(b) MinMaxHeap<string> object with capcity 1:" << endl;
  cout << "\nDump empty heap..." << endl;
  Q2.dump();

  cout << "Delete Min..." << endl;
  try {
    Q2.deleteMin();
  }
  catch (out_of_range e){
    cout << e.what() << endl;
  }
  
  cout << "Delete Max..." << endl;
  try {
    Q2.deleteMax();
  }
  catch (out_of_range e){
    cout << e.what() << endl;
  }
  cout << "\nDump heap after deletes..." << endl;
  Q2.dump();
  
  cout << "Insert 'first'...\n";
  Q2.insert("first");
  cout << "Insert 'second'...\n";
  try {
    Q2.insert("second");
  }
  catch (out_of_range e){
    cout << e.what() << endl;
  }
  cout << "\nDump heap after inserts..." << endl;
  Q2.dump();
  cout << endl;

  cout << "**********************************" << endl;
  cout << "** Test 4 provided by Dr. Chang **" << endl;
  cout << "**********************************" << endl;

  srand(4178012351) ;

  MinMaxHeap<int> H4(1000) ;
  multiset<int> S4 ;
  //multiset<int>::iterator it4 ;
  int key4 ;
  bool passed4 ;

  for (int i=0 ; i < 500 ; i++) {
    key4 = rand() % 100 ;
    H4.insert(key4) ;
    S4.insert(key4) ;
  }
  sanityCheck(H4) ;
  checkAgainstSet(H4,S4) ;

  passed4 = true ;
  for (int i=0 ; i < 450 ; i++) {
    key4 = H4.deleteMin() ;
    if (key4 != *S4.begin()) {
      passed4 = false ;
      cout << "deleteMin() returns key that is not the smallest key!\n" ;
    } else {
      S4.erase(S4.begin()) ;
    }
  }

  sanityCheck(H4) ;

  if (passed4) {
    checkAgainstSet(H4,S4) ;
  } else {
    cout << "***Failed deleteMin() test!\n" ;
    cout << "Skipped check against multiset\n" ;
  }
  cout << endl;

  cout << "**********************************" << endl;
  cout << "** Test 5 provided by Dr. Chang **" << endl;
  cout << "**********************************" << endl;

  MinMaxHeap<int> H5(1000) ;
  multiset<int,greater<int> > S5 ;
  //multiset<int,greater<int> >::iterator it5 ;
  int key5 ;
  bool passed5 ;

  for (int i=0 ; i < 750 ; i++) {
    key5 = rand() % 100 ;
    H5.insert(key5) ;
    S5.insert(key5) ;
  }
  sanityCheck(H5) ;
  checkAgainstSet(H5,S5) ;

  passed5 = true ;
  for (int i=0 ; i < 400 ; i++) {
    key5 = H5.deleteMax() ;
    if (key5 != *S5.begin()) {
      passed5 = false ;
      cout << "deleteMax() returns key that is not the largest key!\n" ;
    } else {
      S5.erase(S5.begin()) ;
    }
  }

  sanityCheck(H5) ;

  if (passed5) {
    checkAgainstSet(H5,S5) ;
  } else {
    cout << "***Failed deleteMax() test!\n" ;
    cout << "Skipped check against multiset\n" ;
  }
  cout << endl;
  
  cout << "**********************************" << endl;
  cout << "** Test 6 provided by Dr. Chang **" << endl;
  cout << "**********************************" << endl;

  MinMaxHeap<int> H6(25) ;
  H6.insert(5) ;
  H6.insert(10) ;
  H6.insert(7) ;
  H6.insert(9) ;
  H6.insert(6) ;
  H6.insert(2) ;
  H6.insert(16) ;
  H6.insert(12) ;
  H6.insert(11) ;

  cout << "Initial MinMax Heap\n" ;
  H6.dump() ;
  sanityCheck(H6) ;

  MinMaxHeap<int> *Gptr = new MinMaxHeap<int>(H6) ;
  cout << "copied MinMax Heap\n" ;
  Gptr->dump();

  H6.deleteMax() ;
  Gptr->deleteMin() ;
  cout << "\nH6 and *Gptr after deleteMax and deleteMin\n" ;
  sanityCheck(H6) ;
  sanityCheck(*Gptr) ;

  delete Gptr ;

  cout << "\nH6 after Gptr deleted\n" ;
  H6.deleteMin() ;
  H6.deleteMax() ;
  sanityCheck(H6) ;

  MinMaxHeap<int> K1(11) ;
  K1.insert(29) ;
  K1.insert(24) ;
  K1.insert(23) ;
  K1.insert(22) ;
  K1.insert(28) ;
  K1.insert(26) ;
  K1.insert(30) ;
  K1.insert(21) ;
  K1.insert(25) ;
  K1.insert(27) ;

  cout << "\nK1 after inserts\n" ;
  sanityCheck(K1) ;

  MinMaxHeap<int> K2(4) ;
  K2.insert(43) ;
  K2.insert(42) ;
  K2.insert(44) ;
  K2.insert(41) ;

  cout << "\nK2 after inserts\n" ;
  sanityCheck(K2) ;

  K2 = K1 ;
  K1.deleteMax() ;
  K2.insert(57) ;

  cout << "\nK1 & K2 after assignment, etc...\n" ;
  sanityCheck(K1) ;
  sanityCheck(K2) ;
  cout << endl;

  cout << "*********************************************\n"
       << "** Test B: Checks for Heap with Capacity 0 **\n"  
       << "*********************************************\n";

  MinMaxHeap<int> P1(0);

  cout << "(a) MinMaxHeap<int> P1 with capcity 0:" << endl;
  cout << "\nDump P1..." << endl;
  P1.dump();

  cout << "Insert 1..." << endl;
  try {
    P1.insert(1);
  }
  catch (out_of_range e){
    cout << e.what() << endl;
  }
  cout << "Delete Min..." << endl;
  try {
    P1.deleteMin();
  }
  catch (out_of_range e){
    cout << e.what() << endl;
  }
  cout << "Delete Max..." << endl;
  try {
    P1.deleteMax();
  }
  catch (out_of_range e){
    cout << e.what() << endl;
  }
  cout << "\nDump heap after deletes..." << endl;
  P1.dump();
  cout << endl;
  
  cout << "(b) Copy Construct MinMaxHeap<int> with P1:" << endl;

  MinMaxHeap<int>* p2Ptr = new MinMaxHeap<int>(P1);

  cout << "\nDump copy constructed MinMaxHeap<int>..." << endl;
  p2Ptr->dump();

  cout << "Insert 1 to copy constructed MinMaxHeap<int>..." << endl;
  try {
    p2Ptr->insert(1);
  }
  catch (out_of_range e){
    cout << e.what() << endl;
  }
  cout << endl;

  cout << "(c) Construct MinMaxHeap<int> P3 with capcaity 3:" << endl;
  MinMaxHeap<int> P3(3);
  cout << "\nInsert 1, 2, 3..." << endl;
  P3.insert(1); P3.insert(2); P3.insert(3);
  cout << "\nDump heap after inserts..." << endl;
  P3.dump();

  cout << "Assign copy constructed object with capcity 0 to P3...\n";
  P3 = *p2Ptr;
  cout << "Dump updated P3..." << endl;
  P3.dump();

  cout << "Insert 1..." << endl;
  try {
    P3.insert(1);
  }
  catch (out_of_range e){
    cout << e.what() << endl;
  }
  cout << "Delete Min..." << endl;
  try {
    P3.deleteMin();
  }
  catch (out_of_range e){
    cout << e.what() << endl;
  }
  cout << "Delete Max..." << endl;
  try {
    P3.deleteMax();
  }
  catch (out_of_range e){
    cout << e.what() << endl;
  }
  cout << "\nDump heap after deletes..." << endl;
  P3.dump();
  
  cout << "(d) Destory copy constructed object, "
       << "and dump P1 and P3:" << endl;

  delete p2Ptr;  
  cout << "Dump P1..." << endl; P1.dump();
  cout << "Dump P3..." << endl; P3.dump();
  cout << endl;

  cout << "****************************************\n"
       << "** Test C: Checks for Self-Assignment **\n"  
       << "****************************************\n";

  cout << "Create MinMaxHeap<int> self..." << endl;
  MinMaxHeap<int> self(5);

  cout << "Insert 1, 2, 3, 4, 5..." << endl;
  self.insert(1); self.insert(2);
  self.insert(3); self.insert(4); self.insert(5);

  cout << "Dump self..." << endl;
  self.dump();
  
  cout << "\nAssign self to itself..." << endl;
  self = self;
  
  cout << "Dump self after self assignment..." << endl;
  self.dump();
  cout << endl;

  cout << "*******************************************************\n"
       << "** Test D: Checks for Large Heap Inserts and Deletes **\n"  
       << "*******************************************************\n";
  cout << "NOTE: takes a long time if run with valgrind, so might \n"
       << "want to comment Test C out if necessary\n";

  cout << "\nConstruct MinMaxHeap<int> with capacity 1 million...";
  cout << "\nInsert 1 million integers..." << endl;
  MinMaxHeap<int> largeInt(1000000);
  for (int i = 1; i <= 1000000; ++i){
    largeInt.insert(i);
  }
  cout << "Sanity Check after inserts:" << endl;
  sanityCheck(largeInt);

  cout << "\nDelete Max 0.5 million integers..." << endl;
  for (int i = 1000000; i >= 500001; --i){
    largeInt.deleteMax();
  }
  cout << "Sanity Check after deletes:" << endl;
  sanityCheck(largeInt);

  cout << "\nDelete Min 0.5 million integers..." << endl;
  for (int i = 500000; i >= 1; --i){
    largeInt.deleteMin();
  }
  cout << "Sanity Check after deletes:" << endl;
  sanityCheck(largeInt);

  cout << "\nConstruct MinMaxHeap<char> with capacity 1 million...";
  cout << "\nInsert 1 million characters..." << endl;
  MinMaxHeap<char> largeChar(1000000);
  for (int i = 1; i <= 1000000; ++i){
    largeChar.insert(i);
  }
  cout << "Sanity Check after inserts:" << endl;
  sanityCheck(largeChar);

  cout << "\nDelete Max 0.5 million characters..." << endl;
  for (int i = 1000000; i >= 500001; --i){
    largeChar.deleteMax();
  }
  cout << "Sanity Check after deletes:" << endl;
  sanityCheck(largeChar);

  cout << "\nDelete Min 0.5 million characters..." << endl;
  for (int i = 500000; i >= 1; --i){
    largeChar.deleteMin();
  }
  cout << "Sanity Check after deletes:" << endl;
  sanityCheck(largeChar);

  return 0;

}
