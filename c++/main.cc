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
  for ( int i = 0; i < 10; ++i ){
    BT.insert( rand()%20, rand()%100 );
  }
  BT.insert(10, -1);
  for ( int i = 0; i < 10; ++i ){
    BT.insert( rand()%30, rand()%100 );
  }
  BT.graph_print();
  std::cout << "The tree has " << BT.len() << " nodes!" << std::endl;
  BT.naive_print();
  BT.print();
  std::cout << "last has key: " << BT.last_key() << "\nfirst has key: " << (*(BT.begin())).first << std::endl;

  BT.erase(10);
  BT.graph_print();
  std::cout << "The tree has " << BT.len() << " nodes!" << std::endl;
  BT.naive_print();
  BT.print();
  std::cout << "last has key: " << BT.last_key() << "\nfirst has key: " << (*(BT.begin())).first << std::endl;

  BT.balance();
  BT.graph_print();
  std::cout << "The tree has " << BT.len() << " nodes!" << std::endl;
  BT.naive_print();
  BT.print();
  std::cout << "last has key: " << BT.last_key() << "\nfirst has key: " << (*(BT.begin())).first << std::endl;

  
  return 0;
}
