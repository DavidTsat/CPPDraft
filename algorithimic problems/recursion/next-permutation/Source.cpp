#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//vector<int> v({ 1,3,2 });
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
    void nextPermutation(vector<int>& nums) {
        nextP(nums.begin(), nums.end());
    }

};

int main()
{
    
      vector<int> v({ 2,1,3 });
   //    vector<int> v({ 2,3, 1 });
   //   vector<int> v({ 3,1,2 });
   //   vector<int> v({ 3,2,1 });
  //  vector<int> v({ 2,1,5,4,6,3,2 });
    Solution s;

    s.nextPermutation(v);
    for (int i : v)
    {
        cout << i << ' ';
    }
    cout << endl;
    return 0;
}