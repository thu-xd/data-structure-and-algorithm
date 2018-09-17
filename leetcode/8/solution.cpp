#include <string>
#include <vector>
#include <climits>
using std::string;
using std::vector;

class Solution
{
    public:
        int myAtoi(string str)
        {
            int negative=false;
            int begin=0;
            for(begin=0;begin<int(str.size());begin++)  //We first find the first valid char.
            {
                if(str[begin]!=' ')
                {
                    if(str[begin]=='-')
                    {
                        negative=true;
                        begin++;
                    }
                    else if(str[begin]=='+')
                        begin++;
                    else if(!(str[begin]>='0' && str[begin]<='9'))
                        return 0;
                    break;
                }
            }

            vector<int> digits;
            int first_non_zero=-1;
            for(;begin<int(str.size());begin++)
            {
                if(str[begin]>='0' && str[begin]<='9')
                {
                    digits.push_back(str[begin]-'0');
                    if(str[begin]!='0' && first_non_zero!=-1)
                        first_non_zero=digits.size()-1;
                    if(first_non_zero!=-1 && digits.size()-first_non_zero>10)  // If the digits number was
                        return (negative)?(INT_MIN):(INT_MAX);                 // larger than 10, it 
                }                                                              // must have overflow int
                else
                    break;
            }
            if(digits.empty()) return 0;

            long long res=0,multiple=1;
            for(int i=int(digits.size())-1;i>=0;i--)
            {
                res+=digits[i]*multiple;
                multiple*=10;
            }

            res=((negative)?(-res):res);
            if(res<INT_MIN) return INT_MIN;
            if(res>INT_MAX) return INT_MAX;
            return res;
        }
};


