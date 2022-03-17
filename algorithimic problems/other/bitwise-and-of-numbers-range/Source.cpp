#include <iostream>

using namespace std;

#include <stdio.h>    
#include <math.h> 

class Solution {
    int f(int l, int r)
    {
        int i = 0;
        int c_i = 2;
        int res = l;

        while (pow(c_i, ++i) <= l);

        if (pow(c_i, i) < r)
        {
            return 0;
        }

        for (long long c = l + 1; c <= r; ++c)
        {
            res &= c;
        }

        return res;
    }

public:
    int rangeBitwiseAnd(int left, int right) {
        if (left == right) return left;
        return f(left, right);
    }
};

int main()
{
    Solution s;
    //2147483646
    //2147483647
    cout << s.rangeBitwiseAnd(2147483646, 2147483647) << endl; //(2,3) - 2; (1,2) -1; (6,7) - 6 (12, 14) - 12
    return 0;
}