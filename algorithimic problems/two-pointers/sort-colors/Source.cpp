#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int i = 0;
        int zero_i = 0;
        int two_i = nums.size() - 1;

        for (; i < nums.size() and i <= two_i;)
        {
            switch (nums[i])
            {
            case 0:
                swap(nums[i], nums[zero_i]);
                   ++zero_i;
                break;
            case 1:
                //   ++i;
                break;
            case 2:
                swap(nums[i], nums[two_i]);
                   --two_i;
                break;
            
            }
            if (nums[i] == 1) ++i;
            if (i < zero_i) i = zero_i;
        }

    }
};

int main()
{
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
    return 0;
}