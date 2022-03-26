#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& nums) {
        vector<vector<int>> r;

        sort(nums.begin(), nums.end(), [](const vector<int>& a, const vector<int>& b) {return a[0] < b[0]; });
        int i = 0;
        int j = 1;

        while (j < nums.size())
        {
            int m = nums[i][1];
            int m_ = nums[i][0];
            bool b = false;
            vector<int> to_merge = nums[i];
            while (j < nums.size() && m >= nums[j][0])
            {
                b = true;
                m = max(m, nums[j][1]);
                to_merge = { m_, m };
                ++i;
                ++j;
            }
            if (b)
            {
                ++i; ++j;
                if (r.empty() || (!r.empty() && r[r.size() - 1] != to_merge))
                    r.push_back(to_merge);
                continue;
            }
            else
            {
                if (r.empty() || (!r.empty() && r[r.size() - 1] != nums[i]))
                    r.push_back(nums[i]);
                ++i;
                ++j;
            }

        }

        if (i == nums.size() - 1)
        {
            if (!r.empty() && r[r.size() - 1] != nums[i])
            {
                r.push_back(nums[i]);
                return r;
            }
            if (r.empty())
                r.push_back(nums[i]);
        }
        return r;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> v1({ { 1,4 }, { 0,0 } });
    vector<vector<int>> v2({ {1,4} ,{0,2},{3,5} });
    vector<vector<int>> v3({ {1, 3},{2, 6},{8, 10},{15, 18} });
    vector<vector<int>> v4({ {1,5} });
    vector<vector<int>> v5({ {2, 3}, { 4, 5}, { 6, 7}, { 8, 9}, { 1, 10 } });
    vector<vector<int>> v6({ { 4, 5 }, { 2, 4 }, { 4, 6 }, { 3, 4 }, { 0, 0 }, { 1, 1 }, { 3, 5 }, { 2, 2 } });
    vector<vector<int>> vv = s.merge(v1);
    // vector<vector<int>> vv = s.merge(vvv);
    for (vector<int> v : vv)
    {
        for (int i : v)
            cout << i << ' ';
        cout << endl;
    }

    /*
    Solution s;

    vector<int> v1({ 2,0,2,1,1,0 });
    vector<int> v2({ 2,0,1 });
    vector<int> v3({ 2,2,0,1,0,1,2,0,2,0,2,1,2 });

    s.sortColors(v3);
    for (int i : v3)
    {
        cout << i << ' ';
    }
    cout << endl;
    */
    return 0;
}