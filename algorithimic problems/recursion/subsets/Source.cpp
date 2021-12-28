#include <vector>
#include <iostream>

using namespace std;

class Solution {
    vector<vector<int>> r;

    void getSubsets(const vector<int>& nums, vector<int> v, const int s, int j)
    {
        if (s == v.size())
        {
            r.push_back(v);
            return;
        }

        for (int i = j + 1; i < nums.size(); ++i)
        {
            v.push_back(nums[i]);
            getSubsets(nums, v, s, i);
            v.pop_back();
        }
    }

public:
    vector<vector<int>> subsets(vector<int>& nums) {

        for (int s = 0; s <= nums.size(); ++s)
        {
            getSubsets(nums, {}, s, -1);
        }
        return r;
    }
};

int main()
{
    Solution s;
    vector<int> v({ 1,2,3,4,5 });

    vector<vector<int>> r = s.subsets(v);

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