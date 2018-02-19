#include<iostream>
#include<tree.h>
#include<time.h>
#include<math.h>
#include<sys/types.h>
#include<sys/time.h>
#include<vector>
#include<numeric>
#include<algorithm>
#ifndef SEED
#define SEED time(NULL)
#endif

#define log2MAXSIZE 20

template<typename K>
struct comp{
  bool operator() (const K &  a, const K & b) const{
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
  
  Tree<int, int, comp<int> > BT{};
  Tree<int,int,comp<int>>::Iterator Bit{nullptr};
  std::vector<std::pair<int,int>> test_inp{};
  std::vector<std::pair<int,double>> timings{};
  std::vector<double> tm{};
  std::pair<int,int> tmp;
  double t1=0,t2=0,t3,t4;
  size_t log2SIZE=0, LOOKUP=0,i, SIZE=0;
  int tmp_value=0;

  srand (SEED);
  
  for(log2SIZE=10;log2SIZE<=log2MAXSIZE;log2SIZE+=2){
    
    SIZE=pow(2,log2SIZE);
    //std::cout << SIZE << std::endl;
    LOOKUP=10;
    
    //Definition of test input
    for(i=0;i<SIZE;++i){
      tmp.first=i;
      tmp.second=rand()%100;
      test_inp.push_back(tmp);
    }

    //Filling the binary tree
    size_t pool=SIZE,label=0;
    for(i=0;i<SIZE;++i){
      label=rand()%(pool);
      BT.insert(test_inp[label].first,test_inp[label].second);
      test_inp.erase(test_inp.begin()+label);      
      pool-=1;      
    }

    // Lookups in BT
    for(i=0;i<LOOKUP;++i){
      label=rand()%(2*SIZE);
      t1=cclock();
      Bit=BT.find(label);
      t2=cclock();
      std::cout << SIZE << " "  << (t2-t1) << std::endl;
      tmp_value+=Bit.foo();
    }

    // t3=cclock();
    // for(i=0;i<LOOKUP;++i){
    //   label=rand()%(2*SIZE);
    // }
    // t4=cclock();

          

    test_inp.clear();

    BT.clean();

  }

  std::cout << "tmp_val=" << tmp_value << std::endl;

  return 0;
}
