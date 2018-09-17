#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution
{
    public:
        string longestPalindrome(string s)
        {
            //The most important part of this problem was to valid
            //s[lo,hi] was a palindrome or not. The total substring was O(n^2)
            //We can use dp to get a O(n^2) solution.
            int n=s.size();
            if(n==0) return s;
            vector<vector<int> > is_palindrome(n,vector<int>(n,-1));  // -1 means has not known.
            for(int i=0;i<n;i++)
            {
                is_palindrome[i][i]=1;    //1 means is palindrome.
                if(i+1<n)
                    is_palindrome[i][i+1]=(s[i]==s[i+1]);
            }

            for(int len=3;len<=n;len++)
                for(int lo=0;lo<n+1-len;lo++)
                {
                    int hi=lo+len-1;
                    is_palindrome[lo][hi]=(is_palindrome[lo+1][hi-1] && s[lo]==s[hi]);
                }

            int max_len=-1;
            int max_len_lo=0,max_len_hi=0;
            for(int i=0;i<n;i++)
                for(int j=i;j<n;j++)
                    if(is_palindrome[i][j] && (j-i+1)>=max_len)
                    {
                        max_len=j-i+1;
                        max_len_lo=i;
                        max_len_hi=j;
                    }
            return string(s,max_len_lo,max_len);
        }
};


