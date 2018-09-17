#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution
{
    public:
        bool isMatch(string s, string p)
            //There is a dp solution.
        {
            int ns=s.size(),np=p.size();
            vector<vector<char> > solved(ns+1,vector<char>(np+1,2));  // 2 means not solved
                                                                      // 1 means match
                                                                      // 0 means not match
            int last_star=np;
            while(last_star>0 && p[last_star-1]=='*') last_star--;
            for(int i=0;i<=np;i++)
                solved[ns][i]=((i<last_star)?0:1);
            for(int i=0;i<ns;i++)
                solved[i][np]=0;
            return dp(s,p,solved,0,0);
        }

        int dp(const string & s, const string & p, vector<vector<char> > & solved, int si, int pi)
        {
            if(solved[si][pi]!=2) return solved[si][pi];
            if(p[pi]==s[si] || p[pi]=='?')
                return solved[si][pi]=dp(s,p,solved,si+1,pi+1);
            else if(p[pi]=='*')
            {
                for(int i=si;i<=int(s.size());i++)
                {
                    int res=dp(s,p,solved,i,pi+1);
                    if(res)
                        return solved[si][pi]=1;
                }
            }
            return solved[si][pi]=0;
        }
};
