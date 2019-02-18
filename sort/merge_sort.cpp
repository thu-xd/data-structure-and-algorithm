#include <iostream>
#include <ctime>
#include <cstdlib>

void merge(int A[],int lo,int mid,int hi)
  //Merge the sorted array A[lo,mid) and A[mid,hi)
  //Args:
  //A: the array name
  //lo: the low index of the array
  //mid: the mid index of the array
  //hi: the high index of the array
  //
  //Return:
  //
{
  int * tmp=new int[mid-lo];
  for(int i=0;i<mid-lo;i++)
    tmp[i]=A[i+lo];
  int i=0,j=mid,k=lo;
  while(i<mid-lo && j<hi)
  {
    if(tmp[i]>A[j])
      A[k++]=A[j++];
    else
      A[k++]=tmp[i++];
  }

  while(i<mid-lo)
    A[k++]=tmp[i++];
}

void  merge_sort(int A[],int lo,int hi)
  // Merge sort of array A
  // Args:
  //  A: the array name.
  //  lo: the low index of the array
  //  hi: the high index of the array
  //  The elements contained was [lo,hi)
  //  
  // Return:
  //
{
  if(hi-lo==1) return;   // base 
  int mid=(hi+lo)>>1;
  merge_sort(A,lo,mid);  //[lo,mid)
  merge_sort(A,mid,hi);  //[mid,hi)
  merge(A,lo,mid,hi);
}

double merge_sort(int A[],int n)
  // The call function of merge sort
  // Args:
  // A: the name of the array
  // n: the size of the array
  //
  // Return:
  // The running time of the merge sort
{
  std::clock_t t=std::clock();
  merge_sort(A,0,n);           //The time complexity of merge sort was O(nlgn)
  t=std::clock()-t;
  return double(t)/CLOCKS_PER_SEC;
}

int main()
{
  int n;
  std::cout<<"How many integers to sort:__\b\b";
  std::cin>>n;
  int * arr=new int[n];
  std::srand(std::time(NULL));
  for(int i=0;i<n;i++)
    arr[i]=std::rand();
  
  if(n<=20)
  {
    std::cout<<"The original array was: "<<std::endl;
    for(int i=0;i<n;i++)
      std::cout<<arr[i]<<" ";
    std::cout<<std::endl;
  }

  double t=merge_sort(arr,n);
  
  if(n<=20)
  {
    std::cout<<"The sorted array was: "<<std::endl;
    for(int i=0;i<n;i++)
      std::cout<<arr[i]<<" ";
    std::cout<<std::endl;
  }

  std::cout<<"The time for merge sort was: "<<t<<" seconds for "<<n<<" integers."<<std::endl;
  delete [] arr;
  return 0;
}
