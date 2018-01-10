#include<iostream>
#include<tree.h>

int main(){
  Tree<int, int> BT{};
  BT.insert(4,7);
  BT.insert(8,-2);
  BT.insert(5,1);
  BT.insert(3,4);
  BT.insert(6,1);
  BT.insert(7,4);
  BT.naive_print();
  return 0;
}
