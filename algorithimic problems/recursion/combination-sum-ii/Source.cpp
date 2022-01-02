#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <map>
using namespace std;


class Solution {
    vector<vector<int>> r;

    /*
    map<int, int> m;
    bool b = false;

    void ff(vector<int>& c, vector<int>& v, int t, int i, int s)
    {
        if (s == t)
        {
          //  if (find(r.cbegin(), r.cend(), v) == r.cend())
            {
                //    cout << i;
                r.push_back(v);

            }
        }
        //   bool cc = r.size() == 1 && b;

        if (i >= c.size() || i < 0 || (r.size() == 1 && b))
        {
            return;
        }


        else if (s < t)
        {
            /*
            if (!v.empty() && v.back() == c[i])
            {
                f(c, v, t, i + 1, s);
                return;
            }
            else
            {

            if (i > 0 && c[i - 1] != c[i])
            {
                v.push_back(c[i]);
                s += c[i];
                f(c, v, t, i + 1, s);

                v.pop_back();
                s -= c[i];
                f(c, v, t, i + 1, s);
            }
            //}

        }

    }
*/
    void f(vector<int>& c, vector<int>& v, int t, int i, int s)
    {
        if (s == t)
        {
            r.push_back(v);
            return;
        }
        else if (s < t)
        {
            for (int j = i; j < c.size(); ++j)
            {

                if (j > i && c[j - 1] == c[j])
                {
                    continue;
                }

                v.push_back(c[j]);
                s += c[j];
                f(c, v, t, j + 1, s);

                v.pop_back();
                s -= c[j];
            }
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> v;

        sort(candidates.begin(), candidates.end());

        f(candidates, v, target, 0, 0);
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
//    vector<int> v({ 48,22,49,24,26,47,33,40,37,39,31,46,36,43,45,34,28,20,29,25,41,32,23 });
  //  vector<int> v({ 10,1,2,7,6,1,5 });
    vector<int> v({ 2,5,2,1,2 });
  //  vector<int> v({ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 });
   
 //   vector<int> v(30, 1);
 
    auto start_time = std::chrono::high_resolution_clock::now();

    vector<vector<int>> r = s.combinationSum2(v, 5);

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