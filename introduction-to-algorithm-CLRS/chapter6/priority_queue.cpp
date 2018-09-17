#include <vector>
#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
using std::vector;

template <typename T>
void swap(T & a, T & b)
{
  T tmp=a;
  a=b;
  b=tmp;
}

template <typename T>
class Priority_queue
{
  private:
    vector<T> data;   // The data in the priority queue.
    void build_heap();
    void down_filter(int i);
    void up_filter(int i);
  public:
    Priority_queue():data(vector<T>()){};
    Priority_queue(vector<T> & v);   // build a priority queue from a vector.
    Priority_queue(T * arr, int n);  // build a priority queue from a array
    bool empty(){return data.empty();};
    int size() {return data.size();};
    T & top() { return data[0];};
    void push(T e);
    void pop();
};

template<typename T>
Priority_queue<T>::Priority_queue(vector<T> & v):data(v.begin(),v.end())
{
  build_heap();
}

template<typename T>
Priority_queue<T>::Priority_queue(T * arr, int n):data(arr,arr+n)
{
  build_heap();
}

template<typename T>
void Priority_queue<T>::push(T e)
{
  data.push_back(e);
  up_filter(data.size()-1);
}

template<typename T>
void Priority_queue<T>::pop()
{
  swap(data[0],data.back());
  data.pop_back();
  down_filter(0);
}

template<typename T>
void Priority_queue<T>::build_heap()
{
  int n=data.size();
  int last_internal=(n-1)>>1;
  for(int i=last_internal;i>=0;i--)
    down_filter(i);
}

template<typename T>
void Priority_queue<T>::down_filter(int i)
{
  int n=data.size();
  while(i<n)
  {
    if(2*i+1>=n) return;
    T left_child=data[2*i+1];
    T right_child=((2*i+2>=n)?left_child:data[2*i+2]);
    T max_elem=(data[i]>=left_child)?((data[i]>=right_child)?data[i]:right_child):
      ((left_child>=right_child)?left_child:right_child);
    if(data[i]==max_elem) return;
    if(max_elem==left_child)
    {
      swap(data[i],data[2*i+1]);
      i=i*2+1;
    }
    else
    {
      swap(data[i],data[2*i+2]);
      i=i*2+2;
    }
  }
}

template<typename T>
void Priority_queue<T>::up_filter(int i)
{
  while(i)
  {
    int parent=(i-1)>>1;
    if(data[parent]>=data[i]) return;
    swap(data[parent],data[i]);
    i=parent;
  }
}


int main()
{
  int N;
  std::cout<<"How many integers to add into the queue:__\b\b";
  std::cin>>N;

  vector<int> arr(N);
  std::srand(std::time(NULL));
  for(int i=0;i<N;i++)
    arr[i]=std::rand()%500;

  std::clock_t t=std::clock();
  Priority_queue<int> Q1(arr);
  for(int i=1;i<=10;i++)
    Q1.push(i*i*i);
  for(int i=0;i<N;i++)
    Q1.pop();
  t=std::clock()-t;

  std::cout<<"The final queue was:\n";
  for(int i=1;i<10;i++)
  {
    std::cout<<Q1.top()<<" ";
    Q1.pop();
  }
  std::cout<<"\nThe time for the implement Priority_queue was "<<double(t)/CLOCKS_PER_SEC
    <<" seconds\n";

  t=std::clock();
  std::priority_queue<int> Q2(arr.begin(),arr.end());
  for(int i=1;i<=10;i++)
    Q2.push(i*i*i);
  for(int i=0;i<N;i++)
    Q2.pop();
  t=std::clock()-t;

  std::cout<<"The final queue was:\n";
  for(int i=1;i<10;i++)
  {
    std::cout<<Q2.top()<<" ";
    Q2.pop();
  }
  std::cout<<"\nThe time for the STL Priority_queue was "<<double(t)/CLOCKS_PER_SEC
    <<" seconds\n";

  return 0;
}






