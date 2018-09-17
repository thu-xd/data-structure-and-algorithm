#include <string>
#include <vector>
using std::vector;
using std::string;

class Solution
{
    public:
        bool isMatch(string s, string p)
            //We can solve this problem using dp.
        {
            int ns=s.size(),np=p.size();
            if(np==0 && ns!=0) return false;
            if(np==0 && ns==0) return true;
            vector<vector<char> > solved(ns+1,vector<char>(np+1,2));  //2 means not solved.
            for(int i=0;i<ns;i++) solved[i][np]=0;
            solved[ns][np]=1;
            for(int i=0;i<np;i++)
            {
                if((np-i)%2!=0) solved[ns][i]=0;
                else
                {
                    for(int j=i;j<np;j+=2)
                    {
                        if(p[j]=='*' ||  p[j+1]!='*')
                        {
                            solved[ns][i]=0;
                            break;
                        }
                    }
                    if(solved[ns][i]!=0) solved[ns][i]=1;
                }
            }
            return match(s,0,p,0,solved);
        }

        bool match(string & s, int index1, string & p, int index2,vector<vector<char> > & solved)
        {
            if(solved[index1][index2]!=2) return solved[index1][index2];  // 1 means match, 0 means not
                                                                          // match.
            if(p[index2]=='*') return solved[index1][index2]=0;
            if(index2==int(p.size()-1))
            {
               if(index1==int(s.size()-1) && equal_char(s[index1],p[index2])) 
                   return solved[index1][index2]=1;
               else
                   return solved[index1][index2]=0;
            }

            if(p[index2+1]!='*')
            {
                if(equal_char(s[index1],p[index2]))
                    return solved[index1][index2]=match(s,index1+1,p,index2+1,solved);
                else
                    return solved[index1][index2]=0;
            }

            // p[index2]!='*'  && p[index2+1]=='*'
            if(!equal_char(s[index1],p[index2])) 
                return solved[index1][index2]=match(s,index1,p,index2+2,solved);
            for(int i=index1;i<int(s.size());i++)
            {
                if(equal_char(s[i],p[index2]))
                {
                    bool res=match(s,i+1,p,index2+2,solved);
                    if(res) return solved[index1][index2]=true;
                }
                else
                    break;
            }
            return solved[index1][index2]=false;
        }
            
        bool equal_char(char s_char, char p_char)
        {
            return p_char=='.' || s_char==p_char;
        }
};
