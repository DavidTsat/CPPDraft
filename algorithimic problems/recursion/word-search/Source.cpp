#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
    bool b = false;

    inline bool valid_index(const vector<vector<char>>& v, int i, int j)
    {
        return i < v.size() && i >= 0 && j < v[i].size() && j >= 0 && v[i][j] != '-';
    }

    void f(vector<vector<char>>& v, const string& w, int i, int j, int s_i)
    {

        if (s_i == w.size())
        {
            b = true;
            return;
        }

        if (!valid_index(v, i, j))
        {
            return;
        }


        if (v[i][j] == w[s_i])
        {
            char c = v[i][j];
            v[i][j] = '-';

            f(v, w, i, j - 1, s_i + 1);
            f(v, w, i, j + 1, s_i + 1);
            f(v, w, i - 1, j, s_i + 1);
            f(v, w, i + 1, j, s_i + 1);

            v[i][j] = c;
        }

    }
public:
    bool exist(vector<vector<char>>& board, string word) {

        for (int i = 0; i < board.size(); ++i)
        {
            for (int j = 0; j < board[i].size(); ++j)
            {
                if (board[i][j] == word[0])
                {
                    f(board, word, i, j, 0);

                    if (b)
                        return b;
                }
            }
        }

        return b;
    }
};


void g(const vector<vector<char>>& v, int i, int j)
{
    if (i >= v.size() || j >= v[i].size())
    {
        return;
    }

    cout << v[i][j] << ' ';
    if (j == v[i].size()-1)
    {
        cout << endl;
        g(v, i + 1, 0);
    }
    else
    {
        g(v, i, j + 1);
    }
    
}

int main()
{
    Solution s;
  //  vector<vector<char>> v{ { 'A','B','C','E' }, { 'S','F','C','S' }, { 'A','D','E','E' } };
 //    vector<vector<char>> v{ { 'A','B','C','E' }, { 'S','F','E','S' }, { 'A','D','E','E' } };
//     vector<vector<char>> v{ {'A'} };
   
   vector<vector<char>> v{ {'A','A','A','A','A','A'}, {'A','A','A','A','A','A'}, {'A','A','A','A','A','A'}, {'A','A','A','A','A','A'}, {'A','A','A','A','A','A'}, {'A','A','A','A','A','A'} };
  //  'AAAAAAAAAAAAAAB'
    //'ABCESEEEFS'
    //g(v, 0, 0);

//    cout << s.exist(v, 'AAAAAAAAAAAAAAB') << endl;


//    vector<vector<char>> v{ { 'C', 'A', 'A'}, {'A', 'A', 'A'}, {'B', 'C', 'D'} }; // AAB
    
    cout << s.exist(v, "AAAAAAAAAAAAAAB") << endl;

    return 0;
}