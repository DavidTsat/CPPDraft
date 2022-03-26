#include <iostream>
#include <vector>

using namespace std;


class Solution {
    vector<vector<int>> r;

    void f(int i, int n, int k, vector<int>& v)
    {
        if (v.size() == k)
        {
            r.push_back(v);
            return;
        }
       
        for (int j = i; j <= n; ++j)
        {
            v.push_back(j);
            f(j + 1, n, k, v);
            v.pop_back();
        }
    }

public:
    vector<vector<int>> combine(int n, int k) {
        vector<int> v;
        f(1, n, k, v);
        return r;
    }
};

int main()
{
    Solution s;

    vector<vector<int>> v = s.combine(4, 5);

    for (auto vv : v)
    {
        for (int c : vv)
        {
            cout << c << ' ';
        }
        cout << endl;
    }
    return 0;
}