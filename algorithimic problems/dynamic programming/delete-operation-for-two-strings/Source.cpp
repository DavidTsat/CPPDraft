#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//slow solution
/*
class Solution {
    int longest_com_subs(string a, string b)
    {
        vector<vector<int>> v(a.size(), vector<int>(b.size(), 0));
        int c = 0;
        int m = min(a.size(), b.size());

        for (int i = 0; i < a.size(); ++i)
        {
            for (int j = 0; j < b.size(); ++j)
            {
                if (a[i] == b[j])
                {

                    int cc = 0;

                    if (i > 0 && j > 0)
                    {
                        if (v[i - 1][j - 1] > 0)
                            cc = v[i - 1][j - 1];
                        else
                        {
                            for (int ii = i - 1; ii >= 0; --ii)
                            {
                                for (int jj = j - 1; jj >= 0; --jj)
                                {
                                    if (v[ii][jj] > cc)
                                    {
                                        cc = v[ii][jj];

                                        break;
                                    }
                                }
                            }
                        }
                    }
                    v[i][j] = cc + 1;
                }
                c = max(c, v[i][j]);
                // else v[i][j] = c;
                // c = min(m, max(c, v[i][j]));
            }
        }
        return c;
    }
public:
    int minDistance(string word1, string word2) {
        // return  longest_com_subs(word1, word2);
        return word1.size() + word2.size() - 2 * longest_com_subs(word1, word2);
    }
};
*/
//fast solution
class Solution {
    int longest_com_subs(string a, string b)
    {
        vector<vector<int>> v(a.size() + 1, vector<int>(b.size() + 1, 0));
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
            }
        }
        return v[a.size()][b.size()];
    }
public:
    int minDistance(string word1, string word2) {
        return word1.size() + word2.size() - 2 * longest_com_subs(word1, word2);
    }
};
int main()
{
    string a1 = "sea";
    string b1 = "eat";
    string a2 = "leetcode";
    string b2 = "etco";
    string a3 = "park";
    string b3 = "spake";
    string a5 = "sea";
    string b5 = "ate";
    string a6 = "mart";
    string b6 = "karma";
    string a7 = "intention";
    string b7 = "execution";

    string a8 = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdef";
    string b8 = "bcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefg";

    Solution s;

    cout << s.minDistance(a8, b8) << endl;
	return 0;
}