class Solution {
    template <typename It>
    It rotate_point(It f, It l)
    {
        auto count = std::distance(f, l);
        decltype(count) step = count / 2;

        while (count && step)
        {
            auto f_next = std::next(f, step);

            if (*f_next < *f)
            {
                count = step;
            }
            else
            {
                f = f_next;
                count -= step;
            }
            step = count / 2;
        }
        return f;
    }

public:
    int findMin(vector<int>& nums) {
        if (nums[0] <= nums[nums.size() - 1]) return nums[0];
        auto p = rotate_point(nums.cbegin(), nums.cend());
        return *next(p);
    }
};