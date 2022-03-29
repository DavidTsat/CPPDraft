#include <iostream>
#include <vector>

using namespace std;


class Solution {
    template <typename It, typename T>
    It lower_bound_(It b, It e, T v)
    {
        auto count = distance(b, e);
        auto step = count / 2;

        while (count)
        {
            auto it2 = next(b, step);
            if (v > *it2)
            {
                b = ++it2;
                count -= (step + 1);
            }
            else
            {
                count = step;
            }
            step = count / 2;
        }
        return b;
    }

    /*
    int vertical_lower_bound(const vector<vector<int>>& v, int t)
    {
        int count = v[0].size();
        int step = count / 2;

        while (count)
        {
            int it2 = step;
            if (t > v[0][step])
        }
    }
    */
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {

        int r = -1;
        for (int i = 0; i < matrix[0].size(); ++i)
        {
            if (target >= matrix[0][i] && target <= matrix[matrix.size() - 1][i])
            {
                r = i;
                //     break;
            }
            //    if (target > matrix[0][i]) break;
        }

        if (r == -1) return false;
        for (int i = 0; i < matrix.size(); ++i)
        {
            if (matrix[i][0] <= target && matrix[i][matrix[i].size() - 1] >= target)
            {
                auto p = lower_bound_(matrix[i].cbegin(), matrix[i].cbegin() + r, target);
                if (p != matrix[i].cend() && *p == target) return true;
            }
        }

        return false;
    }
};

int main()
{
    vector<vector<int>> v1({ {-1, 3} });
    vector<vector<int>> v2({ {{1,2,3,4,5}, {6,7,8,9,10}, {11,12,13,14,15}, {16,17,18,19,20}, {21,22,23,24,25 }} });

    Solution s;
    cout << s.searchMatrix(v1, 1);
    return 0;
}