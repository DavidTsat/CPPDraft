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
        if (r - l <= 1)
        {
            if (l == 0)
                insert(root, n[l]);
            return;
        }

        int i = l + (r - l) / 2;

        insert(root, n[i]);

        f(root, n, l, i);
        f(root, n, i, r);
    }

public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {

        TreeNode* r = nullptr;
        f(r, nums, 0, nums.size());

        return r;
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