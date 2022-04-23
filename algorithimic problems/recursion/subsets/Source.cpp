#include <vector>
#include <iostream>
#include <map>

using namespace std;

class Solution {
/*
    The solution is based on the fact mentioned in the "Guide to Competitive Programming: Antti Laaksonen" book which claims
    that to compute all of the subsets of some set (nums - in our case), represented as an integer number x (binary representation
    of an array consisting of non-negative elements and for which max element is not bigger than sizeof(int)*8. E.g, the set {0,2,3} can be
    represented by an int x = 00...001101 = 13) we can use the following code:

    int b = 0;
    do {
    // process b
    } while (b = (b-x)&x)

    Since our input elements are in the range [-10,10] we can use the above solution with some modification to handle negative numbers too:
    That is we bring the input nums to a valid range of non-negative numbers, and also we keep a map<int, int> to handle indexes with the
    original values.
*/
    vector<vector<int>> r;
    map<int, int> m;

    void getSubsets(const vector<int>& nums, vector<int> v, const int s, int j)
    {
        if (s == v.size())
        {
            r.push_back(v);
            return;
        }

        for (int i = j; i < nums.size(); ++i)
        {
            v.push_back(nums[i]);
            getSubsets(nums, v, s, i + 1);
            v.pop_back();
        }
    }

    vector<int> getSubsetFromBin(int x, const vector<int>& n)
    {
        vector<int> v;
        for (int i = 0; i < sizeof(int)*8 - 1; ++i)
        {
            if (x & (1 << i))
            {
                v.push_back(m[i]);
            }
        }
        return v;
    }

    void getSubsetsBitWise(vector<int>& nums)
    {
        for (int i = 0; i < nums.size(); ++i)
        {
            m[i] = nums[i];
            nums[i] = i;
        }
        int x = 0;
        for (int i : nums)
        {
            x = x | (1 << i);
        }
       
        int b = 0;
        do
        {
            vector<int> ss = getSubsetFromBin(b, nums);
            r.push_back(ss);
        } while (b = ((b - x) & x));
        
    }

    void getSubsetsDP(vector<int>& nums)
    {
        for (int s = 0; s <= nums.size(); ++s)
        {
            getSubsets(nums, {}, s, 0);
        }
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        getSubsetsBitWise(nums);
       
        return r;
    }
};

int main()
{
    Solution s;
    vector<int> v({ 0,2,3 });
    vector<int> v2({ -1,1,2 });
    vector<vector<int>> r = s.subsets(v);

    for (auto& rr : r)
    {
        for (int c : rr)
        {
            cout << c << ' ';
        }
        cout << endl;
    }

    return 0;
}