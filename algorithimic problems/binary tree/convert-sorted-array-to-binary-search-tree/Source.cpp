#include <iostream>
#include <vector>

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
    void insert(TreeNode*& r, int v)
    {
        if (r == nullptr)
        {
            // cout << v << endl;
            r = new TreeNode(v);
            return;
        }
        if (v >= r->val)
        {
            insert(r->right, v);
        }
        else
        {
            insert(r->left, v);
        }
    }


    void f(TreeNode*& root, const vector<int>& n, int l, int r)
    {
        if (l >= r)
        {
            return;
        }

        int i = (r + l) / 2;

        insert(root, n[i]);

        f(root, n, l, i);
        f(root, n, i + 1, r);
    }
    TreeNode* f1(const vector<int>& nums)
    {
        TreeNode* r = nullptr;
        f(r, nums, 0, nums.size());

        return r;
    }

    TreeNode* f2(const vector<int>& nums, int l, int r) // nums is sorted
    {
        if (l == r)
        {
            return nullptr;
            // return new TreeNode(nums[l]);
        }

        int i = (l + r) / 2;
        TreeNode* root = new TreeNode(nums[i]);

        root->left = f2(nums, l, i);
        root->right = f2(nums, i + 1, r);

        return root;
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {

        //     return f2(nums, 0, nums.size());

        return f1(nums);
    }
};
int main()
{
   // int c = 1 / 1;
    vector<int> v{ 0,1,2,3,4,5,6,7,8 };
    vector<int> v1{ 0,1 };
    Solution s;
    TreeNode* t = s.sortedArrayToBST(v);

    return 0;
}