#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution
{
    public:
        int strStr(string haystack,string needle)
            //We can use the KMP algorithm
            //The key point was as followed
            //                    i-th
            //           * * * * * $ * * * * *                 haystack
            //               * * * * * *                       needle
            //                    j-th
            //When i-th element of haystack was not match j-th element of needle
            //We don't roll back the haystack and set j=0
            //We keep the haystack and set j=next(j), so that needle[0,next(j)-1]==needle[j-next(j),j-1]
            //So should find the next array of needle, for every j that j>=0 && j<needle.size()
            //If we have solved next(0),next(1),...next(j)
            //We can solve next(j+1) using the result of above
            //see the code or the wiki for detail.
        {
            int m=haystack.size();
            int n=needle.size();
            if(n==0) return 0;
            vector<int> next=get_next(needle);
            int i=0,j=0;
            while(i<m)
            {
                if(j<0 || haystack[i]==needle[j])
                {
                    i++;
                    j++;
                    if(j==n)
                        return i-j;
                }
                else
                    j=next[j];
            }
            return -1;
        }

        vector<int>  get_next(string & s)
        {
            int n=s.size();
            vector<int> next(n);
            next[0]=-1;  //-1 means i++ and j=0
            for(int i=1;i<n;i++)
            {
                int next_i_minus=next[i-1];
                while(true)
                {
                    if(next_i_minus==-1 || s[next_i_minus]==s[i-1])
                    {
                        next[i]=next_i_minus+1;
                        break;
                    }
                    next_i_minus=next[next_i_minus];
                }
            }
            return next;
        }
};



