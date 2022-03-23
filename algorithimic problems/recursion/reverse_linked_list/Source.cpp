#include <iostream>
#include <vector>

using namespace std;

// рекурсивно развернуть односвязный список

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
    /*TODO*/ reverse_list_recursive(/*TODO*/)
    {
        /*TODO*/
    }

  
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* new_head = nullptr;
        reverse_list_recursive(/*TODO*/);
        return new_head;
    }
};


int main()
{
    Solution s;

    // построить следующие примеры 
    ListNode* ln1 = /*TODO*/ //[1,2,3,4,5]
    ListNode* ln2 = /*TODO*/ //[1,2]
    ListNode* ln3 = /*TODO*/ //[] 
    vector<ListNode*> v({ ln1, ln2, ln3 });

    auto print_ln = /*TODO*/ // Лямбда-функция, которая выводит все элементы списка на экран

    for (ListNode* ln : v)
    {
        print_ln(ln);
        cout << endl;
    }

    for (/*TODO*/ ln : v)
    {
        ln = s.reverseList(ln); //разворачиваем список
    }

    for (ListNode* ln : v)
    {
        print_ln(ln);
        /*
        должно выводить
        * 5,4,3,2,1
        * 2,1
        * 0
        */
        cout << endl;
    }

    return 0;
}

/*
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
    void reverse_list_recursive(ListNode* head, ListNode*& prev)
    {
        if (!head) return;

        ListNode* h = head->next;
        head->next = prev;
        prev = head;
        head = h;
        reverse_list_recursive(head, prev);
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
    ListNode* reverse_list_recursive(ListNode* head)
    {
        if (head->next == nullptr)
        {
            return head;
        }
        ListNode* prev = head;
        ListNode* h = reverse_list_recursive(head->next);
        head->next->next = prev;
        prev->next = nullptr;
        return h;
    }

    public:

    ListNode* reverse_list(ListNode* head)
    {
        if (nullptr == head)
            return nullptr;

        return reverse_list_recursive(head);
    }
};

//examples
//[1,2,3,4,5] -> [5,4,3,2,1]
//[1,2] -> [2,1]
//[] -> []

int main()
{
    Solution s;

    ListNode* ln1 = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5, nullptr)))));
    ListNode* ln2 = new ListNode(1, new ListNode(2, nullptr));
    ListNode* ln3 = new ListNode;
    vector<ListNode*> v({ ln1, ln2, ln3 });

    auto print_ln = [](ListNode* ln) { while (ln) { cout << ln->val << ' '; ln = ln->next; } };

    for (ListNode* ln : v)
    {
        print_ln(ln);
        cout << endl;
    }
    
    for (ListNode*& ln : v)
    {
        ln = s.reverseList(ln);
    }

    for (ListNode* ln : v)
    {
        print_ln(ln);
        cout << endl;
    }

    return 0;
}
*/