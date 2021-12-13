#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
    int maxProfitRec(int i, bool buy, vector<vector<int>>& v, const vector<int>& prices) {
        if (i >= prices.size())
        {
            return 0;
        }

        if (v[buy][i] != -1)
        {
            return v[buy][i];
        }
        if (buy)
        {
            int m1 = max(maxProfitRec(i + 1, false, v, prices) - prices[i], maxProfitRec(i + 1, true, v, prices)); // buy vs hold
            return v[buy][i] = m1;

        }
        else
        {
            int m2 = max(maxProfitRec(i + 1, true, v, prices) + prices[i], maxProfitRec(i + 1, false, v, prices)); // sell vs hold
            return v[buy][i] = m2;
        }
    }

    int maxProfitIterDP(const vector<int>& prices) {
        vector<vector<int>> tab(prices.size(), vector<int>(2));

        tab[0][0] = 0;
        tab[0][1] = -prices[0];


        for (int i = 1; i < prices.size(); ++i)
        {
            tab[i][0] = max(tab[i - 1][1] + prices[i], tab[i - 1][0]); // sell or nothing if not bought
            tab[i][1] = max(tab[i - 1][0] - prices[i], tab[i - 1][1]); // buy or hold
        }

        return max(tab[prices.size() - 1][0], tab[prices.size() - 1][1]);
    }

    int maxProfitIterGreedy(const vector<int>& prices) {
        int max_prof = 0;
        int prev = prices[0];

        for (int i = 1; i < prices.size(); ++i)
        {
            int max_ = max(prev, prices[i]);
            int curr_prof = max_ - prev;
            max_prof += curr_prof;
            prev = prices[i];
        }

        return max_prof;
    }

public:
    int maxProfit(const vector<int>& prices) {
        //    if (prices.size() < 2) return 0;
        return maxProfitIterDP(prices);
        //   vector<vector<int>> v(2, vector<int>(prices.size(), -1));
        //   return  maxProfitRec(0, true, v, prices);
    }
};

int main() {
    //[7, 1, 5, 3, 6, 4]
    //[7, 6, 4, 3, 1]

    Solution s;

    cout << s.maxProfit({ 7, 1, 5, 3, 6, 4 }) << endl;
    return 0;
}