#include <vector>
using std::vector;

class Solution
{
    public:
        int trap(const vector<int> & height)
            //using two-pointer
        {
            int n=height.size();
            if(n==0) return 0;
            int lo=0,hi=1,sum=0;
            while(hi<n)
            {
                if(height[hi]<height[lo])
                {
                    sum+=(height[lo]-height[hi]);
                    hi++;
                }
                else   // a new rain section.
                {
                    lo=hi;
                    hi++;
                }
            }
            
            //We need pay extra attention to the last rain section.
            //This was the most complex.
            if(lo==n-1) return sum;
            for(int i=lo+1;i<n;i++)
                sum-=(height[lo]-height[i]);  // minus the last rain section.
            return sum+=trap(vector<int>(height.rbegin(),height.rbegin()+(n-lo)));
        }
};

