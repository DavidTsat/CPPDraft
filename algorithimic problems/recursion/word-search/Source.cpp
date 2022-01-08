#include <iostream>
#include <vector>

using namespace std;

class Solution {
    bool b = false;

    void f(const vector<vector<char>>& v, string w, int i, int j, int s_i)
    {
        if (s_i >= w.size())
        {
            b |= true;
            return;
        }
        if (i >= v.size() || i < 0 || j >= v[i].size() || j < 0)
        {
            return;
        }

        if (v[i][j] != w[s_i])
        {
            if (j == v[i].size())
            {
                f(v, w, i + 1, 0, s_i);
            }
            else
            {
                f(v, w, i, j + 1, s_i);
            }
        }
        else
        {
            f(v, w, i, j - 1, s_i + 1);
            f(v, w, i, j + 1, s_i + 1);
            f(v, w, i - 1, j, s_i + 1);
            f(v, w, i + 1, j, s_i + 1);
        }

    }

public:
    bool exist(vector<vector<char>>& board, string word) {

        f(board, word, 0, 0, 0);
        return b;
    }
};

int main()
{
    Solution s;
    vector<vector<char>> v{ { 'A','B','C','E' }, { 'S','F','C','S' }, { 'A','D','E','E' } };

    cout << s.exist(v, "SEE") << endl;

    return 0;
}