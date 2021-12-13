#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
    int maxProfitRec(int i, bool buy, vector<vector<int>>& v, const vector<int>& prices, int fee) {
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
            int m1 = max(maxProfitRec(i + 1, false, v, prices, fee) - prices[i], maxProfitRec(i + 1, true, v, prices, fee)); // buy vs hold
            return v[buy][i] = m1;

        }
        else
        {
            int m2 = max(maxProfitRec(i + 1, true, v, prices, fee) + prices[i] - fee, maxProfitRec(i + 1, false, v, prices, fee)); // sell vs hold
            return v[buy][i] = m2;
        }
    }

    int maxProfitIterDP(const vector<int>& prices, int fee) {
        vector<vector<int>> tab(prices.size(), vector<int>(2));

        tab[0][0] = 0;
        tab[0][1] = -prices[0];

        for (int i = 1; i < prices.size(); ++i)
        {
            tab[i][0] = max(tab[i - 1][1] + prices[i] - fee, tab[i - 1][0]); // sell or nothing if not bought
            tab[i][1] = max(tab[i - 1][0] - prices[i], tab[i - 1][1]); // buy or hold
        }

        return max(tab[prices.size() - 1][0], tab[prices.size() - 1][1]);
    }

    int maxProfitIterGreedy(const vector<int>& prices, int fee) {
        int max_prof_wo = 0;                // without stock 
        int max_prof_ws = -prices[0];       // with stock

        for (int i = 1; i < prices.size(); ++i)
        {
            max_prof_wo = max(max_prof_ws + prices[i] - fee, max_prof_wo);
            max_prof_ws = max(max_prof_wo - prices[i], max_prof_ws);
        }

        return max(max_prof_wo, max_prof_ws);
    }
public:
    int maxProfit(const vector<int>& prices, int fee) {
        return maxProfitIterGreedy(prices, fee);
       // return maxProfitIterDP(prices, fee);
        // vector<vector<int>> v(2, vector<int>(prices.size(), -1));
        // return  maxProfitRec(0, true, v, prices, fee);
    }
};

int main() {
    //[7, 1, 5, 3, 6, 4]
    //[7, 6, 4, 3, 1]
    //1,2,3,4,5
    Solution s;

    cout << s.maxProfit({ 1,3,2,8,4,9 }, 2) << endl;
    return 0;
}