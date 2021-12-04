class Solution {

    void minCostClimbingStairs(vector<int>& cost, int& s, int l, int n, bool b) {
        //return min(cost[i] + cost[i + 2], cost[i + 1]);

        if (n - l == 3)
        {
            int c = cost[n - 1] + cost[n - 3];
            if (c <= cost[n - 2])
            {
                //  i = i - 3;
                s += c;
                b = false;
            }
            else {
                s += cost[n - 2];
                //  i = i - 2;
                b = true;
            }
            ++l;
            return;
        }

        minCostClimbingStairs(cost, s, l, n - 1, b);
        if (n - l == 3)
        {
            int c = cost[n - 1] + cost[n - 3];
            if (c <= cost[n - 2])
            {
                //  i = i - 3;
                s += c;
                b = false;
            }
            else {
                s += cost[n - 2];
                //  i = i - 2;
                b = true;
            }
            ++l;
            return;
        }
    }
    int minCostClimbingStairs1(vector<int>& cost)
    {
        int n = cost.size();
        pair<int, int> dp;

        dp.first = cost[0];
        dp.second = cost[1];
        bool first = false;

        for (int i = 2; i < n; i++)
        {
            int cost_i = cost[i] + min(dp.first, dp.second);
            dp.first = dp.second;
            dp.second = cost_i;
        }

        return min(dp.first, dp.second);
    }
public:
    int minCostClimbingStairs(vector<int>& cost) {

        int n = cost.size();
        pair<int, int> dp;

        dp.first = cost[0];
        dp.second = cost[1];
        bool first = false;

        for (int i = 2; i < n; i++)
        {
            int cost_i = cost[i] + min(dp.first, dp.second);
            dp.first = dp.second;
            dp.second = cost_i;
        }

        return min(dp.first, dp.second);

    }
};