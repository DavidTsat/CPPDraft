#include <iostream>
#include <vector>
#include <unordered_map>

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
     TreeNode* f(TreeNode*& r, vector<int>& pr, vector<int>& in, int i, int j, int& k)
     {
         if (i >= pr.size() || j >= in.size()) return r;
         k = i;
         if (pr[i] == in[j])
         {
             r->left = new TreeNode(pr[i]);
             ++j;
             ++i;
             return r;
         }

         r->left = new TreeNode(pr[i]);
         f(r->left, pr, in, ++i, j, k);
         r->right = new TreeNode(pr[i]);
         f(r->right, pr, in, i, j, k);
         return r;
     }

     TreeNode* ff(TreeNode* r, vector<int>& pr, vector<int>& in, int& i, int& j)
     {
         //if (i >= pr.size()|| j >= in.size()) return r;
         int k = 0;
         f(r, pr, in, i, j, k);
         if (i >= pr.size() || j >= in.size()) return r;
         f(r, pr, in, i, j, k);
         r->right = new TreeNode(pr[k]);
         ff(r->right, pr, in, ++i, j += k);
         return r;
     }
     TreeNode* ffff(vector<int>& preorder, vector<int>& inorder)
     {
         int i = 1;
         int j = 0;

         TreeNode* root = new TreeNode(preorder[0]);
         TreeNode* r = root;



         while (i < preorder.size())
         {
             vector<TreeNode*> v;
             bool b = false;
             for (int ii = i; ii < preorder.size(); ++ii)
             {
                 if (preorder[ii] == inorder[j])
                 {
                     b = true;
                     break;
                 }
             }
             if (!b)
             {
                 r->right = new TreeNode(preorder[i]);
                 ++i;
                 continue;
             }
             while (b && i < preorder.size() && j < inorder.size() && preorder[i] != inorder[j])
             {
                 v.push_back(r);
                 r->left = new TreeNode(preorder[i]);
                 r = r->left;
                 ++i;
             }
             if (i < preorder.size() && j < inorder.size() && preorder[i] == inorder[j])
             {
                 v.push_back(r);
                 r->left = new TreeNode(preorder[i]);
                 ++i;
             }

             for (int p = v.size() - 1; p >= 0 and (i < preorder.size() && j < inorder.size()); --p)
             {
                 v[p]->right = new TreeNode(preorder[i]);
                 ++i;
                 r = v[p]->right;
             }
             while (!v.empty() && j < inorder.size() && inorder[j] != v[0]->val)
             {
                 ++j;
             }
             if (!v.empty() && j < inorder.size() && inorder[j] == v[0]->val) ++j;
             //     r = v[0];
         }


         // ff(r, preorder, inorder, i, j);

          //TreeNode* root = nullptr;
      //    f(root, preorder, inorder, i, j);

          /*
          while (i < preorder.size()-1)
          {
              f(root, preorder, inorder, i, j);
              ++i;
              root->right = new TreeNode(preorder[i]);
              root = root->right;
              j += 2;
          }
          */
         return root;
     }

     int i = 0;
     TreeNode* recursively_construct_subtree(unordered_map<int, int>& m, vector<int>& preorder, int l, int r)
     {
         if (l > r) return nullptr;
         
         int v = preorder[i++];
         TreeNode* root = new TreeNode(v);
         root->left = recursively_construct_subtree(m, preorder, l, m[v]-1);
         root->right = recursively_construct_subtree(m, preorder, m[v]+1, r);
         return root;
     }
 public:
     TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
         unordered_map<int, int> m;
         for (int i = 0; i < inorder.size(); ++i)
         {
             m[inorder[i]] = i;
         }

         int l = 0;
         int r = preorder.size() - 1;
         return recursively_construct_subtree(m, preorder, l, r);
     }
 };

 
 class SolutionPostIn {
     int i;

     TreeNode* recursively_construct_subtree(unordered_map<int, int>& m, vector<int>& po, int l, int r)
     {
         if (l > r )
         {
             return nullptr;
         }
         cout << po[i] << endl;
         int v = po[i--];
         TreeNode* root = new TreeNode(v);

         root->left = recursively_construct_subtree(m, po, l, m[v]-1);
         root->right = recursively_construct_subtree(m, po, m[v], i-1);
         return root;
     }
 public:
     TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
         unordered_map<int, int> m;
         for (int i = 0; i < inorder.size(); ++i)
         {
             m[inorder[i]] = i;
         }

         int l = 0;
         int r = postorder.size() - 1;
         i = postorder.size() - 1;
         return recursively_construct_subtree(m, postorder, l, r);
     }
 };


int main()
{
    SolutionPostIn s;

    vector<int> pr1{ 3,9,20,15,7 };
    vector<int> in1{ 9,3,15,20,7 };
    vector<int> po1{ 9,15,7,20,3 };

    vector<int> pr2{ 30,20,15,5,18,25,40,35,50,45,60 };
    vector<int> in2{ 5,15,18,20,25,30,35,40,45,50,60};

    vector<int> pr3{ 1,2 };
    vector<int> in3{ 2, 1 };

    TreeNode* r = s.buildTree(in1, po1);

	return 0;
}