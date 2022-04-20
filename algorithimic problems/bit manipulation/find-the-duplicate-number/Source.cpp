#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int findDuplicateNegative(vector<int>& nums)
    {
        int c = 0;

        for (int i = 0; i < nums.size(); ++i)
        {
            int ind = abs(nums[i]);
            if (nums[ind] < 0)
            {
                c = ind;
                break;
            }
            else
                nums[ind] = ~nums[ind] + 1;
        }
        return c;
    }

    int findDuplicateSwap(vector<int>& nums)
    {
        int c = 0;

        for (int i = 0; i < nums.size(); )
        {
            if (nums[i] - 1 != i)
            {
                if (nums[nums[i] - 1] == nums[i])
                {
                    c = nums[i];
                    break;
                }
                else
                {
                    swap(nums[nums[i] - 1], nums[i]);
                }
            }
            else
            {
                ++i;
            }
        }

        return c;
    }

    int findDuplicate(vector<int>& nums)
    {
        return findDuplicateNegative(nums);
    }
};

int main()
{
    Solution s;
    vector<int> v1 = { 3, 1, 3, 4, 2 };
    vector<int> v2 = { 2, 2, 2, 2 };

    cout << s.findDuplicate(v1) << endl;
    cout << s.findDuplicate(v2) << endl;
    return 0;
}