#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {

public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int max_val = values[0];
        int max_score = INT_MIN;
        int j = 0;
        for (int i = 1; i < values.size(); ++i)
        {
            max_score = max(max_score, max_val + values[i] - i + j);
            if (max_val - i + j <= values[i])
            {
                max_val = values[i];
                j = i;
            }
        }

        return max_score;
    }

   /*
    int maxScoreSightseeingPair(vector<int>& values) {
        int m = 0;
        auto l = values.cbegin();
        auto r = values.cend();
        --r;

        while (l != values.cend() &&)
        {
           
            if (l == r)
            {
                --r;
                continue;
            }
            m = max(m, *l + *r - abs((int)distance(l, r)));

            if (*l > *r)
            {
                --r;
            }
            else if(*l < *r) {
                ++l;
            }
            
            else {
                if (*(l + 1) > *(r - 1))
                {
                    --r;
                }
                else if (*(l + 1) < *(r - 1)) {
                    ++l;
                }
                else {
                    cout << "AAAAAAAAAAAAAAAAA";
                }
            }
            
        }
        return m;
    }
    */
};

int main() {
    Solution s;

    vector<int> v({ 8, 1, 5, 2, 6 });
    vector<int> vv({ 5,3,1 });
    vector<int> v2({ 6, 9, 10, 5, 9, 10, 4, 5 });
    vector<int> v4({ 3,7,2,3 });
    vector<int> v5({ 30, 13, 28, 32, 16, 8, 11, 78, 83, 5, 22, 93, 61, 60, 100, 8, 6, 48, 87, 43, 41, 86, 93, 5, 19, 29, 59, 31, 7, 51, 99, 47, 40, 24, 20, 98, 41, 42, 81, 92, 55, 85, 51, 92, 84, 21, 84, 92, 1, 73, 93, 51, 44, 27, 23, 54, 32, 57, 60, 9, 69, 14, 28, 86, 15, 92, 47, 63, 12, 99, 54, 6, 16, 52, 28, 86, 38, 73, 16, 52, 37, 30, 84, 81, 46, 97, 84, 17, 21, 14, 52, 19, 74, 20, 20, 56, 89, 7, 34, 21});
  /*
    sort(v5.begin(), v5.end());
    for (int c : v5)
    {
        cout << c << ' ';
    }
    */
    cout << endl;
    cout << s.maxScoreSightseeingPair(v5) << endl;
    //[1, 2]

	return 0;
}