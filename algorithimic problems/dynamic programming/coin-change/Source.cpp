#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
    vector<int> r;
    bool b = false;
    void f(const vector<int>& c, vector<int>& v, const int a, int j, long long& s)
    {
        if (b && !r.empty()) return;
        //long long s = accumulate(v.cbegin(), v.cend(), (long long)0);
        if (s == a)
        {
            b = true;
            if (r.empty() || v.size() < r.size()) r = v;
            for (int vv : v) cout << vv << ' ';
            cout << endl;
            s -= v.back();
            v.pop_back();
            return;
        }
        if (s >= a)
        {
            s -= v.back();
            v.pop_back();
            return;

        }

        for (int i = j; i < c.size(); ++i)
        {
            v.push_back(c[i]);
            long long ss = s + c[i];
            f(c, v, a, i, ss);
        }
        //s = 0;
       // v.clear();
        s -= v.back();
        v.pop_back();
       
    }
    void f(const vector<int>& c, vector<int>& v, const int a, int j)
    {
    //    if (b && !r.empty()) return;
        long long s = accumulate(v.cbegin(), v.cend(), (long long)0);
        if (s == a)
        {
            cout << v.size() << endl;
            b = true;
            if (r.empty() || v.size() < r.size()) r = v;
         //   return;
        }
        if (s >= a)
        {
            v.pop_back();
            return;
        }

        //for (int i = j; i < c.size(); ++i)
        for (int i = 0; i <= j; ++i)
        {
            v.push_back(c[i]);

            f(c, v, a, i);
        }
       // v.clear();
        v.pop_back();
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(), coins.end(), greater<int>());
        if (amount == 0) return 0;
        for (int i = 0; i < coins.size(); ++i)
        {
            vector<int> v;
            v.push_back(coins[i]);
            long long s = coins[i];
           // f(coins, v, amount, i, s);
            f(coins, v, amount, i);
        }
        if (r.empty()) return b ? 0 : -1;
        return r.size();
    }
};

int main()
{
    vector<int> v({ 1,2,5 }); //11, 100
    vector<int> v2({ 1, 2147483647 }); // 2
    
    vector<int> v3({ 186, 419, 83, 408 }); //6249
    
    vector<int> v4({ 3, 7, 405, 436 }); // 8839
    

    Solution s;
    
  //  cout << accumulate(v2.cbegin(), v2.cend(), (long long)0) << endl;
  //   cout << s.coinChange(v3, 6249) << endl;
    cout << s.coinChange(v, 11) << endl;

    return 0;
}