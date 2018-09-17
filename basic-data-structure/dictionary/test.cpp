#include <iostream>
#include "hashtable.h"

int main()
{
  HashTable<int,int> map;
  int m,n;
  std::cout<<"Insert:\n";
  while(std::cin>>m>>n)
    map.put(m,n);

  std::cin.clear();
  std::cin.get();
  std::cout<<"Get:\n";
  while(std::cin>>m)
  {
    if(map.get(m))
      std::cout<<*map.get(m)<<std::endl;
    else
      std::cout<<"Not found\n";
  }

  std::cin.clear();
  std::cin.get();
  std::cout<<"Remove:\n";
  while(std::cin>>m)
  {
    if(map.remove(m))
      std::cout<<"succesful\n";
    else
      std::cout<<"Not found\n";
  }

  std::cin.clear();
  std::cin.get();
  std::cout<<"Get:\n";
  while(std::cin>>m)
  {
    if(map.get(m))
      std::cout<<*map.get(m)<<std::endl;
    else
      std::cout<<"Not found\n";
  }

  return 0;
}
