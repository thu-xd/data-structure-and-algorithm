#ifndef LIST_NODE_H_
#define LIST_NODE_H_

template <typename T>
struct ListNode
{
  T data;
  ListNode<T> * pred;
  ListNode<T> * succ;

  ListNode() {};
  ListNode(T e, ListNode<T> * p=0, ListNode<T> * s=0)
    :data(e),pred(p),succ(s) {};

  ListNode<T> * insertAsPred(T const & e);
  ListNode<T> * insertAsSucc(T const & e);
};

template <typename T>
ListNode<T> * ListNode<T>::insertAsPred(T const & e)
{
  ListNode<T> * tmp=new ListNode<T>(e,pred,this);
  pred->succ=tmp;
  pred=tmp;
  return tmp;
}

template <typename T>
ListNode<T> * ListNode<T>::insertAsSucc(T const & e)
{
  ListNode<T> * tmp=new ListNode<T>(e,this,succ);
  succ->pred=tmp;
  succ=tmp;
  return tmp;
}

#endif
