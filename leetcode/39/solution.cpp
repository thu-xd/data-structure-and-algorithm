#include <vector>
#include <unordered_map>
#include <algorithm>
using std::vector;
using std::unordered_map;

class Solution
{
    public:
        vector<vector<int> > combinationSum(vector<int> & candidates,int target)
            //A dp solution
        {
            if(candidates.empty()) return vector<vector<int> >();
            int n=candidates.size();
            vector<unordered_map<int,vector<vector<int> > > >  solved(n);
            std::sort(candidates.begin(),candidates.end());
            return recursive(candidates,solved,target,n-1);
        }

        vector<vector<int> > recursive(vector<int> & candidates,
                vector<unordered_map<int,vector<vector<int> > > > & solved, int target, int index)
        {
            if(target<0) return vector<vector<int> >();
            if(target==0) return vector<vector<int> >(1);
            auto it=solved[index].find(target);
            if(it!=solved[index].end()) return it->second;
            vector<vector<int> > res;
            if(index==0)
            {
                if(target%candidates[0]==0)
                {
                    res=vector<vector<int> >(1,vector<int>(target/ candidates[0],candidates[0]));
                    solved[index].insert(std::make_pair(target,res));
                    return res;
                }
                else
                {
                    solved[index].insert(std::make_pair(target,vector<vector<int> >()));
                    return vector<vector<int> >();
                }
            }

            vector<vector<int> > res1=recursive(candidates,solved,target-candidates[index],index);
            for(auto v:res1)
            {
                v.push_back(candidates[index]);
                res.push_back(v);
            }

            vector<vector<int> > res2=recursive(candidates,solved,target,index-1);
            for(auto v:res2)
                res.push_back(v);

            solved[index].insert(std::make_pair(target,res));
            return res;
        }
};
