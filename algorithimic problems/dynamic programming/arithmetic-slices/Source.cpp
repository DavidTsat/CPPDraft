#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        if (nums.size() < 3) return 0;
        int c = nums[1] - nums[0];
        int s = 0;
        int i = 0;

        for (int j = 2; j < nums.size(); ++j)
        {
            if ((nums[j] - nums[j - 1]) == c)
            {
                s += j - i - 1;
            }
            else
            {
                i = j - 1;
             //   if (j >= nums.size()) break;
                c = nums[i + 1] - nums[i];
            }
        }
        return s;
    }
};

int main()
{
    Solution s;

    vector<int> v1({ 1,3,5,7,9 });
    vector<int> v2({ 1,3,5,8,10,12,0,3,4,5,6 });
    vector<int> v3({ 1,2,3,8,9,10 });
    cout << s.numberOfArithmeticSlices(v1) << endl;
	return 0;
}