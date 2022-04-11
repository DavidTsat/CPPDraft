#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>

using  namespace std;

class Solution {
    int ff(int n, const int k)
    {
        vector<int> v;
        v.reserve(n);
        int c = 1;
        int i = 0;

        int q = (c + k - 1) % n;

        while (i != n - 1)
        {
            q = (c + k - 1) % n; //TODO
            q = q == 0 ? n : q;
            while (find(v.cbegin(), v.cend(), q) != v.cend())
            {
                q = (q + 1) % n;
                q = q == 0 ? n : q;
            }
            // cout << "q: " << q << ',';
             //cout << q << ',';
            v.push_back(q);
            c = (c + 1) % n;
            c = c == 0 ? n : c;
            while (find(v.cbegin(), v.cend(), c) != v.cend())
            {
                c = (c + 1) % n;
                c = c == 0 ? n : c;
            }
            // cout << "c: " << c << ',';
            ++i;
        }
        cout << endl;
        return c;
    }
    /*
    int f(int n, int k)
    {
        queue<int> q;
        int c = 1;
        int i = 0;
        while (i != n - 1)
        {
            ++i;
            int p = (c + k - 1) % n;
            p = p == 0 ? n : p;


            if (q.empty())
            {
                q.push(p);
            }
            else
            {
                bool b = false;
                while (p == q.front())
                {
                    b = true;
                    q.pop();
                    q.push(p);
                    p = (p + 1) % n;
                    p = p == 0 ? n : p;
                }
              //  if (!b)
                {
                    q.push(p);
                }
            }

            cout << p << ' ';
            c = (p + 1) % n;
            c = c == 0 ? n : c;
            if (!q.empty())
            {
                while (c == q.front())
                {
                    q.pop();
                    q.push(c);
                    c = (c + 1) % n;
                    c = c == 0 ? n : c;
                }
            }


        }
        cout << endl;
        return c;
    }
    */
    int f(const int n, const int k)
    {
        queue<int> q;
        int c = 1;
        int i = 0;

        while (i != n - 1)
        {
            ++i;
            int kk = k - 1;
            int p = c;

            for (int j = 0; j < kk - 1; )
            {
                p = p == n ? 1 : p + 1;
                if (!q.empty() && p == q.front())
                {
                    continue;
                }
                else
                {
                    ++j;
                }
            }

            q.push(p);

            c = p == n ? 1 : p + 1;
            while (c == q.front())
            {
                c = c == n ? 1 : c + 1;
            }
        }

        return c;
    }
public:
    queue<int> q;
    void init_q(int n)
    {
        for (int i = 1; i <= n; ++i)
        {
            q.push(i);
        }
    }
    bool b = false;
    
    int f_rec(int n, int k)
    {
        if (!b)
        {
            init_q(n);
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
        return f_rec(n - 1, k);
    }

    int findTheWinner(int n, int k) {
        return f_rec(n, k);
        /*
        if (!b)
        {
            init_q(n);
            b = true;
        }
        
        for (int i = 1; i < n; ++i)
        {
            for (int j = 0; j < k-1; ++j)
            {
                int c = q.front();
                q.pop();
                q.push(c);
            }
            
            q.pop();
        }
        return q.front();
        */
    }
};

int main()
{
    Solution s;
    //5,4 - 5
    cout << s.findTheWinner(5, 4) << endl;

    return 0;
}