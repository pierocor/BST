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

  //Tree<int,int>::Node prova;

  
  Tree<int,int>::Iterator beginning{BT.begin()};
  std::cout << "Beginning: " << (*beginning).first << " " << (*beginning).second << std::endl;
  
  Tree<int,int>::Iterator beginning2{++beginning};
  
  Tree<int,int>::Iterator beginning3{++beginning2};
  
  //Tree<int,int>::Iterator beginning4{++beginning3};
 
  std::cout << "Beginning++: " << (*beginning2).first << " " << (*beginning2).second << std::endl;
    //  std::cout << "Beginning++: " << (*beginning3).first << " " << (*beginning3).second << std::endl;
  

  
  
  return 0;
}
