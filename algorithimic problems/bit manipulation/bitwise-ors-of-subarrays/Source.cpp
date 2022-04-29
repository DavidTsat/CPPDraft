#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>

using namespace std;

class Solution {

public:

    // solution 2
    int subarrayBitwiseORsBad(vector<int>& arr) {
        unordered_set<int> s;

        vector<int> prev_ors;
        prev_ors.push_back(arr[0]);

        for (int i = 0; i < arr.size(); ++i)
        {
            s.insert(arr[i]);
 //           cout << "prev_ors.size(): " << prev_ors.size() << endl;
            vector<int> new_prev_ors;
            new_prev_ors.push_back(arr[i]);
            for (int p : prev_ors)
            {
                int pp = p | arr[i];
                s.insert(pp);
                
                if (new_prev_ors.empty() || pp > new_prev_ors[new_prev_ors.size()-1]) // solution 4 without this if
                    new_prev_ors.push_back(pp);
            }
            
            prev_ors = new_prev_ors;
        }


      //  return unordered_set<int>(or_i_1.cbegin(), or_i_1.cend()).size();
        return s.size();

    }

    // solution 1
    int subarrayBitwiseORsBad1(vector<int>& arr) {

        unordered_set<int> s;

        for (int i = 0; i < arr.size(); ++i)
        {
            s.insert(arr[i]);
            int a = arr[i];
            for (int j = i - 1; j >= 0; --j)
            {
                a |= arr[j];

                s.insert(a);
            }
        }

        return s.size();

    }
    // solution 3
    int subarrayBitwiseORsBetter(vector<int>& arr) {

        vector<int> or_results;

        if (arr.empty()) return 0;

        int i = 0, j = 0;
        for (int a : arr) {
            int start = or_results.size();
            or_results.push_back(a);
            for (int k = i; k < j; k++) {
                int a2 = or_results[k] | a;
                if (a2 > or_results.back()) {
                    or_results.push_back(a2);
                }
            }
            i = start, j = or_results.size();
        }

        //   cout << " or_results.size(): " << or_results.size() << endl;
        return unordered_set<int>(or_results.begin(), or_results.end()).size();
    }

    int subarrayBitwiseORs(vector<int>& arr) {
        return subarrayBitwiseORsBad(arr);
        //    return subarrayBitwiseORsBetter(arr);
    }
};


int main()
{
    Solution s;

    vector<int> v1 = { 1,1,2 };                     // 3
    vector<int> v2 = { 1,2,4 };                     // 6
    vector<int> v3 = { 1,2,3,4 };                   // 5
    vector<int> v4 = { 3,11 };                      // 2
    vector<int> v5 = { 1,11,6,11 };                 // 4
    vector<int> v6 = { 13,4,2 };                    // 5
    vector<int> v7 = { 30, 126, 88, 97, 98, 66 };   // 10
    vector<int> v8 = { 1,2,3,4,5,6,7,8,9 };         // 10

    
    cout << s.subarrayBitwiseORs(v1) << endl;
    cout << s.subarrayBitwiseORs(v2) << endl;
    cout << s.subarrayBitwiseORs(v3) << endl;
    cout << s.subarrayBitwiseORs(v4) << endl;  
    cout << s.subarrayBitwiseORs(v5) << endl;
    cout << s.subarrayBitwiseORs(v6) << endl;
    cout << s.subarrayBitwiseORs(v7) << endl;
    cout << s.subarrayBitwiseORs(v8) << endl;
    
    return 0;
}