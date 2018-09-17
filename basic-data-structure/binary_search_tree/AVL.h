#include "BST.h"
template<typename T>
class AVL:public BST<T>
{
  public:
    virtual Node<T> * insert(const T & e);
    virtual bool remove(const T & e);
    void left_R(Node<T> * x);
    void right_R(Node<T> * x);
};

template <typename T>
bool Balanced(Node<T> * x)
{
  return Height(x->left)==Height(x->right);
}

template <typename T>
int Balance_Factor(Node<T> * x)
{
  return Height(x->left)-Height(x->right);
}

template <typename T>
bool AVL_balanced(Node<T> * x)
{
  return Balance_Factor(x)<2 && Balance_Factor(x)>-2;
}

template <typename T>
void AVL<T>::right_R(Node<T> * y)
{
  /*      y             x                   */
  /*     / \           / \                  */
  /*    x   T3  --->  T1  y                 */
  /*   / \               / \                */
  /*  T1  T2            T2 T3               */

  if(y->left==nullptr) return;
  Node<T> * x=y->left;
  if(y==this->_root)
  {
    this->_root=x;
    x->parent=nullptr;
  }
  else
  {
    y->Is_left_child()?y->parent->left=x:y->parent->right=x;
    x->parent=y->parent;
  }
  y->left=x->right;
  if(y->left) y->left->parent=y;
  x->right=y;
  y->parent=x;
}

template <typename T>
void AVL<T>::left_R(Node<T> * y)
{
  /*          y                      x  
   *         / \                    / \
   *        T1  x       --->       y  T3
   *           / \                / \
   *          T2  T3             T1  T2           */
  if(y->right==nullptr) return;
  Node<T> * x=y->right;
  if(y==this->_root) 
  {
    this->_root=x;
    x->parent=nullptr;
  }
  else
  {
    y->Is_left_child()?y->parent->left=x:y->parent->right=x;
    x->parent=y->parent;
  }
  y->right=x->left;
  if(y->right) y->right->parent=y;
  x->left=y;
  y->parent=x;
}

template <typename T>
Node<T> * AVL<T>::insert(const T & e)
{
  if(this->_root==nullptr) return this->_root=new Node<T>(e);
  Node<T> * parent_node;
  Node<T> * pos=BST<T>::search(e,parent_node);
  if(pos) return pos;
  if(e<parent_node->data)
    pos=parent_node->left=new Node<T>(e,parent_node);
  else
    pos=parent_node->right=new Node<T>(e,parent_node);

  Node<T> * grand_child=pos;
  Node<T> * son=parent_node; // log the son and grand_child of the g.
  int count=0;
  for(Node<T> * g=parent_node;g;g=g->parent)
  {
    if(count++>1)
    {
      grand_child=grand_child->parent;
      son=son->parent;
    }
    this->updateHeight(g);   //the height above the g was not changed. 
    if(!AVL_balanced(g))
    {
      if(son->Is_left_child() && grand_child->Is_left_child())
      { right_R(g);this->updateHeight(g);this->updateHeight(grand_child);this->updateHeight(son);}
      else if(son->Is_left_child() && grand_child->Is_right_child())
      {
        left_R(son);
        right_R(g);
        this->updateHeight(son);this->updateHeight(g);this->updateHeight(grand_child);
      }
      else if(son->Is_right_child() && grand_child->Is_left_child())
      {
        right_R(son);
        left_R(g);
        this->updateHeight(son);this->updateHeight(g);this->updateHeight(grand_child);
      }
      else
      { left_R(g);this->updateHeight(g);this->updateHeight(grand_child);this->updateHeight(son);}
      break;
    }
  }

  return pos;
}

template <typename T>
bool AVL<T>::remove(const T & e)
{
  Node<T> * parent_node=nullptr;
  bool result=BST<T>::removeAt(e,parent_node);  // call the removeAt function of BST, but no height update.
  if(!parent_node) return result;
  for(Node<T> * g=parent_node;g;g=g->parent)
  {
    this->updateHeight(g);
    if(!AVL_balanced(g))
    {
      Node<T> * son=(Height(g->left)>=Height(g->right))?g->left:g->right;
      Node<T> * grand_child;
      if(Height(son->left)>Height(son->right))
        grand_child=son->left;
      else if(Height(son->left)<Height(son->right))
        grand_child=son->right;
      else
        grand_child=(son->Is_left_child())?son->left:son->right;

      if(son->Is_left_child() && grand_child->Is_left_child())
      {
        right_R(g);
        this->updateHeight(g);this->updateHeight(grand_child);this->updateHeight(son);
        g=son;
      }
      else if(son->Is_left_child() && grand_child->Is_right_child())
      {
        left_R(son);
        right_R(g);
        this->updateHeight(son);this->updateHeight(g);this->updateHeight(grand_child);
        g=grand_child;
      }
      else if(son->Is_right_child() && grand_child->Is_left_child())
      {
        right_R(son);
        left_R(g);
        this->updateHeight(son);this->updateHeight(g);this->updateHeight(grand_child);
        g=grand_child;
      }
      else
      {
        left_R(g);
        this->updateHeight(g);this->updateHeight(grand_child);this->updateHeight(son);
        g=son;
      }
    }
  }

  return result;
}



