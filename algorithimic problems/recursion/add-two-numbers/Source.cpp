/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
    void sol(ListNode* l1, ListNode* l2, ListNode* r, int n) {
        if (l1 == nullptr && l2 == nullptr)
        {
            if (n)
            {
                r->next = new ListNode(n);
            }
            return;

        }

        if (l1->next == nullptr && l2->next != nullptr)
        {
            l1->next = new ListNode(0);
        }
        if (l2->next == nullptr && l1->next != nullptr)
        {
            l2->next = new ListNode(0);
        }

        int c = l1->val + l2->val + n;
        int m = c % 10;
        r->val = m;

        l1 = l1->next;
        l2 = l2->next;

        if (l1 != nullptr && l2 != nullptr)
        {
            r->next = new ListNode();
            r = r->next;
        }

        sol(l1, l2, r, c >= 10);

    }

public:

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* res = new ListNode();
        sol(l1, l2, res, 0);
        return res;
    }

    /*
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int hist = 0;
//        ListNode* res = new ListNode();
//        bool init = false;
        ListNode* head = nullptr;
        ListNode* curr = head;

        while (l1 || l2) {
            int i_sum = 0;
            if (l1) {
                i_sum += l1->val;
                l1 = l1->next;
            }
            if (l2) {
                i_sum += l2->val;
                l2 = l2->next;
            }
            if (hist) {
                i_sum += hist;
                --hist;
            }
            if (i_sum >= 10) {
                ++hist;
                i_sum %= 10;
            }

            ListNode* t = new ListNode(i_sum);
            if (!head) {
                head = t;
                curr = head;
                continue;
            }
            curr->next = t;
            curr = t;
            //curr = t;
            //t->next = curr;
            //curr = t;
        }
        if (hist) {
            curr->next = new ListNode(hist);
        }
        return head;
    }
    */
};