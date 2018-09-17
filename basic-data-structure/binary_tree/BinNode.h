#ifndef BIN_NODE_H_
#define BIN_NODE_H_
#include "../stack/stack.h"
#include "../queue/queue.cpp"

template <typename T>
class BinNode
{
  private:
    T _data;
    BinNode<T> * _parent,* _lChild,* _rChild;
    int _height;
  public:
    BinNode():_parent(nullptr),_lChild(nullptr),_rChild(nullptr),_height(0) {};
    BinNode(T e,BinNode<T> *p=nullptr,BinNode<T> * lc=nullptr,BinNode<T> * rc=nullptr,
        int h=0):_data(e),_parent(p),_lChild(lc),_rChild(rc),_height(h){};
    BinNode<T> * & parent(){return _parent;}; // return the reference of _parent;
    BinNode<T> * & lChild(){return _lChild;};
    BinNode<T> * & rChild(){return _rChild;};
    BinNode<T> * succ_I();  // give the direct succ of a binary node in travIn()
    T & data(){return _data;};
    int & height() {return _height;};
    int size();
    BinNode<T> * insertAsLC(const T & e){return _lChild=new BinNode(e,this);};
    BinNode<T> * insertAsRC(const T & e){return _rChild=new BinNode(e,this);};

    bool operator<(const BinNode & bn) const  {return _data<bn._data;};
    bool operator>(const BinNode & bn) const {return _data>bn._data;};
    bool operator==(const BinNode & bn) const {return _data==bn._data;};

    bool IsRoot(){return !(_parent);};
    bool IsLChild(){return !IsRoot() && this==_parent->_lChild;};
    bool IsRChild(){return !IsRoot() && this==_parent->_rChild;};
    bool HasParent(){return !IsRoot();};
    bool HasLChild(){return _lChild;};
    bool HasRChild(){return _rChild;};
    bool HasChild(){return HasLChild() || HasRChild();};
    bool HasBothChild(){return HasLChild() && HasRChild();};
    bool IsLeaf(){return !HasChild();};
    BinNode<T> * sibling(){return IsLChild()?_parent->_rChild:_parent->_lChild;};
    BinNode<T> * uncle(){return _parent->IsLChild()?_parent->_parent->_rChild:_parent->_parent->_lChild;};
};

template <typename T>
int BinNode<T>::size()
{
  if(IsLeaf()) return 1;
  if(HasLChild() && !(HasRChild())) return 1+_lChild->size();
  if(HasRChild() && !(HasLChild())) return 1+_rChild->size();
  return 1+_lChild->size()+_rChild->size();
}


template <typename T>
int height(BinNode<T> * bn) {return bn?bn->height():-1;}; //return the height of a node,
                                                          //if it's nullptr,
                                                          //return -1

template <typename T,typename VST>
void travPre_R(BinNode<T> * x, VST & visit)
{
  if(x==nullptr) return;
  visit(x->data());
  travPre_R(x->lChild(),visit);
  travPre_R(x->rChild(),visit);
}

template<typename T, typename VST>
void travPre_I(BinNode<T> * x, VST & visit)
{
  Stack<BinNode<T> * > path;
  while(true)
  {
    visit(x->data());
    path.push(x->rChild());
    if(x->HasLChild())
      x=x->lChild();
    else
    {
      if(path.empty()) break;
      x=path.pop();
    }
  }
}

template <typename T, typename VST>
void travPre_I2(BinNode<T> * x, VST & visit)
{
  Stack<BinNode<T> *> path;
  while(true)
  {
    while(x)
    {
      visit(x->data());
      path.push(x->rChild());
      x=x->lChild();
    }
    if(path.empty()) break;
    x=path.pop();
  }
}


template <typename T, typename VST>
void travIn_R(BinNode<T> * x, VST & visit)
{
  if(x==nullptr) return;
  travIn_R(x->lChild(),visit);
  visit(x->data());
  travIn_R(x->rChild(),visit);
}

template <typename T, typename VST>
void travIn_I(BinNode<T> * x, VST & visit)
{
  Stack<BinNode<T> *> path;
  while(true)
  {
    path.push(x);
    if(x->HasLChild())
      x=x->lChild();
    else
    {
      while((!path.empty()) && (x=path.pop())->rChild()==nullptr)
        visit(x->data());
      if(path.empty()) break;
      visit(x->data());
      x=x->rChild();
    }
  }
}

template <typename T, typename VST>
void travIn_I2(BinNode<T> * x, VST & visit)  // This algorithm was similar to the travIn_I1.
{
  Stack<BinNode<T> * > path;
  while(true)
  {
    while(x)
    {
      path.push(x);
      x=x->lChild();
    }
    if(path.empty()) break;
    x=path.pop();visit(x->data());
    x=x->rChild();
  };
}

template <typename T, typename VST>
void travIn_I3(BinNode<T> *x ,VST & visit)  // This is same to the I2
{
  Stack<BinNode<T> *> path;
  while(true)
  {
    if(x)
    {
      path.push(x);
      x=x->lChild();
    }
    else if(!path.empty())
    {
      x=path.pop();
      visit(x->data());
      x=x->rChild();
    }
    else
      break;
  }
}

template <typename T, typename VST>
void travIn_I4(BinNode<T> *x,VST & visit) // implementation of travIn without stack.
{
  bool backtrack=false;
  while(true)
  {
    if(!backtrack && x->HasLChild())
      x=x->lChild();
    else
    {
      visit(x->data());
      if(x->HasRChild())
      {
        x=x->rChild();
        backtrack=false;
      }
      else
      {
        if((x=x->succ_I())==nullptr) break;
        backtrack=true;
      }
    }
  }
}


template <typename T>
BinNode<T> * BinNode<T>::succ_I()
{
  BinNode<T> * s=this;
  if(HasRChild())
  {
    s=_rChild();
    while(s->HasLChild())
      s=s->_lChild;
  }
  else
  {
    while(s->IsRChild()) s=s->parent;
    s=s->parent;
  }
  return s;
}

template <typename T, typename VST>
void travPost_R(BinNode<T> * x, VST & visit)
{
  if(x==nullptr) return;
  travPost_R(x->lChild(),visit);
  travPost_R(x->rChild(),visit);
  visit(x->data());
}

template <typename T, typename VST>
void travPost_I(BinNode<T> * x, VST & visit)
{
  Stack<BinNode<T> * > path;
  path.push(x);
  while(true)
  {
    if(path.empty()) break;
    if(x->parent()!=path.top())
    {
      x=path.top();
      while(x)  //add the node and their right child to the Stack;
      {
        if(x->HasLChild())
        {
          if(x->HasRChild()) path.push(x->rChild());
          x=x->lChild();
          path.push(x);
        } 
        else
          x=x->rChild();
      }
    }

    x=path.pop();
    visit(x->data());
  }
}

template <typename T, typename VST>
void travLevel(BinNode<T> *x, VST & visit)
{
  Queue<BinNode<T> * > path;
  path.enqueue(x);
  while(path.last())
  {
    x=path.dequeue();
    visit(x->data());
    if(x->HasLChild()) path.enqueue(x->lChild());
    if(x->HasRChild()) path.enqueue(x->rChild());
  }
}





#endif


