#include <iostream>
#include <vector>

using namespace std;

class Solution {
    vector<int> f(int r)
    {
        if (r == 1) return { 1 };
        if (r == 2) return { 1,1 };

        vector<int> v_prev = f(r - 1);
        vector<int> v(r, 0);
        v[0] = 1;
        v[r - 1] = 1;

        for (int i = 1; i < r - 1; ++i)
        {
            v[i] = v_prev[i] + v_prev[i - 1];
        }
        return v;
    }
public:
    vector<int> getRow(int rowIndex) {
        return f(rowIndex + 1);
    }
};
int main()
{
    Solution s;
    vector<int> v = s.getRow(7);

    for (int c : v)
    {
        cout << c << ' ';
    }
    cout << endl;
    return 0;
}