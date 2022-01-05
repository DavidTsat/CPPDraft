#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
    vector<string> r;

    void f(string s, int p, int q, int n)
    {
        if (s.size() == 2 * n)
        {
            r.push_back(s);
            return;
        }

        if (p < n)
        {
            f(s + '(', p + 1, q, n);
        }
        if (q < n && q < p)
        {
            f(s + ')', p, q + 1, n);
        }
    }

public:
    vector<string> generateParenthesis(int n) {
        f("", 0, 0, n);
        return r;
    }
};

int main()
{
    Solution s;
    vector<string> v = s.generateParenthesis(3);

    for (auto vv : v)
    {
        cout << vv << ',';
    }

	return 0;
}