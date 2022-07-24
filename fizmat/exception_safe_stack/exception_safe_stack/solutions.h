#pragma once
#include "_stack.h"
#include <string>

using namespace std;

class SolutionParentheses {
public:
    bool isValid(string s) {
        _stack<char> st;
        array<char, 3> open_pars({ '(', '{', '[' });
        array<char, 3> close_pars({ ')', '}', ']' });

        for (char c : s)
        {
            if (find(open_pars.cbegin(), open_pars.cend(), c) != open_pars.cend())
            {
                st.push(c);
                continue;
            }
            auto c_close = find(close_pars.cbegin(), close_pars.cend(), c);
            if (c_close != close_pars.cend())
            {
                if (st.empty()) return false;
                char c_st = st.top();
                st.pop();
                if (open_pars[distance(close_pars.cbegin(), c_close)] != c_st) return false;
            }
            else
            {
                return false;
            }
        }

        return st.empty();
    }
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class BSTIterator {
private:
    _stack<TreeNode*> st;
public:
    BSTIterator(TreeNode* root) {
        find_left(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        if (st.empty())
            return false;
        return true;
    }

    /** @return the next smallest number */
    int next() {
        TreeNode* top = st.top();
        st.pop();
        if (top->right != NULL)
            find_left(top->right);

        return top->val;
    }

    /** put all the left child() of root */
    void find_left(TreeNode* root)
    {
        TreeNode* p = root;
        while (p != NULL)
        {
            st.push(p);
            p = p->left;
        }
    }
};

class SolutionCalculator {
    int f_stack(string s)
    {
        _stack<int> ss;
        int r = 0;
        int cur_num = 0;
        char op = '+';
        for (int i = 0; i < s.size(); ++i)
        {
            if (iswspace(s[i]) && i != (s.size() - 1)) continue;

            if (isdigit(s[i]))
            {
                cur_num = cur_num * 10 + (s[i] - '0');
            }
            if (!isdigit(s[i]) || (i == (s.size() - 1)))
            {
                if (op == '-')
                {
                    ss.push(-cur_num);
                }
                else if (op == '+')
                {
                    ss.push(cur_num);
                }
                else if (op == '*')
                {
                    int l = ss.top();
                    ss.pop();
                    ss.push(l * cur_num);
                }
                else if (op == '/')
                {
                    int l = ss.top();
                    ss.pop();
                    ss.push(l / cur_num);
                }
                op = s[i];
                cur_num = 0;
            }
        }

        while (!ss.empty())
        {
            r += ss.top();
            ss.pop();
        }
        return r;
    }
public:
    int calculate(string ss) {
        return f_stack(ss); // calculatess(ss);
        //   f(ss);
     //   return rr;
    }
};

#include <queue>

class SolutionGame {
    void init_q(queue<int>& q, int n)
    {
        for (int i = 1; i <= n; ++i)
        {
            q.push(i);
        }
    }

    int f_rec(queue<int>& q, int n, int k, bool& b)
    {
        if (!b)
        {
            init_q(q, n);
            b = true;
        }

        if (n == 1)
        {
            return q.front();
        }

        for (int j = 0; j < k - 1; ++j)
        {
            int c = q.front();
            q.pop();
            q.push(c);
        }

        q.pop();
        return f_rec(q, n - 1, k, b);
    }
public:
    int findTheWinner(int n, int k) {
        queue<int> q;
        bool b = false;
        return f_rec(q, n, k, b);
    }
};