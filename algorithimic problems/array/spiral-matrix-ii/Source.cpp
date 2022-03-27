#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> v(n, vector<int>(n, 0));

        int k = n % 2 == 0 ? n / 2 : n / 2 + 1;
        int c = 1;

        for (int p = 0; p < k; ++p)
        {
            for (int j = 0; j <= 3; ++j)
            {
                switch (j)
                {
                case 0:
                    // row; from left to right
                    for (int i = 1; i <= n; ++i)
                    {
                        if (!v[p][i - 1])
                            v[p][i - 1] = c++;
                    }
                    break;
                case 1:
                    // column; from up to bottom
                    for (int i = 1; i <= n; ++i)
                    {
                        if (!v[i - 1][v.size() - 1 - p])
                            v[i - 1][v.size() - 1 - p] = c++;
                    }
                    break;
                case 2:
                    // row; from right to left
                    for (int i = 1; i <= n; ++i)
                    {
                        if (!v[v.size() - 1 - p][v.size() - i])
                            v[v.size() - 1 - p][v.size() - i] = c++;
                    }
                    break;
                case 3:
                    // column; from bottom to up
                    for (int i = 1; i <= n; ++i)
                    {
                        if (!v[v.size() - i][p])
                            v[v.size() - i][p] = c++;
                    }
                    break;
                }
            }
        }
        return v;
    }
};

int main()
{
    Solution s;

    vector<vector<int>> v = s.generateMatrix(7);

    for (const vector<int>& vv : v)
    {
        for (int c : vv)
        {
            cout << c << ' ';
        }
        cout << endl;
    }

    return 0;
}