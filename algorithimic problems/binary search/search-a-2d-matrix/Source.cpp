#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {

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
public:

    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
        bool b = false;
        for (const vector<int>& row : matrix)
        {
            if (!row.empty() && *row.cbegin() <= target && row[row.size() - 1] >= target)
            {
                auto it = lower_bound_(row.cbegin(), row.cend(), target);
                b = it != row.cend() && *it == target;
                break;
            }
        }
        return b;
    }
};