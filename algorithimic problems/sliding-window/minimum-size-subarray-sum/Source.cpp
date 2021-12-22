#include <iostream>
#include <vector>

using namespace std;

class Solution {
    int minSubArrayLenNotOptimal(int target, vector<int>& nums) {
        int min_ = INT_MAX;

        for (int i = 0; i < nums.size(); ++i)
        {
            int s = 0;
            for (int j = i; j >= 0; --j)
            {
                s += nums[j];
                if (s >= target)
                {
                    //min_ = min(min_, s);
                    min_ = min(min_, i - j + 1);
                    break;
                }
            }
        }
        return min_ == INT_MAX ? 0 : min_;
    }
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int min_ = INT_MAX;
        int s = 0;
        int sum = 0;

        for (int i = 0; i < nums.size(); ++i)
        {
            sum += nums[i];
            while (sum >= target)
            {
                min_ = min(min_, i - s + 1);
                sum -= nums[s];
                ++s;
            }
        }
        return min_ == INT_MAX ? 0 : min_;
    }
};

int main()
{
    Solution s;
    vector<int> v({ 2,3,1,2,4,3 });
    
    cout << s.minSubArrayLen(7, v);

    return 0;
}