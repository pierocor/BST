#include<iostream>
#include<tree.h>

int main(){
  Tree<int, int> BT{};
  BT.insert(1,2);
  BT.naive_print();
  return 0;
}
