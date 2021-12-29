#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
    vector<vector<int>> r;

    void f_slow(vector<int> nums, int j)
    {
        if (j >= nums.size())
        {
            if (find(r.cbegin(), r.cend(), nums) == r.cend())
                r.push_back(nums);
            return;
        }

        for (int i = j; i < nums.size(); ++i)
        {
            swap(nums[j], nums[i]);
            f_slow(nums, j + 1);
        }
    }

    void f_fast(vector<int> nums, int j)
    {
        if (j >= nums.size())
        {
            r.push_back(nums);
            return;
        }

        for (int i = j; i < nums.size(); ++i)
        {
            swap(nums[j], nums[i]);
            if (i != j && nums[i] == nums[j])
            {
                continue;
            }
            f_fast(nums, j + 1);
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {

        sort(nums.begin(), nums.end());
        f_fast(nums, 0);
        return r;
    }
};

int main()
{
    vector<int> v({ 1,2,2,2,3,3,4,5 });

    Solution s;

   
    auto r = s.permuteUnique(v);

    for (auto& rr : r)
    {
        for (int c : rr)
        {
            cout << c << ' ';
        }
        cout << endl;
    }

    return 0;
}