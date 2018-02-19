#include<iostream>
#include<tree.h>
#ifndef SEED
#include <time.h>
#define SEED time(NULL)
#endif

#include <vector>
#define MAX_SIZE 50000000
#define STEP 5000
#define NLOOK 100000

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
  double t_start, t_stop, t_1, t_2;
  std::vector<int> keys;
  size_t size, i, j;
  Tree<int, int, comp<int> > BT{}, T;
  int tmp;
  srand (SEED);
  std::cout << "#NLOOK: " << NLOOK << "\n#size:\tfind:\tfind2:\t(sec)\n";
  for ( i = 0; i < MAX_SIZE; ++i ){ // ordered vector
    keys.push_back(i);
  }
  for (size = 1024; size < MAX_SIZE; size *= 2 ){
    for ( i = 0; i < size; ++i ){ // shuffle!
      j = rand()%(size - i) + i;
      tmp = keys[i];
      keys[i] = keys[j];
      keys[j] = tmp;
    }

    for ( i = 0; i < size; ++i ){
      BT.insert( keys[i], rand()%100 );
    }

    for ( i = 0; i < size; ++i ){ // shuffle!
      j = rand()%(size - i) + i;
      tmp = keys[i];
      keys[i] = keys[j];
      keys[j] = tmp;
    }
    t_start=cclock();
    for ( i = 0; i < NLOOK; ++i ){
      BT.find( keys[ i%size ] );
    }
    t_stop=cclock();

    t_1 = t_stop - t_start;
    t_start=cclock();
    for ( i = 0; i < NLOOK; ++i ){
      BT.find2( keys[ i%size ] );
    }
    t_stop=cclock();
    t_2 = t_stop - t_start;
    std::cout << size << "\t" << t_1 << "\t" << t_2 << "\n";
    BT.clean();
  }
  return 0;
}
