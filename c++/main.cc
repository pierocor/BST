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

#define log2MAXSIZE 15
#define SAMPLE 1000

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
  
  try {

    Tree<int, int, comp<int> > BT{};
    Tree<int,int,comp<int>>::Iterator Bit{nullptr};
    std::vector<std::pair<int,int>> test_inp{}, bk{};
    std::vector<std::pair<int,double>> timings{};
    std::vector<double> tm{};
    std::pair<int,int> tmp;
    double t1=0,t2=0,t3,t4;
    size_t log2SIZE=0, LOOKUP=0,i, SIZE=1E05;
    int tree_cnt=0,map_cnt=0;
    bool test=true;

    // std::map comparison
    std::map<int,int> test_map;
    int found_map=0;

    srand (SEED);

    // for(log2SIZE=10;log2SIZE<=log2MAXSIZE;log2SIZE+=2){
    
    //   SIZE=pow(2,log2SIZE);
    //   //std::cout << SIZE << std::endl;
    //   LOOKUP=10;
    
    //   //Definition of test input
    //   for(i=0;i<SIZE;++i){
    //     tmp.first=i;
    //     tmp.second=rand()%100;
    //     test_inp.push_back(tmp);
    //   }

    //   //Filling the binary tree
    //   size_t pool=SIZE,label=0;
    //   for(i=0;i<SIZE;++i){
    //     label=rand()%(pool);
    //     BT.insert(test_inp[label].first,test_inp[label].second);
    //     test_map.insert(test_inp[label]);
    //     test_inp.erase(test_inp.begin()+label);      
    //     pool-=1;      

    //   }

    //   // Lookups in BT
    //   for(i=0;i<LOOKUP;++i){
    //     label=rand()%SIZE;
    //     t1=cclock();
    //     for(int j=0;j<SAMPLE;++j)
    //       Bit=BT.find(label);
    //     t2=cclock();
    //     tree_cnt+=(*Bit).second;
    //     t3=cclock();
    //     for(int j=0;j<SAMPLE;++j)
    //       found_map=test_map.find(label)->second;
    //     t4=cclock();
    //     map_cnt+=found_map;
    //     std::cout << "Search key: "<< label << " Find_T: " << (*Bit).second << " Find_M: " << found_map << " Size: " <<SIZE << " Time_T: "  << (t2-t1)/1000 << " Time_M: "  << (t4-t3)/1000 << std::endl;
    //     //std::cout << SIZE << "\t"  << (t2-t1)/SAMPLE << "\t"  << (t4-t3)/SAMPLE << std::endl;

    //   }

    //   if(map_cnt==tree_cnt)
    //     std::cout << "Check: SUCCESS" << std::endl;
    //   else
    //     std::cout << "Check: FAIL - tree: " << tree_cnt << " map: " << map_cnt << std::endl;



    // test

    // for(i=0;i<SIZE;++i){
    //   tmp.first=i;
    //   tmp.second=rand()%100;
    //   test_inp.push_back(tmp);
    // }

    // bk=test_inp;

    // //Filling the binary tree
    // size_t pool=SIZE,label=0;
    // for(i=0;i<SIZE;++i){
    //   label=rand()%(pool);
    //   BT.insert(bk[label].first,bk[label].second);
    //   bk.erase(bk.begin()+label);      
    //   pool-=1;      
    // }

    // t1=cclock();
    // BT.balance();
    // t1=cclock()-t1;

    // std::cout << t1 << std::endl;
    
    // for(i=0;i<5*SIZE;++i){
    //   label=rand()%SIZE;
    //   if(test_inp[label].second!=BT[label]){
    //     std::cout << label << test_inp[label].second << BT[label] <<std::endl;
    //     test=false;
    //   }
    // }

    // if(test==false)
    //   std::cout << "Test FAILED" <<std::endl;
    // else
    //   std::cout << "Test PASSED" <<std::endl;


    //   map_cnt=0;
    //   tree_cnt=0;


    

  } catch (const std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n";
    return 3;
  }
  
  return 0;
}
