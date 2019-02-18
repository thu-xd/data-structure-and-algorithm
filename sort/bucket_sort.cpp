#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

struct ListNode
{
  double val;
  ListNode * next;
  ListNode(double _val=0.0,ListNode * _next=NULL):val(_val),next(_next){};
};

ListNode * insert_sort(ListNode * head)
  //insert sort for a list.
  //Args:
  //  head:The head of the list.
  //Return:
  //  
{
  if(!head) return NULL;
  ListNode * new_head=NULL, * cursor=NULL;
  while(head)
  {
    if(!new_head)
    {
      ListNode * tmp=head->next;
      new_head=head;
      new_head->next=NULL;
      head=tmp;
      continue;
    }
    double  val=head->val;
    cursor=new_head;
    ListNode * parent_node=new_head;
    while(cursor)
    {
      if(cursor==new_head && val<=cursor->val)
      {
        ListNode * tmp=head->next;
        head->next=new_head;
        new_head=head;
        head=tmp;
        break;
      }
      if(val>cursor->val)
      {
        parent_node=cursor;
        cursor=cursor->next;
      }
      else
      {
        ListNode * tmp=parent_node->next;
        ListNode * tmp1=head->next;
        parent_node->next=head;
        head->next=tmp;
        head=tmp1;
        break;
      }
    }

    if(!cursor)  // if head->val is mamxium among new_head
    {
      ListNode * tmp=head->next;
      parent_node->next=head;
      head->next=NULL;
      head=tmp;
    }
  }

  return new_head;
}
   



void bucket_sort(double A[], int n, int elems_per_bucket)
  //This is a naive implementation of bucket sort.
  //Bucket sort was a bit like the algorithm which first classify the elements
  //to each buckets and then using insert sort in each bucket.Finally merge the
  //elements in all buckets
  //Args:
  //  A:The name of the array
  //  n:The size of the array
  //  elems_per_bucket:Average elements in one bucket.
{
  int buckets=n/ elems_per_bucket;
  double max_elem=A[0],min_elem=A[0];
  for(int i=1;i<n;i++)
  {
    if(A[i]>max_elem) max_elem=A[i];
    if(A[i]<min_elem) min_elem=A[i];
  }
  max_elem+=(max_elem-min_elem)/10000;  // to ensure that A[i] must be smaller than max_elem

  ListNode ** bks=new ListNode*[buckets];   // buckets to store the elements
  ListNode ** cursor=new ListNode*[buckets];

  for(int i=0;i<n;i++)   //add the elements in A into buckets.
  {
    int index=buckets*(A[i]-min_elem)/(max_elem-min_elem);
    if(!cursor[index])
      cursor[index]=bks[index]=new ListNode(A[i]);
    else
      cursor[index]=cursor[index]->next=new ListNode(A[i]);
  }

  for(int i=0;i<buckets;i++)
    bks[i]=insert_sort(bks[i]);

  int index=0;
  for(int i=0;i<buckets;i++)
  {
    ListNode * cursor=bks[i];
    while(cursor)
    {
      A[index++]=cursor->val;
      ListNode * tmp=cursor->next;
      delete cursor;
      cursor=tmp;
    }
  }

  delete [] bks;
  delete [] cursor;
}

int main()
{
  int N,elems_per_bucket;
  std::cout<<"How many double to sort:__\b\b";
  std::cin>>N;
  std::cout<<"Elements per bucket:__\b\b";
  std::cin>>elems_per_bucket;

  double * A=new double[N];
  std::srand(std::time(NULL));
  for(int i=0;i<N;i++)
    A[i]=std::rand()/double(RAND_MAX);

  if(N<=20)
  {
    std::cout<<"The original array:\n";
    for(int i=0;i<N;i++)
      std::cout<<A[i]<<" ";
    std::cout<<std::endl;
  }

  std::clock_t t=std::clock();
  bucket_sort(A,N,elems_per_bucket);
  t=std::clock()-t;

  if(N<=20)
  {
    std::cout<<"The sorted array:\n";
    for(int i=0;i<N;i++)
      std::cout<<A[i]<<" ";
    std::cout<<std::endl;
  }

  std::cout<<"The running time was "<<double(t)/CLOCKS_PER_SEC<<" seconds\n";

  delete [] A;
  return 0;
}



