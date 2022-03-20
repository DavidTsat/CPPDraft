#include <iostream>
#include <vector>

using namespace std;

class Solution {
    template<typename It, typename T>
    It lower_bound_(It f, It l, T v)
    {
        auto count = std::distance(f, l);
        decltype(count) step = count / 2;

        while (count)
        {
            auto f_next = std::next(f, step);
            if (v > *f_next)
            {
                f = next(f_next);
                count = count - step - 1;
            }
            else
            {
                count = step;
            }
            step = count / 2;
        }
        return f;
    }

    template<typename It, typename T>
    It upper_bound_(It f, It l, T v)
    {
        auto count = std::distance(f, l);
        decltype(count) step = count / 2;

        while (count)
        {
            auto f_next = std::next(f, step);
            if (v >= *f_next)
            {
                f = next(f_next);
                count = count - step - 1;
            }
            else
            {
                count = step;
            }
            step = count / 2;
        }
        return f;
    }

    template<typename It, typename T>
    pair<It, It> equal_range_(It f, It l, It e, T v)
    {
        auto l_ = lower_bound_(f, l, v);
        auto r_  = upper_bound_(f, l, v);
        if (l_ == e || *l_ != v) 
        {
            return { e, e };
        }
        return { l_, next(r_, -1) };
    }
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> v{ -1, -1 };
        auto res = equal_range_(nums.cbegin(), nums.cend(), nums.cend(), target);
        if (res.first == nums.cend()) return v;
        v[0] = distance(nums.cbegin(), res.first);
        v[1] = distance(nums.cbegin(), res.second);
        return v;
    }
};

int main()
{
    Solution s;
    vector<int> v({ 5, 7, 7, 8, 8, 10 });
    vector<int> v2({1}); // 0
    vector<int> p = s.searchRange(v2, 1);

    cout << p[0] << ' ' << p[1] << endl;
    return 0;
}