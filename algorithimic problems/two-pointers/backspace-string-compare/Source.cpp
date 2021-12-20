#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
    void clear_backspaces(string& s)
    {
        for (auto itb = s.begin(); itb != s.end(); ++itb)
        {
            if (*itb == '#')
            {
                auto itbb = itb;
                while (itbb != s.begin() && (*itbb == '#' || *itbb == '_'))
                {
                    --itbb;
                }
                *itbb = '_';
                *itb = '_';
            }
        }
        clear_underscores(s);
    }

    void clear_underscores(string& s)
    {
        for (auto itb = s.begin(); itb != s.end(); ++itb)
        {
            if (*itb == '_')
            {
                auto itbb = itb;
                ++itbb;
                while (itbb != s.end() && *itbb == '_')
                {
                    ++itbb;
                }
                if (itbb != s.end())
                {
                    iter_swap(itbb, itb);
                   // ++itb;
                   // itb = itbb;
                }
            }
        }
    }
public:
    bool backspaceCompare(string s, string c) {
        clear_backspaces(s);
        clear_backspaces(c);

        auto itb = s.cbegin();
        auto itc = c.cbegin();

       // auto itb = find(s.cbegin(), s.cend(), '_');
       // auto itc = find(c.cbegin(), c.cend(), '_');
        
        while(itb != s.end() && *itb != '_' && itc != c.end() && *itc != '_')
        {
            if (*itb != *itc)
                return false;
            ++itb;
            ++itc;
        }

        if ((itb != s.cend() && *itb != '_') || (itc != c.cend() && *itc != '_'))
            return false;
        
        return true;
    }
};

int main()
{
    Solution s;
 //   string a("nzp#o#g");
 //   string b("b#nzp#o#g");

    string a("aaa###a");
    string b("aaaa###a");

    cout << s.backspaceCompare(a, b) << endl;

    return 0;
}