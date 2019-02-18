#include "red_black_tree_order_statistic.cpp"
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
  Red_Black_Tree_Order_Statistic<int>  tree;
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
  
  for(int i=0;i<10;i++)
  {
    int e=std::rand()%200;
    int r=tree.rank(e);
    if(r!=-1)
      std::cout<<"The rank of "<<e<<" was: "<<r<<std::endl;
    else
      i--;
  }

  for(int i=0;i<10;i++)
  {
    int r=std::rand()%N+1;
    int e=tree.select_K(r);
    if(e!=0)
      std::cout<<"The "<<r<<"-th smallest element was: "<<e<<std::endl;
    else
      i--;
  }
  return 0;
}
