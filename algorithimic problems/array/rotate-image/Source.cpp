#include <iostream>
#include <vector>

using namespace std;


class Solution {

public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size() - 1;
        for (int i = 0; i <= n; ++i)
        {
            int j = n - i;
            for (int k = i; k <= n; ++k)
            {
                swap(matrix[k][i], matrix[j][k]);
            }
        }

        for (int j = 0; j <= n - 2; ++j)
        {
            for (int i = j+1; i + j < n; ++i)
            {
                swap(matrix[j][i], matrix[i][n-j]);
            }
        }
    }
};

int main()
{
    Solution s;
    vector<vector<int>> v1({ {1,2,3},{4,5,6}, {7,8,9} });
    vector<vector<int>> v2({ {5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16} });
    vector<vector<int>> v3({ {1,2,3,4,5}, {6,7,8,9,10}, {11,12,13,14,15}, {16,17,18,19,20}, {21,22,23,24,25} });
    
    vector<vector<int>> v_test = v3;

    for (vector<int>& v : v_test)
    {
        for (int c : v)
        {
            cout << c << ' ';
        }
        cout << endl;
    }
    cout << endl;

    s.rotate(v_test);

    for (vector<int>& v : v_test)
    {
        for (int c : v)
        {
            cout << c << ' ';
        }
        cout << endl;
    }
    return 0;
}