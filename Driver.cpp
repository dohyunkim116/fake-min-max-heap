#include "MinMaxHeap.h"
#include <iostream>
using namespace std;

int main(){
  cout << "Heap" << endl;
  MinMaxHeap<int> H(7);
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

  cout << "Dump after Delete Max" << endl;
  H.deleteMax();
  H.dump();
  cout << endl;

  cout << "Dump after Delete Min" << endl;
  H.deleteMin();
  H.dump();
  cout << endl;

}
