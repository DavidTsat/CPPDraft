#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> r(nums.size(), 1);

        for (int i = 1; i < nums.size(); ++i)
        {
            r[i] = r[i - 1] * nums[i - 1];
        }
        for (int i = nums.size() - 2; i >= 0; --i)
        {
            r[i] *= nums[i + 1];
            nums[i] *= nums[i + 1];
        }

        return r;
    }
};

int main()
{
    Solution s;

    vector<int> v1{ 1, 2, 3, 4 };
    vector<int> v2{ -1, 1, 0, -3, 3 };
    
    v1 = s.productExceptSelf(v1);
    v2 = s.productExceptSelf(v2);

    for (int c : v1)
    {
        cout << c << ' ';
    }
    cout << endl;

    for (int c : v2)
    {
        cout << c << ' ';
    }
    cout << endl;

    return 0;
}