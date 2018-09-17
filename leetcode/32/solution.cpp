#include <string>
#include <stack>
#include <utility>
#include <algorithm>
using std::string;
using std::stack;

class Solution
{
    public:
        int longestValidParentheses(string s)
            //The stack was a efficient data struct for parentheses problems
        {
            int n=s.size();
            int max_len=0;
            stack<std::pair<char,int> > parentheses;
            parentheses.push(std::make_pair('*',-1));
            for(int i=0;i<n;i++)
            {
                if(parentheses.top().first=='(' && s[i]==')')
                    parentheses.pop();
                else
                {
                    max_len=std::max(max_len,i-parentheses.top().second-1);
                    parentheses.push(std::make_pair(s[i],i));
                }
            }
            max_len=std::max(max_len,n-1-parentheses.top().second);
            return max_len;
        }
};


        
