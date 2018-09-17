#include "red_black_tree.cpp"
#include <ctime>
#include <cstdlib>

template<typename T>
void print_RBT(Node<T> * root)
{
  if(!root) return;
  print_RBT(root->left);
  std::cout<<root->val<<" ";
  print_RBT(root->right);
}


int main()
{
  Red_Black_Tree<int>  tree;
  std::cout<<"How many numbers to insert:__\b\b";
  int N;
  std::cin>>N;
  std::srand(std::time(nullptr));
  for(int i=0;i<N;i++)
    tree.insert(std::rand()%200);
  print_RBT(tree.root());
  std::cout<<std::endl;
  for(int i=0;i<N;i++)
    tree.erase(std::rand()%200);
  print_RBT(tree.root());
  std::cout<<std::endl;
  return 0;
}
