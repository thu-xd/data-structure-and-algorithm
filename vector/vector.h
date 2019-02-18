#ifndef VECTOR_V_
#define VECTOR_V_

#include <cstdlib>
#include <iostream>

template <typename T>
class Vector
{
  private:
    static const int DEFAULT_CAPACITY=3;
  protected:
    int _size;
    int _capacity;
    T * _elem;
    void copyFrom(T const * A,int lo,int hi);
    void expand();
    void shrink();
    void merge(int lo,int mid,int hi);
  public:
    Vector(int c=DEFAULT_CAPACITY,int s=0,T v=0);
    Vector(T const *A,int lo,int hi){copyFrom(A,lo,hi);};
    Vector(T const *A,int n){copyFrom(A,0,n);};
    Vector(Vector<T> const & V,int lo,int hi){copyFrom(V._elem,lo,hi);};
    Vector(Vector<T> const & V){copyFrom(V._elem,0,V._size);};
    ~Vector() {delete [] _elem;}

    int size() const {return _size;};
    bool empty() const {return !_size;};
    int disordered() const;
    int find(T const & e) const {return find(e,0,_size);};
    int find(T const & e,int lo,int hi) const;
    Vector<T> & operator=(Vector<T> const & v);
    T & operator[](int r) const;
    void permute(){permute(0,_size);};
    void permute(int lo,int hi);
    int insert(T const & e){return insert(_size,e);};
    int insert(int r,T const & e);
    T remove(int r);
    int remove(int lo,int hi);
    int deduplicate();// used for unsorted vector
    template <typename VST> void traverse(VST &); //for-each item, call the function object
    int uniquify(); //used only for sorted vector
    int search(T const & e)const {return (0>=_size)?-1:search(e,0,_size);};
    int search(T const & e,int lo,int hi) const;
    void bubble_sort(int lo,int hi);
    void merge_sort(int lo,int hi);
    friend std::ostream & operator<<(std::ostream & os,Vector<T> const & v);


};

template <typename T>
void Vector<T>::copyFrom(T const * A,int lo,int hi)
  //This function can only be used in the construct function. If you want to
  //used it in other functions.Please add delete [] _elem in the begin of the
  //function before _elem=new T[_capacity=2*(hi-lo)].
{
  _elem=new T[_capacity=2*(hi-lo)];
  _size=0;
  while(lo<hi)
    _elem[_size++]=A[lo++];
}
template <typename T>
Vector<T>::Vector(int c,int s,T v)
{
  _elem=new T[_capacity=c];
  for(_size=0;_size<s;_elem[_size++]=v);
}

template <typename T>
int Vector<T>::disordered() const
{
  int count=0;
  for(int i=0;i<_size-1;i++)
    if(_elem[i]>_elem[i+1])
      count++;
  return count;
}

template <typename T>
int Vector<T>::find(T const & e,int lo,int hi) const
// if e not in _elem, return lo-1.
{
  while((lo<hi--)&&(_elem[hi]!=e));
  return hi;
}

template <typename T>
Vector<T> & Vector<T>::operator=(Vector<T> const & v)
{
  if(_elem) delete [] _elem;
  copyFrom(v._elem,0,v._size);
  return *this;
}

template <typename T>
void Vector<T>::expand()
{
  if(_size<_capacity) return;
  if(_capacity<DEFAULT_CAPACITY) _capacity=DEFAULT_CAPACITY;
  T * old_elem=_elem;
  _elem=new T[_capacity<<=1];
  for(int i=0;i<_size;i++)
    _elem[i]=old_elem[i];
  delete [] old_elem;
}

template <typename T>
void Vector<T>::shrink()
{
  if(_capacity<DEFAULT_CAPACITY<<1) return;
  if(_size<<2>_capacity) return;
  T * old_elem=_elem;
  _elem=new T[_capacity>>=1];
  for(int i=0;i<_size;i++)
    _elem[i]=old_elem[i];
  delete old_elem;
}

