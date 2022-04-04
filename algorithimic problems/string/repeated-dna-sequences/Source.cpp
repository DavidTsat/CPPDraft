#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> v;
        if (s.size() < 10) return {};

        unordered_map<string, int> m;
        string::const_iterator b = s.cbegin();
        string::const_iterator p = s.cbegin() + 10;
        bool t = true;

        while (t)
        {
            string ss(b, p);
            // pair<const string, int>& o = m[ss];
            int& o = m[ss];
            ++o;

            if (o == 2)
            {
                v.push_back(ss);
            }
            ++b;
            if (p == s.cend())
                t = false;
            else
                ++p;
        }

        return v;
    }
};

int main()
{
    Solution s;
    vector<string> vs = s.findRepeatedDnaSequences("AAAAAAAAAAA");
    for (string& ss : vs)
    {
        cout << ss << endl;
    }

    return 0;
}