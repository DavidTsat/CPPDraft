#include <iostream>
#include <vector>
using namespace std;


class Solution {
    vector<int> v;
    int num_trees(int n)
    {
        if (n == 0 || n == 1)
        {
            return 1;
        }

        if (v[n] != -1)
        {
            return v[n];
        }
        int sum_ = 0;

        for (int i = 1; i <= n; ++i)
        {
            sum_ += num_trees(i - 1) * num_trees(n - i);
        }
        
        if (v[n] == -1)
        {
            v[n] = sum_;
        }

        return sum_;
    }

public:
    int numTrees(int n) {
        //int k=0;

        v = vector<int>(n+1, -1);
        int k = num_trees(n);


        return k;
    }
};


int main() {
    Solution s;

    cout << s.numTrees(50) << endl;
    //cout << "c: " << c << endl;
    return 0;
}