#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


class Solution {
    int m_len = INT_MAX;

    void visit1(vector<vector<int>>& g, int i, int j, int m, int p, int q)
    {
        if (!is_valid_index(g, i, j))
        {
            return;
        }

        g[i][j] = 1;
        if (i == g.size() - 1 && j == g[0].size() - 1)
        {
            m_len = min(m_len, m);
            return;
        }

        visit(g, i + 1, j + 1, m + 1);
        visit(g, i + 1, j - 1, m + 1);
        visit(g, i - 1, j + 1, m + 1);
        visit(g, i + 1, j, m + 1);
        visit(g, i - 1, j, m + 1);
        visit(g, i, j + 1, m + 1);
        visit(g, i, j - 1, m + 1);
        visit(g, i - 1, j - 1, m + 1);


        /*

         is_valid_index(g, i + 1, j);
            visit1(g, i+1, j, m+1);

        is_valid_index(g, i - 1, j);
            visit1(g, i-1, j, m+1);

        is_valid_index(g, i + 1, j);
            visit1(g, i, j+1, m+1);

        is_valid_index(g, i + 1, j);
            visit1(g, i, j-1, m+1);

        is_valid_index(g, i + 1, j);
            visit1(g, i+1, j+1, m+1);

        is_valid_index(g, i + 1, j);
            visit1(g, i-1, j-1, m+1);

        is_valid_index(g, i + 1, j);
            visit1(g, i+1, j-1, m+1);

        is_valid_index(g, i + 1, j);
            visit1(g, i-1, j+1, m+1);*/
    }


    inline bool is_valid_index(vector<vector<int>>& g, int i, int j) const
    {
        if (i < 0 || i >= g.size() || j < 0 || j >= g[0].size() || g[i][j] == 1)
       // if (i < 0 || i >= g.size() || j < 0 || j >= g[0].size())
        {
            return false;
        }
        return true;
     //   return g[i][j] == 0;
    }

    
    void visitBFS1(vector<vector<int>>& g, queue<pair<pair<int, int>, int>>& q)
    {
        if (q.empty())
            return;
        //   while (!q.empty())
        //   {

        while (!q.empty())
        {
            pair<pair<int, int>, int > p = q.front();
            q.pop();

            int m = p.first.first;
            int i = p.first.second;
            int j = p.second;

            if (i == g.size() - 1 && j == g[0].size() - 1)
            {
                m_len = min(m_len, m);
                return;
            }

            for (int p = -1; p < 2; ++p) {
                for (int k = -1; k < 2; ++k) {
                    if (p == 0 && k == 0) continue;
                    int x = i + p;
                    int y = j + k;

                    if (is_valid_index(g, x, y))
                    {
                        g[x][y] = 1;
                        q.push({ {m + 1, x}, y });
                    }
                }
            }

        }
        

        visitBFS1(g, q);
        // }
    }
    
    int visitBFS(vector<vector<int>>& g, queue<pair<pair<int, int>, int>>& q)
    {
        if (q.empty())
            return -1;
        //   while (!q.empty())
        //   {


        pair<pair<int, int>, int > p = q.front();
        q.pop();

        int m = p.first.first;
        int i = p.first.second;
        int j = p.second;

        if (i == g.size() - 1 && j == g[0].size() - 1)
        {
            //   cout << m << endl;
              // m_len = min(m_len, m);
            return m;
        }

        if (is_valid_index(g, i - 1, j - 1))
        {
            g[i - 1][j - 1] = 1;
            q.push({ {m + 1, i - 1}, j - 1 });
        }

        if (is_valid_index(g, i - 1, j))
        {
            g[i - 1][j] = 1;
            q.push({ {m + 1, i - 1}, j });
        }

        if (is_valid_index(g, i - 1, j + 1))
        {
            g[i - 1][j + 1] = 1;
            q.push({ {m + 1, i - 1}, j + 1 });
        }

        if (is_valid_index(g, i, j - 1))
        {
            g[i][j - 1] = 1;
            q.push({ {m + 1, i}, j - 1 });
        }

        if (is_valid_index(g, i, j + 1))
        {
            g[i][j + 1] = 1;
            q.push({ {m + 1, i}, j + 1 });
        }
        if (is_valid_index(g, i + 1, j - 1))
        {
            g[i + 1][j - 1] = 1;
            q.push({ {m + 1, i + 1}, j - 1 });
        }
        if (is_valid_index(g, i + 1, j))
        {
            g[i + 1][j] = 1;
            q.push({ {m + 1, i + 1}, j });
        }
        if (is_valid_index(g, i + 1, j + 1))
        {
            g[i + 1][j + 1] = 1;
            q.push({ {m + 1, i + 1}, j + 1 });
        }

        return visitBFS(g, q);
    }

