#include <vector>
#include <array>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
    int rob_optimal(const vector<int>& nums, const int first_elem_idx, const int last_elem_idx)
    {
        array<int, 3> v{ -1, -1, -1 };
        if (nums.size() == 1) return nums[0];

        v[0] = nums[first_elem_idx];
        v[1] = nums[first_elem_idx + 1];

        for (int i = first_elem_idx + 2; i < last_elem_idx; ++i)
        {
            int m = v[0];
            if (v[2] != -1)
            {
                m = max(m, v[1]);
                v[0] = v[1];
                v[1] = v[2];
            }
            v[2] = m + nums[i];
        }

        return *max_element(v.cbegin(), v.cend());
    }
public:
    int deleteAndEarn(const vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        int m = *max_element(nums.cbegin(), nums.cend());

        vector<int> v(m + 1, 0);

        for (int n : nums)
        {
            v[n] += n;
        }

        int f = 0;
        while (v[f] == 0) ++f;
        return rob_optimal(v, f, v.size());
    }
};


int main()
{
    Solution s;
    cout << s.deleteAndEarn({ 2,2,3,3,3,4 });

    return 0;
}