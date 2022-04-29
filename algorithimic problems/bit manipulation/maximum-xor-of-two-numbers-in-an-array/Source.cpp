#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
    int findMaximumXORPerebor(vector<int>& nums) {
        // auto p = max_element(nums.cbegin(), nums.cend());
        int a, b;
        int max_xor = INT_MIN;// = *p ^ nums[0];


        for (int i = 0; i < nums.size(); ++i)
        {
            for (int j = i; j < nums.size(); ++j)
            {
                if ((nums[i] ^ nums[j]) > max_xor)
                {
                    max_xor = nums[i] ^ nums[j];
                    a = i;
                    b = j;
                }
            }
        }
        /*
        for (int i : nums)
        {
            max_xor = max(max_xor, *p ^ i);
        }
        */
        return max_xor;
    }

    int findMaximumXORBetter(vector<int>& nums) {
        int p = *max_element(nums.cbegin(), nums.cend());
        if (p == 0) return 0;
        int a, b;
        int max_xor = INT_MIN;// = *p ^ nums[0];
        int pow = 0;
        vector<int> maxs;

        for (int i = 0; i < sizeof(int) * 8 - 1; ++i)
        {
            if (p & 1)
            {
                pow = i;
            }
            p = p >> 1;
        }
        int max_2_pow = 1 << pow;

        for (int i : nums)
        {
            if (i >= max_2_pow)
            {
                maxs.push_back(i);
            }
        }

        for (int i = 0; i < maxs.size(); ++i)
        {
            for (int j = 0; j < nums.size(); ++j)
            {
                if ((maxs[i] ^ nums[j]) > max_xor)
                {
                    max_xor = maxs[i] ^ nums[j];
                    a = i;
                    b = j;
                }
            }
        }

        return max_xor;
    }

    int findMaximumXORBetter2(vector<int>& nums)
    {
        int max = 0, mask = 0;
        for (int i = 31; i >= 0; i--) {
            mask = mask | (1 << i);
            set<int> s;
            for (int num : nums) {
                int c = num & mask;
                s.insert(num & mask);
            }
            int tmp = max | (1 << i);
            for (int prefix : s) {
                if (s.find(tmp ^ prefix) != s.end()) {
                    max = tmp;
                    break;
                }
            }
        }
        return max;
      //  while (i < nums.size())
    
       // return max_xor;
    }
public:
    int findMaximumXOR(vector<int>& nums) {
        return findMaximumXORBetter2(nums);
    }
};


int main()
{
    Solution s;
    vector<int> v1 = { 3, 10, 5, 25, 2, 8 };
    vector<int> v2 = { 14, 70, 53, 83, 49, 91, 36, 80, 92, 51, 66, 70 };
    vector<int> v3 = { 0 };

    cout << s.findMaximumXOR(v1) << endl;
    cout << s.findMaximumXOR(v2) << endl;
    cout << s.findMaximumXOR(v3) << endl;

    return 0;
}