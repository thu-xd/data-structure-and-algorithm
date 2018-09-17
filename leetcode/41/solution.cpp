#include <vector>
#include <algorithm>
using std::vector;

class Solution
{
    public:
        int firstMissingPositive(vector<int> & nums)
            //The key point of this problem was count sort for the positive interge.
            //But this will waste much space.
        {
            int n=nums.size();
            for(int i=0;i<n;i++)
            {
                if(nums[i]==i+1) continue;  //If the nums[i] has finished, then continue.
                while(nums[i]>0 && nums[i]<=n)
                {
                    if(nums[i]==i+1) break;
                    if(nums[nums[i]-1]==nums[i]) break; //If the nums[nums[i]-1] has finished, continue.
                    std::swap(nums[i],nums[nums[i]-1]);
                }
                //After each loop, one of the nums was finished.
            }

            for(int i=0;i<n;i++)
                if(nums[i]!=i+1)
                    return i+1;
            return n+1;
        }
};
                    

