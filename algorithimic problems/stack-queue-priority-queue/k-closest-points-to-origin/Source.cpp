#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
    struct cmp_
    {
        bool operator()(const pair<double, int>& p1, const pair<double, int>& p2)
        {
            return p1.first < p2.first;
        }
    };
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        vector<vector<int>> r;
        priority_queue<pair<double, int>, vector<pair<double, int>>, cmp_> pq;

        for (int i = 0; i < points.size(); ++i)
        {
            const vector<int>& v = points[i];

            double d = sqrt(v[0] * v[0] + v[1] * v[1]);
            pq.push({ sqrt(v[0] * v[0] + v[1] * v[1]), i });
            
            
            if (pq.size() > k)
            {
                pq.pop();
            }
            
        }

        while (k--)
        {
            r.push_back(points[pq.top().second]);
            pq.pop();
        }
        reverse(r.begin(), r.end());
        return r;
    }
};


int main()
{
    Solution s;
    vector<vector<int>> v1 = {{347, -989}, {-237, 817}, {-289, -972}, {-502, -697}, {720, 942}, {798, 797}, {-679, -400}, {648, 699}, {-918, 772}, {-445, -626}, {11, 340}, {810, 498}, {144, 906}, {-767, -539}, {129, -878}, {244, 372}, {-124, 588}, {-480, -617}, {569, -224}, {-80, 849}, {479, 708}, {115, 7}, {-198, 363}, {-319, -138}, {392, 462}, {-404, 748}, {134, -228}, {975, 97}, {-872, 636}, {494, 366}, {-943, -314}, {463, -909}, {100, 788}, {-105, 426}, {-934, 980}, {784, 420}, {509, 702}, {43, -294}, {18, 740}, {40, 97}, {609, 979}, {565, 980}, {454, 431}, {-159, 714}, {532, -689}, {540, -957}, {216, -4}, {-68, 914}, {-690, 794}, {677, -730}}; //22
    vector<vector<int>> v2 = { {-5, 4}, {-6, -5}, {4, 6} };
    vector<vector<int>> v1_ = s.kClosest(v1, 22);

    for (int i = 0; i < v1_.size(); ++i)
    {
        cout << v1_[i][0] << ' ' << v1_[i][1] << ',';
    }
    cout << endl;
    return 0;
}