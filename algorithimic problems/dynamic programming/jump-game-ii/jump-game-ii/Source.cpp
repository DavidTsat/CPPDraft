#include <vector>
#include <iostream>

using namespace std;
class Solution {
    int jump(vector<int>& v, const vector<int>& nums, int i) {
        if (i >= nums.size() - 1)
        {
            return 0;
        }
        if (v[i] != -1) return v[i];

        int k = INT_MAX - 10;
        for (int j = nums[i]; j >= 1; --j)
        {
            int q = i + j;
            k = min(k, 1 + jump(v, nums, q));
        }
        v[i] = k;
        return k;
    }
public:
    int jump(const vector<int>& nums) {
        if (nums.size() == 1) return 0;
        vector<int> v(nums.size(), -1);

        int m = jump(v, nums, 0);
        return m;
    }

};

int main()
{
    Solution s;
   // cout << s.jump({ 2,3,1,1,4 }) << endl;
    // { 5,9,3,2,1,0,2,3,3,1,0,0}
    // 2, 1
    // 9,8,2,2,0,2,2,0,4,1,5,7,9,6,6,0,6,5,0,5
    vector<int> vv({ 9,8,2,2,0,2,2,0,4,1,5,7,9,6,6,0,6,5,0,5 });
    cout << s.jump(vv) << endl;
    return 0;
}