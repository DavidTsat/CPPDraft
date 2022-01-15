#include <vector>
#include <iterator>
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

public:
    void recoverTree(TreeNode* root) {
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
};

int main()
{
    Solution s;
    TreeNode* r = new TreeNode(146, new TreeNode(71, new TreeNode(55, new TreeNode(321, new TreeNode(-33, nullptr, nullptr), nullptr), nullptr),nullptr), new TreeNode(-13, new TreeNode(231, nullptr, nullptr), new TreeNode(399, nullptr, nullptr)));
    s.recoverTree(r);
    return 0;
}