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
#ifndef SEED
#define SEED time(NULL)
#endif

#define MAX_SIZE 20000
#define STEP 5000
#define NLOOK 100000

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
  double t_start, t_stop, t_1;
  std::vector<int> keys;
  size_t size, i, j;
  Tree<int, int, comp<int> > BT{}, T;
  int tmp, sum = 0, check = 0;
  srand (SEED);
  std::cout << "#NLOOK: " << NLOOK << "\n#size:\tbefore:\tafter:\t(sec)\n";
  for ( i = 0; i < MAX_SIZE; ++i ){ // keys: ordered vector
    keys.push_back(i);
  }
  for (size = 1024; size < MAX_SIZE; size *= 2 ){
    // for ( i = 0; i < size; ++i ){ // shuffle!
    //   j = rand()%(size - i) + i;
    //   tmp = keys[i];
    //   keys[i] = keys[j];
    //   keys[j] = tmp;
    // }

    for ( i = 0; i < size; ++i ){  //BT: totally unbalnced tree
      BT.insert( keys[i], rand()%100 );
    }

    for ( i = 0; i < size; ++i ){ // shuffle the keys!
      j = rand()%(size - i) + i;
      tmp = keys[i];
      keys[i] = keys[j];
      keys[j] = tmp;
    }

    t_start=cclock();
    for ( i = 0; i < NLOOK; ++i ){ // search for keys (inside the tree)
      sum += (*(BT.find( keys[ i%size ] ))).first;
      check +=  keys[ i%size ];
    }

    t_stop=cclock();
    t_1 = t_stop - t_start;
    BT.balance(); // balnce BT
    t_start=cclock();
    for ( i = 0; i < NLOOK; ++i ){ // search for keys (inside the tree)
      sum += (*(BT.find( keys[ i%size ] ))).first;
      check +=  keys[ i%size ];
    }

    t_stop=cclock();


    std::cout << size << "\t" << t_1 << "\t" << t_stop - t_start << "\tsum:" << sum << "\tcheck: " << check;
    if ( check == sum )
      std::cout << "\tOK\n";
    else
      std::cout << "\tERROR\n";
    BT.clean();
  }

  return 0;
}
