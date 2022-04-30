#include <iostream>

using namespace std;

class Solution {
public:
    int minFlips(int a, int b, int c) {
        int m = a | b;
        int r = 0;

        for (int i = 0; i < sizeof(c) * 8 - 1; ++i)
        {
            int s = 1 << i;
            if ((m & s) != (c & s))
            {
                if ((a & s) && (b & s))
                    r += 2;
                else
                    ++r;
            }
        }
        return r;
    }
};

int main()
{
    Solution s;

    cout << s.minFlips(2, 6, 5) << endl;
    return 0;
}