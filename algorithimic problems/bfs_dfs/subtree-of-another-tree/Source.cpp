/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    void areSameBTree(TreeNode* r, TreeNode* s, bool& b)
    {
        if (r == nullptr)
        {
            b &= s == nullptr;
            return;
        }
        if (s == nullptr)
        {
            b &= r == nullptr;
            return;
        }

        areSameBTree(r->left, s->left, b);
        areSameBTree(r->right, s->right, b);

        b &= r->val == s->val;
    }

    void isSubtreeCheck(TreeNode* root, TreeNode* subRoot, bool& b)
    {
        if (root == nullptr)
        {
            b |= subRoot == nullptr;
            return;
        }

        isSubtreeCheck(root->left, subRoot, b);
        isSubtreeCheck(root->right, subRoot, b);

        bool bb = true;
        areSameBTree(root, subRoot, bb);
        b |= bb;
    }

public:

    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        bool b = false;

        isSubtreeCheck(root, subRoot, b);
        return b;
    }
};