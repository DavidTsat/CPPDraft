#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
    vector<vector<int>> r;

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

    void f_slow(vector<int> nums, int j)
    {
        if (j >= nums.size())
        {
            if (find(r.cbegin(), r.cend(), nums) == r.cend())
                r.push_back(nums);
            return;
        }

        for (int i = j; i < nums.size(); ++i)
        {
            swap(nums[j], nums[i]);
            f_slow(nums, j + 1);
        }
    }

    void f_fast(vector<int> nums, int j)
    {
        if (j >= nums.size())
        {
            r.push_back(nums);
            return;
        }

        for (int i = j; i < nums.size(); ++i)
        {
            swap(nums[j], nums[i]);
            if (i != j && nums[i] == nums[j])
            {
                continue;
            }
            f_fast(nums, j + 1);
        }
    }

    template <typename It>
    bool nextP(It b, It e) {
        if (b == e) return false;
        bool c = false;
        It f = e;
        --f;
        if (b == f) return false;
        It f2 = f;

        while (*--f2 >= *f-- && f2 != b);

        if (f2 != b || (f2 == b && *f2 < *next(f2)))
        {
            c = true;
            It e2 = e;
            while (--e2 != f2 && *e2 <= *f2);
            iter_swap(f2, e2);
        }

        if (c)
        {
            reverse(next(f2), e);
            return true;
        }
        else
        {
            reverse(b, e);
            return false;
        }
    }

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        //    f_fast(nums, 0);
        vector<int> v = nums;

        while (nextP(v.begin(), v.end()))
        {
            r.push_back(v);
        }
        r.push_back(v);
        return r;
    }
};

int main()
{
    vector<int> v({ 1,2,2,2,3,3,4,5 });

  //  vector<int> v({ 0,-1,1 });
    Solution s;

   
    auto r = s.permuteUnique(v);

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