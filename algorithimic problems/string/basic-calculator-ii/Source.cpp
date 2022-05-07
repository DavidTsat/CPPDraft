#include <string>
#include <iostream>
#include <vector>

using namespace std;


class Solution {
    int rr = 0;

    void f(string ss)
    {
        string s;

        for (int i = 0; i < ss.size(); ++i)
        {
            if (ss[i] != ' ')
                s += ss[i];
        }

        int cp = 1;
      //  while ((s.find('*') != std::string::npos) || (s.find('/') != std::string::npos))
        {
            for (int i = 0; i < s.size(); ++i)
            {
                if (s[i] == '*' || s[i] == '/')
                {
                    int l = i - 1;
                    int r = i + 1;

                    while (l >= 0 && (s[l] != '+' && s[l] != '-'))
                        --l;
                    while (r < s.size() && (s[r] != '+' && s[r] != '-' && s[r] != '*' && s[r] != '/'))
                        ++r;

                    if (l < 0) ++l;
                    if (r >= s.size()) --r;

                    int cl = atoi(s.substr(l, i - l).c_str());
                    int cr = atoi(s.substr(i + 1, r - i).c_str());

                    int c = (s[i] == '*' ? cl * cr : cl / cr);// *cp;
                    cp = c;
                    int aa = c;

                    /*
                    string ss = (l == 0 ? "" : s.substr(0, l + 1));
                    string ss2 = (r == s.size() - 1 ? "" : s.substr(r, s.size() - r));

                    s = ss + to_string(aa) + ss2;
                    if (l == 0) i = 0;
                    i = (ss + to_string(aa)).size() - 1;
                    */
                    
                    string ss = (l == 0 ? "" : s.substr(0, l + 1));
                    string ss2 = (r == s.size() - 1 ? "" : s.substr(r, s.size() - r));
                    string aa_str = to_string(aa);

                    s = ss + aa_str + ss2;
                    if (l == 0) i = 0;
                   // i = (ss + to_string(aa)).size() - 1;
                    i = ss.size() + aa_str.size() - 1;
                    
                }
            }
            int a = cp;
        }
    
        int l = 0;
        char c = '+';
        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] != '+' && s[i] != '-')
            {
                int j = i;
                while (j < s.size() && (s[j] != '+') && (s[j] != '-'))
                {
                    ++j;
                }
                int ss = atoi(s.substr(l, j).c_str());
                rr = (c == '+' ? rr + ss : rr - ss);
                c = s[i];
                i = j - 1;
            }
            else
            {
                c = s[i];
                l = i + 1;
            }
        }
    }
public:
    int calculate(string ss) {
        f(ss);
        return rr;
    }
};

int main()
{
    Solution s;

    string s1 = "3+2*2";
    string s2 = " 3/2 ";
    string s3 = " 3+5 / 2 ";
    string s4 = "0-2147483647";
    string s5 = "1+1+1";
    string s6 = "1+1+4*5+ 7+ 9*123+4/2-9";
    string s7 = "2*3*4";
    string s8 = "1*2*3*4*5*6*7*8*9*10";
    string s9 = "1787+2136/3/2*2";

    vector<string> vs = { s1, s2, s3, s4, s5, s6, s7, s8, s9 };

    for (string ss : vs)
    {
        s = Solution();
        cout << s.calculate(ss) << endl;
    }

    return 0;
}