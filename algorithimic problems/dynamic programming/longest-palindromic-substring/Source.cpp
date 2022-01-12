#include <iostream>
#include <string>
#include <iterator>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
    string r;

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

    string longestPalindrome_imrpoved_slow(string s)
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
public:
    string longestPalindrome(string s) {

        return longestPalindrome_imrpoved_slow(s);
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
    cout << s.longestPalindrome("abacdfgdcaba"); // "ddtattarrattatdd" // ooooo
    return 0;
}