#include "MinHeap.h"
#include <iostream>
using namespace std;

int main(){
  MinHeap<int> H(8);
  H.insert(1);
  H.insert(2);
  H.insert(3);
  H.insert(4);
  H.insert(5);
  H.insert(-1);
  H.insert(-5);
  H.dump();
}
