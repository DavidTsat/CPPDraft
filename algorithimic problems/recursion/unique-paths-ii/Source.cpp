#include <iostream>
#include <vector>

using namespace std;

class Solution {
    int c = 0;
    int m = 0;

    void f_perebor(vector<vector<int>>& v, int i, int j)
    {
        if ((i == v.size() - 1) && (j == v[0].size() - 1))
        {
            ++c;
            return;
        }
        if (v[i][j] == 1) return;

        if (i < v.size() - 1)
            f_perebor(v, i + 1, j);

        if (j < v[0].size() - 1)
            f_perebor(v, i, j + 1);
    }

    int fdp(vector<vector<int>>& dp, vector<vector<int>>& v, int i, int j)
    {
        if (v[i][j] == 1) return 0;

        int m_ = 0;
        if (i < v.size() - 1)
        {
            if (dp[i + 1][j])
                m_ = dp[i + 1][j];
            else m_ += fdp(dp, v, i + 1, j);
        }
        if (j < v[0].size() - 1)
        {
            if (dp[i][j + 1])
                m_ = dp[i][j + 1];
            else m_ += fdp(dp, v, i, j + 1);
        }

        return dp[i][j] = m_;
    }

public:
    int uniquePathsWithObstacles(vector<vector<int>>& o) {
        if (o.empty() || o[0][0] == 1 || o[o.size() - 1][o[0].size() - 1] == 1) return 0;
        if (o.size() == 1 || o[0].size() == 1) return o[o.size() - 1][o[0].size() - 1] == 0;
        /*
        c = 0;
        f_perebor(o, 0, 0);
        return c;
        */

        vector<vector<int>> dp(o.size(), vector<int>(o[0].size(), 0));
        dp[dp.size() - 1][dp[0].size() - 1] = 1;
        fdp(dp, o, 0, 0);

        return dp[0][0];
    }
};
int main()
{
    Solution s;
    vector<vector<int>> v1 = { {0,0,0},{0,1,0},{0,0,0} };
    vector<vector<int>> v2 = { {0,0,0,0},{0,0,1,0},{0,0,0,0} };
    vector<vector<int>> v3 = { {0,0}, {0,0} };
    vector<vector<int>> v4 = { {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0} };
    vector<vector<int>> v5 = { {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0} };
    vector<vector<int>> v6 = { {0} };
    vector<vector<int>> v7 = { {1,0} };
    vector<vector<int>> v8 = { {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 1}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} };

    cout << s.uniquePathsWithObstacles(v1) << endl; 
    cout << s.uniquePathsWithObstacles(v2) << endl;
    cout << s.uniquePathsWithObstacles(v3) << endl;
    cout << s.uniquePathsWithObstacles(v4) << endl;
    cout << s.uniquePathsWithObstacles(v5) << endl; 
    cout << s.uniquePathsWithObstacles(v6) << endl;
    cout << s.uniquePathsWithObstacles(v7) << endl;
    cout << s.uniquePathsWithObstacles(v8) << endl;
    return 0;
}