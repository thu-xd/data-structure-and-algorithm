#include <string>
#include <vector>
#include <utility>
using std::string;
using std::vector;

class Solution
{
    public:
        string longestPalindrome(string s)
        {
            if(s.empty()) return s;
            //We can just solve it using recursive.
            vector<vector<int> > chars(128,vector<int>());
            for(int i=0;i<int(s.size());i++)
                chars[s[i]].push_back(i);
            std::pair<int,int> max_res(-1,-1);
            recursive(s, chars, max_res, 0); 
            return string(s,max_res.first,max_res.second-max_res.first+1);
        }

        void recursive(string & s, vector<vector<int> > & chars, std::pair<int,int> & max_res, int index)
        {
            if(index>=int(s.size())) return;
            for(int i=chars[s[index]].size()-1;i>=0;i--)
            {
                int pos=chars[s[index]][i];
                if(pos<index)
                    break;
                else
                {
                    if(palindrome(s,index,pos+1))
                    {
                        if(pos+1-index>=(max_res.second-max_res.first+1))
                            max_res=std::pair<int,int>(index,pos);
                        break;
                    }
                }
            }
            recursive(s,chars,max_res,index+1);
        }

        bool palindrome(string & s, int lo, int hi) // [lo,hi)
        {
            int mid=(lo+hi)>>1;
            for(int i=lo;i<mid;i++)
                if(s[i]!=s[lo+hi-i-1])
                    return false;
            return true;
        }
};

