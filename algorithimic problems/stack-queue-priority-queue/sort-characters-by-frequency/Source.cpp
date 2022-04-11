#include <iostream>
#include <string>
#include <queue>
#include <set>

using namespace std;

class Solution {
    struct length_cmp
    {
        bool operator()(const string& s1, const string& s2)
        {
            return s1.size() < s2.size();
        }
    };
public:
    
    string frequencySort(string s) {
        priority_queue<string, vector<string>, length_cmp> pq;

        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == '-') continue;
            int j = i + 1;
            int c = 1;
            while (j < s.size()) {
                if (s[j] == s[i] && s[j] != '-')
                {
                    ++c;
                    s[j] = '-';
                }
                ++j;
            }
            string ss = string(c, s[i]);
            pq.push(ss);
        }
        s = "";
        while (!pq.empty())
        {
            s += pq.top();
            pq.pop();
        }
        return s;
    }
    
};

int main()
{
    Solution s;

    string s1 = "tree";
    string s2 = "raaeaedere";
    cout << s.frequencySort(s2) << endl;
	return 0;
}