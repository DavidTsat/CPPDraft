#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int maxProfit(const vector<int>& prices) {
        int min_ = prices[0];
        int max_ = prices[0];

        int max_prof = 0;

        for (int i = 1; i < prices.size(); ++i)
        {
            if (prices[i] <= min_)
            {
                min_ = max_ = prices[i];
            }

            max_ = max(prices[i], max_);
            max_prof = max(max_prof, max_ - min_);
        }
        return max_prof;
    }
};

int main() {
    //[7, 1, 5, 3, 6, 4]
    //[7, 6, 4, 3, 1]

    Solution s; 

    cout << s.maxProfit({ 7, 1, 5, 3, 6, 4 }) << endl;
    return 0;
}