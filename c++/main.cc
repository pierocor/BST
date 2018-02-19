#include<iostream>
#include<tree.h>
#ifndef SEED
#include <time.h>
#define SEED time(NULL)
#endif

#include <vector>
#define MAX_SIZE 100000
#define STEP 5000
#define NLOOK 10000000

#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/time.h>


double cclock()
  /* Returns elepsed seconds past from the last call to timer rest */
{

    struct timeval tmp;
    double sec;
    gettimeofday( &tmp, (struct timezone *)0 );
    sec = tmp.tv_sec + ((double)tmp.tv_usec)/1000000.0;
    return sec;
}

template<typename K>
struct comp{
  bool operator() (const K &  a, const K & b) const {
    return a < b;
  }
};

int main(){
  double t_start, t_stop;
  std::vector<int> keys;
  size_t size, i, j;
  Tree<int, int, comp<int> > BT{}, T;
  int tmp;
  srand (SEED);
  for ( i = 0; i < MAX_SIZE; ++i ){ // ordered vector
    keys.push_back(i);
  }
  for (size = STEP; size < MAX_SIZE; size += STEP ){
    for ( i = 0; i < size; ++i ){ // shuffle!
      j = rand()%(size - i) + i;
      tmp = keys[i];
      keys[i] = keys[j];
      keys[j] = tmp;
    }

    for ( i = 0; i < size; ++i ){
      BT.insert( keys[i], rand()%100 );
    }

    t_start=cclock();
    for ( i = 0; i < NLOOK; ++i ){
      BT.find2( keys[ rand()%size ] );
    }
    t_stop=cclock();
    std::cout << "size: " << size << "\tNLOOK: " << NLOOK << " in " << t_stop - t_start << " sec.\n";
    BT.clean();
  }
  return 0;
}
