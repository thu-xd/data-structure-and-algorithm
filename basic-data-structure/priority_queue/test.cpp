#include "heap.h"
#include <iostream>

int main()
{
  int arr[]={2,3,1,5,7,9};
  Heap<int> h(arr,0,sizeof(arr)/sizeof(arr[0]));
  std::cout<<h.getMax()<<std::endl;
  h.delMax();
  std::cout<<h.getMax()<<std::endl;
  return 0;
}

