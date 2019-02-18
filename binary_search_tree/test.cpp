#include "AVL.h"
#include <iostream>

int main()
{
  AVL<int> tree;
  int m;
  while(std::cin>>m)
  {
    tree.insert(m);
    tree.In_order();
    tree.Pre_order();
  }
  std::cin.clear();
  std::cin.get();
  while(std::cin>>m)
  {
    tree.remove(m);
    tree.In_order();
    tree.Pre_order();
  }
  return 0;
}
