#include <vector>
#include <list>
#include <numeric>
#include <iostream>

using namespace std;

 struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {
    void path_sum(TreeNode* root, vector<vector<int>>& vv, list<int> l, const int targetSum)
    {
        if (root == nullptr)
        {
            return;
        }

        l.push_back(root->val);

        path_sum(root->left, vv, l, targetSum);
        path_sum(root->right, vv, l, targetSum);

        if (root->left == nullptr && root->right == nullptr)
        {
            if (accumulate(l.cbegin(), l.cend(), 0) == targetSum)
            {
                vv.push_back(vector<int>(l.cbegin(), l.cend()));
            }
        }
        l.pop_back();
    }
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> v;
        path_sum(root, v, {}, targetSum);
        return v;
    }
};


int main() {

    return 0;
}