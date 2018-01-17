#include<iostream>
#include<tree.h>
#ifndef SEED
#include <time.h>
#define SEED time(NULL)
#endif

int main(){
  Tree<int, int> BT{};
  srand (SEED);
  BT.insert( 5, -1);
  for ( int i = 0; i < 10; ++i ){
    BT.insert( rand()%10, rand()%100 );
  }
  Tree<int, int>::Iterator tmp{BT.insert( 5, -1)};
  BT.graph_print();
  std::cout << std::endl << " ++node(5): " << *(++tmp) << std::endl;
  std::cout << std::endl << " node(5)++: " << *(tmp++) << std::endl;

  for (Tree<int, int>::Iterator it = BT.begin(); it != BT.end(); ++it) {
   std::cout << *it << " ";
}
  std::cout << std::endl;

  for (auto& it : BT) {
    std::cout << it << " ";
  }
  std::cout << std::endl;

  // BT.naive_print();
  return 0;
}
