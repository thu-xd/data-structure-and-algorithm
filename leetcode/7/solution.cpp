#include <stack>
#include <cmath>
#include <climits>

class Solution
{
    public:
        int reverse(int x)
        {
            std::stack<int> digits;
            bool negative=(x<0);
            long long n=std::fabs(x);  //avoid overflow
            while(n)
            {
                digits.push(n%10);
                n/=10;
            }

            long long res=0, multiple=1;
            while(!digits.empty())
            {
                res+=multiple*digits.top();
                digits.pop();
                multiple*=10;
            }

            res=((negative)?(-res):(res));
            if(res<=INT_MAX && res>=INT_MIN) return res;
            else  return 0;
        }
};

            
