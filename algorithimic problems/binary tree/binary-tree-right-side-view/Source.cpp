#include <vector>
#include <iostream>
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
    vector<int> r;
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
            r.push_back(t.first->val);
        }
        else
        {
            r[t.second - 1] = t.first->val;
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
    vector<int> rightSideView(TreeNode* root) {
        if (!root) return {};

        queue<pair<TreeNode*, int>> q;
        q.push({ root, 1 });

        bfs(q);

        return r;
    }
};