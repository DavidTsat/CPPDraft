#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>


using namespace std;

class Solution {
    int max_product(vector<int>& nums)
    {
        int i = 0, n = 0, l = 0;
        int fn = 0, ln = 0;
        long long pr = 1;
        vector<int> prods;

        while (i < nums.size())
        {

            if (nums[i] == 0)
            {
                if (pr != 0) {
                    if (n % 2)
                    {
                        vector<int> vr({ fn - l, i - fn - 1, ln - l, i - ln - 1 });
                        prods.push_back(*max_element(vr.cbegin(), vr.cend()));
                    }
                    else
                    {
                        prods.push_back(i - l);
                    }
                }
                pr = 1;
                fn = 0;
                l = min((int)nums.size() - 1, i + 1);
                //  l = i;
                n = 0;
                //++i;
            }
            else if (nums[i] < 0)
            {

                if (fn == 0 && nums[fn] >= 0)
                {
                    fn = i;
                    //  fn = min((int)nums.size() - 1, i + 1);
                }
                ln = i;
                //fn = min((int)nums.size() - 1, i + 1);
                ++n;
                //  ++i;
            }

            pr *= nums[i] > 0 ? nums[i] : 1;
            ++i;
        }
        //l = nums[l] == 0 ? l : l - 1;
        while (l < nums.size() && nums[l] == 0) ++l;

        if (n % 2)
        {
            vector<int> vr({ fn - l, i - fn - 1, ln - l, i - ln - 1 });
            prods.push_back(*max_element(vr.cbegin(), vr.cend()));
        }
        else
        {
            prods.push_back(i - l);
        }

        return *max_element(prods.cbegin(), prods.cend());
    }


    int getMaxLen2(vector<int>& nums) {
        int l = 0, r = 0, fn = -1, n = 0, m = 0;

        while (r < nums.size())
        {
            if (nums[r] == 0)
            {
                l = r + 1;
                fn = -1;
                n = 0;
            }
            if (nums[r] < 0)
            {
                ++n;
                if (fn == -1) fn = r;
            }

            if (n % 2 == 1)
            {
                m = max(m, r - fn);
            }
            else {
                m = max(m, r - l + 1);
            }
            ++r;
        }

        return m;
    }
public:
    int getMaxLen(vector<int>& nums) {
        return getMaxLen2(nums);
    }
};

int main() {

    vector<int> vv({ 1,-2,-3,4 });
    vector<int> v({ -16,0,-5,2,2,-13,11,8 });
    vector<int> vvv({ 9, 10, 1, 0, 19, 20, -28, 30, -12, 20, 11, -8, 7, 21, -26 });

    vector<int> v4({ 5, -20, -20, -39, -5, 0, 0, 0, 36, -32, 0, -7, -10, -7, 21, 20, -12, -34, 26, 2 });
    vector<int> v5({ 0,1,-2,-3,-4 });

    vector<int> v6({ 1,2,3,5,-6,4,0,10 });
    vector<int> v7({ 0,-19,26,-24,-13,-2,26,10,0,4,0,-26,-22,9,35,-11,-14,0,-29 });
    vector<int> v8({ -17,-9,17,-3,-5,-13,2,6,0 });
    vector<int> v9({ 0,1,1, -2 });
    Solution s;

    cout << s.getMaxLen(v9) << endl;
    return 0;
}