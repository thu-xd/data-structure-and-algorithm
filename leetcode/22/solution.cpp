#include <vector>
#include <string>
using std::vector;
using std::string;

class Solution
{
    public:
        vector<string> generateParenthesis(int n)
        //This is obvoiusly a dp problem
        {
            if(n==0) return vector<string>();
            vector<vector<string> > solved(n+1);
            solved[0]=vector<string>(1);
            solved[1]=vector<string>(1,"()");
            for(int i=2;i<=n;i++)     // (str1)str2, str1 and str2 are both well-formed parenthesis
                for(int j=0;j<i;j++)
                    for(auto str1:solved[j])
                        for(auto str2:solved[i-1-j])
                            solved[i].push_back('('+str1+')'+str2);
            return solved[n];
        }
};
                    


