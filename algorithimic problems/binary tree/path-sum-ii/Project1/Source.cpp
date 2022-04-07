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
     vector<vector<int>> rv;
     void f(TreeNode* r, int t, vector<int>& v)
     {
         if (!r) return;

         v.push_back(r->val);

         f(r->left, t, v);
         f(r->right, t, v);

         if (accumulate(v.cbegin(), v.cend(), 0) == t && !r->left && !r->right)
             rv.push_back(v);

         v.pop_back();
     }

 public:
     vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
         vector<int> v;
         f(root, targetSum, v);
         return rv;
     }
 };


int main() {

    return 0;
}