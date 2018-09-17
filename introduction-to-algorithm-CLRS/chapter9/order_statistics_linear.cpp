#include <iostream>
#include <cstdlib>
#include <ctime>

int partition(int A[], int lo, int hi,int ith);
void insert_sort(int A[], int lo,int hi);

template<typename T>
void swap(T & a, T & b)
{
  T tmp=a;
  a=b;
  b=tmp;
}

int ith_smallest(int A[], int n, int ith)
{
  return A[partition(A,0,n-1,ith)];
}

int partition(int A[], int lo, int hi,int ith)
  //This was a worst linear implementation of select the ith smallest element.
  //The key point was to find a good pivot point using the property of the
  //medians.
  //Args:
  //  A:The name of the array
  //  lo:The low index
  //  hi:The high index
  //  ith:Find the ith smallest element
  //Return:
  //  The index of the ith smallest element
{
  if(hi==lo) return lo;
  int sub_arrays=(hi-lo)/5+1;
  int * medians=new int[sub_arrays];
  for(int i=0;i<sub_arrays-1;i++)
  {
    insert_sort(A,5*i,5*i+4);
    medians[i]=A[5*i+2];
  }
  insert_sort(A,(sub_arrays-1)*5,hi);
  medians[sub_arrays-1]=A[((sub_arrays-1)*5+hi)>>1];

  int pivot=partition(medians,0,sub_arrays-1,sub_arrays>>1);  //This was used to find the good pivot point.
  pivot=((pivot<sub_arrays-1)?(pivot*5+2):(((sub_arrays-1)*5+hi)>>1));

  swap(A[pivot],A[hi]);
  int i=lo;
  for(int j=lo;j<hi;j++)
    if(A[j]<A[hi])
      swap(A[j],A[i++]);
  swap(A[i],A[hi]);
  if(i-lo==ith) return i;
  if(i-lo>ith) return partition(A,lo,i-1,ith);
  else return partition(A,i+1,hi,ith-(i-lo)-1);
}


void insert_sort(int A[], int lo, int hi)
{
  if(hi==lo) return;
  for(int i=lo+1;i<=hi;i++)
    for(int j=i-1;j>=lo;j--)
    {
      if(A[j]>A[j+1])
        swap(A[j],A[j+1]);
      else
        break;
    }
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
     
