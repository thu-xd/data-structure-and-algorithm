#include <vector>

template <typename T>
class Heap
{
  private:
    std::vector<T> data;
    int Parent(int i) {return (i-1)>>1;};
    int LChild(int i) {return 1+(i<<1);};
    int RChild(int i) {return 2+(i<<1);};
    bool HasParent(int i){return i>0;};
    bool HasLChild(int i){return LChild(i)<=data.size()-1;};
    bool HasRChild(int i){return RChild(i)<=data.size()-1;}; //Has right child must has left child;
    int LastInternal() {return Parent(data.size()-1);}
    void go_up(int i);
    void go_down(int i);
  public:
    Heap(){};
    Heap(T * A,int lo,int hi); //[lo,hi)
    Heap(const std::vector<T> & vec);
    void insert(T);
    T getMax();
    T delMax();
};

template <typename T>
Heap<T>::Heap(T * A,int lo,int hi):data(A+lo,A+hi)
{
  for(int i=LastInternal();i>=0;i--)
    go_down(i);    // the time complexity was O(n);
}

template <typename T>
Heap<T>::Heap(const std::vector<T> & vec):data(vec)
{
  for(int i=LastInternal();i>=0;i--)
    go_down(i);
}

template <typename T>
void Heap<T>::go_down(int i)
{
  while(HasLChild(i))
  {
    int c=data[i];
    int l=data[LChild(i)];
    int r=(HasRChild(i)?data[RChild(i)]:l);
    int swap;
    if(c>=l && c>=r)
      break;
    else if(l>c && l>=r)
      swap=LChild(i);
    else
      swap=RChild(i);
    data[i]=data[swap];
    data[swap]=c;
    i=swap;
  }
}

template <typename T>
T Heap<T>::getMax()
{
  return data[0];
}

template <typename T>
void Heap<T>::insert(T e)
{
  data.push_back(e);
  int size=data.size();
  go_up(size-1);
}

template <typename T>
void Heap<T>::go_up(int i)
{
  while(HasParent(i))
  {
    if(data[Parent(i)]>=data[i])
      break;
    else
    {
      T tmp=data[Parent(i)];
      data[Parent(i)]=data[i];
      data[i]=tmp;
      i=Parent(i);
    }
  }
}

template <typename T>
T Heap<T>::delMax()
{
  T maxElem=data[0];
  data[0]=data.back();
  data.pop_back();
  go_down(0);
}

