#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution
{
    public:
        string convert(string s, int numRows)
        {
            if(numRows==1 || s.empty()) return s;
            int n=s.size();
            vector<vector<int> > indices(numRows);
            int gap=2*(numRows-1);         // The gap between two full column
            for(int i=0;i<n;i+=gap)
            {
                indices[0].push_back(i);   // The first row
                if(i+numRows-1<n)
                    indices[numRows-1].push_back(i+numRows-1);  //The last row.
            }

            for(int r=1;r<numRows-1;r++)
            {
                for(int i=r;i<n+gap;i+=gap)
                {
                    if(i>r && i-2*r<n) indices[r].push_back(i-2*r);
                    if(i<n) indices[r].push_back(i);
                }
            }

            string res;
            for(int i=0;i<numRows;i++)
                for(auto & ind:indices[i])
                    res+=s[ind];
            return res;
        }
};
