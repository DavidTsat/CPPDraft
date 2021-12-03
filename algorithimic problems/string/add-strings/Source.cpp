#include <string>
#include <iostream>

using namespace std;

class Solution {
    string sum_str(string& s1, string& s2, int i)
    {
        string s;

        string z(i, '0');
        s2 += z;
        if (s1.size() < s2.size())
        {
            string z(s2.size() - s1.size(), '0');
            s1 = z + s1;
        }
        else if (s2.size() < s1.size())
        {
            string z(s1.size() - s2.size(), '0');
            s2 = z + s2;
        }

        int  h = 0;
        for (int i = s1.size() - 1; i >= 0; --i)
        {
            int c1 = s1[i] - '0';
            int c2 = s2[i] - '0';

            int c = c1 + c2 + h;
            int cc = c % 10;
            s = char('0' + cc) + s;

            if (c >= 10) h = c / 10;
            else if (h) --h;
        }

        if (h)
            s = char('0' + h) + s;
        //    s1 = s;
        return s;
    }
public:
    string addStrings(string num1, string num2) {
        return sum_str(num1, num2, 0);
    }
};

int main() {
    Solution s;

    cout << s.addStrings("134", "533");
    return 0;
}