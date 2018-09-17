#include <iostream>
#include <stack>
#include <queue>
using std::queue;
using std::stack;

template <typename T>
struct Node
{
  T data;
  Node * left, *right,*parent;
  int height;
  Node(T _data=T(),Node * _parent=nullptr,Node * _left=nullptr,Node * _right=nullptr,int _height=0):
    data(_data),parent(_parent),left(_left),right(_right),height(_height){};
  bool Is_left_child(){return data<parent->data;};
  bool Is_right_child(){return data>parent->data;};
};

template <typename T>
class BST
{
  protected:
    Node<T> * _root;
    void updateHeightAbove(Node<T> * x);
    void updateHeight(Node<T> * x);
    bool removeAt(const T &,Node<T> * &);
  public:
    BST(){_root=nullptr;};
    Node<T> *  & root(){return _root;};
    Node<T> * search(const T &, Node<T> * &);
    virtual Node<T> * insert(const T &);
    virtual bool remove(const T &);
    void Pre_order();
    void In_order();
    void Post_order();
    void Level_order();
};

template <typename T>
int Height(Node<T> * x)
{
  return x?x->height:-1;
}

template<typename T>
void BST<T>::updateHeight(Node<T> * x)
{
    int left_height=Height(x->left);
    int right_height=Height(x->right);
    x->height=left_height<right_height?right_height+1:left_height+1;
}

template<typename T>
void BST<T>::updateHeightAbove(Node<T> * x)
{
  while(x)
  {
    updateHeight(x);
    x=x->parent;
  }
}

template<typename T>
Node<T> * BST<T>::search(const T & e, Node<T> * & parent_node)
  // The parent_node was a reference to a pointer which point to the father of
  // the found position.If not found, the parent_node give the last visited
  // node.
{
  if(_root==nullptr) return _root;
  Node<T> * x=_root;
  while(x)
  {
    if(x->data==e) return x;
    else
    {
      parent_node=x;
      if(x->data>e) x=x->left;
      else x=x->right;
    }
  }

  return x;
}

template<typename T>
Node<T> * BST<T>::insert(const T & e)
{
  if(_root==nullptr) return _root=new Node<T>(e);
  Node<T> * parent_node;
  Node<T> * pos=search(e,parent_node);
  if(pos) return pos;
  if(parent_node->data>e)
  {
    parent_node->left=new Node<T>(e,parent_node);
    updateHeightAbove(parent_node);
    return parent_node->left;
  }
  else 
  {
    parent_node->right=new Node<T>(e,parent_node);
    updateHeightAbove(parent_node);
    return parent_node->right;
  }
}

template<typename T>
void BST<T>::Pre_order()
{
  stack<Node<T> *> path;
  Node<T> * x=_root;
  while(true)
  {
    while(x)
    {
      std::cout<<x->data<<" ";
      if(x->right!=nullptr) path.push(x->right);
      x=x->left;
    }
    if(path.empty()) break;
    x=path.top();
    path.pop();
  }
  std::cout<<std::endl;
}

template<typename T>
void BST<T>::In_order()
{
  stack<Node<T> *> path;
  Node<T> * x=_root;
  while(true)
  {
    while(x)
    {
      path.push(x);
      x=x->left;
    }
    if(path.empty()) break;
    x=path.top();
    path.pop();
    std::cout<<x->data<<" ";
    x=x->right;
  }
  std::cout<<std::endl;
}

template<typename T>
void BST<T>::Post_order()
{
  stack<Node<T> *> path;
  Node<T> * x=_root;
  bool begin=true;
  while(true)
  {
    if(begin || (!path.empty() && path.top()!=x->parent)) // The begin flag was used to jump the first loop.
    {
      if(!begin) {x=path.top();path.pop();}
      begin=false;
      while(x)
      {
        path.push(x);
        if(x->left!=nullptr)
        {
          if(x->right!=nullptr) path.push(x->right);
          x=x->left;
        }
        else
          x=x->right;
      }
    }
    if(path.empty()) break;
    x=path.top();
    path.pop();
    std::cout<<x->data<<" ";
  }
  std::cout<<std::endl;
}

template<typename T>
void BST<T>::Level_order()
{
  queue<Node<T> *> Q;
  Q.push(_root);
  while(!Q.empty())
  {
    Node<T> * x=Q.front();
    Q.pop();
    std::cout<<x->data<<" ";
    if(x->left!=nullptr) Q.push(x->left);
    if(x->right!=nullptr) Q.push(x->right);
  }
  std::cout<<std::endl;
}

template<typename T>
bool BST<T>::remove(const T & e)
{
  Node<T> * tmp;
  bool result=removeAt(e,tmp);
  updateHeightAbove(tmp);
  return result;
}

template<typename T>
bool  BST<T>::removeAt(const T & e,Node<T> * & parent_of_remove)
  // The parent_of_remove was used to point to the parent of the actual removed
  // node. It could be used in AVL to rebalance the tree.If it don't need to
  // rebalance. The parent_of_remove return nullptr.It has no effect on
  // ordinary BST.
{
  Node<T> * parent_node=nullptr;
  Node<T> * pos=search(e,parent_node);
  if(!pos) return false;
  if(!parent_node)  // The found node was the _root
  {
    if(pos->left==nullptr)
    {
      _root=pos->right;
      if(pos->right) pos->right->parent=nullptr;
      delete pos;
    }
    else if(pos->right==nullptr)   //if the found node was _root and has only one child
    {                              //if it was a AVL tree. you don't need to rebalance.
      _root=pos->left;             
      pos->left->parent=nullptr;   
      delete pos;
    }
  }
  else
  {
    if(pos->left==nullptr)
    {
      ((parent_node->data>e)?parent_node->left:parent_node->right)=pos->right;
      if(pos->right) pos->right->parent=parent_node;
      delete pos;
    }
    else if(pos->right==nullptr)
    {
      ((parent_node->data>e)?parent_node->left:parent_node->right)=pos->left;
      pos->left->parent=parent_node;
      delete pos;
    }
    parent_of_remove=parent_node;
  }

  //The next was used to remove node which has both children
  if(pos->left!=nullptr && pos->right !=nullptr)
  {
    Node<T> * x=pos->right;
    Node<T> * tmp;
    while(x)   //tmp is the succ of pos in Inorder traversal.
    {
      tmp=x;
      x=x->left;
    }

    if(tmp==pos->right)
    {
      if(!parent_node)   //pos==_root;
      {
        Node<T> * s=_root;
        _root=pos->right;
        _root->parent=NULL;
        _root->left=pos->left;
        parent_of_remove=_root;
        delete s;
      }
      else
      {
        pos->data=tmp->data;
        tmp->parent->right=tmp->right;
        if(tmp->right) tmp->right->parent=tmp->parent;
        parent_of_remove=tmp->parent;
        delete tmp;
      }
      return true;
    }

    pos->data=tmp->data;
    tmp->parent->left=tmp->right; //tmp must be the left child and has no left child
    if(tmp->right) tmp->right->parent=tmp->parent;
    parent_of_remove=tmp->parent;
    delete tmp;
  }
  return true;
}
