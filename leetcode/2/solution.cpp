// Definition for single-linked list
struct ListNode
{
    int val;
    ListNode * next;
    ListNode(int x):val(x),next(nullptr){};
};


class Solution
{
    public:
        ListNode * addTwoNumbers(ListNode * l1, ListNode * l2)
        {
            ListNode * cursor1=l1, * cursor2=l2;
            ListNode * res=nullptr, * cursor=nullptr;
            int carry=0;
            while(cursor1 ||  cursor2)
            {
                int digit1,digit2;
                if(cursor1)
                {
                    digit1=cursor1->val;
                    cursor1=cursor1->next;
                }
                else
                    digit1=0;
                
                if(cursor2)
                {
                    digit2=cursor2->val;
                    cursor2=cursor2->next;
                }
                else
                    digit2=0;
                
                if(!res)
                    res=cursor=new ListNode((digit1+digit2+carry)%10);
                else
                    cursor=cursor->next=new ListNode((digit1+digit2+carry)%10);
                carry=(digit1+digit2+carry)/10;
            }
            if(carry) cursor->next=new ListNode(1);
            return res;
        }
};


