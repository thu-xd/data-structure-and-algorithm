struct ListNode
{
    int val;
    ListNode * next;
    ListNode(int x):val(x),next(nullptr){};
};

class Solution
{
    public:
        ListNode * reverseKGroup(ListNode * head, int k)
        {
            ListNode * virtual_head=new ListNode(0); 
            ListNode * group_parent=virtual_head, * cursor=head, * group_tail=nullptr;
            int count=0;
            while(cursor)
            {
                if(!group_tail) group_tail=cursor;
                ListNode * tmp=cursor->next;
                insert_after(group_parent,cursor);
                cursor=tmp;
                count++;
                if(count==k)
                {
                    group_parent=group_tail;
                    group_tail=nullptr;
                    count=0;
                }
            }
            if(count)    //If the number of nodes is not a multiple of k
            {
                cursor=group_parent->next;
                group_parent->next=nullptr;
                while(cursor)
                {
                    ListNode * tmp=cursor->next;
                    insert_after(group_parent,cursor);
                    cursor=tmp;
                }
            }
            return virtual_head->next;
        }

        void insert_after(ListNode * parent, ListNode * cursor)
        {
            ListNode * tmp=parent->next;
            parent->next=cursor;
            cursor->next=tmp;
        }
};


                
            



