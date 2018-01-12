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

  Tree<int,int>::Iterator beginning=BT.begin();
  Tree<int,int>::Iterator ending=BT.last();

  std::cout << std::endl;
  std::cout << "The begin has key " << (*beginning).first  << std::endl;
  std::cout << "The end has key " << (*ending).first  << std::endl;

  //Tree<int,int>::Iterator second=++beginning;
  //std::cout << "The second element has key" << (*second).first << std::endl;
  
  return 0;
}
