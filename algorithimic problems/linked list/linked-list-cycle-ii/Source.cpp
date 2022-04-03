#include <iostream>
using namespace std;


 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

/*
The runtime of the algorithm is O(n^2), but the memory is O(1).
We use the distances from head node to the current node and on
each step we compare the distance from head to the previous node  (c)
to the distance from head to the current node (l), if the former is greater or equal- we found the cycle starting node
*/
class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        if (head == nullptr) return nullptr;

        ListNode* p = head->next;
        int c = 0;
        while (p)
        {
            int l = 0;
            ListNode* h = head;
            while (h != p)
            {
                h = h->next;
                ++l;
            }
            if (l <= c)
            {
                return p;
            }
            c = l;
            p = p->next;
        }
        return nullptr;
    }
};

int main()
{
    Solution s;

    ListNode* l0 = new ListNode(1);
    ListNode* l1 = new ListNode(3);
    ListNode* l2 = new ListNode(2);
    ListNode* l3 = new ListNode(0);
    ListNode* l4 = new ListNode(4);

    l0->next = l1;
    l1->next = l2;
    l2->next = l3;
    l3->next = l4;
    l4->next = l2;
    
    cout << s.detectCycle(l0)->val << endl;

    return 0;
}