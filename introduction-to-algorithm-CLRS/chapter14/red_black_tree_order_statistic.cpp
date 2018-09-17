//This is a augmentation for red black tree for order statistic which can
//select the k-th smaller element in O(logn) time. The basic red black tree
//implementation was just copy from chapter13. The key point for high
//performance order statistic was store the number of descendants in each
//nodes.
#include<algorithm>
#include<iostream>
typedef enum {RB_RED,RB_BLACK} RB_COLOR;

template<typename T>
struct Node
{
  T val;
  RB_COLOR color;
  Node * left, * right, * parent;
  int size;   //The size of the subtree rooted at this node. The size of nullptr was 0.
  Node(T _val=T(),RB_COLOR _color=RB_BLACK,Node * _left=nullptr,
      Node * _right=nullptr, Node * _parent=nullptr, int _size=1)
    :val(_val),color(_color),left(_left),right(_right),parent(_parent),size(_size){};
};

template<typename T>
bool is_left(Node<T> * p){return p->parent->left==p;};

template<typename T>
bool is_right(Node<T> * p){return p->parent->right==p;};

template<typename T>
bool is_black(Node<T> * p) {return (!p) || (p->color==RB_BLACK);};

template<typename T>
bool is_red(Node<T> * p) {return !(is_black(p));};

template<typename T>
int size(Node<T> * p) {return (p)?(p->size):0;};

template<typename T>
void update_size(Node<T> * p) { p->size=size(p->left)+size(p->right)+1;};

template<typename T>
void update_size_above(Node<T> * p)
{
  while(p)
  {
    update_size(p);
    p=p->parent;
  }
}

template<typename T>
class Red_Black_Tree_Order_Statistic
{
  private:
    Node<T> * _root;
    Node<T> * last_valid_node;  //This is just a temp node which track the cursor and log the last valid node
                                //before the cursor became nullptr.It can
                                //simplify the function call.
    void solve_double_red(Node<T> * x);
    void solve_double_black(Node<T> * child,Node<T> * parent);
    void right_rotation(Node<T> * x);
    void left_rotation(Node<T> * x);
  public:
    Red_Black_Tree_Order_Statistic(){_root=nullptr;};
    Node<T> * root(){return _root;};
    Node<T> * search(const T & e);
    Node<T> * insert(const T & e);
    void erase(const T & e);
    T select_K(int K);
    int rank(const T & e);
};

template<typename T>
Node<T> * Red_Black_Tree_Order_Statistic<T>::search(const T & e)
  //search element e in the red black tree.
  //If not found, return nullptr and the temp variable last_valid_node restore
  //the last valid node cursor visited.
{
  Node<T> * cursor=_root;
  last_valid_node=nullptr;
  while(cursor)
  {
    if(cursor->val==e)
      return cursor;
    else
    {
      last_valid_node=cursor;
      if(cursor->val>e)
        cursor=cursor->left;
      else
        cursor=cursor->right;
    }
  }
  return cursor;
}

template<typename T>
Node<T> * Red_Black_Tree_Order_Statistic<T>::insert(const T & e)
  //insert new element e into the red black tree.
{
  Node<T> * pos=search(e);
  if(pos) return pos;
  if(!last_valid_node) return _root=new Node<T>(e);
  Node<T> * insert_node=new Node<T>(e,RB_RED,nullptr,nullptr,last_valid_node); // pos must be a leaf node.
  (last_valid_node->val>e)?(last_valid_node->left=insert_node):(last_valid_node->right=insert_node);
  //After insertion, we must update the size of the ancestor of the insert nodes
  update_size_above(last_valid_node);
  //Until now, the new node has insert into the red black tree. The new node
  //was set to be red.The reason was that if the new insert node was black then
  //the parent of the insert node will not satisfy the balance black height
  //condition 4. After insertion, only the condition 3 might not satisfied.The
  //parent of new node might be also red. We need to solve the double red
  //problem.
  solve_double_red(insert_node);
  return insert_node;
}

template<typename T>
void Red_Black_Tree_Order_Statistic<T>::solve_double_red(Node<T> * x)   //x must be red.
  //To solve the double red problem after insection.
  //There are two cases.
  //        case1(u==black)
  //   black_height(T1)==black_height(T2)==black_height(T3)==black_height(u)
  //
  //             |                             |
  //            g(b)                          p(b) 
  //           /   \                         /    \
  //          p(r) u(b)      ------>        x(r)  g(r)
  //         /  \   |                       /  \   / \
  //        x(r) T3 T4                     T1  T2 T3  u
  //       /  \
  //      T1   T2
  //
  //        case2(u==red)
  //  black_height(T1)==black_height(T2)==black_height(T3)==black_height(T4)==black_height(T5)
  //
  //             |                              |
  //            g(b)                           g(r)
  //           /    \                         /    \
  //         p(r)   u(r)     ------->        p(b)   u(b)
  //        /   \   / \                     /   \   /  \
  //      x(r)  T3 T4  T5                  x(r) T3 T4  T5
  //       / \                            /   \
  //      T1  T2                         T1    T2
  //For case1 we need not recursive, and the black height of all node was not
  //changed. But for case2, we need recursive. 