    int visitBFS4(vector<vector<int>>& g, queue<pair<int, int>>& q, int& m)
    {
        if (q.empty())
            return -1;
        //   while (!q.empty())
        //   {


        pair<int, int> p = q.front();
        q.pop();

      //  int m = p.first.first;
        int i = p.first;
        int j = p.second;

        if (i == g.size() - 1 && j == g[0].size() - 1)
        {
            //   cout << m << endl;
              // m_len = min(m_len, m);
            return m;
        }

        if (is_valid_index(g, i - 1, j - 1))
        {
            ++m;
            g[i - 1][j - 1] = 1;
            q.push({ i - 1, j - 1 });
        }

        if (is_valid_index(g, i - 1, j))
        {
            ++m;
            g[i - 1][j] = 1;
            q.push({ i - 1, j });
        }

        if (is_valid_index(g, i - 1, j + 1))
        {
            ++m;
            g[i - 1][j + 1] = 1;
            q.push({ i - 1, j + 1 });
        }

        if (is_valid_index(g, i, j - 1))
        {
            ++m;
            g[i][j - 1] = 1;
            q.push({ i, j - 1 });
        }

        if (is_valid_index(g, i, j + 1))
        {
            ++m;
            g[i][j + 1] = 1;
            q.push({ i, j + 1 });
        }
        if (is_valid_index(g, i + 1, j - 1))
        {
            ++m;
            g[i + 1][j - 1] = 1;
            q.push({ i + 1, j - 1 });
        }
        if (is_valid_index(g, i + 1, j))
        {
            ++m;
            g[i + 1][j] = 1;
            q.push({ i + 1, j });
        }
        if (is_valid_index(g, i + 1, j + 1))
        {
            ++m;
            g[i + 1][j + 1] = 1;
            q.push({ i + 1, j + 1 });
        }

        return visitBFS4(g, q, m);
    }

