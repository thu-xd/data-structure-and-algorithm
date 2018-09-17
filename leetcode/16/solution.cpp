#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
using std::vector;

class Solution
{
    public:
        int threeSumClosest(vector<int> & nums, int target)
        {
            std::sort(nums.begin(),nums.end());
            int closest=INT_MAX,closet_sum;
            int n=nums.size();
            for(int i=0;i<n-2;i++)
            {
                int lo=i+1,hi=n-1;
                while(lo<hi)
                {
                    if(std::abs(nums[i]+nums[lo]+nums[hi]-target)<closest)
                    {
                        closest=std::abs(nums[i]+nums[lo]+nums[hi]-target);
                        closet_sum=nums[i]+nums[lo]+nums[hi];
                    }
                    if(nums[i]+nums[lo]+nums[hi]>target)
                        hi--;
                    else if(nums[i]+nums[lo]+nums[hi]==target)
                        return target;
                    else
                        lo++;
                }
            }
            return closet_sum;
        }
};
