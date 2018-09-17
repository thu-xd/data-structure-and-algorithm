#include <iostream>
#include <cstdlib>
#include <ctime>

int partition(int A[], int lo, int hi,int ith);

template<typename T>
void swap(T & a, T & b)
{
  T tmp=a;
  a=b;
  b=tmp;
}

int ith_smallest(int A[],int n,int ith)
  //Find the ith smallest element in the A array. The worst time comlexity was
  //O(n^2). The average time complexity was O(n).
  //Args:
  //  A:The name of the array
  //  n:The size of the array
  //  ith:The ith smallest
  //Return:
  //  The ith smallest element in the A
{
  return partition(A,0,n-1,ith);
}

int partition(int A[], int lo,int hi,int ith) //[lo,hi]
  //Find the ith smallest element in the A[lo,hi].
  //This subroutine was similar to the partition subroutine in the quick sort.
  //Args:
  //  A:The name of the array
  //  lo:The low index.
  //  hi:The high index.
  //  ith:Find the ith smallest
  //Return:
  //  The ith smallest element in the A[lo,hi]
{
  if(hi==lo) return A[lo];
  std::srand(std::time(NULL));
  int pivot=(std::rand()%(hi-lo+1))+lo;
  swap(A[pivot],A[hi]);
  int i=lo;
  for(int j=lo;j<hi;j++)
    if(A[j]<A[hi])
      swap(A[i++],A[j]);
  swap(A[i],A[hi]);
  if(i-lo==ith) return A[i];
  if(i-lo<ith) return partition(A,i+1,hi,ith-(i-lo)-1);
  else return partition(A,lo,i-1,ith);
}

int main()
{
  int N,ith;
  std::cout<<"How many integers:__\b\b";
  std::cin>>N;
  std::cout<<"Please enter which element to find(ith):__\b\b";
  std::cin>>ith;

  int * A=new int[N];
  std::srand(std::time(NULL));
  for(int i=0;i<N;i++)
    A[i]=std::rand()%1000;

  if(N<=20)
  {
    std::cout<<"The original array was:\n";
    for(int i=0;i<N;i++)
      std::cout<<A[i]<<" ";
    std::cout<<std::endl;
  }
  std::cout<<"The "<<ith<<"th smallest element in the array was "<<ith_smallest(A,N,ith)<<std::endl;
  delete [] A;
  return 0;
}
