#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Solution {

    double pow_(vector<double>& v, double a, int k)
    {
        if (k == 0)
        {
            return 1;
        }
        if (k == 1)
        {
            return a;
        }
        if (v[abs(k)] != -1) return v[k];

        v[abs(k/2)] = pow_(v, a, abs(k / 2));
        double r = v[abs(k/2)];

        if ((int)k % 2 == 0)
        {
            r *= r;
        }
        else
        {
            r = a * r * r;
        }

        if (k > 0)
        {
            return r;
        }
        else
        {
            return (double)(1 / r);
        }
    }


    double pow_(double a, int k)
    {
        if (k == 0)
        {
            return 1;
        }
        if (k == 1)
        {
            return a;
        }

        double r = pow_(a, abs(k / 2));

        if ((int)k % 2 == 0)
        {
            r *= r;
        }
        else
        {
            r = a * r * r;
        }

        if (k > 0)
        {
            return r;
        }
        else
        {
            return (double)(1 / r);
        }
    }
public:
    double myPow(double x, int n) {
        vector<double> v(abs(n)+1, -1);
        return pow_(v, x, n);
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