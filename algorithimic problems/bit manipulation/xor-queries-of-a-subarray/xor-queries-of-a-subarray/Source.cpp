#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        vector<int> r;
        vector<int> pr_xors;

        pr_xors.reserve(arr.size());
        r.reserve(arr.size());

        pr_xors.push_back(arr[0]);

        for (int i = 1; i < arr.size(); ++i)
        {
            pr_xors.push_back(pr_xors[i - 1] ^ arr[i]);
        }

        for (int i = 0; i < queries.size(); ++i)
        {
            int a = pr_xors[queries[i][1]];
            if (queries[i][0] != 0)
            {
                a ^= pr_xors[queries[i][0] - 1];
            }
            r.push_back(a);
        }
        return r;
    }
};

int main()
{
    Solution s;
    vector<int> vs1{ 1, 3, 4, 8 };
    vector<vector<int>>  vs2{ {0, 1}, {1, 2}, {0, 3}, {3, 3} };

    vector<int> r = s.xorQueries(vs1, vs2);
    for (int i : r)
    {
        cout << i << ' ';
    }

    cout << endl;
    cout << endl;
 
    return 0;
}