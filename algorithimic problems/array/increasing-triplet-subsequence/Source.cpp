#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        if (nums.size() < 3) return false;

        int i_num = nums[0];
        int j_num = INT_MAX;

        for (int i = 1; i < nums.size(); ++i)
        {
            if (nums[i] > j_num) return true;

            if (nums[i] > i_num && nums[i] < j_num)
            {
                j_num = nums[i];
            }

            if (nums[i] < i_num)
            {
                i_num = nums[i];
            }
        }

        return false;
    }
};



int main()
{
    vector<int> v1 = { 0,4,2,1,0,-1,-3 };
    vector<int> v2 = { 20,100,10,12,5,13 };
    
    Solution s;

    cout << s.increasingTriplet(v1) << endl;
    return 0;
}