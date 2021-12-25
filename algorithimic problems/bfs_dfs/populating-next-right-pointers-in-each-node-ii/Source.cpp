#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};


/*
We traverse the tree in level order (BFS), while keeping a queue of pairs of nodes and their corressponding
levels and second - argument n is the previous node for which we should populate next pointer to the current
node of the queue front
*/
class Solution {

    void level_order_connect(queue<pair<Node*, int>>& q, pair<Node*, int> n)
    {
        if (q.empty())
            return;

        pair<Node*, int> r = q.front();
        q.pop();

        if (r.first->left) q.push({ r.first->left, r.second + 1 });
        if (r.first->right) q.push({ r.first->right, r.second + 1 });

        cout << "level: " << r.second << ' ' << r.first->val << endl;
        if (n.second == r.second)
        {
            n.first->next = r.first;
        }

        level_order_connect(q, r);
    }

public:
    Node* connect(Node* root) {
        if (root == NULL)
            return root;

        queue<pair<Node*, int>> q;
        q.push({ root, 0 });

        level_order_connect(q, { root, -1 });
        return root;
    }
};

int main()
{
    //{ 1, 2, 3, 4, 5, null, 7 }
    Node* r = new Node(1, new Node(2, new Node(4), new Node(5), NULL), new Node(3, NULL, new Node(7), NULL), NULL);
    Solution s;
    s.connect(r);

    return 0;
}