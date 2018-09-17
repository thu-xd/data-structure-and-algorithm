struct ListNode
{
    int val;
    ListNode * next;
    ListNode(int x):val(x),next(nullptr){};
};

class Solution
{
    public:
        ListNode * mergeTwoLists(ListNode * l1, ListNode * l2)
        {
            if(!l1) return l2;
            if(!l2) return l1;
            ListNode * cursor1=l1, * cursor2=l2, * new_head=nullptr, * cursor;
            while(cursor1 && cursor2)
            {
                if(cursor1->val<cursor2->val)
                {
                    if(!new_head)
                        cursor=new_head=cursor1;
                    else
                        cursor=cursor->next=cursor1;
                    cursor1=cursor1->next;
                }
                else
                {
                    if(!new_head)
                        cursor=new_head=cursor2;
                    else
                        cursor=cursor->next=cursor2;
                    cursor2=cursor2->next;
                }
            }
            if(cursor1)
                cursor->next=cursor1;
            else
                cursor->next=cursor2;
            return new_head;
        }
};

