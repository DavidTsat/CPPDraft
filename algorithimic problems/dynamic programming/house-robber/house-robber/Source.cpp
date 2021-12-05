#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <array>

using namespace std;

class Solution {
    int rob_recursive(const vector<int>& nums, int i)
    {
        if (i >= nums.size()) return 0;

        return max(nums[i] + rob_recursive(nums, i + 2), rob_recursive(nums, i + 1));
    }

    int rob_optimal(const vector<int>& nums)
    {
        array<int, 3> v{};
        if (nums.size() == 1) return nums[0];

        v[0] = nums[0];
        v[1] = nums[1];

        for (int i = 2; i < nums.size(); ++i)
        {
            int m = v[0];
            if (i > 2)
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
    int rob(const vector<int>& nums) {
        //return rob_recursive(nums, 0);  
        return rob_optimal(nums);
    }
};

class Solution_circle {
    int rob_optimal(const vector<int>& nums, const int first_elem_idx, const int last_elem_idx)
    {
        array<int, 3> v{-1, -1, -1};
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
    int rob(const vector<int>& nums) {
        if (nums.size() < 3) return *max_element(nums.cbegin(), nums.cend());
        int m1 = rob_optimal(nums, 0, nums.size() - 1);
        int m2 = rob_optimal(nums, 1, nums.size());
        return max(m1, m2);
    }
};
int main() {
    Solution_circle s;

    //[114,117,207,117,235,82,90,67,143,146,53,108,200,91,80,223,58,170,110,236,81,90,222,160,165,195,187,199,114,235,197,187,69,129,64,214,228,78,188,67,205,94,205,169,241,202,144,240]
    // 6,6,4,8,4,3,3,10

    
    auto start_time = chrono::high_resolution_clock::now();

    int c = s.rob({ 114,117,207,117,235,82,90,67,143,146,53,108,200,91,80,223,58,170,110,236,81,90,222,160,165,195,187,199,114,235,197,187,69,129,64,214,228,78,188,67,205,94,205,169,241,202,144,24 });
    //int c = s.rob({ 1,3,1,3,100 });
  //  int c = s.rob({ 1,7,9,2 });
    cout << c << endl;

    auto end_time = chrono::high_resolution_clock::now();
    auto time = end_time - start_time;

    cout << time/ chrono::milliseconds(1) << endl;
    
    return 0;
}