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
  for ( int i = 0; i < 5; ++i ){
    BT.insert( rand()%20, rand()%100 );
  }
  BT.insert(10, -1);
  for ( int i = 0; i < 25; ++i ){
    BT.insert( rand()%30, rand()%100 );
  }
  BT.graph_print();
  /*
  std::cout << std::endl << " ++node(5): " << (*(++tmp)).first << std::endl;
  std::cout << std::endl << " node(5)++: " << (*(tmp++)).first << std::endl;

  for (Tree<int, int>::Iterator it = BT.begin(); it != BT.end(); ++it) {
   std::cout << *it << " ";
  }
  std::cout << std::endl;

  */
  std::cout << "The tree has " << BT.len() << " nodes!" << std::endl;


  // std::cout << "Beccati questo const iterator: " << (*tmp2).first << std::endl;

  //BT.clean();
  BT.graph_print();

  std::cout << "last has key: " << BT.last_key() << std::endl;
  
  return 0;
}
