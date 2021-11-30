#include <vector>
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
public:

    ListNode* mergeKLists(vector<ListNode*>& lists) {

        ListNode* l = new ListNode();
        ListNode* ll = l;
        ListNode* l_prev = l;
        bool is_empty = true;

        while (true) {
            int min_;
            int min_index;
            bool assigned = false;
            bool done_cond = true;
            for (int i = 0; i < lists.size(); ++i) {
                if (lists[i]) {
                    done_cond = false;
                    if (!assigned) {
                        min_ = lists[i]->val;
                        min_index = i;
                        assigned = true;
                    }
                    else if (lists[i]->val < min_) {
                        min_ = lists[i]->val;
                        min_index = i;
                    }
                }
            }
            if (done_cond) {
                break;
            }
            if (assigned) {
                l->val = min_;
                l_prev = l;
                l->next = new ListNode();
                lists[min_index] = lists[min_index]->next;
                l = l->next;
                is_empty = false;
            }

        }

        // delete l;
        if (!is_empty) {
            l_prev->next = nullptr;
            return ll;
        }
        else {
            return nullptr;
        }

    }
};

int main() {
    //[[1,4,5],[1,3,4],[2,6]]
    ListNode* l1 = new ListNode(1, new ListNode(4, new ListNode(5)));
    ListNode* l2 = new ListNode(1, new ListNode(3, new ListNode(4)));
    ListNode* l3 = new ListNode(2, new ListNode(6));
    
    Solution s;
    vector<ListNode*> v;
    v.push_back(l1);
    v.push_back(l2);
    v.push_back(l3);

    ListNode* ll = s.mergeKLists(v);

    while (ll)
    {
        cout << ll->val << ' ';
        ll = ll->next;
    }

    return 0;
}