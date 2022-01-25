#include <iostream>
#include <vector>

using namespace std;

class Solution {

    int f(vector<int>& v, int n)
    {
        if (n == 2) return 1;
        if (v[n] != -1) return v[n];

        int r = 0;
        for (int i = 1; i < n; ++i)
        {
            v[n - i] = f(v, n - i);
            r = max(r, max(n, i * v[n - i]));
        }
        return r;
    }

public:
    int integerBreak(int n) {
        if (n == 3) return 2;
        vector<int> v(n + 1, -1);
        return f(v, n);
    }
};

int main()
{
    Solution s;
    for (int i = 2; i < 20; ++i)
    {
        cout << s.integerBreak(i) << endl;
    }
}