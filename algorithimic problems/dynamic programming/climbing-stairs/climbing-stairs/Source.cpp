#include <vector>
using namespace std;

class Solution {
    int f(int n, vector<int>& v)
    {

        int f1, f2;
        if (n == 1) return 1;
        if (n == 2) return 2;


        if (v[n - 1])
        {
            f1 = v[n - 1];
        }
        else {
            f1 = f(n - 1, v);
            v[n - 1] = f1;
        }

        if (v[n - 2])
        {
            f2 = v[n - 2];
        }
        else {
            f2 = f(n - 2, v);
            v[n - 2] = f2;
        }

        return f1 + f2;
    }
public:
    int climbStairs(int n) {
        vector<int> v(n + 1, 0);
        return f(n, v);
    }
};