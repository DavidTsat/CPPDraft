#include <iostream>
#include <vector>
#include <set>

using namespace std;
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> r;
        int i = 0;

        while (i < nums.size())
        {
            if (nums[i] != i + 1 && nums[i] != nums[nums[i] - 1])
            {
                swap(nums[i], nums[nums[i] - 1]);
            }
            else {
                ++i;
            }
        }

        for (int i = 0; i < nums.size(); ++i)
        {
            if (i + 1 != nums[i])
            {
                r.push_back(i + 1);
            }
        }

        return r;
    }
};

class Solution_duplicates {
    vector<int> find_duplicates(vector<int>& nums) {
        vector<int> r;
        set<int> s;
        int i = 0;

        while (i < nums.size())
        {
            if (nums[i] != i + 1 && nums[i] != nums[nums[i] - 1])
            {
                swap(nums[i], nums[nums[i] - 1]);
            }
            else {
                if (nums[i] == nums[nums[i] - 1] && i != nums[i] - 1)
                {
                    s.insert(nums[i]);
                }
                ++i;
            }
        }


        for (auto i : s)
        {
            r.push_back(i);
        }

        return r;
    }
public:
    vector<int> findDuplicates(vector<int>& nums) {
        return find_duplicates(nums);
    }
};

int main() {
    // {4,3,2,7,8,2,3,1} -> {5,6}
    // { 4, 3, 2, 7, 8, 2, 3, 1 }  -> {2, 3}
    return 0;
}