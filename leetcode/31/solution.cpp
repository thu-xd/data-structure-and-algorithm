#include <vector>
#include <algorithm>
using std::vector;

class Solution
{
    public:
        void nextPermutation(vector<int> & nums)
        {
            if(nums.empty()) return;
            next_permutation(nums,0);
        }

        bool next_permutation(vector<int> & nums,int index)
            //Return if it's descending order nums[index,:]
        {
            int n=nums.size();
            if(index==n-1) return true;
            bool is_descending=true;
            int last_ascending_element;
            for(last_ascending_element=n-1;last_ascending_element>index;
                    last_ascending_element--)
                if(nums[last_ascending_element]>nums[last_ascending_element-1])
                {
                    is_descending=false;
                    break;
                }
            if(is_descending)
            {
                int mid=(index+n)>>1;
                for(int i=index;i<mid;i++)
                    std::swap(nums[i],nums[index+n-1-i]);
                return true;
            }
            else
            {
                bool descending=next_permutation(nums,last_ascending_element);
                if(descending)
                {
                    int i;
                    for(i=last_ascending_element;i<n;i++)  //We can use binary search here 
                        if(nums[i]>nums[last_ascending_element-1]) // to further decrease the run time
                            break;
                    std::swap(nums[i],nums[last_ascending_element-1]);
                }
                return false;
            }
        }
};
