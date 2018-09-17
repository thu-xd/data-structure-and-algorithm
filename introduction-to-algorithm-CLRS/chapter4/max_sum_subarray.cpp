#include <iostream>
#include <cstdlib>
#include <ctime>

int max_sum_subarray(int A[],int n)
  //To find the continue subarray of A which has maxmium sum
  //Args:
  //A:the name of the array
  //n:the size of the array
  //
  //Return:
  //the maxmium sum of the subarrays
{
  int max_sum=A[0];
  if(n==1) return max_sum;
  
  //We use sum[i] to represent the maxmium subarray sum which ending up at A[i]
  //(A[i]) was included). Then we can get the
  //sum[i+1]=(sum[i]>0)?(sum[i]+A[i+1]):A[i+1]
  int previous_sum=max_sum;   //previous_sum means sum[i];
  for(int i=1;i<n;i++)  //this is an O(n) solution without recursive
  {
    previous_sum=(previous_sum>0)?(previous_sum+A[i]):A[i];
    if(previous_sum>max_sum) max_sum=previous_sum;
  }

  return max_sum;
} 

int recursive(int A[],int lo,int hi) //[lo,hi)
// This is a recursive function to calculate the maxmium subarray sum int
// A[lo,hi)  This was a O(nlgn) solution
{
  if(hi-lo<=1) return A[lo];
  int mid=(hi+lo)>>1;
  //The maxmium subarray might in the [lo,mid) or [mid,hi) or cross the mid
  int res1=recursive(A,lo,mid);
  int res2=recursive(A,mid,hi);

  //we need to find the maxmium subarray which cross the mid
  int sum_left=A[mid-1];
  int max_left=sum_left;
  for(int i=mid-2;i>=lo;i--)
  {
    sum_left+=A[i];
    if(sum_left>max_left) max_left=sum_left;
  }

  int sum_right=A[mid];
  int max_right=sum_right;
  for(int i=mid+1;i<hi;i++)
  {
    sum_right+=A[i];
    if(sum_right>max_right) max_right=sum_right;
  }
  int res3=max_left+max_right;

  //The result was the maxmium of res1,res2,res3;
  return (res1>res2)?(res1>res3?res1:res3):(res2>res3?res2:res3);
}


int max_sum_subarray_recursive(int A[],int n)
  //This is the same as the max_sum_subarray but using recursive method
{
  return recursive(A,0,n);
}


int main()
{
  int n;
  std::cout<<"How many integers:__\b\b";
  std::cin>>n;
  int * arr=new int[n];
  std::srand(std::time(NULL));
  for(int i=0;i<n;i++)
    arr[i]=std::rand()%100-50;

  std::cout<<"The array was: "<<std::endl;
  for(int i=0;i<n;i++)
    std::cout<<arr[i]<<" ";
  std::cout<<std::endl;

  std::cout<<"The maxmium subarray sum was: ";
  std::cout<<max_sum_subarray(arr,n)<<std::endl;
  std::cout<<"The maxmium subarray sum was: ";
  std::cout<<max_sum_subarray_recursive(arr,n)<<" using recursive method"<<std::endl;
  delete [] arr;
  return 0;
}


