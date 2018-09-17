#include <vector>
#include <algorithm>
using std::vector;

class Solution
{
    public:
        int maxArea(vector<int> & height)
            //The brute force solution using O(n^2) time to search all the candidate solution,
            //it's stupid, we could use two pointer to reduce it to O(n)
        {
            int lo=0,hi=height.size()-1,max_area=0;
            while(lo<hi)
            {
                if(height[lo]<=height[hi])
                {
                    max_area=std::max(max_area,(hi-lo)*height[lo]);
                    lo++;
                }
                else
                {
                    max_area=std::max(max_area,(hi-lo)*height[hi]);
                    hi--;
                }
            }
            return max_area;
        }
};
