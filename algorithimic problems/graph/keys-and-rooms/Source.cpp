#include <iostream>
#include <vector>

using namespace std;

class Solution {

    void create_g_matrix(const vector<vector<int>>& r, vector<vector<int>>& g)
    {
        for (int i = 0; i < r.size(); ++i)
        {
            for (int j : r[i])
            {
                g[i][j] = 1;
            }
        }
    }

    void dfs(int v, vector<vector<int>>& g)
    {
        for (int i = 0; i < g[v].size(); ++i)
        {
            if (g[v][i] == 1)
            {
                g[v][i] = 0;
                dfs(i, g);
            }
        }
    }

public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        vector<vector<int>> g(rooms.size(), vector<int>(rooms.size(), 0));
        create_g_matrix(rooms, g);
        dfs(0, g);

        for (int i = 0; i < g.size(); ++i)
        {
            for (int j = 0; j < g.size(); ++j)
            {
                if (g[i][j] == 1) return false;
            }
        }
        return true;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> g1 = { {1},{2},{3},{} };
    vector<vector<int>> g2 = { {1, 3},{3, 0, 1},{2},{0} };

    cout << s.canVisitAllRooms(g1) << endl;
    return 0;
}