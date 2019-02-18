#include <iostream>
#include <ctime>
#include <cstdlib>

//Count sort was very quick when the elements was integers.The time complexity
//of count sort was O(n+max_value)

void count_sort(int A[], int n, int max_value)
  //count sort implementation. The value in the A array must be in the range of
  //0~max_value
  //Args:
  //  A:The name of the array
  //  n:The size of the array
  //  max_value:The max value of the array
  //Return:
  //  
{
  int * count=new int[max_value+1];
  for(int i=0;i<max_value+1;i++) count[i]=0;
  for(int i=0;i<n;i++) count[A[i]]++;
  for(int i=1;i<max_value+1;i++) count[i]+=count[i-1];
  int * result=new int[n];
  for(int i=n-1;i>=0;i--)
  {
    result[count[A[i]]-1]=A[i];
    count[A[i]]--;
  }
  for(int i=0;i<n;i++) A[i]=result[i];
  delete [] count;
  delete [] result;
}

int main()
{
  int N,max_value;
  std::cout<<"How many integers to sort:__\b\b";
  std::cin>>N;
  std::cout<<"The maxmium value of the sorted integers:__\b\b";
  std::cin>>max_value;

  int * arr= new int[N];
  std::srand(std::time(NULL));
  for(int i=0;i<N;i++)
    arr[i]=std::rand()%(max_value+1);

  if(N<=20)
  {
    std::cout<<"The original array was :\n";
    for(int i=0;i<N;i++)
      std::cout<<arr[i]<<" ";
    std::cout<<std::endl;
  }

  std::clock_t t=std::clock();
  count_sort(arr,N,max_value);
  t=std::clock()-t;

  if(N<=20)
  {
    std::cout<<"The sorted array was :\n";
    for(int i=0;i<N;i++)
      std::cout<<arr[i]<<" ";
    std::cout<<std::endl;
  }

  std::cout<<"The runing time for "<<N<<" integers which was smaller than "<<max_value<<" was "<<
    double(t)/CLOCKS_PER_SEC<<" seconds\n";

  delete [] arr;
  return 0;
}
