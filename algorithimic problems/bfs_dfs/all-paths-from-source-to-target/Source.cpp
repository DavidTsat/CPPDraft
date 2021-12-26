#include <iostream>
#include <vector>

using namespace std;

class Solution {
    vector<vector<int>> paths;

    void startDFS(vector<vector<int>>& g, vector<int> p, int v)
    {
        p.push_back(v);
        if (v == g.size() - 1)
        {
            paths.push_back(p);
        }

        for (int i : g[v])
        {
            startDFS(g, p, i);
        }
    }

public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        startDFS(graph, {}, 0);
        return paths;
    }
};
int main()
{
    vector<vector<int>> v({ {{1,2},{3},{3},{}} });

    Solution s;
    s.allPathsSourceTarget(v);

    return 0;
}