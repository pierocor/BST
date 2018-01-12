#include<iostream>
#include<tree.h>
#ifndef SEED
#include <time.h>
#define SEED time(NULL)
#endif

int main(){
  Tree<int, int> BT{};
  srand (SEED);
  for ( int i = 0; i < 100; ++i ){
    BT.insert( rand()%100000, rand()%100 );
  }

  BT.graph_print();
  // BT.naive_print();
  return 0;
}
