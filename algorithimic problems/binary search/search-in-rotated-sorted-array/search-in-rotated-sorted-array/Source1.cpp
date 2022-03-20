#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class Solution {

    template <typename It>
    It rotate_point(It f, It l)
    {
        auto count = std::distance(f, l);
        decltype(count) step = count / 2;

        while (count && step)
        {
            auto f_next = std::next(f, step);

            if (*f_next < *f)
            {
                count = step;
            }
            else
            {
                f = f_next;
                count -= step;
            }
            step = count / 2;
        }
        return f;
    }

public:

    int search(std::vector<int>& nums, int target)
    {
        if (nums[0] <= nums[nums.size() - 1])
        {
            auto it = std::lower_bound(nums.cbegin(), nums.cend(), target);
            return (it != nums.cend() && *it == target) ? distance(nums.cbegin(), it) : -1;
        }
        auto p = rotate_point(nums.cbegin(), next(nums.cend(), -1));
        auto it1 = std::lower_bound(nums.cbegin(), p, target);
        if (*it1 == target) return distance(nums.cbegin(), it1);

        auto it2 = std::lower_bound(next(p), nums.cend(), target);
        if (it2 != nums.cend() && *it2 == target) return distance(nums.cbegin(), it2);
        return -1;
    }
};