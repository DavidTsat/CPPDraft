#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int singleNumber1(vector<int>& s)
    {
        int l = sizeof(int) * 8;
        vector<int> t(l);////Made a array contain 32 elements.
        int sz = s.size();
        int i, j, n;
        
        for (i = 0; i < sz; ++i)
        {
            n = s[i];
            for (j = l-1; j >= 0; --j)
            {
                t[j] += n & 1;//Find the last digit.
                n >>= 1;
                if (!n)
                    break;
            }
        }
        int res = 0;
        for (j = l - 1; j >= 0; --j)
        {
            n = t[j] % 3;//"3" represents k times. 
            if (n)
                res += 1 << (l-1 - j);
        }
        return res;
    }
    int singleNumber(vector<int>& nums) {
        return singleNumber1(nums);
    }
};

int main()
{
    vector<int> v1 = { 4,2,4,3,4,2,2 };
    vector<int> v2 = { 2,2,3,2 };
    vector<int> v3 = { 0,1,0,1,0,1,99 };
    Solution s;
    cout << s.singleNumber1(v3) << endl;
    return 0;
}