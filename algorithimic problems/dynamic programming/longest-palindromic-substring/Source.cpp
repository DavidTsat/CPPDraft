#include <iostream>
#include <string>
#include <iterator>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
    string r;
    int m = 0;

    inline pair<bool, bool> check_palindrome(string::const_iterator l, string::const_iterator r) const
    {
        auto l_prev = l;
        bool same = true;

        while (l < r && *l == *r)
        {
            ++l;
            --r;
            if (same && *l != *l_prev)
            {
                same = false;
            }
            l_prev = l;
        }

        return { l >= r, same };
    }

    pair<pair<bool, bool>, string::const_iterator> longest_palindrome_before(const string& s, string::const_iterator itr)
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
                pair<bool, bool> b = check_palindrome(l, itr);
                if (b.first)
                {
                    if (distance(l, next(itr)) >= r.size())
                    {
                        string p(l, next(itr));
                        r = p;
                    }
                    return { {true, b.second}, l };
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
        return { {false, false}, s.cend() };
    }

    string longestPalindrome_slow(string s) // n^2
    {
        for (auto it = s.cbegin(); it != s.cend(); ++it)
        {
            longest_palindrome_before(s, it);
        }

        return !r.empty() ? r : s.substr(0, 1);
    }

    string longestPalindrome_improved_slow(string s) // fastest one
    {
        pair<pair<bool, bool>, string::const_iterator> p = { {false, false}, s.cbegin() };
        for (auto it = s.cbegin(); it != s.cend(); ++it)
        {
            if (p.first.first == true)
            {
                if (p.first.second == true)
                {
                    if (*p.second == *it)
                    {
                        if (distance(p.second, it) >= r.size())
                        {
                            r = string(p.second, next(it));

                            continue;
                        }
                    }
                    else if (p.second != s.cbegin() && *--p.second == *it)
                    {
                        if (distance(p.second, it) >= r.size())
                        {
                            r = string(p.second, next(it));

                        }
                        p.first.second = false;
                        continue;
                    }
                    else
                    {
                        p = { {false,false}, s.cbegin() };
                        continue;
                    }
                }
                else
                {
                    if (p.second == s.cbegin())
                    {
                        p = { {false,false}, s.cbegin() };
                        continue;
                    }
                    else
                    {
                        if (*--p.second == *it)
                        {
                            if (distance(p.second, it) >= r.size())
                            {
                                r = string(p.second, next(it));
                            }
                            continue;
                        }
                        else
                        {
                            p = { {false,false}, s.cbegin() };
                            continue;
                        }
                    }
                }
            }

            p = longest_palindrome_before(s, it);

        }

        return !r.empty() ? r : s.substr(0, 1);
    }

    void longest_common_palindromic_substr(const string& a, const string& b, string& s_)
    {
        vector<vector<int>> v(a.size(), vector<int>(b.size()));
        int m = -1;
        string s;

        for (int i = 0; i < a.size(); ++i)
        {
            for (int j = 0; j < b.size(); ++j)
            {
                if (a[i] == b[j])
                {
                    if (i == 0 || j == 0)
                    {
                        v[i][j] = 1;
                    }
                    else
                    {
                        v[i][j] = v[i - 1][j - 1] + 1;
                    }
                }
                else
                {
                    v[i][j] = 0;
                }

                if (v[i][j] > m && i - v[i][j] + 1 == (int)a.size() - j - 1)
                {
                    m = v[i][j];
                    s = a.substr(i - m + 1, m);
                }
            }
        }
        s_ = s;
    }

    string longestPalindrome_longest_c_substring(string s)
    {
        string s_rev = s;
        reverse(s_rev.begin(), s_rev.end());

        longest_common_palindromic_substr(s, s_rev, r);
        return r;
    }

    bool f(const string& s, vector<vector<int>>& v, int i, int j)
    {
        if (v[i][j] != -1)
        {
            return v[i][j];
        }

        if (i == j)
        {
            return v[i][j] = 1;
        }
        if (j == i + 1)
        {

            return v[i][j] = s[j] == s[i];
        }

        return v[i][j] = (s[i] == s[j]) && f(s, v, i + 1, j - 1);
    }

    string longestPalindrome_dp(string s)
    {
        vector<vector<int>> v(s.size(), vector<int>(s.size(), -1));

        for (int i = 0; i < s.size(); ++i)
        {
            for (int j = i; j < s.size(); ++j)
            {

                bool b = f(s, v, i, j);

                if (b && j - i + 1 > r.size())
                {
                    r = s.substr(i, j + 1 - i);
                }

            }
        }

        return !r.empty() ? r : s.substr(0, 1);
    }
public:
    string longestPalindrome(string s) {

        //  return longestPalindrome_improved_slow(s);
        return longestPalindrome_dp(s);
    }
};


int main()
{
    Solution s;

    //cout << s.longestPalindrome("aacabdkacaa"); 
    // "abcdbbfcba"
    // "babaddtattarrattatddetartrateedredividerb"
    //lqlvciwekzxapmjxyddlaoqhfhwphamsyfwjinkfvciucjhdgwodvmnpkibumexvlsxxumvrznuuyqfavmgwfnsvfbrvqhlvhpxaqehsiwxzlvvtxsnmlilbnmvnxyxitxwoahjricdjdncvartepfpdfndxqoozkfpdmlpvshzzffsspdjzlhmamqooooor
    //azwdzwmwcqzgcobeeiphemqbjtxzwkhiqpbrprocbppbxrnsxnwgikiaqutwpftbiinlnpyqstkiqzbggcsdzzjbrkfmhgtnbujzszxsycmvipjtktpebaafycngqasbbhxaeawwmkjcziybxowkaibqnndcjbsoehtamhspnidjylyisiaewmypfyiqtwlmejkpzlieolfdjnxntonnzfgcqlcfpoxcwqctalwrgwhvqvtrpwemxhirpgizjffqgntsmvzldpjfijdncexbwtxnmbnoykxshkqbounzrewkpqjxocvaufnhunsmsazgibxedtopnccriwcfzeomsrrangufkjfzipkmwfbmkarnyyrgdsooosgqlkzvorrrsaveuoxjeajvbdpgxlcrtqomliphnlehgrzgwujogxteyulphhuhwyoyvcxqatfkboahfqhjgujcaapoyqtsdqfwnijlkknuralezqmcryvkankszmzpgqutojoyzsnyfwsyeqqzrlhzbc
    //"abbcccbbbcaaccbababcbcabca"
    //"eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"
    cout << s.longestPalindrome("cbbd"); // "abacdgfdcaba" // ooooo // abacdgfdcaba
    return 0;
}