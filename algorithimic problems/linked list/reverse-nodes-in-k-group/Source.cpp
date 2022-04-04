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
    void reverse_l(ListNode* b, ListNode* e)
    {

    }
public:
    ListNode* reverseKGroup(ListNode* head, int kk) {
        if (head == nullptr) return head;

        ListNode* p = head;
        ListNode* c = head->next;
        ListNode* b = head;
        ListNode* l = nullptr;

        int k = kk - 1;
        bool b_e = true;
        bool b_f = true;

        while (c)
        {
            ListNode* c_ = c;
            int k_ = k;
            while (c_ && k_ > 0)
            {
                c_ = c_->next;
                --k_;
            }
            if (k_ != 0) break;

            ListNode* q = c;

            if (k > 0)
            {
                ListNode* n = c->next;
                c->next = p;
                p = c;
                c = n;
                --k;
            }
           
            if (k == 0)
            //else
            {
                if (l)
                {
                    l->next = p;
                }
                l = b;
                if (b)
                    b->next = c;
                b = c;
                p = c;
                if (c)
                    c = c->next;
                k = kk - 1;
                if (b_e)
                {
                    b_e = false;
                    head = q;
                }
            }


            /*
            if (k > 0)
            {
                ListNode* n = c->next;
                c->next = p;
                p = c;
                c = n;
                --k;
            }
            else
            {
                k = kk - 1;
                c->next = p;
              //  p = c;
            //    c = c->next;
            }
            if (b && k == 0)
            {
                b = false;
                head = q;
            }
            */
        }
        return head;
    }
};

int main()
{
    Solution s;
    ListNode* l1 = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5, nullptr)))));
    ListNode* l2 = new ListNode(1, new ListNode(2, nullptr));

    auto pr = [](ListNode* l) {while (l) { cout << l->val << ' '; l = l->next; } cout << endl; };
    pr(l2);
    l2 = s.reverseKGroup(l2, 3);
    pr(l2);
    return 0;
}