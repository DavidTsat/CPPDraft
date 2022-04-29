#include <iostream>
#include <vector>

using namespace std;

class Solution {
    int missingNumberMostOptimal(vector<int>& nums)
    {
        int xor_ = 0, i = 0;
        for (; i < nums.size(); i++) {
            xor_ = xor_ ^ i ^ nums[i];
        }

        return xor_ ^i;
    }
public:
    int missingNumberAlmostOptimal(vector<int>& nums)
    {
        vector<int> r(sizeof(int) * 8, 0);

        for (int i = 0; i < sizeof(int) * 8 - 1; ++i)
        {
            int c = 1 << i;

            for (int j = 0; j < nums.size(); ++j)
            {
                int aa = nums[j];
                r[i] += (nums[j] & c) != 0;
            }

        }

        int res = 0;

        for (int i = 1; i < nums.size() + 1; ++i)
        {
            int a = i;
            for (int j = 0; j < sizeof(int) * 8 - 1; ++j)
            {
                int c = 1 << j;
                if (c & i)
                {
                    --r[j];
                }
                if (r[j] == -1)
                {
                    res |= 1 << j;
                }
            }
        }

        /*
                for (int i = 0; i < r.size(); ++i)
                {
                    if (r[i] == -1)
                    {
                        res |= 1 << i;
                    }
                }
            */
        return res;
    }
    int missingNumber(vector<int>& nums) {
       
        return missingNumberMostOptimal(nums);
    }

};

int main()
{
    Solution s;
    vector<int> v1 = { 3,0,1 };
    vector<int> v2 = { 0,1 };
    vector<int> v3 = { 9,6,4,2,3,5,7,0,1 };

    cout << s.missingNumber(v1) << endl;
    cout << s.missingNumber(v2) << endl;
    cout << s.missingNumber(v3) << endl;

    return 0;
}