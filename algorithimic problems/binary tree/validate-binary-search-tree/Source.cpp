#include <climits>
#include <algorithm>
#include <numeric>

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

    void traverse_subtree(TreeNode* root, long long& min_, long long& max_)
    {
        if (root == nullptr)
        {
            return;
        }

        traverse_subtree(root->left, min_, max_);
        traverse_subtree(root->right, min_, max_);

        min_ = min(min_, (long long)root->val);
        max_ = max(max_, (long long)root->val);
    }
public:
    void isValidBST(TreeNode* root, bool& b) {
        if (root == nullptr) return;

        long long min_ = LLONG_MAX;
        long long max_ = LLONG_MIN;

        traverse_subtree(root->left, min_, max_);
        long long left_min = min_;
        long long left_max = max_;

        min_ = LLONG_MAX;
        max_ = LLONG_MIN;
        traverse_subtree(root->right, min_, max_);
        long long right_min = min_;
        long long right_max = max_;

        if (left_max >= root->val || right_min <= root->val)
        {
            b = false;
            return;
        }

        isValidBST(root->left, b);
        isValidBST(root->right, b);
    }

    bool isValidBST(TreeNode* root)
    {
        bool b = true;
        if (root == nullptr)
        {
            return true;
        }

        isValidBST(root, b);
        return b;
    }
};

int main() {

    return 0;
}