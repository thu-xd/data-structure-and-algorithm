#include <iostream>
#include <algorithm>

template<typename T>
struct Node
{
  T val;
  Node * left, * right;
  Node(T _val=T(),Node * _left=nullptr, Node * _right=nullptr)
    :val(_val),left(_left),right(_right){};
};

template<typename T>
class BST
//A simple implementation of binary search tree.
{
  private:
    Node<T> * root;
    Node<T> * parent;  //This is just a tmp variable which store the parent of the cursor.
    void _in_order_tranverse(Node<T> * node);
  public:
    BST(){root=nullptr;};
    Node<T> * search(const T & e);
    Node<T> * insert(const T & e);
    void erase(const T & e);
    void in_order_tranverse();
};

template<typename T>
Node<T> * BST<T>::search(const T & e)
  //If not exist, return nullptr.
{
  Node<T> * cursor=root;
  parent=nullptr;
  while(cursor)
  {
    if(cursor->val==e)
      break;
    else
    {
      parent=cursor;
      if(cursor->val<e)
        cursor=cursor->right;
      else
        cursor=cursor->left;
    }
  }
  return cursor;
}

template<typename T>
Node<T> * BST<T>::insert(const T & e)
  //Insert element e into the BST
{
  Node<T> * cursor=search(e);
  if(cursor) return cursor;
  if(!parent) return root=new Node<T>(e);   //parent=nullptr means that this is a new tree.
  if(parent->val>e) return parent->left=new Node<T>(e);
  return parent->right=new Node<T>(e);
}

template<typename T>
void BST<T>::erase(const T & e)
  //We assume that the BST was not empty.
{
  Node<T> * cursor=search(e);
  if(!cursor) return;
  //We should first treat the case that the erase element was the root.
  if(!parent && (!root->left || !root->right))
  {
    Node<T> * child=(root->left)?(root->left):root->right;
    delete root;
    root=child;
    return;
  }

  //We should then treat the case that the erase node has only one child.
  if(!cursor->left || !cursor->right)
  {
    Node<T> * child=(cursor->left)?(cursor->left):(cursor->right);
    delete cursor;
    (parent->val>e)?(parent->left=child):(parent->right=child);
    return;
  }

  //Finally, we should treat the case that the erase node has both child.
  //We need find the successor of the node.
  Node<T> * new_cursor=cursor->right;
  parent=cursor;
  while(true)
  {
    if(new_cursor->left)
    {
      parent=new_cursor;
      new_cursor=new_cursor->left;
    }
    else
      break;
  }
  std::swap(cursor->val,new_cursor->val);

  //Then the problem becames delete new_cursor, which must not have left child;
  Node<T> * child=new_cursor->right;
  delete new_cursor;
  (parent==cursor)?(parent->right=child):(parent->left=child);
}

template<typename T>
void BST<T>::in_order_tranverse()
{
  _in_order_tranverse(root);
}

template<typename T>
void BST<T>::_in_order_tranverse(Node<T> * node)
{
  if(!node) return;
  _in_order_tranverse(node->left);
  std::cout<<node->val<<" ";
  _in_order_tranverse(node->right);
}


int main()
{
  BST<int> tree;
  tree.insert(44);
  tree.insert(17);
  tree.insert(28);
  tree.insert(29);
  tree.insert(88);
  tree.insert(97);
  tree.in_order_tranverse();
  std::cout<<std::endl;
  tree.erase(44);
  tree.in_order_tranverse();
  std::cout<<std::endl;
  tree.erase(17);
  tree.in_order_tranverse();
  std::cout<<std::endl;
  return 0;
}

