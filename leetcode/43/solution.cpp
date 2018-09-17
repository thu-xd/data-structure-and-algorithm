#include <string>
using std::string;

class Solution
{
    public:
        string multiply(string num1, string num2)
            //This was a straight solution which convert the multiple to be add operator and
            //multiple_digit operator.
        {
            if(num1==string(1,'0') || num2==string(1,'0'))
                return string(1,'0');
            string res;
            int n2=num2.size();
            for(int i=0;i<n2;i++)
                res=add(res,multiple_digit(num1,num2[n2-1-i]-'0',i));
            return res;
        }

        string add(const string &  num1, const string &  num2)
        {
            int n1=num1.size(),n2=num2.size(),carry=0;
            string res;
            int n=0;
            while(n<n1 || n<n2)
            {
                int digit1=((n<n1)?(num1[n1-1-n]-'0'):0);
                int digit2=((n<n2)?(num2[n2-1-n]-'0'):0);
                res=string(1,'0'+(digit1+digit2+carry)%10)+res;
                carry=(digit1+digit2+carry)/10;
                n++;
            }

            if(carry) res=string(1,'1')+res;
            return res;
        }

        string multiple_digit(const string & num1, int digit, int multiple)
        {
            string res, new_num1=num1+string(multiple,'0');
            for(int i=0;i<digit;i++)
                res=add(res,new_num1);
            return res;
        }
};

