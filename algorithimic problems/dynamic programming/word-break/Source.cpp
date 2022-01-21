#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>

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
            f(r, s + w[j], w, b);
        }
        // f(r, s + w[i], i+1, w);
       // return;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        bool b = false;
        f(s, "", wordDict, b);
        return b;
        
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
    vector<string> w2({ "apple","pen" });

    string s3 = "bccdbacdbdacddabbaaaadababadad";
    vector<string> w3({ "cbc", "bcda", "adb", "ddca", "bad", "bbb", "dad", "dac", "ba", "aa", "bd", "abab", "bb", "dbda", "cb", "caccc", "d", "dd", "aadb", "cc", "b", "bcc", "bcd", "cd", "cbca", "bbd", "ddd", "dabb", "ab", "acd", "a", "bbcc", "cdcbd", "cada", "dbca", "ac", "abacd", "cba", "cdb", "dbac", "aada", "cdcda", "cdc", "dbc", "dbcb", "bdb", "ddbdd", "cadaa", "ddbc", "babb" });
    cout << s.wordBreak(s3, w3) << endl;

	return 0;
}