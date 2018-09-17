#include <string>
#include <unordered_map>
#include <algorithm>
using std::string;
using std::unordered_map;;

class Solution
{
    public:
        int lengthOfLongestSubstring(string s)
            //This is a typical problem which can be solved by slide windows
            //together with unordered_map;
        {
            unordered_map<char,int> visited;
            int begin=0, end=0;  // The begin and end index of the slide windows.
            int max_len=0;       // To restore the max_len of the substring.
            while(end<int(s.size()))
            {
                auto it=visited.find(s[end]);
                if(it!=visited.end())   // If we have visited s[end]
                {
                    max_len=std::max(max_len,end-begin);
                    for(int i=begin;i<=it->second;i++)
                        visited.erase(s[i]);    //Move begin to it->second+1
                    begin=it->second+1;
                }
                visited.insert(std::make_pair(s[end],end));
                end++;
            }
            max_len=std::max(max_len,end-begin+1);
            return max_len;
        }
};
