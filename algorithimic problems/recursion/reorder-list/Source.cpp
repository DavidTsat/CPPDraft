#include <iostream>

using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 
class Solution {
    void f(ListNode* b, ListNode* c)
    {
        if (b == c || c == nullptr || c->next == nullptr)
        {
            return;
        }
        if (c->next->next == nullptr)
        {
            c->next->next = b->next;
            b->next = c->next;
            b = b->next->next;
            c->next = nullptr;
            f(b, b->next);
        }
        else
        {
            f(b, c->next);
        }
    }

public:
    void reorderList(ListNode* head) {
        f(head, head->next);
    }
};

int main()
{
    Solution s;
    ListNode* l1 = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5, nullptr)))));
    ListNode* l2 = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, nullptr))));
    ListNode* l3 = new ListNode(1, new ListNode(2, new ListNode(3, nullptr)));

    auto print_f = [](ListNode* l) {while (l) { cout << l->val << ' '; l = l->next; } cout << endl; };

    for (ListNode* h : { l1, l2, l3 })
    {
        print_f(h);
    }
    
    for (ListNode* h : { l1, l2, l3 })
    {
        s.reorderList(h);
    }

    cout << endl;
    for (ListNode* h : { l1, l2, l3 })
    {
        print_f(h);
    }
    return 0;
}