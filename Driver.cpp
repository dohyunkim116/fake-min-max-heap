#include "MinHeap.h"
#include "MaxHeap.h"
#include <iostream>
using namespace std;

int main(){
  cout << "MinHeap" << endl;
  MinHeap<int> H(8);
  H.insert(1);
  H.insert(2);
  H.insert(3);
  H.insert(4);
  H.insert(5);
  H.insert(-1);
  H.insert(-5);
  cout << "Dump after inserts" << endl;
  H.dump();
  cout << endl;

  cout << "Dump after delete min" << endl;
  H.deleteMin();
  H.dump();
  cout << endl;

  MaxHeap<int> Max(5);
  Max.insert(1);
  Max.insert(2);
  Max.insert(-1);
  Max.insert(-2);
  Max.insert(3);
  cout << "Dump after inserts" << endl;
  Max.dump();
  cout << endl;

  cout << "Dump after delete max" << endl;
  Max.deleteMax();
  Max.dump();
  cout << endl;
  
  
}
