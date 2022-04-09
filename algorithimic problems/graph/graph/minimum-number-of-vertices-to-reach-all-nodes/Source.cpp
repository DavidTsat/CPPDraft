#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
    vector<int> v;

    void f(int n, vector<vector<int>>& edges, int ii)
    {
        for (int i = ii; i < edges.size() - 1; ++i)
        {
            for (int j = i + 1; j < edges.size(); ++j)
            {
                if (edges[i][0] == edges[j][0])
                {
                    edges[i].push_back(edges[j][1]);
                    f(n, edges, j + 1);
                }
            }
            if (i > 0 && edges[i][0] == edges[i - 1][0])
            {
                edges.erase(edges.begin() + i);
                continue;
            }
        }
    }

    void bfs(vector<vector<int>>& v, vector<int>& vis, int c, queue<int>& q)
    {
        if (q.empty())
        {
            return;
        }

        int i = q.front();
        cout << i << ' ';
        q.pop();

        vis.push_back(i);

        for (int j = 0; j < v.size(); ++j)
        {
            if (v[j][0] == i)
            {
                if (find(vis.cbegin(), vis.cend(), v[j][1]) == vis.cend())
                {
                    q.push(v[j][1]);
                    v[j][0] = -1; // todo
                }
            }
        }
        bfs(v, vis, c, q);
    }

public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {

      //  sort(edges.begin(), edges.end(), [](const vector<int>& v1, const vector<int>& v2) {return v1 <= v2; });
        vector<int> visited;

        int c = n;
        for (int i = 0; i < n; ++i)
        {
            bool b = false;
            vector<int> vv;
            for (int j = 0; j < edges.size(); ++j)
            {
                if (edges[j][1] == i)
                {
                    b = true;
                 //   break;
                }
             //   if (edges[j][0] == i)
             //       vv.push_back(edges[j][1]);
            }
            if (!b)
            {
                v.push_back(i);
               /*
                for (int cv : vv)
                {
                    visited.push_back(cv);
                }
                */
            }
            /*
            else
            {
                if (find(visited.cbegin(), visited.cend(), i) == visited.cend())
                    v.push_back(i);
                cout << "i: " << i << endl;
            }
            */
        }
        /*
        f(n, edges, 0);

        for (int i = 0; i < edges.size(); ++i)
        {
            v.push_back(edges[i][0]);
        }
        */

        for (int i : v)
        {
            cout << "i: " << i << endl;
            queue<int> q;
            q.push(i);
            vector<int> vv;
            bfs(edges, vv, i, q);
            cout << endl;
        }
        for (vector<int>& vi : edges)
        {
            if (vi[0] != -1)
            {
                v.push_back(vi[0]);
            }
        }
        return v;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> v1{ {0, 1}, {0, 2}, {2, 5}, {3, 4}, {4, 2} };
    vector<vector<int>> v2{ {0, 1}, {0, 2}, {2, 5}, {3, 4}, {4, 2}, {6,7}, {7,8}, {8,6} };
    vector<int> v = s.findSmallestSetOfVertices(6, v2);

    for (int i : v)
    {
        cout << i << ' ';
    }
    cout << endl;
    return 0;
}