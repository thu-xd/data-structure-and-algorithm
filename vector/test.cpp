#include <iostream>
#include "vector.h"

int main()
{
  int N;
  std::cout<<"Please enter the numer: "<<std::endl;
  std::cin>>N;
  int * A=new int[N];
  std::cout<<"Please enter "<<N<<" numbers"<<std::endl;
  for(int i=0;i<N;i++)
    std::cin>>A[i];
  Vector<int> a(A,N);
  std::cout<<a<<std::endl;
  std::cout<<"2 is at position "<<a.find(2)<<std::endl;
  a.insert(3,19);
  std::cout<<"After insert 19 at position 3 "<<std::endl;
  std::cout<<a<<std::endl;
  a.deduplicate();
  std::cout<<"After deduplicate: "<<std::endl;
  std::cout<<a<<std::endl;
  a.bubble_sort(0,a.size());
  std::cout<<"After sort: "<<std::endl;
  std::cout<<a<<std::endl;
  return 0;
}
