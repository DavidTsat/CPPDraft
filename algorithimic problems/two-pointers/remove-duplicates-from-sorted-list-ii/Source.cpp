#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 
class Solution {
public:
    /*
    ListNode* deleteDuplicates(ListNode* head)
    {
        ListNode* curr = head;
        ListNode* prev = head;
        ListNode* prev_prev = head;

        while (curr)
        {
            curr = curr->next;
            if (curr && curr->val == prev->val)
            {
                while (curr && curr->val == prev->val)
                {
                    prev->next = curr->next;
                    delete curr;
                    curr = prev->next;
                }
                
                if (head->val == prev->val)
                    head = curr;

                if (prev_prev)
                    prev_prev->next = curr;
                delete prev;
            }
            
            if (curr && curr->next && curr->next->val != curr->val)
                prev_prev = curr;

            prev = curr;
        }

        return head;
    }
    */
    ListNode* deleteDuplicates(ListNode* head)
    {
        if (!head) return head;

        ListNode* curr = head;
        ListNode* prev = head;
        ListNode* prev_prev = head;

        while (curr && curr->next)
        {
            curr = curr->next;
            bool b = false;
            while (curr && curr->val == prev->val)
            {
                prev->next = curr->next;
                delete curr;
                curr = prev->next;
                b = true;
            }
            if (b)
            {
                if (head->val == prev->val)
                    head = curr;

                if (prev == prev_prev)
                    prev_prev = curr;
                else
                    prev_prev->next = curr;

                delete prev;
            }
            else
                prev_prev = prev;
            prev = curr;
        }

        return head;
    }
};

int main()
{
    Solution s;

  //  ListNode* l1 = new ListNode(1, new ListNode(1, new ListNode(1, new ListNode(2, new ListNode(3, nullptr)))));
    
 //   ListNode* l1 = new ListNode(1, new ListNode(1, nullptr));
  //  ListNode* l1 = new ListNode(1, new ListNode(1, nullptr));

   // ListNode* l1 = new ListNode(1, new ListNode(1, new ListNode(2, new ListNode(2, new ListNode(2, nullptr)))));

    ListNode* l1 = new ListNode(1, new ListNode(1, new ListNode(2, new ListNode(2, nullptr))));
  // [1, 2, 3, 3, 4, 4, 5]

 //   ListNode* l1 = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(3, new ListNode(3, new ListNode(4, new ListNode(4, new ListNode(5, nullptr))))))));

    for (auto l = l1; l; l = l->next)
    {
        cout << l->val << ' ';
    }
    cout << endl;

    auto ll1 = s.deleteDuplicates(l1);

    for (auto l = ll1; l; l = l->next)
    {
        cout << l->val << ' ';
    }
    cout << endl;
    return 0;
}