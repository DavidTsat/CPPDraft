#include <stack>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    //stack<pair<char, int>> sc;
    stack<int> sc;
    /*
    string minRemoveToMakeValid_BAD_MEMOORY(string s) { // memory exceeded
        string s2;

        for (int i = 0; i < s.size(); ++i)
        {
            char c = s[i];
            if (c != '(' && c != ')')
            {
                s2 += c;
                continue;
            }

            if (c == '(')
            {
                //           s2 += '(';
                sc.push({ c,s2.size() - 1 });
            }
            else
            {
                if (!sc.empty())
                {
                    pair<char, int> p = sc.top();
                    s2 = s2.substr(0, p.second + 1) + '(' + s2.substr(p.second + 1) + ')';
                    sc.pop();
                }
            }

        }
        return s2;
    }
    */
public:
  
    string minRemoveToMakeValid(string s)
    {
       // vector<int> v;
        char c = s[0];

        for (int i = 0; i < s.size(); ++i)
        {
            c = s[i];
            if (c == '(')
            {
                sc.push(i);
            }
            else if (c == ')')
            {
                if (!sc.empty())
                {
                    if (s[sc.top()] == '(')
                        sc.pop();
                    else
                        sc.push(i);
                }
                else
                    sc.push(i);
            }
        }
        while (!sc.empty())
        {
            int i = sc.top();
            sc.pop();
            s.erase(i,1);
        }
        return s;
    }
};

int main()
{
    Solution s;
    string s1 = "lee(t(c)o)de)";
    string s2 = "a)b(c)d";
    string s3 = "))((";
    string s4 = "(s)((())f((())((()()())())(((m)))))())(q)(()(f)()())(()u(((((((())cf)()())()(((()()())(x()())))((()()))())))))(())()())a)))()))((()()f((())(e((()())(k))())))m)(()()a))))))i)))(()(hq(((((())())))ts)(z()())()()e(())())c(()((((()((((()((()(((((()(h)(()(";
    
    cout << s.minRemoveToMakeValid(s3) << endl;
    return 0;
}