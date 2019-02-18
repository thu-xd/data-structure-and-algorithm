#include <iostream>
#include <ctime>
#include <cstdlib>


//This is a naive implementation of heap sort, which is a O(nlgn) algorithm.
//This code can also be extended to construct a priority queue

void build_heap(int A[],int n);
void swap(int & a,int & b);
void down_filter(int A[],int n,int i);

void heap_sort(int A[], int n)
  // heap sort
  // Args:
  //   A: the array.
  //   n: the size of the array.
{
  build_heap(A,n);
  while(n>1)
  {
    swap(A[0],A[n-1]);
    n--;
    down_filter(A,n,0);
  }
}


void build_heap(int A[],int n)
  //build heap from array A using Floyd algorithm.
  //The time complexity of Floyd algorithm was as follow:
  // There were log2(n)+1 levels in the binary tree.
  //                      0            level 0
  //                     / \
  //                    1   2          level 1
  //                   / \ / \
  //                  3  4 5  6        level 2
  //                      .
  //                      .
  //                      .
  //The total time complexity was:
  //T(n)=log2(n)+2*(log2(n)-1)+4*(log2(n)-2)+...2^(log2(n)-1)*(1)
  //    =O(n)
  //So the build heap algorithm was O(n).
  //
  //Args:
  //  A: the array
  //  n: the size of the array.
  //
{
  int last_leaf=(n-1)>>1;  // The last leaf node int 0,1,2...n-1
  while(last_leaf>=0)
  {
    down_filter(A,n,last_leaf);
    last_leaf--;
  }
}

void down_filter(int A[], int n,int i)
  //In array A, if the children of node i maintain the max heap conditions.
  //But node i might not maintain the max heap conditions.
  //We can use down_filter to maintain the max heap condition in node i
  //Args:
  //  A:The array
  //  n:The size of the array
  //  i:The node which don't maintain the max heap condition
{
  while(i<n)   //The time complexity of down filter was proportional to the height of the node i
  {
    if(2*i+1>=n) return;  //If the left child was not exists
    int left_child=A[2*i+1];
    int right_child=((2*i+2)>=n)?left_child:A[2*i+2];
    int max_num=(A[i]>=left_child)?((A[i]>=right_child)?A[i]:right_child):
      ((left_child>=right_child)?left_child:right_child);
    if(max_num==A[i]) return;
    if(max_num==left_child)
    {
      swap(A[i],A[2*i+1]);
      i=2*i+1;
    }
    else
    {
      swap(A[i],A[2*i+2]);
      i=i*2+2;
    }
  }
}


void swap(int & a, int & b)
{
  int tmp=a;
  a=b;
  b=tmp;
}

int main()
{
  int N;
  std::cout<<"How many intergers to sort:__\b\b";
  std::cin>>N;

  int * arr= new int[N];
  std::srand(std::time(NULL));
  for(int i=0;i<N;i++)
    arr[i]=std::rand();

  if(N<=20)
  {
    std::cout<<"The original array was:\n";
    for(int i=0;i<N;i++)
      std::cout<<arr[i]<<" ";
    std::cout<<std::endl;
  }

  std::clock_t t=std::clock();
  heap_sort(arr,N);
  t=std::clock()-t;

  if(N<=20)
  {
    std::cout<<"The sorted array was :\n";
    for(int i=0;i<N;i++)
      std::cout<<arr[i]<<" ";
    std::cout<<std::endl;
  }

  std::cout<<"The running time for "<<N<<" intergers was: "<<
    double(t)/CLOCKS_PER_SEC<<" seconds"<<std::endl;

  return 0;
}
