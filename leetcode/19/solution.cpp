struct ListNode
{
    int val;
    ListNode * next;
    ListNode(int x):val(x),next(nullptr){};
};

class Solution
{
    public:
        ListNode * removeNthFromEnd(ListNode * head, int n)
        {
            ListNode * cursor=head, * removed_parent=nullptr;
            while(cursor)
            {
                if(n)
                    n--;
                else
                    (removed_parent)?(removed_parent=head):(removed_parent=removed_parent->next);
                cursor=cursor->next;
            }
            if(!removed_parent)
            {
                ListNode * new_head=head->next;
                delete head;
                return new_head;
            }
            else
            {
                ListNode * removed=removed_parent->next;
                removed_parent->next=removed->next;
                delete removed;
                return head;
            }
        }
};
            
