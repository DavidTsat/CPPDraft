#include <vector>
#include <iterator>
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
     vector<TreeNode*> v;

     void sorted_traversal(TreeNode* root)
     {
         if (root == nullptr)
         {
             return;
         }
         sorted_traversal(root->left);
         v.push_back(root);
         sorted_traversal(root->right);
     }

     void recoverTreeVec(TreeNode* root) // O(n) space
     {
         sorted_traversal(root);
         if (v.empty()) return;

         auto it = v.begin();
         auto it2 = next(it);

         for (; it2 != v.end(); ++it2)
         {
             if ((*it2)->val < (*it)->val)
             {
                 auto it2_ = next(it2);
                 while (it2_ != v.end())
                 {
                     if (((*it2_)->val < (*it2)->val))
                     {
                         it2 = it2_;
                     }
                     ++it2_;
                 }
                 swap((*it)->val, (*it2)->val);
                 break;
             }
             else
             {
                 ++it;
             }
         }
     }

     void recoverTreeOpt(TreeNode* root, TreeNode*& prev, TreeNode*& max_, TreeNode*& min_)
     {
         if (root == nullptr)
         {
             return;
         }

         recoverTreeOpt(root->left, prev, max_, min_);

         if (prev && max_ == nullptr && prev->val > root->val)
         {
             max_ = prev;
             min_ = root;
         }

         if (min_ && root->val < min_->val)
         {
             min_ = root;
         }

         prev = root;
         recoverTreeOpt(root->right, prev, max_, min_);
     }

 public:
     void recoverTree(TreeNode* root) {
         TreeNode* max_ = nullptr;
         TreeNode* min_ = nullptr;
         TreeNode* prev = nullptr;
         recoverTreeOpt(root, prev, max_, min_);

         swap(max_->val, min_->val);

         // debug
         sorted_traversal(root);
         for (TreeNode* t : v)
         {
             cout << t->val << ' ';
         }
         cout << endl;
     }
 };


int main()
{
    Solution s;
    TreeNode* r1 = new TreeNode(146, new TreeNode(71, new TreeNode(55, new TreeNode(321, new TreeNode(-33, nullptr, nullptr), nullptr), nullptr),nullptr), new TreeNode(-13, new TreeNode(231, nullptr, nullptr), new TreeNode(399, nullptr, nullptr)));
    TreeNode* r2 = new TreeNode(3, nullptr, new TreeNode(2, nullptr, new TreeNode(1, nullptr, nullptr)));
    TreeNode* r3 = new TreeNode(1, nullptr, new TreeNode(3, nullptr, new TreeNode(2, nullptr, nullptr)));
    s.recoverTree(r1);
    return 0;
}