#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:

    int maxArea(vector<int>& height)
    {
        int max_area = 0;
        auto f = height.cbegin();
        auto l = height.cend();
        --l;

        while (f != l)
        {
            max_area = max(max_area, (int)distance(f, l) * min(*f, *l));
            if (*f <= *l) ++f;
            else --l;
        }
        return max_area;
    }
};

int main()
{
    Solution s;
    vector<int> v({ 1, 8, 6, 2, 5, 4, 8, 3, 7 });

    cout << s.maxArea(v);
    return 0;
}
