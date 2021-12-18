#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class Solution {
    int _binary_search(std::vector<int>& nums, size_t begin, size_t end, int target) {

        size_t count = end - begin;
        size_t mid = begin + (size_t)(end - begin) / 2;
        size_t begin_cp = begin;

        while (count) {

            //     auto dist = end - begin;
            if (target >= nums[begin] && target <= nums[mid]) {
                end = mid;
                auto dist = end - begin;
                mid = begin + size_t(dist / 2);
                count = size_t(dist);
                continue;
            }
            else if (target >= nums[mid] && target <= nums[end]) {

                begin = mid + 1;
                auto dist = end - begin;
                mid = begin + size_t(dist / 2);
                count = size_t(dist);
                continue;
            }
            else {
                return -1;
            }
        }
        return nums[mid] == target ? mid - begin_cp : -1;
    }

    int search_(std::vector<int>& nums, int target) {
        size_t left = 0;
        size_t mid = (size_t)nums.size() / 2;
        size_t end = nums.size() - 1;

        size_t count = nums.size();


        if (nums[end] > nums[left]) {
            return _binary_search(nums, left, end, target);
        }


        while (count >= 0) {
            if (nums[left] < nums[mid]) // left sorted
            {
                size_t i = _binary_search(nums, left, mid, target);
                if (i != -1) return left + i;
                left = mid + 1 > end ? end : mid + 1;
            }

            else if (nums[mid] < nums[end]) // right sorted
            {
                size_t i = _binary_search(nums, mid, end, target);
                if (i != -1) return mid + i;
                end = mid < 1 ? left : mid - 1;
            }
            else {
                // 2 elems
                if (nums[left] == target) return left;
                if (nums[end] == target) return end;
                return -1;
            }
            mid = left + (end - left) / 2;
            count = end - left;
            if (mid <left || mid >end) {
                return -1;
            }
        }

        return -1;
    }

    template <typename It, typename T>
    It lower_bound_(It first, It last, T value)
    {
        auto count = distance(first, last);
        decltype(count) step = 0;
        auto it = first;

        while (count > 0)
        {
            it = first;
            step = count / 2;
            advance(it, step);
            if (*it < value)
            {
                advance(first, step + 1);
                count -= step + 1;
            }
            else
            {
                count = step;
            }
        }
        return first;
    }

    template <typename It>
    It find_rot_point(It first, It last)
    {
        It f(first);
        auto count = distance(first, last);
        decltype(count) step = 0;
        auto it = first;

        while (count > 0)
        {
            it = first;
            step = count / 2;
            advance(it, step);

            if (*it >= *f)
            {
                advance(first, step + 1);
                count -= step + 1;
            }
            else
            {
                auto it_prev(it);
                --it_prev;
                if (*it < *it_prev)
                {
                    break;
                }
                count = step;
            }
        }
        return it;
    }

    template <typename It>
    int find_elem(It f, It l, int target)
    {
        auto rot_point = find_rot_point(f, l);
        auto it1 = lower_bound_(f, rot_point, target);
        if (it1 != l && *it1 == target)
        {
            return distance(f, it1);
        }

        auto it2 = lower_bound_(rot_point, l, target);
        if (it2 != l && *it2 == target)
        {
            return distance(f, it2);
        }

        return -1;
    }
 public:

    int search(std::vector<int>& nums, int target)
    {
        return find_elem(nums.cbegin(), nums.cend(), target);
    }
};

int main()
{
    Solution s;
    vector<int> v1({ 4, 5, 6, 7, 0, 1, 2 }); // 0, 3
    vector<int> v2({ 1 }); // 0
    
    cout << s.search(v1, 0) << ' ' << s.search(v1, 3) << ' ' << s.search(v2, 0) << endl;

    return 0;
}