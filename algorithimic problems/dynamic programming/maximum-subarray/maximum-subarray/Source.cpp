class Solution {
    int max_sub_array(const vector<int>& nums, vector<int>& v, int i)
    {
        if (i >= nums.size())
        {
            return 0;
        }

        int m = max(nums[i], v[i]);

        if (v[i] == -1)
        {
            m = max(nums[i], nums[i] + max_sub_array(nums, v, i + 1));
            v[i] = m;
        }
        return m;
    }
    int max_sub_array(const vector<int>& nums, int& gl_m, int i)
    {
        if (i == 1)
        {
            return nums[0];
        }

        //  int m = max(nums[i], v[i]);

        int m = max(nums[i - 1], nums[i - 1] + max_sub_array(nums, gl_m, i - 1));
        gl_m = max(m, gl_m);
        return m;
    }
    int max_sub_array_kadane(const vector<int>& nums)
    {
        int best_sum = INT_MIN;
        int cur_sum = 0;
        for (int n : nums)
        {
            cur_sum = max(n, cur_sum + n);
            best_sum = max(cur_sum, best_sum);
        }
        return best_sum;
    }
    int maxSubArrayDP(const vector<int>& nums) {
        vector<int> dp(nums);
        for (int i = 1; i < size(nums); i++)
            dp[i] = max(nums[i], nums[i] + dp[i - 1]);
        return *max_element(begin(dp), end(dp));
    }
public:
    int maxSubArray(const vector<int>& nums) {
        return maxSubArrayDP(nums);
        //     if (nums.size() == 1) return nums[0];
            // return max_sub_array_kadane(nums);
             /*
             int global_max = nums[0];
             max_sub_array(nums, global_max, nums.size());
             */
             /*
             int m = INT_MIN;
             vector<int> v(nums.size(), -1);
             for (int i = nums.size()-1; i >= 0; --i)
             {
                 m = max(m, max_sub_array(nums, v, i));
             }*/
             //  return global_max;
    }
};