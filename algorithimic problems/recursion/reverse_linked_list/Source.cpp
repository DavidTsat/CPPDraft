struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
    void reverse_list_iterative(ListNode* head, ListNode*& prev)
    {
        if (!head) return;

        ListNode* h = head->next;
        head->next = prev;
        prev = head;
        head = h;
        reverse_list_iterative(head, prev);
        return;
    }

    ListNode* reverse_list_iterative(ListNode* head)
    {
        if (!head) return nullptr;
        ListNode* curr_ = head;
        ListNode* next_ = head->next;
        ListNode* prev = nullptr;
        while (next_) {
            ListNode* temp = next_->next;
            next_->next = curr_;
            curr_->next = prev;
            prev = curr_;
            curr_ = next_;
            next_ = temp;
        }
        return curr_;
    }
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* new_head = nullptr;
        reverse_list_iterative(head, new_head);
        return new_head;
    }
};

//examples
//[1,2,3,4,5] -> [5,4,3,2,1]
//[1,2] -> [2,1]
//[] -> []