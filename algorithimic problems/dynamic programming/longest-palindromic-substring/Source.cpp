#include <iostream>
#include <string>

using namespace std;

class Solution {
    string r;

    string longest_palindrome_mid(const string& s, string::const_iterator it)
    {
        char cc = *it;
        auto r_it = make_reverse_iterator(it);
        //char c = *r_it;
        auto r_end = make_reverse_iterator(s.cend());
        ++it;
      //  ++r_it;
        while (it != s.cend() && r_it != s.rend() && *it == *r_it)
        {
            ++it;
            ++r_it;
        }
        string s2(r_it.base(), it);
        return s2;
    }

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
            //auto l = itl;

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