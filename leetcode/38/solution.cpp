#include <string>
using std::string;

class Solution
{
    public:
        string countAndSay(int n)
        {
            if(n==1) return string(1,'1');
            string previous_res=countAndSay(n-1);
            int begin=0,end=0;
            string res;
            while(end<int(previous_res.size()))
            {
                if(previous_res[end]==previous_res[begin])
                    end++;
                else
                {
                    res+=string(1,'0'+end-begin)+string(1,previous_res[begin]);
                    begin=end;
                }
            }
            res+=string(1,'0'+end-begin)+string(1,previous_res[begin]);
            return res;
        }
};
            
