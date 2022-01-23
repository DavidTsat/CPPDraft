#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    int f(string a, string b)
    {
        int m = 0;
        vector<vector<int>> v(a.size() + 1, vector<int>(b.size() + 1));

        for (int i = 1; i <= a.size(); ++i)
        {
            for (int j = 1; j <= b.size(); ++j)
            {
                if (a[i - 1] == b[j - 1])
                {
                    v[i][j] = v[i - 1][j - 1] + 1;
                }
                else
                {
                    v[i][j] = max(v[i - 1][j], v[i][j - 1]);
                }

                m = max(m, v[i][j]);
            }
        }
        return m;
    }

public:
    int longestCommonSubsequence(string text1, string text2) {
        return f(text1, text2);
    }
};

int main()
{
    Solution s;

    string a1 = "ezupkr";
    string b1 = "ubmrapg";
    
    string a2 = "abcde";
    string b2 = "ace";

    string a3 = "oxcpqrsvwf";
    string b3 = "shmtulqrypy";

    string a4 = "abcba";
    string b4 = "abcbcba";

    string a5 = "pmjghexybyrgzczy"; // 4  hbgc
    string b5 = "hafcdqbgncrcbihkd";

    string a6 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    string b6 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    
    cout << s.longestCommonSubsequence(a6, b6) << endl;
    
    return 0;
}