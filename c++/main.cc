#include<iostream>
#include<tree.h>
#include<vector>
#ifndef SEED
#include <time.h>
#define SEED time(NULL)
#endif

int main(){
  
  Tree<int, int> BT{};
  BT.insert( 10, 0);
  BT.insert( 8, 0);
  BT.insert( 9, 0);
  BT.insert( 5, 0);
  BT.insert( 7, 0);
  BT.insert( 1, 0);
  BT.insert( 11, 0);
  BT.insert( 16, 0);
  BT.insert( 15, 0);
  BT.insert( 12, 0);
  BT.insert( 13, 0);
  BT.naive_print();
  //BT.linearize();
  BT.graph_print();

  BT.linearize();
  //BT.graph_print();
      
  /*
  BT.naive_print();
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

  return 0;
}
