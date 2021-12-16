#include <iostream>
#include <vector>

using namespace std;

class Solution {
    template <typename ForwardIt, typename T>
    ForwardIt lower_bound_(ForwardIt first, const ForwardIt last, const T& value)
    {
        auto count = std::distance(first, last);
        decltype(count) step = 0;

        auto it = first;

        while (count > 0)
        {
            it = first;
            step = count / 2;
            advance(it, step);

            if (*it < value)
            {
                first = ++it;
                count -= step + 1;
            }
            else
            {
                count = step;
            }
        }

        return it;
    }

    template <typename ForwardIt, typename T>
    ForwardIt upper_bound_(ForwardIt first, const ForwardIt last, const T& value)
    {
        auto count = std::distance(first, last);
        decltype(count) step = 0;

        auto it = first;

        while (count > 0)
        {
            it = first;
            step = count / 2;
            advance(it, step);

            if (*it <= value)
            {
                first = ++it;
                count -= step + 1;
            }
            else
            {
                count = step;
            }
        }

        return it;
    }

    template <typename ForwardIt, typename T>
    std::pair<ForwardIt, ForwardIt> equal_range_(ForwardIt first, ForwardIt last, const T& value)
    {
        auto lb = lower_bound_(first, last, value);
        if (lb == last || *lb > value)
            return { last, last };

        auto rb = upper_bound_(first, last, value);
        return { lb, rb };
    }

public:
    vector<int> searchRange(vector<int>& nums, int target) {
        auto p = equal_range_(nums.cbegin(), nums.cend(), target);
        if (p.first == nums.cend())
        {
            return { -1, -1 };
        }

        return { (int)distance(nums.cbegin(), p.first), (int)distance(nums.cbegin(), p.second - 1) };
    }
};

int main()
{
    Solution s;
    vector<int> v({ 5, 7, 7, 8, 8, 10 });
    vector<int> p = s.searchRange(v, 8);

    cout << p[0] << ' ' << p[1] << endl;
    return 0;
}