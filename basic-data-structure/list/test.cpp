#include "List.h"
#include <cstdlib>
#include <iostream>

int main()
{
  List<int> list;
  std::cout<<"please enter the list size: "<<std::endl;
  int N;
  std::cin>>N;
  for(int i=0;i<N;i++)
    list.insertAsFirst(std::rand()%100);
  std::cout<<list;
/*  List<int> list2(list,1,N-1);
  list2.insertAsFirst(123);
  list2.insertAsLast(123);
  std::cout<<list2; 
  list2.deduplicate();
  std::cout<<list2;*/
  list.merge_sort();
  std::cout<<list;
  return 0;
}

  
