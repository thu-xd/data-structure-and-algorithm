#include <vector>
#include <algorithm>
using std::vector;

class Solution
{
    public:
        vector<vector<int> > fourSum(vector<int> & nums,int target)
        {
            int n=nums.size();
            if(n<4) return vector<vector<int> >();
            std::sort(nums.begin(),nums.end());   //To avoid duplicate quadruplets
            vector<vector<int> > res;
            for(int i=0;i<n-3;i++)
            {
                if(nums[i]*4>target) return res;
                if(i>0 && nums[i]==nums[i-1]) continue;  //avoid duplicate quadruplets
                for(int j=i+1;j<n-2;j++)
                {
                    if(nums[i]+nums[j]*3>target) break;
                    if(j>i+1 && nums[j]==nums[j-1]) continue;  //avoid duplicate quadruplets.
                    //This time we used two-pointer method to solve this two-sum problem.
                    //We could also use the unordered_map method.
                    int lo=j+1,hi=n-1;
                    while(lo<hi)
                    {
                        if(nums[i]+nums[j]+nums[lo]+nums[hi]==target)
                        {
                            res.push_back(vector<int>({nums[i],nums[j],nums[lo],nums[hi]}));
                            do
                            {
                                lo++;
                            }while(lo<hi && nums[lo]==nums[lo-1]);
                            do
                            {
                                hi--;
                            }while(lo<hi && nums[hi]==nums[hi+1]);
                        }
                        else if(nums[i]+nums[j]+nums[lo]+nums[hi]>target)
                            hi--;
                        else
                            lo++;
                    }
                }
            }

            return res;
        }
};





