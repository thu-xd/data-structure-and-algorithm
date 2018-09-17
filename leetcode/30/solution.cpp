#include <vector>
#include <string>
#include <unordered_map>
using std::vector;
using std::string;
using std::unordered_map;

class Solution
{
    public:
        vector<int> findSubstring(string s, vector<string> & words)
            //This problem can be solved by slide windows and unordered_map.
        {
            if(s.empty() || words.empty()) return vector<int>();
            unordered_map<string,int> dict;
            for(auto word:words)
                dict[word]++;
            vector<int> res;
            int begin=0,end=0;
            int word_len=words[0].size();
            int word_count=0,words_num=words.size();
            unordered_map<string,int> dict_backup(dict);
            for(int i=0;i<word_len;i++)
            {
                begin=end=i;
                dict=dict_backup;
                word_count=0;
                while(end+word_len<=int(s.size()) && begin+word_len*words_num<=int(s.size()))
                    //while(end<int(s.size())  is also ok, but much slower
                {
                    string current_word=string(s,end,word_len);
                    auto it=dict.find(current_word);
                    if(it==dict.end())
                    {   
                        begin=end=end+word_len;
                        dict=dict_backup;
                        word_count=0;
                        continue;
                    }
                    else if(it->second==0)
                        while(dict[current_word]==0)
                        {
                            dict[string(s,begin,word_len)]++;
                            word_count--;
                            begin+=word_len;
                        }
                    dict[current_word]--;
                    word_count++;
                    end+=word_len;
                    if(word_count==words_num)
                        res.push_back(begin);
                }
            }
            return res;
        }
};

