/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    TreeNode* lca_node = nullptr;
    int lca_level = 1;
    void bfs(queue<pair<TreeNode*, int>>& qu, const TreeNode* p, const TreeNode* q, bool& pb, bool& pq)
    {
        if (qu.empty()) return;

        pair<TreeNode*, int> r = qu.front();
        qu.pop();
        if (r.first == p)
            pb = true;
        if (r.first == q)
            pq = true;

        if (r.first->left)
            qu.push({ r.first->left, r.second + 1 });
        if (r.first->right)
            qu.push({ r.first->right, r.second + 1 });

        bfs(qu, p, q, pb, pq);
    }

    void bfs(queue<pair<TreeNode*, int>>& qu, const TreeNode* p, const TreeNode* q)
    {
        if (qu.empty()) return;

        pair<TreeNode*, int> r = qu.front();
        qu.pop();

        if (lca_node && r.second > lca_level)
        {
            queue<pair<TreeNode*, int>> qu2;
            bool pb = false;
            bool pq = false;
            qu2.push(r);
            bfs(qu2, p, q, pb, pq);
            if (pb && pq)
            {
                if (r.second >= lca_level)
                {
                    lca_level = r.second;
                    lca_node = r.first;
                }
            }
        }

        if (r.first->left)
            qu.push({ r.first->left, r.second + 1 });
        if (r.first->right)
            qu.push({ r.first->right, r.second + 1 });
        bfs(qu, p, q);
    }

    TreeNode* perebor(TreeNode* root, const TreeNode* p, const TreeNode* q)
    {
        queue<pair<TreeNode*, int>> qu;
        lca_node = root;
        qu.push({ root, 1 });

        bfs(qu, p, q);
        return lca_node;
    }


    void dfs(TreeNode* r, const TreeNode* p, const TreeNode* q, bool& bp, bool& bq)
    {
        if (r == nullptr || bp && bq) return;

        if (r == p)
            bp = true;
        if (r == q)
            bq = true;
        dfs(r->left, p, q, bp, bq);
        dfs(r->right, p, q, bp, bq);
    }

    void f(TreeNode* r, const TreeNode* p, const TreeNode* q)
    {
        if (r == nullptr || lca_node) return;

        f(r->left, p, q);
        f(r->right, p, q);

        bool bp = false;
        bool bq = false;
        dfs(r, p, q, bp, bq);
        if (bp && bq && !lca_node)
        {
            lca_node = r;
        }
    }

    void dfs(TreeNode* r, const TreeNode* pq, vector<TreeNode*>& v)
    {
        if (r == nullptr || !v.empty() && v[v.size() - 1] == pq) return;

        v.push_back(r);

        dfs(r->left, pq, v);
        dfs(r->right, pq, v);
    }

    void f2(TreeNode* r, const TreeNode* p, const TreeNode* q)
    {
        if (r == nullptr) return;

        vector<TreeNode*> vp;
        vector<TreeNode*> vq;

        dfs(r, p, vp);
        vq.reserve(vp.size());
        dfs(r, q, vq);

        int i = vp.size() <= vq.size() ? vp.size() - 1 : vq.size() - 1;

        while (vp[i] != vq[i])
            --i;

        lca_node = vp[i];

        /*
        for (auto ip = vp.crbegin(); ip != vp.crend(); ++ip)
        {
            for (auto iq = vq.crbegin(); iq != vq.crend(); ++iq)
            {
                if (*ip == *iq)
                {
                    lca_node = *ip;
                    return;
                }
            }
        }
        */
    }

public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        f(root, p, q);
        return lca_node;
    }
};