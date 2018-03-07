#include<iostream>
#include<tree.h>
#include<time.h>
#include<math.h>
#include<sys/types.h>
#include<sys/time.h>
#include<vector>
#include<numeric>
#include<algorithm>
#include <map>
#include <iomanip>
#ifndef SEED
#define SEED 0
#endif

#define MAX_SIZE 1E07
#define NLOOK 100000

#define COUT  \
  std::cout.fill(' '); \
  std::cout.width(15); \
  std::cout << std::left <<


template<typename K>
struct comp{
  bool operator() (const K &  a, const K & b) const {
    return a < b;
  }
};

double cclock()
{
  struct timeval tmp;
  double sec;
  gettimeofday(&tmp,(struct timezone*)0);
  sec=tmp.tv_sec+((double)tmp.tv_usec)/1000000.0;
  return sec;
}

int main(){
  double t_start, t_stop, t_bal, t_unbal, t_map, t_ins_map, t_ins_tree, t_to_bal;
  std::map<int,double> map;
  std::vector<std::pair<int,double>> pairs;
  size_t size, i, j;
  Tree<int, double, comp<int> > BT{};
  std::pair<int,double> tmp;
  double sum_unbal = 0, sum_bal = 0, sum_map = 0, check = 0;

  srand (SEED);
  std::cout << "#NLOOK: " << NLOOK << "\t time in seconds\n";
  COUT "#size:";
  COUT "insert map:";
  COUT "insert tree:";
  COUT "balance():";
  COUT "unbalanced:";
  COUT "balanced:";
  COUT "map:";
  COUT "checks:";
  std::cout << std::endl;
  for ( i = 0; i < MAX_SIZE; ++i ){ // pairs: ordered vector
    pairs.push_back(std::pair<int,double>{i, rand()%100 });
  }
  for (size = 1024; size < MAX_SIZE; size *= 2 ){
    // SHUFFLE THE PAIRS
    for ( i = 0; i < size; ++i ){
      j = rand()%(size - i) + i;
      tmp = pairs[i];
      pairs[i] = pairs[j];
      pairs[j] = tmp;
    }
    // INSERT TREE
    t_start=cclock();
    for ( i = 0; i < size; ++i ){
      BT.insert( pairs[i] );
    }
    t_stop=cclock();
    t_ins_tree = t_stop - t_start;
    // INSERT MAP
    t_start=cclock();
    for ( i = 0; i < size; ++i ){
      map.insert( pairs[i] );
    }
    t_stop=cclock();
    t_ins_map = t_stop - t_start;
    // compute the check sum
    srand (SEED + 1 );
    for ( i = 0; i < NLOOK; ++i ){
      check += pairs[rand()%size].second;
    }
    // FIND IN RANDOM TREE
    srand (SEED + 1 );
    t_start=cclock();
    for ( i = 0; i < NLOOK; ++i ){ // search for keys (inside the tree)
      sum_unbal += (*(BT.find( rand()%size ))).second;
    }
    t_stop=cclock();
    t_unbal = t_stop - t_start;

    // BALANCE
    t_start=cclock();
    BT.balance();
    t_stop=cclock();
    t_to_bal = t_stop - t_start;
    // FIND IN BALANCED TREE
    srand (SEED + 1 );
    t_start=cclock();
    for ( i = 0; i < NLOOK; ++i ){
      sum_bal += (*(BT.find( rand()%size ))).second;
    }
    t_stop=cclock();
    t_bal = t_stop - t_start;
    // FIND IN MAP
    srand (SEED + 1 );
    t_start=cclock();
    for ( i = 0; i < NLOOK; ++i ){ // search for keys (inside the tree)
      sum_map += (*(map.find( rand()%size ))).second;
    }
    t_stop=cclock();
    t_map = t_stop - t_start;


    COUT size;
    COUT t_ins_map;
    COUT t_ins_tree;
    COUT t_to_bal;
    COUT t_unbal;
    COUT t_bal;
    COUT t_map;
    std::cout << (check == sum_unbal) << (check == sum_bal) << (check == sum_map) << "\n";

    BT.clean();
  }

  return 0;
}
