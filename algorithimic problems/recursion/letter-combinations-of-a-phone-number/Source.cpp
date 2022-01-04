#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Solution {
    vector<string> r;

    void f(const vector<string>& v, string s, int i)
    {
        if (v.size() == s.size())
        {
            r.push_back(s);
            return;
        }

        for (int q = i; q < v.size(); ++q)
        {
            for (int k = 0; k < v[q].size(); ++k)
            {
                s += v[q][k];
                f(v, s, q + 1);

                s.pop_back();
            }
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        vector<string> v;
        if (digits.empty())
        {
            return {};
        }

        map<char, string> m
        {
            make_pair<char, string>('2', "abc"),
            make_pair<char, string>('3', "def"),
            make_pair<char, string>('4', "ghi"),
            make_pair<char, string>('5', "jkl"),
            make_pair<char, string>('6', "mno"),
            make_pair<char, string>('7', "pqrs"),
            make_pair<char, string>('8', "tuv"),
            make_pair<char, string>('9', "wxyz")
        };

        for (char d : digits)
        {
            v.push_back(m[d]);
        }

        f(v, "", 0);
        return r;
    }
};



int main()
{
    Solution s;
    vector<string> r = s.letterCombinations("5678");

    for (string s : r)
    {
        cout << s << ", ";
    }
    cout << endl;
    return 0;
}