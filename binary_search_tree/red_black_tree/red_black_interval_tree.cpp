//This code was a interval tree implementation which based on the red black tree.
#include<algorithm>
#include<iostream>
typedef enum {RB_RED,RB_BLACK} RB_COLOR;

template<typename T>   //The type T must have define the operator<
struct Interval 
{
    T lo,hi;
    Interval(T _lo=T(),T _hi=T()):lo(_lo),hi(_hi){};
    bool operator<(const Interval<T> & val)const  { return lo<val.lo;};  // using lo as the key
    bool operator>(const Interval<T> & val)const  { return !(*this<val);};
    bool operator==(const Interval<T> & val)const  { return lo==val.lo && hi==val.hi;};
};

template<typename T>
bool Interval_overlap(const Interval<T> & a, const Interval<T> & b)
{
    return a.lo<=b.hi && b.lo<=a.hi;
}
   

template<typename T>
struct Node
{
    Interval<T> val;    // The red black tree using the val.lo as the key.
                        // There were no same key in the tree.
    RB_COLOR color;
    T max_hi;      // maxmium hi in the descendants
    Node * left, * right, * parent;
    Node(Interval<T> _val=Interval<T>(),RB_COLOR _color=RB_BLACK,Node * _left=nullptr,
      Node * _right=nullptr, Node * _parent=nullptr)
    :val(_val),color(_color),left(_left),right(_right),parent(_parent)
    {
        if(left) left->parent=this;
        if(right) right->parent=this;
        if(parent) (parent->val<val)?(parent->right=this):(parent->left=this);
        update_node_max_hi_above(this);
    }
};

template<typename T>
void update_node_max_hi(Node<T> * node)
    //Update the max_hi of the node.
{
    if(!node) return;
    Node<T> * left=node->left, * right=node->right;
    if(!left && !right) node->max_hi=node->val.hi;
    else if(!left) node->max_hi=std::max(node->val.hi,node->right->max_hi);
    else if(!right) node->max_hi=std::max(node->val.hi,node->left->max_hi);
    else node->max_hi=std::max(std::max(node->left->max_hi,node->right->max_hi),node->val.hi);
}

template<typename T>
void update_node_max_hi_above(Node<T> * node)
    //Update the max_hi above the node.
{
    while(node)
    {
        update_node_max_hi(node);
        node=node->parent;
    }
}

template<typename T>
bool is_left(Node<T> * p){return p->parent->left==p;};

template<typename T>
bool is_right(Node<T> * p){return p->parent->right==p;};

template<typename T>
bool is_black(Node<T> * p) {return (!p) || (p->color==RB_BLACK);};

template<typename T>
bool is_red(Node<T> * p) {return !(is_black(p));};

template<typename T>
class Red_Black_Interval_Tree
{
  private:
    Node<T> * _root;
    Node<T> * last_valid_node;  //This is just a temp node which track the cursor and log the last valid node
                                //before the cursor became nullptr.
    void solve_double_red(Node<T> * x);
    void solve_double_black(Node<T> * child,Node<T> * parent);
    void right_rotation(Node<T> * x);
    void left_rotation(Node<T> * x);
  public:
    Red_Black_Interval_Tree(){_root=nullptr;};
    Node<T> * root(){return _root;};
    Node<T> * search(const Interval<T> & val);
    Node<T> * insert(const Interval<T> & val);
    void erase(const Interval<T> & val);
    Node<T> * interval_search(const Interval<T> & val);
};

template<typename T>
Node<T> * Red_Black_Interval_Tree<T>::search(const Interval<T> & val)
  //search element e in the red black tree.
  //If not found, return nullptr and the temp variable last_valid_node restore
  //the last valid node cursor visited.
{
  Node<T> * cursor=_root;
  last_valid_node=nullptr;
  while(cursor)
  {
    if(cursor->val==val)
      return cursor;
    else
    {
      last_valid_node=cursor;
      if(cursor->val>val)
        cursor=cursor->left;
      else
        cursor=cursor->right;
    }
  }
  return cursor;
}

template<typename T>
Node<T> * Red_Black_Interval_Tree<T>::insert(const Interval<T> & val)
  //insert new element e into the red black tree.
{
  Node<T> * pos=search(val);
  if(pos) return pos;
  if(!last_valid_node) return _root=new Node<T>(val);
  Node<T> * insert_node=new Node<T>(val,RB_RED,nullptr,nullptr,last_valid_node);
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
void Red_Black_Interval_Tree<T>::solve_double_red(Node<T> * x)   //x must be red.
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
void Red_Black_Interval_Tree<T>::erase(const Interval<T> & val)
  //The implementation of delete in red black tree was disgusting.
  //We will first implement the odinary BST delete.
{
  Node<T> * pos=search(val);
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
  update_node_max_hi_above(parent);
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
void Red_Black_Interval_Tree<T>::solve_double_black(Node<T> * child, Node<T> * parent)
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
Node<T> * Red_Black_Interval_Tree<T>::interval_search(const Interval<T> & val)
    //Find a node in the red black tree whose val was overlap with val.
{
    Node<T> * cursor=_root;
    while(cursor)
    {
        if(Interval_overlap(cursor->val,val))
            return cursor;
        else if(cursor->max_hi>val.lo)
            cursor=cursor->left;
        else
            cursor=cursor->right;
    }
    return cursor;
}

template <typename T>
void Red_Black_Interval_Tree<T>::right_rotation(Node<T> * x)
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
  update_node_max_hi(x);
  update_node_max_hi(left);   //Update the max_hi of x and l.
}

template<typename T>
void Red_Black_Interval_Tree<T>::left_rotation(Node<T> * x)
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
  update_node_max_hi(x);
  update_node_max_hi(right);
}

