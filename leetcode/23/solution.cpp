#include <vector>
#include <queue>
using std::vector;
using std::priority_queue;

struct ListNode
{
    int val;
    ListNode * next;
    ListNode(int x):val(x),next(nullptr){};
};

struct compare
{
    bool operator()(ListNode * node1, ListNode * node2)
    {
        if(!node2) return false;
        if(!node1) return true;
        return node1->val>node2->val;
    }
};

class Solution
{
    public:
        ListNode * mergeKLists(vector<ListNode *> lists)
        {
            priority_queue<ListNode *, vector<ListNode *>, compare> lists_front(lists.begin(),lists.end());
            ListNode * head=nullptr, * cursor=nullptr;
            while(!lists_front.empty() && lists_front.top())
            {
                if(!head)
                    cursor=head=lists_front.top();
                else
                    cursor=cursor->next=lists_front.top();
                ListNode * new_add=lists_front.top()->next;
                lists_front.pop();
                lists_front.push(new_add);
            }
            return head;
        }
};


