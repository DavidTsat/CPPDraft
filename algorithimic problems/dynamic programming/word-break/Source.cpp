#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


class Solution {
    unordered_set<string> m;

    void f(const string& r, string s, int i, const vector<string>& w)
    {
        if (s.size() == r.size())
        {
            m.insert(s);
            return;
        }
        if (s.size() > r.size())
        {
            return;
        }

        for (int j = 0; j < w.size(); ++j)
        {
            cout << s + w[j] << endl;
            f(r, s + w[j], j, w);
        }
        // f(r, s + w[i], i+1, w);

    }

    void f(const string& r, string s, const vector<string>& w, bool& b)
    {
        if (b == true) return;
        // cout << "AAAAAAAAAAAAAAAAAAAAA\n";
        if (s.size() == r.size())
        {

            if (s == r)
            {
                //          cout << "AAAAAAAAAAAAAAAAAAAAA\n";
                b = true;
                return;
            }
            // m.insert(s);
           //  return false;
            return;
        }
        if (s.size() > r.size())
        {
            return;
            //return false;
        }

        for (int j = 0; j < w.size(); ++j)
        {
            //      cout << s + w[j] << endl;
            if (r.rfind(s + w[j], 0) == 0)
                f(r, s + w[j], w, b);
        }
        // f(r, s + w[i], i+1, w);
       // return;
    }

    bool g(string s, unordered_set<string>& w)
    {
        vector<bool> v(s.size() + 1);
        v[0] = true;

        for (int i = 1; i <= s.size(); ++i)
        {
            for (int j = i - 1; j >= 0; --j)
            {
                //   auto k = s.substr(j, i-j);
                if (w.find(s.substr(j, i - j)) != w.end())
                {
                    //  bool bb = (j == 0 || v[j] == 1);
                    v[i] = v[j];
                    if (v[i]) break;
                }
            }
        }

        return v[s.size()];
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        for (string& s : wordDict)
        {
            m.insert(s);
        }

        return g(s, m);
        /*
        bool b = false;
        f(s, "", wordDict, b);
        return b;
        */
        /*
        string ss;
        f(s, "", 0, wordDict);
        return m.find(s) != m.end();
        */
    }
};

int main()
{
    Solution s;
    vector<string> w1({ "leet", "code" });
    vector<string> w2({ "apple", "pen" });

    string s3 = "bccdbacdbdacddabbaaaadababadad";
    vector<string> w3({ "cbc", "bcda", "adb", "ddca", "bad", "bbb", "dad", "dac", "ba", "aa", "bd", "abab", "bb", "dbda", "cb", "caccc", "d", "dd", "aadb", "cc", "b", "bcc", "bcd", "cd", "cbca", "bbd", "ddd", "dabb", "ab", "acd", "a", "bbcc", "cdcbd", "cada", "dbca", "ac", "abacd", "cba", "cdb", "dbac", "aada", "cdcda", "cdc", "dbc", "dbcb", "bdb", "ddbdd", "cadaa", "ddbc", "babb" });
   
    string s4 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
    vector<string> w4({ "a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa" });

    string s5 = "catsandog";
    vector<string> w5({ "cats", "dog", "sand", "and", "cat" });

    string s6 = "dogs";
    vector<string> w6({ "dog", "s", "gs" });

    cout << s.wordBreak(s6, w6) << endl;

	return 0;
}