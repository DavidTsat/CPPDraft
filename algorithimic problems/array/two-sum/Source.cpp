#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        multimap<int, int> indices;
        vector<int> v(2);

        for (int i = 0; i < nums.size(); ++i) // o(n)
        {
            indices.insert({ nums[i],i });
        }

        sort(nums.begin(), nums.end()); // o(nlog(n))

        for (int i = 0; i < nums.size(); ++i) // o(n)
        {
            auto it1 = lower_bound(nums.cbegin(), nums.cend(), target - nums[i]); // o(log(n))
            if (it1 != nums.cend() && *it1 == target - nums[i])
            {
                auto range1 = indices.equal_range(nums[i]);
                int ii = 0;
                for (auto i = range1.first; i != range1.second; ++i)
                {
                    v[ii++] = i->second;
                }
                if (ii != 2)
                {
                    auto range2 = indices.equal_range(target - nums[i]);
                    for (auto i = range2.first; i != range2.second; ++i)
                    {
                        v[ii++] = i->second;
                    }

                }

                break;
            }
        }
        return v;
    }
};


int main()
{
    Solution s;
   // vector<int> v({ -3, 4, 3, 90 });
    vector<int> v({ 3,2,4 });
    vector<int> r = s.twoSum(v, 6);

    return 0;
}