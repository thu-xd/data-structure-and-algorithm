#include <vector>
using std::vector;

class Solution
{
    public:
        int search(vector<int> & nums, int target)
        {
            //We'd better first find the pivot 
            int n=nums.size();
            if(n==0) return -1;
            if(n==1) return (nums[0]==target)?0:-1;
            if(nums[n-1]>nums[0]) return binary_search(nums,0,n-1,target);
            int lo=0,hi=n-1;
            while(lo<hi)
            {
                int mid=(lo+hi)>>1;
                if(nums[mid]>=nums[0])
                    lo=mid+1;
                else
                    hi=mid;
            }

            if(target>nums[hi-1] || target<nums[hi]) return -1;
            if(target>=nums[0]) return binary_search(nums,0,hi-1,target); //[lo,hi]
            if(target<=nums[n-1])  return binary_search(nums,hi,n-1,target);
            return -1;
        }

        int binary_search(vector<int> & nums, int lo,int hi, int target)
        {
            while(lo<=hi)
            {
                int mid=(lo+hi)>>1;
                if(nums[mid]==target)
                    return mid;
                else if(nums[mid]>target)
                    hi=mid-1;
                else
                    lo=mid+1;
            }
            return -1;
        }
};



