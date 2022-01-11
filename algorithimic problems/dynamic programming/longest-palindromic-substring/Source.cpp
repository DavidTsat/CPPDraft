#include <iostream>
#include <string>

using namespace std;

class Solution {
    string r;

    bool check_palindrome(string::const_iterator l, string::const_iterator r)
    {
        while (l < r && *l == *r)
        {
            ++l;
            --r;
        }

        return l >= r;
    }

    void longest_palindrome_before(const string& s, string::const_iterator itr)
    {
        auto l = s.cbegin();

        while (true)
        {

            while (*l != *itr)
            {
                ++l;
            }
            if (l != itr)
            {
                bool b = check_palindrome(l, itr);
                if (b)
                {
                    string p(l, next(itr));
                    r = p.size() > r.size() ? p : r;
                    break;
                }
                else
                {
                    ++l;
                }
            }
            else
            {
                break;
            }
        }

    }

public:
    string longestPalindrome(string s) {

        for (auto it = s.cbegin(); it != s.cend(); ++it)
        {
            longest_palindrome_before(s, it);
            // r = p.size() > r.size() ? p : r;
        }

        return !r.empty() ? r : s.substr(0, 1);

    }
};

int main()
{
    Solution s;

    cout << s.longestPalindrome("aacabdkacaa");

    return 0;
}