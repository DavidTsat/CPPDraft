#include <iostream>
#include <vector>
using namespace std;

class Solution {
    /*
    function LCSubstr(S[1..r], T[1..n])
    L := array(1..r, 1..n)
    z := 0
    ret := {}

    for i := 1..r
        for j := 1..n
            if S[i] = T[j]
                if i = 1 or j = 1
                    L[i, j] := 1
                else
                    L[i, j] := L[i − 1, j − 1] + 1
                if L[i, j] > z
                    z := L[i, j]
                    ret := {S[i − z + 1..i]}
                else if L[i, j] = z
                    ret := ret ∪ {S[i − z + 1..i]}
            else
                L[i, j] := 0
    return ret
    */
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        vector<vector<int>> v(nums1.size(), vector<int>(nums2.size()));
        int m = 0;

        for (int i = 0; i < nums1.size(); ++i)
        {
            for (int j = 0; j < nums2.size(); ++j)
            {
                if (nums1[i] == nums2[j])
                {
                    if (i == 0 || j == 0)
                    {
                        v[i][j] = 1;
                        m = max(m, 1);
                    }
                    else
                    {
                        v[i][j] = v[i - 1][j - 1] + 1;
                        m = max(m, v[i][j]);
                    }
                }
                else
                {
                    v[i][j] = 0;
                }
            }

        }

        return m;
    }
};

int main()
{
    Solution s;
    vector<int> v1{ 1, 2, 3, 2, 1 };
    vector<int> v2{ 3, 2, 1, 4, 7 };

    cout << s.findLength(v1, v2) << endl;

    return 0;
}