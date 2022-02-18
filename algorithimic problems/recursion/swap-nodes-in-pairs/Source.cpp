#include <iostream>
#include <algorithm>

using namespace std;

 // Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 
class Solution {
    void swap_pairs(ListNode* p, ListNode* a, ListNode* b)
    {
        if (b == nullptr) return;

        a->next = b->next;
        b->next = a;
        if (p != nullptr)
        {
            p->next = b;
        }
        swap_pairs(a, a->next, a->next ? a->next->next : nullptr);
    }
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr) return head;

        ListNode* h = head->next ? head->next : head;

        swap_pairs(nullptr, head, head->next);
        return h;
    }
};

int main()
{
    ListNode* ln = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, nullptr))));
    
    auto print_ln = [](ListNode* l) {while (l) { cout << l->val << ' '; l = l->next; } cout << endl; };
    print_ln(ln);
    
    Solution s;
    
    ln = s.swapPairs(ln);
    print_ln(ln);

    return 0;
}