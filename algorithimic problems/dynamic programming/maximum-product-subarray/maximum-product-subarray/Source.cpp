class Solution {
    /*
      int maxProduct(vector<int>& nums, vector<int>& v)
      {
          v[0] = nums[0];
          int prev = nums[0];
          for (int i = 1; i < nums.size(); ++i)
          {
              vector<int> r({nums[i], v[i-1]*nums[i]});
              if (prev < 0) r.push_back(prev*nums[i]);

              auto p = max_element(r.cbegin(), r.cend());
              auto m = min_element(r.cbegin(), r.cend());
              prev = *m;
              v[i] = *p;
          }
          return *max_element(v.begin(), v.end());
      }
      */
    int max_product(vector<int>& nums)
    {
        int ans = nums[0];
        int cur_max = nums[0];
        int prev = nums[0];

        for (int i = 1; i < nums.size(); ++i)
        {
            vector<int> r({ nums[i], cur_max * nums[i] });
            if (prev < 0) r.push_back(prev * nums[i]);

            auto p = max_element(r.cbegin(), r.cend());
            auto m = min_element(r.cbegin(), r.cend());
            prev = *m;
            cur_max = *p;
            ans = max(ans, cur_max);
        }
        return ans;
    }
public:
    int maxProduct(vector<int>& nums) {
        return max_product(nums);
    }
};