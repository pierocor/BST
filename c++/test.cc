#include<iostream>

int main (){
  int x=5;
  const int y{x};
  std::cout << x << y << std::endl;
  return 0;
}
