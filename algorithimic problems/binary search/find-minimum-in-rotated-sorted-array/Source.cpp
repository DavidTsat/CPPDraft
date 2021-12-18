#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

class Solution {
    template <typename It>
    It find_rot_point(It first, It last)
    {
        It f(first);
        auto count = distance(first, last);
        decltype(count) step = 0;
        auto it = first;

        while (count > 0)
        {
            it = first;
            step = count / 2;
            advance(it, step);

            if (*it >= *f)
            {
                advance(first, step + 1);
                count -= step + 1;
            }
            else
            {
                auto it_prev(it);
                --it_prev;
                if (*it < *it_prev)
                {
                    break;
                }
                count = step;
            }
        }
        return it;
    }
public:
    int findMin(vector<int>& nums) {
        if (*nums.cbegin() < nums[nums.size() - 1]) return *nums.cbegin();
        auto rot_point = find_rot_point(nums.cbegin(), nums.cend());
        return *rot_point;
    }
};

int main()
{
    Solution s;
    vector<int> v({ 3,4,5,1,2 });
    cout << s.findMin(v) << endl;
    return 0;
}