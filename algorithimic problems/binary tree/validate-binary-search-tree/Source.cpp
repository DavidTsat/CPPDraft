#include <climits>
#include <algorithm>
#include <numeric>
#include <iostream>

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
     void dfs(TreeNode* r, long long& min_, long long& max_)
     {
         if (r == nullptr) return;

         min_ = min(min_, (long long)r->val);
         max_ = max(max_, (long long)r->val);

         dfs(r->left, min_, max_);
         dfs(r->right, min_, max_);
     }

 public:
     bool isValidBST(TreeNode* root)
     {
         if (root == nullptr) return true;

         long long min_ = LLONG_MAX;
         long long max_ = LLONG_MIN;

         dfs(root->left, min_, max_);

         if (max_ >= root->val) return false;

         min_ = LLONG_MAX;
         max_ = LLONG_MIN;

         dfs(root->right, min_, max_);

         if (min_ <= root->val) return false;

         return isValidBST(root->left) && isValidBST(root->right);
     }
 };

int main() {
    Solution s;
    TreeNode* r = new TreeNode(2, new TreeNode(1), new TreeNode(3));
    TreeNode* r1 = new TreeNode(2147483647);
    cout << s.isValidBST(r1) << endl;
    return 0;
}