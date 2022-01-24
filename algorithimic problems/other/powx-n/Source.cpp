#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Solution {
    double pow_(double a, double k)
    {
        if (k == 0)  return 1;
        if (k == 1)  return a;

        double r = pow_(a, abs(k / 2));

        if ((int)k % 2 == 0)  r *= r;
        else r = a * r * r;

        return k > 0 ? r : 1 / r;
    }
public:
    double myPow(double x, double n) {
        return pow_(x, n);
    }
};

int main()
{
    Solution s;
    cout << double(1 / (34.00515 * 34.00515 * 34.00515)) << endl;
    cout << double(1 / 39321.862905431590) << endl;
    cout << double(s.myPow(34.00515, -3)) << endl;
    cout <<std::pow(34.00515, -3) << endl;
    return 0;
}