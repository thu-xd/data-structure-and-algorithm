#include <vector>
using std::vector;

class Solution
{
    public:
        int removeElement(vector<int> & nums,int val)
        {
            int current=0;
            for(int i=0;i<int(nums.size());i++)
                if(nums[i]!=val)
                    nums[current++]=nums[i];
            return current;
        }
};
