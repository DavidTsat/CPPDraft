#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
    void nextP(vector<int>& nums) {
        int i = nums.size() - 1;
        bool b = false;

        for (; i >= 0 && !b; --i)
        {
            if (i > 0 && nums[i - 1] < nums[i])
            {
                for (int j = nums.size() - 1; j > i - 1; --j)
                {
                    if (nums[j] > nums[i - 1])
                    {
                        swap(nums[j], nums[i - 1]);
                        b = true;
                        break;
                    }
                }
            }
        }
        reverse(nums.begin() + max(0, i + 1), nums.end());
    }

public:
    void nextPermutation(vector<int>& nums) {
        nextP(nums);
    }

};

int main()
{
    //  vector<int> v({ 1,3,2 });
   //   vector<int> v({ 2,1,3 });
   //    vector<int> v({ 2,3, 1 });
   //   vector<int> v({ 3,1,2 });
   //   vector<int> v({ 3,2,1 });
    vector<int> v({ 2,1,5,4,6,3,2 });
    Solution s;

    s.nextPermutation(v);
    for (int i : v)
    {
        cout << i << ' ';
    }
    cout << endl;
    return 0;
}