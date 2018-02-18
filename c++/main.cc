#include<iostream>
#include<tree.h>
#ifndef SEED
#include <time.h>
#define SEED time(NULL)
#endif

template<typename K>
struct comp{
  bool operator() (const K &  a, const K & b) const {
    return a < b;
  }
};

int main(){
  Tree<int, int, comp<int> > BT{}, T;
  //BT.naive_print();
  srand (SEED);
  BT.insert( 5, -1);
  for ( int i = 0; i < 10; ++i ){
    BT.insert( rand()%20, rand()%100 );
  }
  BT.insert(10, -1);
  for ( int i = 0; i < 10; ++i ){
    BT.insert( rand()%30, rand()%100 );
  }
  BT.graph_print();
  std::cout << "Voila 15 " << *(BT.find(15)) << std::endl;
  std::cout << "The tree has " << BT.len() << " nodes!" << std::endl;
  BT.print();

  for (Tree<int, int, comp<int> >::Iterator it = BT.last(); it != BT.end(); --it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  BT.clean();
  return 0;
}
