#include <iostream>
#include <vector>

using namespace std;
/*
* 
Найти K - й наименьший элемент в бинарном дереве поиска
Индексация начинается с 1.
Пример 1.
        3       kthSmallest(1) == 1
       / \      kthSmallest(2) == 2
      1   4
       \
        2
Пример 2.
        5       kthSmallest(3) == 3
       / \
      3   6
     / \
    2   4
   /
  1
Пример 3.
        7       kthSmallest(4) == 7
       / \      kthSmallest(7) == 18
      4   14
     /   /  \
    2   10   18
   /
  0
*
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    int c;

    void f(TreeNode* r, int k, int& i)
    {
        if (r == nullptr)
        {
            return;
        }

        f(r->left, k, i);
        if (k == i)
            c = r->val;

        ++i;
        f(r->right, k, i);
    }

public:
    int kthSmallest(TreeNode* root, int k) {
        int i = 1;
        f(root, k, i);
        return c;
    }
};

int main()
{
    Solution s;
    //3,1,4,null,2
    //5,3,6,2,4,null,null,1
    TreeNode* r1 = new TreeNode(3, new TreeNode(1, nullptr, new TreeNode(2)), new TreeNode(4)); //1-1
    TreeNode* r2 = new TreeNode(5, new TreeNode(3, new TreeNode(2, new TreeNode(1), nullptr), new TreeNode(4)), new TreeNode(6)); //3-3
    TreeNode* r3 = new TreeNode(7, new TreeNode(4, new TreeNode(2, new TreeNode(0), nullptr), nullptr), new TreeNode(14, new TreeNode(10), new TreeNode(18)));

    cout << std::boolalpha << (s.kthSmallest(r1, 1) == 1)  << endl;
    cout << std::boolalpha << (s.kthSmallest(r1, 2) == 2)  << endl;

    cout << std::boolalpha << (s.kthSmallest(r2, 3) == 3)  << endl;

    cout << std::boolalpha << (s.kthSmallest(r3, 4) == 7)  << endl;
    cout << std::boolalpha << (s.kthSmallest(r3, 7) == 18) << endl;
	return 0;
}