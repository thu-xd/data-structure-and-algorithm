#include <cmath>
#include <climits>


class Solution
{
    public:
        int divide(int dividend,int divisor)
        {
            bool dividend_negative=(dividend<0);
            bool divisor_negative=(divisor<0);
            long long new_dividend=std::fabs(dividend);
            long long new_divisor=std::fabs(divisor);
            long long quotient=0;
            //We can use divide or multiple operator, so we can use add and minus to simulate divide and 
            //multiple
            long long multiple_divisor=new_divisor, multiple=1;
            while(new_dividend>=new_divisor)
            {
                if(new_dividend==multiple_divisor)
                {
                    quotient+=multiple;
                    break;
                }
                else if(new_dividend>multiple_divisor)
                {
                    quotient+=multiple;
                    new_dividend-=multiple_divisor;
                    multiple_divisor+=new_divisor;
                    multiple++;
                }
                else
                {
                    multiple_divisor-=new_divisor;
                    multiple--;
                }
            }

            if(divisor_negative ^ dividend_negative)
                return -quotient;
            else
                return (quotient>INT_MAX)?INT_MAX:quotient;
        }
};
