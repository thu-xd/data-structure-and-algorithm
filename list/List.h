#ifndef LIST_H_
#define LIST_H_
#include "ListNode.h"
#include <iostream>

template <typename T>
class List
{
  private:
    int _size;
    ListNode<T> * header;
    ListNode<T> * trailer;
  protected:
    void init();
    void clear();
    void copyNodes(ListNode<T> *,int);
    void merge_sort(ListNode<T> *lo,ListNode <T> * hi);
    void merge(ListNode<T> *lo,ListNode<T> * mid,ListNode<T> * hi);
    int get_rank(ListNode<T> * p) const;  //get the rank which corrsponding to the ListNode<T> * p
    ListNode <T> * get_link(int r) const;   //get the ListNode<T> * which corresponding to the rank r.

  public:
    List(){init();};
    List(List<T> const & L) {copyNodes(L.header->succ,L._size);};
    List(ListNode<T> *p,int n) {copyNodes(p,n);};
    List(List<T> const & L,int r,int n);
    ~List();
    ListNode<T> * first(){return header->succ;};
    bool empty(){return _size==0;};
    ListNode<T> * last(){return trailer->pred;};
    T & operator[](int r) const;
    ListNode<T> * insertAsFirst(T const & e);
    ListNode<T> * insertAsLast(T const & e);
    ListNode<T> * insertBefore(ListNode<T> * p,T const & e);
    ListNode<T> * insertAfter(ListNode<T> * p,T const & e);
    T remove(ListNode<T> *p);
    ListNode<T> * find(T const & e) const {return find(e,_size,trailer);};
    ListNode<T> * find(T const & e,int n,ListNode<T> * p) const;
    int deduplicate();
    template<typename VST> void traverse(VST & visit);
    int uniquify();//for sorted vector.
    ListNode<T> * search(T const & e,int n,ListNode<T> * p) const;
    void insert_sort();
    void select_sort();
    void merge_sort();
    friend std::ostream & operator<<(std::ostream & os, const List<T> & L);
    
    
};


template <typename T>
void List<T>::init()
{
  header=new ListNode<T>;
  trailer=new ListNode<T>;
  header->succ=trailer;
  header->pred=0;
  trailer->succ=0;
  trailer->pred=header;
  _size=0;
}

template <typename T>
T & List<T>::operator[](int r) const
{
  ListNode<T> * tmp=header->succ;
  while(r--) tmp=header->succ;
  return tmp->data;
}

template <typename T>
int List<T>::get_rank(ListNode<T> *p) const
{
  ListNode<T> * cursor=header;
  for(int i=0;i<_size;i++)
    if((cursor=cursor->succ)==p)
      return i;
}

template <typename T>
ListNode<T> * List<T>::get_link(int r) const
{
  ListNode<T> * cursor=header;
  for(int i=0;i<=r;i++)
    cursor=cursor->succ;
  return cursor;
}

template <typename T>
ListNode<T> * List<T>::find( T const & e,int n,ListNode<T> *p) const
{
  while(n--)
    if((p=p->pred)->data==e)
      return p;
  return 0;
}

template <typename T>
ListNode<T> * List<T>::insertAsFirst(T const & e)
{
  _size++;
  return  header->insertAsSucc(e);
}

template <typename T>
ListNode<T> * List<T>::insertAsLast(T const & e)
{
  _size++;
  return trailer->insertAsPred(e);
}

template <typename T>
ListNode<T> * List<T>::insertBefore(ListNode<T> *p,T const & e)
{
  _size++;
  return p->insertAsPred(e);
}

template <typename T>
ListNode<T> * List<T>::insertAfter(ListNode<T> * p,T const & e)
{
  _size++;
  return p->insertAsSucc(e);
}

template <typename T>
void List<T>::copyNodes(ListNode<T> *p,int n)
{
  init();
  while(n--) {insertAsLast(p->data);p=p->succ;};
}

template <typename T>
List<T>::List(List<T> const & L,int r,int n)
{
  ListNode<T> * tmp=L.header->succ;
  while(r--)
    tmp=tmp->succ;
  copyNodes(tmp,n);
}

