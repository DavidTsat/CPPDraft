#include <iostream>
#include <vector>

using namespace std;

class Solution {
    void find_zeros(vector<vector<char>>& b, vector<pair<int, int>>& v, int i, int j, bool& z)
    {
        if (i <= 0 || i >= b.size() - 1 || j <= 0 || j >= b[0].size() - 1)
        {
            if (i < 0 || i > b.size() - 1 || j < 0 || j > b[0].size() - 1)
            {
                return;
            }
            if (b[i][j] == 'O')
            {
                z |= true;
            }
            return;
        }

        if (b[i][j] == 'X')
        {
            return;
        }

        v.push_back({ i, j });
        b[i][j] = 'X';

        find_zeros(b, v, i - 1, j, z);
        find_zeros(b, v, i + 1, j, z);
        find_zeros(b, v, i, j - 1, z);
        find_zeros(b, v, i, j + 1, z);
    }

public:
    void solve(vector<vector<char>>& board) {

        for (int i = 0; i < board.size(); ++i)
        {
            for (int j = 0; j < board[0].size(); ++j)
            {
                if (board[i][j] == 'O' && i != 0 && i != board.size() - 1 && j != 0 && j != board[0].size() - 1)
                {
                    bool z = false;
                    vector<pair<int, int>> v;
                    find_zeros(board, v, i, j, z);
                    if (z == true)
                    {
                        for (const pair<int, int>& p : v)
                        {
                            board[p.first][p.second] = 'O';
                        }
                    }
                }
            }
        }
    }
};

int main()
{
    Solution s;
    vector<vector<char>> v({ {'X','X','X','X'}, {'X','O','O','X'}, {'X','X','O','X'}, {'X','O','X','X'} });
    
    vector<vector<char>> v2({ {'O', 'O', 'O'}, {'O', 'O', 'O'}, {'O', 'O', 'O'} });
    s.solve(v);

    for (auto& vv : v)
    {
        for (char c : vv)
        {
            cout << c << ' ';
        }
        cout << endl;
    }

    return 0;
}