#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class TreeFromPreorderInorder {

    unordered_map<int, pair<int, vector<int>>> m;
    int i = 0;
    
    TreeNode* recursively_construct_subtree(unordered_map<int, int>& m, vector<int>& preorder, vector<int>& inorder, int l, int r)
    {
        if (l > r) return nullptr;

        int v = preorder[i++];
       //cout << v << endl;
        TreeNode* root = new TreeNode(v);
        root->left = recursively_construct_subtree(m, preorder, inorder, l, m[v]-1);
        root->right = recursively_construct_subtree(m, preorder, inorder, m[v]+1, r);
        return root;
    }
    /*
    TreeNode* construct_b_tree(const vector<int>& in, const vector<int>& pr, int l, int r)
    {
        if (l > r)
        {
            return nullptr;
        }

        pair<int, vector<int>>& p_val = m[pr[i]];
        int val_i = p_val.second[p_val.first];
        if (p_val.second.size() > 1)
            ++p_val.first;
        //int val_i = m[pr[pr_i]];

        TreeNode* root = new TreeNode(pr[i]);
        ++i;

        root->left = construct_b_tree(in, pr, l, val_i - 1);
        root->right = construct_b_tree(in, pr, val_i + 1, r);

        return root;
    }
    */
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        
        unordered_map<int, int> m;
        for (int i = 0; i < inorder.size(); ++i)
        {
            m[inorder[i]] = i;
        }
        
        int l = 0;
        int r = preorder.size() - 1;
        TreeNode* t = recursively_construct_subtree(m, preorder, inorder, 0, inorder.size() - 1);
        
        return t;
        // return recursively_construct_subtree(m, preorder, inorder, l, r);
    }
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
    int pr_i = 0;
    
    string inorder(TreeNode* r)
    {
        if (!r)
        {
            return "";
        }

        string s = "";
        s = inorder(r->left);
        s += ";" + to_string(r->val) + ";";
        s += inorder(r->right);
        return s;
    }

    string preorder(TreeNode* r)
    {
        if (!r)
        {
            return "";
        }

        string s = ";" + to_string(r->val) + ";";

        s += preorder(r->left);
        s += preorder(r->right);
        return s;
    }

    vector<int> traversal_to_vec(const string& d)
    {
        vector<int> v;

        for (int i = 0; i < d.size(); ++i)
        {
            if (d[i] != ';')
            {
                int j = i + 1;
                while (j < d.size() && d[j] != ';')
                {
                    ++j;
                }
                string ss = d.substr(i, j - i);
                //   cout << ss << endl;
                v.push_back(stoi(ss));
            }
        }
        return v;
    }

public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) return "";
        string s = inorder(root) + ":" + preorder(root);
        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;
        TreeFromPreorderInorder s;
        vector<int> in;
        vector<int> pr;

        auto p_split = find(data.cbegin(), data.cend(), ':');
        in = traversal_to_vec(string(data.cbegin(), p_split));
        pr = traversal_to_vec(string(p_split + 1, data.cend()));

       // TreeNode* t = s.buildTree(in, pr);
       
        return s.buildTree(pr, in);
    }
};

int main()
{
    Codec c;
    /*
    TreeNode* r1 = new TreeNode(1);
    r1->left = new TreeNode(-2);
    r1->right = new TreeNode(-2);
    r1->right->left = new TreeNode(-2);
    r1->right->right = new TreeNode(5);
    */
    TreeNode* r1 = new TreeNode(1);
    r1->left = new TreeNode(2);
    r1->right = new TreeNode(3);
    r1->right->left = new TreeNode(4);
    r1->right->right = new TreeNode(5);
    TreeNode* r2 = new TreeNode(1);
    r2->left = new TreeNode(2);
    r2->right = new TreeNode(2);
   // c.deserialize(c.serialize(nullptr));
    TreeNode* tr = c.deserialize(c.serialize(r1));

    return 0;
}