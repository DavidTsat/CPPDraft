#include <iostream>
#include <vector>

using namespace std;

class Solution {
    vector<vector<int>> intervalIntersectionPerebor(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        vector<vector<int>> r;

        for (const vector<int>& f : firstList)
        {
            for (const vector<int>& s : secondList)
            {
                if (s[0] > f[1]) break;

                int p = max(f[0], s[0]);
                int q = min(f[1], s[1]);
                if (p <= q)
                    r.push_back({ p, q });
            }
        }
        return r;
    }

    vector<vector<int>> intervalIntersectionOptimized(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        vector<vector<int>> r;

        auto itf = firstList.cbegin();
        auto its = secondList.cbegin();

        while (itf != firstList.cend() && its != secondList.cend())
        {
            if ((*itf)[0] > (*its)[1])
            {
                ++its;
                continue;
            }
            if ((*its)[0] > (*itf)[1])
            {
                ++itf;
                continue;
            }

            int p = max((*itf)[0], (*its)[0]);
            int q = min((*itf)[1], (*its)[1]);
            r.push_back({ p, q });

            if ((*itf)[1] <= (*its)[1]) ++itf;
            else ++its;
        }

        return r;
    }
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        return intervalIntersectionOptimized(firstList, secondList);
    }
};

int main()
{
    Solution s;
    vector<vector<int>> v1({ {0, 2}, {5, 10}, {13, 23}, {24, 25} });
    vector<vector<int>> v2({ {1, 5}, {8, 12}, {15, 24}, {25, 26} });
    /*
    [[1, 3], [5, 9]]
    []
    []
    [[4, 8], [10, 12]]
    [[1, 7]]
    [[3, 10]]
    */

    vector<vector<int>> r = s.intervalIntersection(v1, v2);

    for (auto& rr : r)
    {
        int i = 0;
        for (int c : rr)
        {
            if (++i == 2)
                cout << c;
            else
                cout << c << ' ';
        }
        cout << ", ";
    }
    return 0;
}