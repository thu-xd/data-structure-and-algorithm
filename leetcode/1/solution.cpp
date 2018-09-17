#include <vector>
#include <unordered_map>
#include <functional>
using std::vector;
using std::unordered_map;

class Solution
{
    public:
        vector<int> twoSum(vector<int> & nums, int target)
        {
            unordered_map<int,int> visited;  //We can use unordered_map to store the visited elements.
                                             //So we can quickly retrieval afterward.
            for(int i=0;i<int(nums.size());i++)
            {
                int residual=target-nums[i];
                auto it=visited.find(residual);
                if(it!=visited.end())
                    return vector<int>({it->second,i});
                else
                    visited.insert(std::make_pair(nums[i],i));
            }
            return vector<int>({-1,-1});     // If no solution ,return [-1,-1]
        }
};