template <typename T>
T & Vector<T>::operator[](int r) const
{
  return _elem[r];
}

template <typename T>
void Vector<T>::permute(int lo,int hi)
{
  for(int i=lo;i<hi;i++)
  {
    int rand_r=i+(std::rand()%(hi-i));
    T tmp=_elem[i];
    _elem[i]=_elem[rand_r];
    _elem[rand_r]=tmp;
  }
}

template <typename T>
int Vector<T>::insert(int r,T const & e)
{
  expand();
  _size++;
  for(int i=_size-1;i>r;i--)
    _elem[i]=_elem[i-1];
  _elem[r]=e;
  return r;
}

template <typename T>
T Vector<T>::remove(int r)
{
  T tmp=_elem[r];
  for(int i=r;i<_size-1;i++)
    _elem[i]=_elem[i+1];
  _size--;
  return tmp;
}

template <typename T>
int Vector<T>::remove(int lo,int hi)
{
  if(lo==hi) return 0;
  int len=hi-lo;
  while(lo++<_size-len)
    _elem[lo-1]=_elem[lo-1+len];
  _size-=len;
  shrink();
  return len;
}

template <typename T>
int Vector<T>::deduplicate()
{
  int old_size=_size;
  for(int i=1;i<_size;i++)
    for(int j=0;j<i;j++)
      if(_elem[j]==_elem[i])
      {
        remove(i--);
        break;
      }
  return old_size-_size;
}

template <typename T>
template <typename VST>
void Vector<T>::traverse(VST & visit)
{for (int i=0;i<_size;i++) visit(_elem[i]);}

template <typename T>
int Vector<T>::uniquify()
  //The time complexity was O(n)  compared to the O(n^2) of deduplicate.
  //But the uniquify can only be used for sorted vector.
{
  int i=0,j=0;
  while(j++<_size)
    if(_elem[j+1]!=_elem[j])
      _elem[++i]=_elem[j+1];
  _size=++i;
  shrink();
  return j-i;
}

template <typename T>
int Vector<T>::search(T const &e,int lo,int hi) const
{
  //This was the first version of binary search.
  while(lo<hi)
  {
    int mid=(lo+hi)>>1;
    if(_elem[mid]<e)  lo=mid+1;
    else if(_elem[mid]>e) hi=mid;
    else return mid;
  }
  return -1;
  //end of binary search.
  
}

template <typename T>
void Vector<T>::bubble_sort(int lo,int hi)
{
  bool sorted=false;
  while(!sorted)
  {
    sorted=true;
    for(int i=lo;i<hi-1;i++)
      if(_elem[i+1]<_elem[i])
      {
        T tmp=_elem[i];
        _elem[i]=_elem[i+1];
        _elem[i+1]=tmp;
        sorted=false;
      }
    hi--;
  }
}

template <typename T>
void Vector<T>::merge_sort(int lo,int hi)
{
  if(hi-lo<2) return;
  int mid=(lo+hi)>>1;
  merge_sort(lo,mid);
  merge_sort(mid,hi);
  merge(lo,mid,hi);
}

template <typename T>
void Vector<T>::merge(int lo,int mid,int hi)
{
  T * tmp=new T[mid-lo];
  for(int i=lo;i<mid;i++) tmp[i-lo]=_elem[i];
  int i=0,j=mid,k=lo;
  while(i<mid-lo && j<hi)
  {
    if(tmp[i]<_elem[j])
      _elem[k++]=tmp[i++];
    else
      _elem[k++]=_elem[j++];
  }

  while(i<mid-lo)
    _elem[k++]=tmp[i++];

  delete [] tmp;
}

std::ostream & operator<<(std::ostream & os, Vector<int> const & v)
{
  for(int i=0;i<v._size;i++)
    os<<v._elem[i]<<", ";
  return os;
}


#endif
