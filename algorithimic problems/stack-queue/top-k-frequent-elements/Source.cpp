#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;


class Solution {
public:
    struct lesser {
        bool operator()(const pair<int, int>& a, const pair<int, int>& b) { return a.first > b.first; }
    };
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> word_counts;
        priority_queue<pair<int, int>, std::vector<pair<int, int>>, lesser> top_words;
        vector<int> res(k, 0);

        for (int i : nums)
        {
            ++word_counts[i];
        }

        for (auto it = word_counts.cbegin(); it != word_counts.cend(); ++it)
        {
            top_words.push({ it->second, it->first });
            if (top_words.size() > k)
            {
                top_words.pop();
            }
        }

        for (int i = 0; i < k; ++i)
        {
            pair<int, int> c = top_words.top();
            top_words.pop();
            res[k - i - 1] = c.second;
        }

        return res;
    }
};

int main()
{
    Solution s;
    vector<int> v1 = { 4,1,-1,2,-1,2,3 }; //2

    vector<int> r = s.topKFrequent(v1, 2);
    for (int i : r)
    {
        cout << i << ' ';
    }
    return 0;
}