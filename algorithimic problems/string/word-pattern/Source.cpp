#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution {
    vector<string> split(string s, string delimiter)
    {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        string token;
        vector<string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
            token = s.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }

        res.push_back(s.substr(pos_start));
        return res;
    }
public:
    bool wordPattern(string pattern, string s) {
        vector<string> v = split(s, " ");

        if (v.size() != pattern.size()) return false;
        map<char, string> m;
        map<string, char> m2;

        for (int i = 0; i < pattern.size(); ++i)
        {
            if (m2.end() == m2.find(v[i]))
            {
                m2[v[i]] = pattern[i];
            }
           
            else if (m2[v[i]] != pattern[i])
            {
                return false;
            }
        }

        for (int i = 0; i < pattern.size(); ++i)
        {
            string& cs = m[pattern[i]];
            if (cs.empty())
            {
                cs = v[i];
            }
            else if (cs != v[i])
            {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    Solution s;
    //"dog dog dog dog" dog cat cat dog
    cout << s.wordPattern("abba", "dog cat cat dog") << endl;
    return 0;
}