{   
  if(x==_root)
  {
    _root->color=RB_BLACK;
    return;
  }

  Node<T> * p=x->parent;
  if(is_black(p)) return;
  Node<T> * g=p->parent;  //g must not be nullptr and g is black
  Node<T> * u=(is_left(p))?g->right:g->left; //The uncle of the x.
  if(is_black(u))   //case 1
  {
    if(is_left(p) && is_left(x))
      right_rotation(g);
    else if(is_left(p) && is_right(x))
    {
      left_rotation(p);
      right_rotation(g);
    }
    else if(is_right(p) && is_left(x))
    {
      right_rotation(p);
      left_rotation(g);
    }
    else
      left_rotation(g);
    g->color=RB_RED;
    g->parent->color=RB_BLACK;
  }
  else             //case 2
  {
    p->color=RB_BLACK;
    u->color=RB_BLACK;
    g->color=RB_RED;
    solve_double_red(g);
  }
}

template <typename T>
void Red_Black_Tree_Order_Statistic<T>::erase(const T & e)
  //The implementation of delete in red black tree was disgusting.
  //We will first implement the odinary BST delete.
{
  Node<T> * pos=search(e);
  if(!pos) return;
  if(!last_valid_node)    //The erased was the _root, pos=_root;
  {
    if(!(pos->left && pos->right))    //If _root has only one child or no child.
    {
      _root=(pos->left)?(pos->left):(pos->right);
      _root->color=RB_BLACK;
      delete pos;
      return;
    }
  }

  //If the pos has both child,then we will swap pos with its successor, then
  //delete successor instead, successor must have less than two children.
  Node<T> * deleted;  //deleted means which node was actually deleted.
  if(pos->left && pos->right)
  {
    deleted=pos->right;
    while(true)
    {
      if(deleted->left)
        deleted=deleted->left;
      else
        break;
    }
    std::swap(pos->val,deleted->val);
  }
  else
    deleted=pos;

  RB_COLOR deleted_node_color=deleted->color;
  Node<T> * child=(deleted->left)?(deleted->left):(deleted->right);
  Node<T> * parent=deleted->parent;
  (is_left(deleted))?(parent->left=child):(parent->right=child);
  if(child) child->parent=parent;
  delete deleted;
  //update the size of the ancestor of the child.
  update_size_above(parent);
  //Until now, the ordinary delete operation has finished. If the deleted node
  //was red, we have finished the delete operation. But if the deleted node was
  //black, then the condition 4 might not satisified. We should deal with this
  //problem.
  if(deleted_node_color==RB_RED) return;
  if(is_red(child))
  {
    child->color=RB_BLACK;
    return;
  }
  //If the deleted node color was not red and the child color was not red.
  //We need the solve double black subroutine.
  solve_double_black(child,parent);
}

