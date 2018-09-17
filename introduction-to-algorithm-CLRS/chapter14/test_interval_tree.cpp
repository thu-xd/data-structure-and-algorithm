#include "red_black_interval_tree.cpp"

int main()
{
    Red_Black_Interval_Tree<int> tree; 
    tree.insert(Interval<int>(0,3));
    tree.insert(Interval<int>(5,8));
    tree.insert(Interval<int>(6,10));
    tree.insert(Interval<int>(8,9));
    tree.insert(Interval<int>(15,23));
    tree.insert(Interval<int>(16,21));
    tree.insert(Interval<int>(17,19));
    tree.insert(Interval<int>(19,20));
    Node<int> *res =tree.interval_search(Interval<int>(4,7));
    std::cout<<"The result was: "<<res->val.lo<<" ,"<<res->val.hi<<std::endl;
    tree.erase(Interval<int>(5,8));
    tree.erase(Interval<int>(0,3));
    res =tree.interval_search(Interval<int>(4,7));
    std::cout<<"The result was: "<<res->val.lo<<" ,"<<res->val.hi<<std::endl;
    return 0;
}
