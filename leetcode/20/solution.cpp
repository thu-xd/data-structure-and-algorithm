#include <stack>
#include <string>

class Solution
{
    public:
        bool isValid(string s)
        {
            std::stack<char> parentheses;
            for(int i=0;i<int(s.size());i++)
            {
                if(s[i]=='(' || s[i]=='[' || s[i]=='{')
                    parentheses.push(s[i]);
                else
                {
                    if(parentheses.empty())
                        return false;
                    if((s[i]==')' && parentheses.top()=='(')||
                            (s[i]==']' && parentheses.top()=='[') ||
                            (s[i]=='}' && parentheses.top()=='{'))
                        parentheses.pop();
                    else
                        return false;
                }
            }
            return parentheses.empty();
        }
};


