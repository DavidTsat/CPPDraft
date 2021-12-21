#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int numSubarrayProductLessThanKNotOptimal(vector<int>& nums, int k) {
        int prod = 1;
        int r = 0;

        for (int i = 0; i < nums.size(); ++i)
        {
            int pr = nums[i];
            if (pr < k) ++r;
            for (int j = i - 1; j >= 0; --j)
            {
                pr *= nums[j];
                if (pr < k) ++r;
                else break;
            }
        }
        return r;
    }

    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int prod = 1;
        int r = 0;
        int s = 0;

        for (int i = 0; i < nums.size(); ++i)
        {
            prod *= nums[i];
            if (prod < k)
            {
                r += i - s + 1;
                continue;
            }

            while (s < nums.size() && prod >= k)
            {
                prod /= nums[s];
                ++s;
            }
            if (prod < k)
                r += i - s + 1;
        }
        return r;
    }
};

int main()
{
    Solution s;
    vector<int> v({ 10,5,2,6 });
    
    cout << s.numSubarrayProductLessThanK(v, 100) << endl;

    return 0;
}