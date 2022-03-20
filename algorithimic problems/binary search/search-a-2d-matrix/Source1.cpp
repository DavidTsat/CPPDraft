#include <algorithm>
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

    int vertical_lower_bound(const std::vector<std::vector<int>>& m, int v)
    {
        int f = 0;
        int count = m.size();
        int step = count / 2;

        while (count)
        {
            int f_next = f + step;
            if (v > m[f_next][0])
            {
                f = f_next + 1;
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

public:

    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
        if (matrix.empty()) return false;
        if (matrix.size() == 1)
        {
            auto it = lower_bound_(matrix[0].cbegin(), matrix[0].cend(), target);
            return (it == matrix[0].cend() || *it != target) ? false : true;
        }

        int p = vertical_lower_bound(matrix, target);
        if (p == matrix.size())
        {
            auto it = lower_bound_(matrix[matrix.size() - 1].cbegin(), matrix[matrix.size() - 1].cend(), target);
            return (it == matrix[matrix.size() - 1].cend() || *it != target) ? false : true;
        }
        if (matrix[p][0] == target) return true;
        if (p == 0) return false;
        auto it = lower_bound_(matrix[p - 1].cbegin(), matrix[p - 1].cend(), target);
        return (it == matrix[p - 1].cend() || *it != target) ? false : true;
    }
};