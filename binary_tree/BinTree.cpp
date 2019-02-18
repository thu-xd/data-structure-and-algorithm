#include <iostream>
#include "BinNode.h"

template <typename T>
class BinTree
{
  private:
    BinNode<T> * _root;
    int _size;
    void updateHeightAbove(BinNode<T> * x); //update the height of the anccestor of x
    static int removeAt(BinNode<T> * x);
  public:
    BinTree():_size(0),_root(nullptr) {};
    ~BinTree() {if(_root!=nullptr) remove(_root);};
    int size() const {return _size;};
    int remove(BinNode<T> * x);
    bool empty() const {return _size>0;};
    BinNode<T> * root() {return _root;};
    BinNode<T> * insertAsRoot(const T & e);
    BinNode<T> * insertAsLC(BinNode<T> * x, const T & e);
    BinNode<T> * insertAsRC(BinNode<T> * x, const T & e);
    BinNode<T> * attachAsLC(BinNode<T> * x, BinTree<T> * S);
    BinNode<T> * attachAsRC(BinNode<T> * x, BinTree<T> * S);
    BinTree<T> * secede(BinNode<T> * x);

};

template <typename T>
void BinTree<T>::updateHeightAbove(BinNode<T> * x)
{
  if(x==nullptr) return;
  do
  {
    int l=height(x->lChild()); // height(BinNode <T> *) was a no-member function in the BinNode.h
    int r=height(x->rChild());
    x->height()=l>r?l+1:r+1;
  }while((x=x->parent())!=nullptr);
}

template <typename T>
int BinTree<T>::remove(BinNode<T> * x)
{
  if(!x->IsRoot())
    x->IsLChild()?(x->parent()->lChild()=nullptr):(x->parent()->rChild()=nullptr);
  updateHeightAbove(x->parent());
  int n=removeAt(x);
  _size-=n;
  return n;
}

template <typename T>
int BinTree<T>::removeAt(BinNode<T> * x)
{
  if(x==nullptr) return 0;
  int n=1+removeAt(x->lChild())+removeAt(x->rChild());
  delete x;
  return n;
}

template <typename T>
BinNode<T> * BinTree<T>::insertAsRoot(const T & e)
{
  _root=new BinNode<T>(e);
  _size=1;
  return _root;
}

template <typename T>
BinNode<T> * BinTree<T>::insertAsLC(BinNode<T> * x, const T & e)
{
  x->lChild()=new BinNode<T>(e);
  _size++;
  updateHeightAbove(x);
  return x->lChild();
}

template <typename T>
BinNode<T> * BinTree<T>::insertAsRC(BinNode<T> * x, const T & e)
{
  x->rChild()=new BinNode<T>(e);
  _size++;
  updateHeightAbove(x);
  return x->rChild();
}

template <typename T>
BinNode<T> * BinTree<T>::attachAsLC(BinNode<T> * x, BinTree<T> * S)
{
  if((x->lChild()=S->root())!=nullptr) x->lChild()->parent()=x;
  _size+=S->size();
  updateHeightAbove(x);
  delete S;
  return x;
}

template <typename T>
BinNode<T> * BinTree<T>::attachAsRC(BinNode<T> * x, BinTree<T> * S)
{
  if((x->rChild()=S->root())!=nullptr) x->rChild()->parent()=x;  // x->rChild() must return a reference .
  _size+S->size();
  updateHeightAbove(x);
  delete S;
  return x;
};

template <typename T>
BinTree<T> * BinTree<T>::secede(BinNode<T> * x)
{
  x->IsLChild()?(x->parent()->lChild()==nullptr):(x->parent()->rChild()==nullptr);
  updateHeightAbove(x->parent());
  x->parent()=nullptr;
  BinTree<T> * new_tree=new BinTree;
  new_tree->_root=x;
  new_tree->_size=x->size();
  _size-=new_tree->_size;
  return new_tree;
}

