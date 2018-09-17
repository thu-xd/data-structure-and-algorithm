#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

inline int ith_digit(int e, int base, int i)
  //Get the ith digit of the integer e
  //Args:
  //  e:The integer
  //  base:The base of the integer
  //  i:The ith digit
  //Return:
  //  The ith digit
{
  return (e%(int(std::pow(base,i+1))))/(int(std::pow(base,i)));
} 

void radix_sort(int A[], int n, int base)
  //This was a naive implementation of radix sort.
  //Radix sort can be used in many situations when there are many keys to
  //compare.The different keys has different priority, such as sorting a lot of
  //time or different integers. We always sort from the lowest priority keys to
  //the highest keys using a stable sort algorithm like count sort.
  //The time complexity of radix sort was O(d*(base+n))  where base^d=A[max].
  //when base=A[max], radix sort was just count sort.
  //Args:
  //  A:The array need to sort
  //  n:The size of the array
  //  base:The base used by radix_sort
  //Return:
  //
{
  int non_zero_digits; // count the non_zero digit, when non_zero_digit==0, the array has already sorted.
  int d=0;
  int * result=new int[n];
  int * count=new int[base];
  while(true)
  {
    non_zero_digits=0;
    for(int i=0;i<base;i++) count[i]=0;
    for(int i=0;i<n;i++) count[ith_digit(A[i],base,d)]++;
    for(int i=1;i<base;i++)
    {
      if(count[i]>0)
        non_zero_digits++;
      count[i]+=count[i-1];
    }
    
    if(non_zero_digits==0) break;

    for(int i=n-1;i>=0;i--)   // from n-1 to 0 to get a stable sort algorithm
    {
      result[count[ith_digit(A[i],base,d)]-1]=A[i];
      count[ith_digit(A[i],base,d)]--;
    }

    for(int i=0;i<n;i++)
      A[i]=result[i];

    d++;
  }

  delete [] result;
  delete [] count;
}

int main()
{
  int N,base,e_max;
  std::cout<<"How many integers to sort:__\b\b";
  std::cin>>N;
  std::cout<<"The maxmium of these integers:__\b\b";
  std::cin>>e_max;
  std::cout<<"The base of the radix sort algorithm:__\b\b";
  std::cin>>base;

  int * arr=new int[N];
  std::srand(std::time(NULL));
  for(int i=0;i<N;i++)
    arr[i]=std::rand()%(e_max+1);

  if(N<=20)
  {
    std::cout<<"The original array was:\n";
    for(int i=0;i<N;i++)
      std::cout<<arr[i]<<" ";
    std::cout<<std::endl;
  }

  std::clock_t t=std::clock();
  radix_sort(arr,N,base);
  t=std::clock()-t;

  if(N<=20)
  {
    std::cout<<"The sorted array was:\n";
    for(int i=0;i<N;i++)
      std::cout<<arr[i]<<" ";
    std::cout<<std::endl;
  }

  std::cout<<"The running time of radix sort for "<<N<<" integers whose maxmium was "<<e_max
    <<" was "<<double(t)/CLOCKS_PER_SEC<<" seconds\n";

  delete [] arr;
  return 0;
}
