#include <vector>
#include <unordered_set>
#include <algorithm>

using std::vector;
using std::unordered_set;

class Solution
{
    public:
        vector<vector<int> > threeSum(vector<int> & nums)
        {
            int n=nums.size();
            if(n<3 || (n==3 && (nums[0]+nums[1]+nums[2]!=0)))  return vector<vector<int> >();
            std::sort(nums.begin(),nums.end());  // To avoid duplicate  
            vector<vector<int> > res;
            for(int i=0;i<n-2;i++)
            {
                if(nums[i]>0) return res;
                if(i>0 && nums[i]==nums[i-1]) continue;
                unordered_set<int> visited;
                for(int j=i+1;j<n;j++)
                {
                    if(nums[j]<0)
                    {
                        visited.insert(nums[j]);
                        continue;
                    }
                    if(j>i+1 && nums[j]==nums[j-1])
                    {
                        if(nums[i]+nums[j]*2==0)
                            res.push_back(vector<int>({nums[i],nums[j-1],nums[j]}));
                        while(j<n && nums[j]==nums[j-1]) j++;  //jump over the duplicate elements.
                        j--;continue;
                    }

                    int b=-nums[i]-nums[j];
                    if(b>=nums[j])
                    {
                        visited.insert(nums[j]);
                        continue;
                    }
                    auto it=visited.find(b);
                    if(it!=visited.end())
                        res.push_back(vector<int>({nums[i],b,nums[j]}));
                    visited.insert(nums[j]);
                }
            }

            return res;
        }
};
