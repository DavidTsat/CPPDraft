#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
class Solution {
public:
    int maxProfit(const vector<int>& prices) {
        int max_prof = 0;
        int prev = prices[0];

        for (int i = 1; i < prices.size(); ++i)
        {
            int max_ = max(prev, prices[i]);
            int curr_prof = max_ - prev;
            prev = prices[i];

            max_prof += curr_prof;
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
