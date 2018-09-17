#include <iostream>
#include <ctime>
#include <cstdlib>

void swap(int & a,int & b);
void quick_sort(int A[],int lo, int hi); //[lo,hi]
int partition_L(int A[],int lo, int hi);

void quick_sort(int A[],int n)
  //This is an naive quick sort implementation.
  //The intuition of quick sort was as follow.
  //For A[lo,hi], we need to find where A[mi] should place. The A[mi] was a
  //random elements in A[lo,hi].
  //So we place elements smaller than A[mi] at the left and elements larger
  //than A[mi] at the right.
  //
  //The worst time comlexity of quick sort was O(n^2) when A[mi] is the maxmium
  //or mimium elements in A[lo,hi]. But this situation was very rare. The
  //average time complexity of quick sort was O(nlgn)
  //
  //Args:
  //  A:The array
  //  n:Size of the array
{
  quick_sort(A,0,n-1);
}

void quick_sort(int A[], int lo,int hi)
{
  if(hi<=lo) return;
  std::srand(std::time(NULL));
  int pivot=std::rand()%(hi-lo+1)+lo;  //random choose the pivot point.
  swap(A[pivot],A[hi]);
  int i=partition_L(A,lo,hi);
  quick_sort(A,lo,i-1);
  quick_sort(A,i+1,hi);
}

int partition_L(int A[], int lo, int hi)
  //Lomuto partition scheme. It's easy to understand but less efficient than
  //the original Hoare partition scheme.
  //Args:
  //  A:The array name
  //  lo:The low index
  //  hi:The high index
  //Return:
  //  The index of the pivot element.
{
  int i=lo;  // indicate where to place the elements smaller than A[mid]. The pivot was always choosen as
             // hi in this scheme.
  for(int j=lo;j<hi;j++)
    if(A[j]<A[hi])
    {
      swap(A[i],A[j]);
      i++;
    }
  swap(A[i],A[hi]);
  return i;
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
  std::cout<<"How many integers to sort:__\b\b";
  std::cin>>N;
  int * arr= new int[N];

  std::srand(std::time(NULL));
  for(int i=0;i<N;i++)
    arr[i]=std::rand()%500;

  if(N<=20)
  {
    std::cout<<"The original array was:\n";
    for(int i=0;i<N;i++)
      std::cout<<arr[i]<<" ";
    std::cout<<std::endl;
  }

  std::clock_t t=std::clock();
  quick_sort(arr,N);
  t=std::clock()-t;

  if(N<=20)
  {
    std::cout<<"The sorted array was:\n";
    for(int i=0;i<N;i++)
      std::cout<<arr[i]<<" ";
    std::cout<<std::endl;
  }

  std::cout<<"The running time of quick sort for "<<N<<" integers was: "
    <<double(t)/CLOCKS_PER_SEC<<" seconds\n";

  delete [] arr;
  return 0;
}

