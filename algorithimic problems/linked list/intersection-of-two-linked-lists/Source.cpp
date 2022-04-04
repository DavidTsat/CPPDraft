/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    ListNode* getIntersectionNodeModif(ListNode* headA, ListNode* headB) {
        if (headA == nullptr || headB == nullptr) return nullptr;

        ListNode* l = nullptr;
        ListNode* p = headA->next;
        if (p == nullptr) l = headA;
        else
        {
            while (p)
            {
                headA->next = nullptr;
                p = p->next;
            }
            l = headA;
        }
        if (l == headB) return l;
        p = headB->next;
        while (p)
        {
            headB = headB->next;
            p = p->next;
        }
        if (headB == l) return l;
        return nullptr;
    }

public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode* hA = headA;
        ListNode* hB = headB;
        if (headA == nullptr || headB == nullptr) return nullptr;
        ListNode* p = headA->next;
        int l1 = 1;
        while (p)
        {
            ++l1;
            headA = headA->next;
            p = p->next;
        }
        p = headB->next;
        int l2 = 1;
        while (p)
        {
            ++l2;
            headB = headB->next;
            p = p->next;
        }
        if (headA != headB) return nullptr;
        if (l1 >= l2)
        {
            l1 = l1 - l2;
            while (l1)
            {
                hA = hA->next;
                --l1;
            }
            //hA == hB
            while (hA != hB)
            {
                hA = hA->next;
                hB = hB->next;
            }
            return hA;
        }
        else
        {
            l2 = l2 - l1;
            while (l2)
            {
                hB = hB->next;
                --l2;
            }
            //hA == hB
            while (hA != hB)
            {
                hA = hA->next;
                hB = hB->next;
            }
            return hA;
        }
        return nullptr;
    }
};