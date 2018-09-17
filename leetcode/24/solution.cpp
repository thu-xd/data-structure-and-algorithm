struct ListNode
{
    int val;
    ListNode * next;
    ListNode(int x):val(x),next(nullptr){};
};


class Solution
{
    public:
        ListNode * swapPairs(ListNode * head)
        {
            if((!head) || (!head->next)) return head;
            ListNode * parent=nullptr, * first=head, * second=first->next;
            ListNode * tmp=second->next;
            head=second;
            head->next=first;
            head->next->next=tmp;
            parent=head->next;

            while(parent->next && parent->next->next)
            {
                first=parent->next;
                second=first->next;
                ListNode * tmp=second->next;
                parent->next=second;
                parent->next->next=first;
                parent->next->next->next=tmp;
                parent=parent->next->next;
            }
            return head;
        }
};
                