template <typename T>
T List<T>::remove(ListNode<T> * p)
{
  p->pred->succ=p->succ;
  p->succ->pred=p->pred;
  T tmp=p->data;
  _size--;
  delete p;
  return tmp;
}

template <typename T>
List<T>::~List()
{
  clear();
  delete header;
  delete trailer;
}

template <typename T>
void List<T>::clear()
{
  while(_size) remove(header->succ);
}

template <typename T>
int List<T>::deduplicate()
{
  if(_size<2) return 0;
  int count=0;
  int r=1;
  ListNode<T> * cursor=header->succ;
  while((cursor=cursor->succ)!=trailer)
  {
    ListNode<T> * tmp=find(cursor->data,r,cursor);
    if(tmp)
    {
      count++;
      remove(tmp);
    }
    else
      r++;
  }
  return count;
}

template <typename T>
template <typename VST>
void List<T>::traverse(VST & visit)
{
  for(ListNode<T> * p=header->succ;p!=trailer;p=p->succ)
    visit(p->data);
}

template <typename T>
int List<T>::uniquify()
{
  if(_size<2) return 0;
  int count=0;
  ListNode<T> * p=header->succ;
  while((p=p->succ)!=trailer)
  {
    if(p->data==(p->pred->data))
    {
      remove(p->pred);
      count++;
    }
  }
}

template <typename T>
ListNode<T> * List<T>::search (T const & e,int n,ListNode<T> *p) const
//The search algorithm of sorted list is almost the same as the find algorithm
//of unsorted algorithm.
{
  while(0<=n--)
    if(((p=p->pred)->data)<=e) break;
  return p;
}

template <typename T>
void List<T>::insert_sort()
{
  ListNode<T> * p=header->succ->succ;
  int i=0;
  while(++i<_size)
  {
    insertAfter(search(p->data,i,p),p->data);
    p=p->succ;
    remove(p->pred);
  }
}

template <typename T>
void List<T>::select_sort()
{
  ListNode<T> * p=trailer->pred;
  ListNode<T> * max_elem;
  int size=_size;
  while(p!=header->succ)
  {
    max_elem=p;
    ListNode<T> * tmp=p->pred;
    for(int i=1;i<size;i++)
    {
      if((tmp->data)>(max_elem->data))
        max_elem=tmp;
      tmp=tmp->pred;
    }
    if(p!=max_elem)
    {
      insertAfter(p,max_elem->data);
      remove(max_elem);
    }
    else
      p=p->pred;
    size--;
  }
}

template <typename T>
void List<T>::merge_sort()
{
  merge_sort(header->succ,trailer);
}

template <typename T>
void List<T>::merge_sort(ListNode<T> * lo,ListNode<T> *hi)
{
 if(lo->succ==hi) return ;
  ListNode<T> * mid=lo;
  ListNode<T> * cursor=lo;
  int count=0;
  while((cursor=cursor->succ)!=hi)
    mid=(((count++)%2==0)?mid->succ:mid);
  int begin=get_rank(lo),medium=get_rank(mid);
  merge_sort(lo,mid);
  merge_sort(mid,hi);
  lo=get_link(begin);
  mid=get_link(medium);// be careful, the lo and mid will changed after merge_sort,so you should get their link
                      // again.
  merge(lo,mid,hi);
}

template <typename T>
void List<T>::merge(ListNode<T> * lo,ListNode<T> *mid,ListNode<T> *hi)
{
  ListNode<T> * cursor1=lo;
  ListNode<T> * cursor2=mid;
  ListNode<T> * stop_cursor1=mid->pred;
  while(cursor1 !=stop_cursor1->succ && cursor2!=hi)
  {
    if(cursor1->data>cursor2->data)
    {
      cursor2=cursor2->succ;
      insertBefore(cursor1,remove(cursor2->pred));
    }
    else
      cursor1=cursor1->succ;
  }
}

std::ostream & operator<<(std::ostream & os, const List<int> & L)
{
  ListNode<int> * p=L.header;
  while((p=p->succ)!=L.trailer)
    os<<p->data<<", ";
  os<<std::endl;
  return os;
}


#endif
