#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    vector<vector<int>> r;

    void getSubsets(const vector<int>& nums, vector<int> v, const int s, int j)
    {
        if (s == v.size())
        {
            sort(v.begin(), v.end());
            if (find(r.cbegin(), r.cend(), v) == r.cend())
            {
                r.push_back(v);
            }
            return;
        }

        for (int i = j; i < nums.size(); ++i)
        {
            v.push_back(nums[i]);
            getSubsets(nums, v, s, i + 1);
            v.pop_back();
        }
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        for (int s = 0; s <= nums.size(); ++s)
        {
            getSubsets(nums, {}, s, 0);
        }
        return r;
    }
};
int main()
{
    Solution s;
    vector<int> v({ 4,4,4,1,4 });

    vector<vector<int>> r = s.subsetsWithDup(v);

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