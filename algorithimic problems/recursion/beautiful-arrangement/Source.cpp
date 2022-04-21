#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

class Solution {
    int c = 0;

    template <typename It>
    bool next_permute(It bb, It ee)
    {
        if (bb == ee) return false;
        const reverse_iterator<It> b = make_reverse_iterator(bb);
        const reverse_iterator<It> e = make_reverse_iterator(ee);
        auto p1 = e;
        auto p2 = next(e, 1);

        while (p2 != b)
        {
            if (*p2 < *p1)
            {
                auto m = p2.base();
                auto p11 = p2.base();
                while (p11 != ee)
                {
                    if (*p11 < *m && *p11 > *p2)
                        m = p11;
                    ++p11;
                }
                auto mm = m;
                iter_swap(m, p2);
                reverse(p2.base(), ee);
                return true;
            }
            else
            {
                ++p1;
                ++p2;
            }
        }
        return false;
    }

    bool valid(const vector<int>& v)
    {
        for (int i = 0; i < v.size(); ++i)
        {
            if (v[i] % (i + 1) != 0 && (i + 1) % v[i] != 0) return false;
        }
        return true;
    }

    void print_vec(const vector<int>& v)
    {
        for (int i : v) cout << i << ' ';
        cout << endl;
    }


    void all_permuts(vector<int> v, int j)
    {
        if (j >= v.size())
        {
            if (valid(v))
                ++c;
            // print_vec(v);
        }

        for (int i = j; i < v.size(); ++i)
        {
            swap(v[i], v[j]);
            all_permuts(v, j + 1);

        }
    }

    void valid_permuts(int n, int j, vector<bool>& vb)
    {
        if (j > n)
        {
           // return;
            ++c;
        }

        for (int i = 1; i <= n; ++i)
        {
            if (vb[i] == false && (j % i == 0 || i % j == 0))
            {
                vb[i] = true;
              //  cout << i << endl;
             //   ++c;
                //++c;
                valid_permuts(n, j + 1, vb);
                vb[i] = false;
            }
        }
    }

    int countArrangementWithPermut(int n)
    {
        vector<int> v(n);
        for (int i = 1; i <= n; ++i)
        {
            v[i - 1] = i;
        }
        bool b = true;

        while (b)
        {
            print_vec(v);
            if (valid(v))
                ++c;
            b = next_permute(v.begin(), v.end());

        }



        //    all_permuts(v, 0);


        return c;
    }

public:
    int countArrangement(int n) {
        vector<bool> vb(n + 1, false);
        valid_permuts(n, 1, vb);
        return c;
      //  return countArrangementWithPermut(n);
       
    }
};

int main()
{
    Solution s;

    cout << s.countArrangement(4) << endl;

	return 0;
}