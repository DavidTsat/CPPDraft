#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    bool isPalindrome(long long x) {
        if (x < 0) return false;
        vector<int> v;
        //int prev_m = -1;
        long long c = 10;

        while (true)
        {
            long long m = x % c;

            long long cur = m / (c / 10);
            v.push_back(cur);
            if (x / c == 0)
                break;
            c *= 10;

            // prev_m = m;
        }
        /*
        for (int i : v)
        {
            cout << i << ' ';
        }
        cout << endl;
        */
        c = pow(10, v.size() - 1);
        long long r = 0;
        for (int i : v)
        {
            r += c * i;
            c /= 10;
            //   cout << i << " : " << x/c <<endl;
           //    int xc = x/c;
               //if (i != x/c)
             //      return false;
            //   c /= 10;
        }

        //  cout << "r = " << r << endl;
        return x == r;
    }
};

int main()
{
    Solution s;
    cout << s.isPalindrome(1234567899);
    return 0;
}