    void visit(vector<vector<int>>& g, int i, int j, int m)
    {
        //cout << i << ' ' << j << endl;

        if (!is_valid_index(g, i, j))
        {
            return;
        }

        //g[i][j] = 1;

       // if (!is_valid_index(g, i + 1, j + 1) && !is_valid_index(g, i + 1, j - 1)&& !is_valid_index(g, i + 1, j)&& !is_valid_index(g, i - 1, j)&& !is_valid_index(g, i, j + 1)&& !is_valid_index(g, i, j - 1)&& !is_valid_index(g, i - 1, j - 1)&& !is_valid_index(g, i - 1, j + 1))
      //      g[i][j] = 1;
        if (i == g.size() - 1 && j == g[0].size() - 1)
        {
            m_len = min(m_len, m);
            return;
        }

        visit(g, i + 1, j, m + 1);
        visit(g, i + 1, j + 1, m + 1);
        visit(g, i + 1, j - 1, m + 1);
        visit(g, i - 1, j, m + 1);
        visit(g, i - 1, j + 1, m + 1);
        visit(g, i, j + 1, m + 1);
        visit(g, i, j - 1, m + 1);
        visit(g, i - 1, j - 1, m + 1);

        /*
        if (is_valid_index(g, i + 1, j + 1))
            visit(g, i + 1, j + 1, m + 1);

        if (is_valid_index(g, i + 1, j - 1))
            visit(g, i + 1, j - 1, m + 1);

        if (is_valid_index(g, i + 1, j))
            visit(g, i + 1, j, m + 1);

        if (is_valid_index(g, i - 1, j))
            visit(g, i - 1, j, m + 1);

        if (is_valid_index(g, i, j + 1))
            visit(g, i, j + 1, m + 1);

        if (is_valid_index(g, i, j - 1))
            visit(g, i, j - 1, m + 1);

        if (is_valid_index(g, i - 1, j - 1))
            visit(g, i - 1, j - 1, m + 1);

        if (is_valid_index(g, i - 1, j + 1))
            visit(g, i - 1, j + 1, m + 1);
        */
        // g[i][j] = 1;
         /*
         visit(g, i + 1, j + 1, m + 1);
         visit(g, i + 1, j - 1, m + 1);
         visit(g, i - 1, j + 1, m + 1);
         visit(g, i + 1, j, m + 1);
         visit(g, i - 1, j, m + 1);
         visit(g, i, j + 1, m + 1);
         visit(g, i, j - 1, m + 1);
         visit(g, i - 1, j - 1, m + 1);
         */

         /*
         for (int i = p; i < grid.size(); ++i)
         {
             for (int j = q; j < grid.size(); ++j)
             {
                 if (g{i}{j} == 1)
                 {
                     return INT_MAX;
                 }
                 return visit(g, i+1, j);
             }
         }
         */
    }

    void visit2(vector<vector<int>>& g, int i, int j, int m)
    {
        if (i < 0 || i >= g.size() || j < 0 || j >= g[0].size() || g[i][j] == 1)
        {
            return;
        }

        g[i][j] = 1;
        if (i == g.size() - 1 && j == g[0].size() - 1)
        {
            m_len = min(m_len, m);
            return;
        }

        visit2(g, i + 1, j + 1, m + 1);

        visit2(g, i, j + 1, m + 1);

        visit2(g, i - 1, j, m + 1);
        visit2(g, i + 1, j - 1, m + 1);
        visit2(g, i - 1, j + 1, m + 1);
        visit2(g, i + 1, j, m + 1);

        visit2(g, i, j - 1, m + 1);
        visit2(g, i - 1, j - 1, m + 1);
        
    }

public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        if (grid[0][0] == 1) return -1;
 
//        queue<pair<int, int>> q;
        queue<pair<pair<int, int>, int>> q;

        q.push(make_pair<pair<int, int>, int>(make_pair<int, int>(1, 0), 0));
        //   visit(grid, 0, 0, 1);
//        q.push({ 0,0 });
        grid[0][0] = 1;

        int m = 1;
        //visitBFS(grid, q, m);
        return visitBFS(grid, q);
        
     //   visit2(grid, 0, 0, 1);
    //    return m_len == INT_MAX ? -1 : m_len;
    }
};

int main() {
    vector<vector<int>> v1{ {0, 1}, { 1, 0 } };
    vector<vector<int>> v2{ {0,0,0}, {1,1,0}, {1,1,0} };
    
    vector<vector<int>> v3{ {{0, 1, 0, 0, 0, 0},{0, 1, 0, 1, 1, 0},{0, 1, 1, 0, 1, 0},{0, 0, 0, 0, 1, 0},{1, 1, 1, 1, 1, 0},{1, 1, 1, 1, 1, 0}} };
    vector<vector<int>> v4{ {{0, 0, 1, 1, 0, 0},{0, 0, 0, 0, 1, 1},{1, 0, 1, 1, 0, 0},{0, 0, 1, 1, 0, 0},{0, 0, 0, 0, 0, 0},{0, 0, 1, 0, 0, 0}} };

    vector<vector<int>> v5{ {0, 0, 0},{0, 1, 0},{0, 0, 0} };

    Solution s;

    cout << s.shortestPathBinaryMatrix(v3) << endl;

    return 0;
}