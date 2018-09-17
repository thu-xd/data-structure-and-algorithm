#include <vector>
using std::vector;

class Solution
{
    public:
        int removeDuplicates(vector<int> & nums)
        {
            if(nums.empty()) return 0;
            int current=0;
            for(int i=1;i<int(nums.size());i++)
                if(nums[i]!=nums[current])
                    nums[++current]=nums[i];
            return current+1;
        }
};
