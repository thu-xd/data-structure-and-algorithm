#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution
{
    public:
        vector<string> letterCombinations(string digits)
        {
            if(digits.empty()) return vector<string>();
            vector<vector<char> > dict(8);
            for(int i=0;i<5;i++)
                for(int j=0;j<3;j++)
                    dict[i].push_back('a'+3*i+j);
            for(int i=0;i<4;i++)
            {
                dict[5].push_back('p'+i);
                dict[7].push_back('w'+i);
            }
            for(int i=0;i<3;i++)
                dict[6].push_back('t'+i);

            return recursive(digits,0,dict);
        }

        vector<string> recursive(string & s, int index, vector<vector<char> > & dict)
        {
            vector<string> res;
            if(index==int(s.size())-1)
            {
                for(auto ch:dict[s[index]-'2'])
                    res.push_back(string(1,ch));
                return res;
            }
            vector<string> res_next=recursive(s,index+1,dict);
            for(auto ch:dict[s[index]-'2'])
                for(auto str:res_next)
                    res.push_back(ch+str);
            return res;
        }
};
