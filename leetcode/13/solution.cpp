#include <string>
using std::string;

class Solution
{
    public:
        int romanToInt(string s)
        {
            char symbols[]={'I','V','X','L','C','D','M'};
            // 1: 'I'  2: 'II'  3:'III'  4:'IV'  5:'V'  6:'VI'  7:'VII'  8:'VIII'  9:'IX' 
            int res=0;
            int pivot=0;
            while(pivot<int(s.size()))
            {
                if(s[pivot]==symbols[6])
                    pivot++;
                else
                    break;
            }
            res+=pivot*1000;

            int multiple=100;
            for(int i=2;i>=0;i--)
            {
                int begin=pivot;
                while(pivot<int(s.size()))
                {
                    if(s[pivot]==symbols[i*2+2] || s[pivot]==symbols[i*2+1] || s[pivot]==symbols[2*i])
                        pivot++;
                    else
                        break;
                }

                int n=pivot-begin;
                if(n==1)
                {
                    if(s[begin]==symbols[2*i+1])
                        res+=5*multiple;
                    else
                        res+=multiple;
                }
                if(n==2)
                {
                    if(s[begin]==symbols[2*i])
                    {
                        if(s[begin+1]==symbols[2*i])
                            res+=2*multiple;
                        else if(s[begin+1]==symbols[2*i+1])
                            res+=4*multiple;
                        else
                            res+=9*multiple;
                    }
                    else
                        res+=6*multiple;
                }

                if(n==3)
                {
                    if(s[begin]==symbols[2*i])
                        res+=3*multiple;
                    else
                        res+=7*multiple;
                }

                if(n==4)
                    res+=8*multiple;
                multiple/=10;
            }
            return res;
        }
};

