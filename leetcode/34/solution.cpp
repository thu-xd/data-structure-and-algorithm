#include <vector>
using std::vector;

class Solution
{
    public:
        vector<int> searchRange(vector<int> & nums, int target)
        {
            int n=nums.size();
            if(n==0) return vector<int>({-1,-1});
            int lo=0,hi=n-1;
            int one_of_target=binary_search(nums,lo,hi,target);
            if(one_of_target==-1) return vector<int>({-1,-1});
            int hi1=one_of_target, lo2=one_of_target;
            while(true)
            {
                int new_hi=binary_search(nums,lo,hi1,target);
                if(nums[lo]==target)
                {
                    hi1=lo;
                    break;
                }
                if(new_hi==hi1) break;
                hi1=new_hi;
            }
            while(true)
            {
                int new_lo=binary_search(nums,lo2,hi,target);
                if(nums[hi]==target)
                {
                    lo2=hi;
                    break;
                }
                if(new_lo==lo2) break;
                lo2=new_lo;
            }

            return vector<int>({hi1,lo2});
        }

        int binary_search(vector<int> & nums, int &  lo, int & hi, int target)  //[lo,hi]
        {
            int mid;
            while(lo<=hi)
            {
                mid=(lo+hi)>>1;
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
