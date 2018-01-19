#include<iostream>
#include<tree.h>
#ifndef SEED
#include <time.h>
#define SEED time(NULL)
#endif

int main(){
  Tree<int, int> BT{};
  //BT.naive_print();
  srand (SEED);
  BT.insert( 5, -1);
  for ( int i = 0; i < 100; ++i ){
    BT.insert( rand()%10000, rand()%100 );
  }
  Tree<int, int>::Iterator tmp{BT.insert( 5, -1)};
  BT.graph_print();
  /*
  std::cout << std::endl << " ++node(5): " << (*(++tmp)).first << std::endl;
  std::cout << std::endl << " node(5)++: " << (*(tmp++)).first << std::endl;

  for (Tree<int, int>::Iterator it = BT.begin(); it != BT.end(); ++it) {
   std::cout << *it << " ";
  }
  std::cout << std::endl;

  for (auto& it : BT) {
    std::cout << (*it).first << " ";
  }
  std::cout << std::endl;
  */
  std::cout << "The tree has " << BT.len() << " nodes!" << std::endl;

  Tree<int, int>::ConstIterator tmp2{BT.cbegin()};
  // std::cout << "Beccati questo const iterator: " << (*tmp2).first << std::endl;

  //BT.clean();
  BT.naive_print();

  tmp=BT.find(5);
  std::cout << "The node with key 5 has value: "<< tmp.val() << std::endl;
  
  return 0;
}
