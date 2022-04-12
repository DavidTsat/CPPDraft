class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        if (trust.empty()) return n == 1 ? 1 : -1;
        map<int, int> m;
        set<int> m1;

        for (int i = 0; i < trust.size(); ++i)
        {
            ++m[trust[i][1]];
            m1.insert(trust[i][0]);
        }

        for (const pair<int, int>& p : m)
        {
            if (p.second == n - 1 && m1.find(p.first) == m1.end())
            {
                return p.first;
            }
        }
        return -1;
    }

    /*
    int findJudge(int n, vector<vector<int>>& trust) {
        if (trust.empty()) return n == 1 ? 1 : -1;
        map<int, set<int>> m;
        set<int> m1;

        for (int i = 0; i < trust.size(); ++i)
        {
            m[trust[i][1]].insert(trust[i][0]);
            m1.insert(trust[i][0]);
        }

        for (const pair<int, set<int>>& p : m)
        {
            if (p.second.size() == n -1 && m1.find(p.first) == m1.end())
            {
                return p.first;
            }
        }
        return -1;
    }
    */
};