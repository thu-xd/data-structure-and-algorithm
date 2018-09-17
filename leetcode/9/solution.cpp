#include <vector>
using std::vector;
class Solution
{
    public:
        bool isPalindrome(int x)
        {
            if(x<0) return false;
            vector<int> digits;
            while(x)
            {
                digits.push_back(x%10);
                x/=10;
            }

            int n=digits.size(),mid=n>>1;
            for(int i=0;i<mid;i++)
                if(digits[i]!=digits[n-1-i])
                    return false;
            return true;
        }
};

