#include <iostream>
#include <vector>

using namespace std;

class Solution_trib {
    vector<long long> v;
public:
    long long tribonacci(int n) {

        if (n == 0)
        {
            //  v[n] = 0;
            return 0;
        }
        if (n == 1 || n == 2)
        {
            //   v[n] = 1;
            return 1;
        }

        if (v.empty())
        {
            v = vector<long long>(n, -1);
        }

        long long f1 = 0, f2 = 0, f3 = 0;

        if (v[n - 1] != -1)
        {
            f1 = v[n - 1];
        }
        else {
            f1 = tribonacci(n - 1);
            v[n - 1] = f1;
        }

        if (v[n - 2] != -1)
        {
            f2 = v[n - 2];
        }
        else {
            f2 = tribonacci(n - 2);
            v[n - 2] = f2;
        }

        if (v[n - 3] != -1)
        {
            f3 = v[n - 3];
        }
        else {
            f3 = tribonacci(n - 3);
            v[n - 3] = f3;
        }

        return f1 + f2 + f3;
    }
};

class Solution_fib {
    vector<long long> v;
public:
    long long fib(int n) {


        if (n == 0)
        {
            //  v[n] = 0;
            return 0;
        }
        if (n == 1)
        {
            //   v[n] = 1;
            return 1;
        }

        if (v.empty())
        {
            v = vector<long long>(n, -1);
        }

        long long f1 = 0, f2 = 0;


        if (v[n - 1] != -1)
        {
            f1 = v[n - 1];
        }
        else {
            f1 = fib(n - 1);
            v[n - 1] = f1;
        }

        if (v[n - 2] != -1)
        {
            f2 = v[n - 2];
        }
        else {
            f2 = fib(n - 2);
            v[n - 2] = f2;
        }

        return f1 + f2;
    }
};

int main() {

    Solution_fib s;

    cout << s.fib(50);
    return 0;
}