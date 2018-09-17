#include<vector>
#include <algorithm>
#include <unordered_map>
using std::vector;
using std::unordered_map;


class Solution
{
    public:
        vector<vector<int> > combinationSum2(vector<int> & candidates,int target)
        {
            //We can give a dp solution.
            int n=candidates.size();
            if(n==0) return vector<vector<int> >();
            std::sort(candidates.begin(),candidates.end());
            vector<unordered_map<int,vector<vector<int> > > > solved(n);
            return recursive(candidates,solved,target,0);
        }

        vector<vector<int> > recursive(vector<int> & candidates,
                vector<unordered_map<int,vector<vector<int> > > > solved, int target, int index)
        {
            if(target<0) return vector<vector<int> >();
            if(target==0) return vector<vector<int> >(1);
            if(index>=int(candidates.size())) return vector<vector<int> >();
            auto it=solved[index].find(target);
            if(it!=solved[index].end()) return it->second;

            vector<vector<int> > res, res1, res2;
            res1=recursive(candidates,solved,target-candidates[index],index+1);
            for(auto v:res1)
            {
                v.push_back(candidates[index]);
                res.push_back(v);
            }
            int new_index=index+1;
            while(new_index<int(candidates.size()) && candidates[new_index]==candidates[new_index-1])
                new_index++; //To avoid duplicate
            res2=recursive(candidates,solved,target,new_index);
            for(auto v:res2)
                res.push_back(v);
            solved[index].insert(std::make_pair(target,res));
            return res;
        }
};
