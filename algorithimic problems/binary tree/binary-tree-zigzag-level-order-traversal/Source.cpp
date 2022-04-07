#include <iostream>
#include <vector>
#include <queue>

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
class Solution {
    vector<vector<int>> r;
    int l = 1;

    void bfs(queue<pair<TreeNode*, int>>& q)
    {
        if (q.empty())
        {
            return;
        }

        pair<TreeNode*, int> t = q.front();
        q.pop();


        if (r.size() < t.second)
        {
            r.push_back({ t.first->val });
        }
        else
        {
            if (t.second % 2 == 0)
            {
                r[t.second - 1].insert(r[t.second - 1].begin(), t.first->val);
            }
            else
            {
                r[t.second - 1].push_back(t.first->val);
            }

        }

        if (t.first->left)
        {
            q.push({ t.first->left, t.second + 1 });
        }
        if (t.first->right)
        {
            q.push({ t.first->right, t.second + 1 });
        }


        return bfs(q);
    }

public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (!root) return vector<vector<int>>();
        queue<pair<TreeNode*, int>> q;


        q.push({ root,1 });

        bfs(q);

        /*
        for (int i = 1; i <= r.size(); ++i)
        {
            if (i % 2 ==0)
            {
                reverse(r[i-1].begin(), r[i-1].end());
            }
        }
        */
        return r;
    }
};

int main()
{
    Solution s;
    //3,9,20,null,null,15,7
    // [1, 2, 3, 4, null, null, 5]
    
    TreeNode* r = new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)));
    TreeNode* r1 = new TreeNode(1);
    TreeNode* r2 = new TreeNode(1, new TreeNode(2, nullptr, new TreeNode(4)), new TreeNode(3, nullptr, new TreeNode(5)));
    vector<vector<int>> v = s.zigzagLevelOrder(r2);
    for (const vector<int>& vv : v)
    {
        for (int i : vv)
        {
            cout << i << ' ';
        }
        cout << endl;
    }
    return 0;
}