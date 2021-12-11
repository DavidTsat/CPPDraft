#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int maxProfit(const vector<int>& prices) {
        int max_ = prices[0];
        int cur = prices[0];
        int max_prof = 0;
        int curr_prof = 0;

        for (int i = 1; i < prices.size(); ++i)
        {
            max_ = max(max_, prices[i]);
            curr_prof = max(curr_prof, max_ - cur);
            if (prices[i] < max_)
            {
                cur = max_ = prices[i];
                max_prof += curr_prof;
                curr_prof = 0;
            }

        }

        return max_prof + curr_prof;
    }
};

int main() {
    //[7, 1, 5, 3, 6, 4]
    //[7, 6, 4, 3, 1]

    Solution s;

    cout << s.maxProfit({ 7, 1, 5, 3, 6, 4 }) << endl;
    return 0;
}
