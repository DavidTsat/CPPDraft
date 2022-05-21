#include <iostream>
using namespace std;


class Solution {
    bool isUglyIterative(int n) {
        if (n <= 0) return false;

        while (true)
        {
            if (n == 1 || n == 2 || n == 3 || n == 5)
                return true;
            if (!(n & 1))
            {
                n >>= 1;
            }
            else if (n % 3 == 0)
            {
                n /= 3;
            }
            else if (n % 5 == 0)
            {
                n /= 5;
            }
            else
            {
                break;
            }
        }

        return false;
    }
    bool isUglyRecursive(int n) {
        if (n <= 0) return false;

        if (n == 1 || n == 2 || n == 3 || n == 5)
            return true;

        if (!(n & 1))
        {
            n >>= 1;
        }
        else if (n % 3 == 0)
        {
            n /= 3;
        }
        else if (n % 5 == 0)
        {
            n /= 5;
        }
        else
            return false;

        return isUglyRecursive(n);
    }
public:
    bool isUgly(int n) {
        return isUglyRecursive(n);
    }
};

int main()
{
    Solution s;
    
    cout << s.isUgly(8) << endl;

    return 0;
}