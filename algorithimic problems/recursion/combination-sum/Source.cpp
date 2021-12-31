#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>

using namespace std;

class Solution {
    vector<vector<int>> r;


    void f_slow(vector<int>& c, vector<int> v, int t, int i)
    {

        int s = accumulate(v.cbegin(), v.cend(), 0);

        if (s < t)
        {
            if (i < c.size())
            {
                v.push_back(c[i]);
                f_slow(c, v, t, i);
            }
        }
        else {
            if (s == t)
            {
                if (find(r.cbegin(), r.cend(), v) == r.cend())
                {
                    r.push_back(v);
                }
            }

            while (!v.empty() && i < c.size() - 1)
            {
                v.pop_back();
                f_slow(c, v, t, i + 1);
            }

        }
    }

    void f(vector<int>& c, vector<int> v, int t, int i)
    {
        if (i >= c.size())
        {
            return;
        }

        int s = accumulate(v.cbegin(), v.cend(), 0);
        if (s == t)
        {
            if (find(r.cbegin(), r.cend(), v) == r.cend())
            {
                r.push_back(v);
            }
        }

        else if (s < t)
        {
            v.push_back(c[i]);
            f(c, v, t, i);
            if (!v.empty())
            {
                v.pop_back();
                f(c, v, t, i + 1);
            }
        }
    }

    void f_fast(vector<int>& c, vector<int>& v, int t, int i, int s)
    {
        if (i >= c.size())
        {
            return;
        }

        if (s == t)
        {
            r.push_back(v);
        }

        else if (s < t)
        {
            s += c[i];
            v.push_back(c[i]);
            f_fast(c, v, t, i, s);

            v.pop_back();
            s -= c[i];
            f_fast(c, v, t, i + 1, s);
        }
    }

public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        //    sort(candidates.begin(), candidates.end(), greater<int>());
        vector<int> v;
        f_fast(candidates, v, target, 0, 0);

        return r;
    }
};


int main()
{
    Solution s;
    //  vector<int> v({ 2,3,6,7 });
   //     vector<int> v({ 2,7,6,3,5,1 });
  //    vector<int> v({4,8,11,10,9,3,12,7,6});
   //   vector<int> v({2,7,6,3,5,1});
    vector<int> v({ 48,22,49,24,26,47,33,40,37,39,31,46,36,43,45,34,28,20,29,25,41,32,23 });

    auto start_time = std::chrono::high_resolution_clock::now();

    vector<vector<int>> r = s.combinationSum(v, 69);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;

    cout << time / std::chrono::milliseconds(1) << "ms to run.\n";
    for (auto& vv : r)
    {
        for (int c : vv)
        {
            cout << c << ' ';
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}