#include <iostream>
#include <vector>

using namespace std;

class Solution {

    int f(int m, int n, vector<vector<int>>& v)
    {
        if (m == 1 || n == 1)
        {
            return 1;
        }

        if (v[m][n] != -1)
        {
            return v[m][n];
        }

        v[m - 1][n] = f(m - 1, n, v);
        v[m][n - 1] = f(m, n - 1, v);

        return v[m - 1][n] + v[m][n - 1];
    }

public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> v(max(m, n) + 1, vector<int>(max(m, n) + 1, -1));

        return f(m, n, v);
    }
};

int main()
{
    Solution s;
    cout << s.uniquePaths(3, 7) << endl;

}