#include <string>
using std::string;

class Solution
{
    public:
        string intToRoman(int num)
        {
            string units[9], tens[9], hundreds[9], thousands[9];
            char symbols[]={'I','V','X','L','C','D','M'};
            for(int i=0;i<3;i++)
            {
                units[i]=string(i+1,symbols[0]);
                units[i+5]=string(1,symbols[1])+units[i];
                tens[i]=string(i+1,symbols[2]);
                tens[i+5]=string(1,symbols[3])+tens[i];
                hundreds[i]=string(i+1,symbols[4]);
                hundreds[i+5]=string(1,symbols[5])+hundreds[i];
                thousands[i]=string(i+1,symbols[6]);
            }

            units[3]=string(1,symbols[0])+string(1,symbols[1]);
            units[4]=string(1,symbols[1]);
            units[8]=string(1,symbols[0])+string(1,symbols[2]);
            tens[3]=string(1,symbols[2])+string(1,symbols[3]);
            tens[4]=string(1,symbols[3]);
            tens[8]=string(1,symbols[2])+string(1,symbols[4]);
            hundreds[3]=string(1,symbols[4])+string(1,symbols[5]);
            hundreds[4]=string(1,symbols[5]);
            hundreds[8]=string(1,symbols[4])+string(1,symbols[6]);

            int u=num%10;
            num/=10;
            int t=num%10;
            num/=10;
            int h=num%10;
            num/=10;
            int s=num;

            string res;
            if(s) res+=thousands[s-1];
            if(h) res+=hundreds[h-1];
            if(t) res+=tens[t-1];
            if(u) res+=units[u-1];
            return res;
        }
};


