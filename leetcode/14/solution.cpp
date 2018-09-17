#include <string>
#include <vector>
#include <climits>
#include <algorithm>
using std::vector;
using std::string;

class Solution
{
    public:
        string longestCommonPrefix(vector<string> & strs)
        {
            if(strs.empty()) return string();
            int min_len=INT_MAX;
            for(auto s:strs)
                min_len=std::min(int(s.size()),min_len);
            for(int i=0;i<min_len;i++)
            {
                for(int j=1;j<int(strs.size());j++)
                {
                    if(strs[j][i]!=strs[0][i])
                        return string(strs[0],0,i);
                }
            }
            return string(strs[0],0,min_len);
        }
};
                