template <typename T>
void Red_Black_Tree_Order_Statistic<T>::solve_double_black(Node<T> * child, Node<T> * parent)
  //Child might be nullptr,child might be left or right child of parent.Parent
  //can't be nullptr
  //Solve the double black problem was complicate.There were totally four case.
  //
  // case 1 (sibling's right child was red. The sibling was black)
  //            |                              |                            |
  //           p(?)                           p(b)                         s(?)
  //          /   \                          /    \                        /  \
  //        x(b)  s(b)        ------->     x(b)   s(?)     --------->    p(b) c2(b)
  //             /   \                           /   \                  /   \
  //          c1(?)  c2(r)                    c1(?) c2(b)            x(b) c1(?)
  // case 2 (sibling's left child was red. The sibling was black)
  //       |                         |                              |          
  //      p(?)                      p(?)                           p(?)
  //     /   \                     /    \           case1          /  \
  //   x(b)  s(b)      ------->  x(b)   s(r)     --------->      x(b) c1(b)
  //        /   \                      /   \                          /   \
  //     c1(r)  c2(b)               c1(b) c2(b)                      T1   s(r)
  //    /    \                     /   \                                  /  \
  //   T1    T2                   T1   T2                               T2  c2(b)
  // case 3 (sibling's both child was black. The sibling was black)
  //      |                              |        
  //     p(r)                           p(b)       
  //    /   \                          /    \
  //  x(b)  s(b)        ------->     x(b)   s(r)     
  //       /   \                           /   \
  //    c1(b)  c2(b)                    c1(b) c2(b)
  //
  //      |                              |        
  //     p(b)                           p(b)       
  //    /   \                          /    \
  //  x(b)  s(b)        ------->     x(b)   s(r)   ---->recursive(p)
  //       /   \                           /   \
  //    c1(b)  c2(b)                    c1(b) c2(b)
  // case 4 (The sibling was red)
  //      |                              |                       | 
  //     p(b)                           p(r)                    s(b)
  //    /   \                          /    \                  /    \
  //  x(b)  s(r)        ------->     x(b)   s(b)   ----->    p(r)   c2(b)  --->recursive(x)
  //       /   \                           /   \             /  \
  //    c1(b)  c2(b)                    c1(b) c2(b)        x(b) c1(b)
  //
{
  if(child==_root) return;
  Node<T> * sibling=(parent->left==child)?(parent->right):(parent->left);
  if(is_black(sibling) && ((is_right(sibling) && is_red(sibling->right)) || 
        (is_left(sibling) && is_red(sibling->left))))     //case1
  {
    std::swap(parent->color,sibling->color);
    if(is_left(sibling))
    {
      sibling->left->color=RB_BLACK;
      right_rotation(parent);
    }
    else
    {
      sibling->right->color=RB_BLACK;
      left_rotation(parent);
    }
  }

  else if(is_black(sibling) && ((is_right(sibling) && is_red(sibling->left)) ||
        (is_left(sibling) && is_red(sibling->right))))    //case2
  {
    if(is_left(sibling))
    {
      std::swap(sibling->color,sibling->right->color);
      left_rotation(sibling);
    }
    else
    {
      std::swap(sibling->color,sibling->left->color);
      right_rotation(sibling);
    }
    solve_double_black(child,parent);
  }

  else if(is_black(sibling) && (is_black(sibling->left)) && (is_black(sibling->right)))  //case3
  {
    sibling->color=RB_RED;
    if(is_red(parent))
    {
      parent->color=RB_BLACK;
      return;
    }
    else
      solve_double_black(parent,parent->parent);
  }
  
  else if(is_red(sibling))
  {
    std::swap(parent->color,sibling->color);
    is_left(sibling)?right_rotation(parent):left_rotation(parent);
    solve_double_black(child,parent);
  }
}

template <typename T>
T Red_Black_Tree_Order_Statistic<T>::select_K(int K)
  //select the k-th smallest element in the tree.
  //The 1-th means the smallest.
{
  Node<T> * cursor=_root;
  while(cursor)
  {
    if(size(cursor->left)+1==K)
      return cursor->val;
    else if((size(cursor->left)+1>K))
      cursor=cursor->left;
    else
    {
      K-=(size(cursor->left)+1);
      cursor=cursor->right;
    }
  }
  return T();  //If not found, return the default value of T.This might cause some problems.
}

template <typename T>
int Red_Black_Tree_Order_Statistic<T>::rank(const T & e)
{
  Node<T> * pos=search(e);
  if(!pos) return -1;  //-1 means e don't exist.
  int res=size(pos->left)+1;
  while(pos!=_root)
  {
    if(is_right(pos))
      res+=(size(pos->parent->left)+1);
    pos=pos->parent;
  }
  return res;
}

template <typename T>
void Red_Black_Tree_Order_Statistic<T>::right_rotation(Node<T> * x)
  //Right rotation at x (the left child of x can't be nullptr)
  //              |                    |
  //              x                    l
  //             / \                  / \
  //            l   T3  ----->       T1  x
  //           / \                      / \
  //          T1  T2                   T2  T3
{
  Node<T> * parent=x->parent;
  Node<T> * left=x->left;
  if(parent) (parent->val>x->val)?(parent->left=left):(parent->right=left);
  else _root=left;
  left->parent=parent;
  Node<T> * left_right=left->right;
  left->right=x;
  x->parent=left;
  x->left=left_right;
  if(left_right) left_right->parent=x;
  //update the size of x and left.
  update_size(x);
  update_size(left);
}

template<typename T>
void Red_Black_Tree_Order_Statistic<T>::left_rotation(Node<T> * x)
  //Left rotation at x (the right child of x can't be nullptr)
  //                |                        |
  //                x                        r
  //               / \                      / \
  //              T1  r      ------>       x   T3
  //                 / \                  / \
  //                T2  T3               T1  T2
{
  Node<T> * parent=x->parent;
  Node<T> * right=x->right;
  if(parent) (parent->val>x->val)?(parent->left=right):(parent->right=right);
  else _root=right;
  right->parent=parent;
  Node<T> * right_left=right->left;
  right->left=x;
  x->parent=right;
  x->right=right_left;
  if(right_left) right_left->parent=x;
  //update the size of x and right.
  update_size(x);
  update_size(right);
}
