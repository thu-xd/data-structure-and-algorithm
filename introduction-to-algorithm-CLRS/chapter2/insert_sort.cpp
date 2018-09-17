#include <iostream>
#include <ctime>
#include <cstdlib>

void swap(int & a,int & b)
  //Swap integer a and b
  //
  //Args:
  //a:the first integer
  //b:the second integer
  //
  //Return:
  //
{
  int tmp=a;
  a=b;
  b=tmp;
}

double insert_sort(int A[],int n)
  //Insert sort of array A.
  //
  //Args:
  //  A:the name of the array.
  //  n:the size of the array.
  //
  //Return:
  //  The running time of the sort algorithm
{
  std::clock_t t;
  t=std::clock();
  for(int i=1;i<n;i++)       //The time complexity of insert sort was O(n^2)
    for(int j=0;j<=i-1;j++)
    {
      if(A[i-j]<A[i-j-1])
        swap(A[i-j],A[i-j-1]);
      else
        break;
    }
  t=std::clock()-t;
  return double(t)/CLOCKS_PER_SEC;
}


int main()
{
  int n;
  std::cout<<"How many integers to be sorted:__\b\b";
  std::cin>>n;
  int * arr=new int[n];
  std::srand(time(NULL));
  for(int i=0;i<n;i++)
    arr[i]=std::rand()%1000;

  if(n<=20)
  {
    std::cout<<"The original arr was:\n";
    for(int i=0;i<n;i++)
      std::cout<<arr[i]<<" ";
    std::cout<<std::endl;
  }

  double t=insert_sort(arr,n);
  if(n<=20)
  {
    std::cout<<"The sorted arr was :\n";
    for(int i=0;i<n;i++)
      std::cout<<arr[i]<<" ";
    std::cout<<std::endl;
  }

  std::cout<<"The time to sort "<<n<<" integers was "<<t<< " second."<<std::endl;
  delete [] arr;
  return 0;
}
