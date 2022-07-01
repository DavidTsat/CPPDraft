#pragma once
#include "_list.h"
#include <vector>
#include <assert.h>
#include <iterator>
using namespace std;

// Problem 1

class problem1_solution 
{
    void sol(_list<int>& _l1, _list<int>& _l2, _list<int>& _r, _list<int>::iterator l1, _list<int>::iterator l2, _list<int>::iterator r, int n) {
        if (l1 == _l1.end()  && l2 == _l2.end())
        {
            if (n)
            {
                _r.push_back(n);
            }
            return;

        }

        auto l11 = l1;
        auto l22 = l2;
        if (++l11 == _l1.end() && ++l22 != _l2.end())
        {
            _l1.push_back(0);
        }
        l11 = l1;
        l22 = l2;
        if (++l22 == _l2.end() && ++l11 != _l1.end())
        {
            _l2.push_back(0);
        }

        int c = *l1 + *l2 + n;
        int m = c % 10;
        *r = m;

        ++l1;
        ++l2;
        if (l1 != _l1.end() && l2 != _l2.end())
        {
            _r.push_back(0);
            ++r;
        }

        sol(_l1, _l2, _r, l1, l2, r, c >= 10);

    }

public:

    _list<int> addTwoNumbers(_list<int>& l1, _list<int>& l2) {
        _list<int> res(1);
        sol(l1, l2, res, l1.begin(), l2.begin(), res.begin(), 0);
        return res;
    }
};

void problem1_test1()
{
    /*
    Input: l1 = [2, 4, 3], l2 = [5, 6, 4]
    Output : [7, 0, 8]
    Explanation : 342 + 465 = 807.
    */
    vector<int> answers = { 7,0,8 };

    _list<int> l1;
    _list<int> l2;

    l1.push_back(2);
    l1.push_back(4);
    l1.push_back(3);

    l2.push_back(5);
    l2.push_back(6);
    l2.push_back(4);

    problem1_solution s;

    _list<int> r = s.addTwoNumbers(l1, l2);

    int i = 0;
    for (auto it = r.cbegin(); it != r.cend(); ++it)
    {
        assert(*it == answers[i++]);
  //      cout << *it << ' ';
    }
    cout << "problem1_test1 passed" << endl;
}

void problem1_test2()
{
    /*
    Input: l1 = [0], l2 = [0]
    Output: [0]
    */
    vector<int> answers = { 0 };
    _list<int> l1;
    _list<int> l2;

    l1.push_back(0);
    l2.push_back(0);

    problem1_solution s;

    _list<int> r = s.addTwoNumbers(l1, l2);

    int i = 0;
    for (auto it = r.cbegin(); it != r.cend(); ++it)
    {
        assert(*it == answers[i++]);
   //     cout << *it << ' ';
    }
    cout << "problem1_test2 passed" << endl;
}

void problem1_test3()
{
    /*
    Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
    Output: [8,9,9,9,0,0,0,1]
    */
    vector<int> answers = { 8,9,9,9,0,0,0,1 };
    _list<int> l1;
    _list<int> l2;
    
    for (int i = 0; i < 7; ++i)
    {
        l1.push_back(9);
    }
    for (int i = 0; i < 4; ++i)
    {
        l2.push_back(9);
    }

    problem1_solution s;

    _list<int> r = s.addTwoNumbers(l1, l2);

    int i = 0;
    for (auto it = r.cbegin(); it != r.cend(); ++it)
    {
        assert(*it == answers[i++]);
     //   cout << *it << ' ';
    }
    cout << "problem1_test3 passed" << endl;
}

// Problem 2
class problem2_solution
{
public:
    _list<int> mergeTwoLists(const _list<int>& l1, const _list<int>& l2) {
        _list<int> r;

        _list<int>::iterator list1 = l1.cbegin();
        _list<int>::iterator list2 = l2.cbegin();

        while (list1 != l1.cend() && list2 != l2.cend())
        {
            bool b = false;
            if (*list1 < *list2)
            {
                r.push_back(*list1);
                ++list1;
            }
            else
            {
                r.push_back(*list2);
                ++list2;
            }
            
        }
        while (list1 != l1.cend())
        {
            r.push_back(*list1);
            ++list1;
           
        }
        while (list2 != l2.cend())
        {
            r.push_back(*list2);
            ++list2;
        }

        return r;
    }
};

void problem2_test1()
{
    /*
    Input: list1 = [1,2,4], list2 = [1,3,4, 8]
    Output: [1,1,2,3,4,4,8]
    */
    vector<int> answers = { 1,1,2,3,4,4,8 };
    _list<int> l1;
    _list<int> l2;

    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(4);

    l2.push_back(1);
    l2.push_back(3);
    l2.push_back(4);
    l2.push_back(8);

    problem2_solution s;
    _list<int> r = s.mergeTwoLists(l1, l2);

    int i = 0;
    for (auto it = r.cbegin(); it != r.cend(); ++it)
    {
        assert(*it == answers[i++]);
   //     cout << *it << ' ';
    }

    cout << "problem2_test1 passed" << endl;
}

void problem2_test2()
{
    /*
    Input: list1 = [], list2 = []
    Output: []
    */
    vector<int> answers = { };
    _list<int> l1;
    _list<int> l2;


    problem2_solution s;
    _list<int> r = s.mergeTwoLists(l1, l2);

    int i = 0;
    for (auto it = r.cbegin(); it != r.cend(); ++it)
    {
        assert(*it == answers[i++]);
    //    cout << *it << ' ';
    }
    
    cout << "problem2_test2 passed" << endl;
}

void problem2_test3()
{
    /*
    Input: list1 = [], list2 = [1]
    Output: [1]
    */
    vector<int> answers = { 1 };
    _list<int> l1;
    _list<int> l2;

    l2.push_back(1);

    problem2_solution s;
    _list<int> r = s.mergeTwoLists(l1, l2);

    int i = 0;
    for (auto it = r.cbegin(); it != r.cend(); ++it)
    {
        assert(*it == answers[i++]);
    //    cout << *it << ' ';
    }
    
    cout << "problem2_test3 passed" << endl;
}

template <typename T>
void _list<T>::deleteDuplicates()
{
    if (!head) return;

    node* curr = head;
    node* prev = head;
    node* prev_prev = head;

    while (curr && curr->next_)
    {
        curr = curr->next_;
        bool b = false;
        while (curr && curr->val == prev->val)
        {
            prev->next_ = curr->next_;
            if (curr->next_)
                curr->next_->prev_ = prev;
            if (curr == tail) tail = prev;
            delete curr;
            --size_;
            curr = prev->next_;
            b = true;
        }
        if (b)
        {
            if (head == prev)
            {
                head = curr;
                head->prev_ = nullptr;
            }
            if (prev == prev_prev)
                prev_prev = curr;
            else
            {
                prev_prev->next_ = curr;
                if (curr)
                    curr->prev_ = prev_prev;
            }

            if (prev == tail) tail = prev_prev;
            delete prev;
            --size_;
        }
        else
            prev_prev = prev;
        prev = curr;
    }
}

void problem3_test1()
{
    /*
    Input:  [1,2,3,3,4,4,5,5]
    Output: [1,2]
    */
    vector<int> answers = { 1, 2 };
    _list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(3);
    l.push_back(4);
    l.push_back(4);
    l.push_back(5);
    l.push_back(5);

    l.deleteDuplicates();

    int i = 0;
    for (auto it = l.cbegin(); it != l.cend(); ++it)
    {
        assert(*it == answers[i++]);
    //    cout << *it << ' ';
    }

    //  testing "prev" pointers with reversed list
    i = answers.size() - 1;
    l.reverse();
    for (auto it = l.cbegin(); it != l.cend(); ++it)
    {
        assert(*it == answers[i--]);
    //    cout << *it << ' ';
    }

    cout << "\nproblem2_test2 passed" << endl;
}

void problem3_test2()
{
    /*
    Input:  [1,1,1,2,3]
    Output: [2,3]
    */
    vector<int> answers = { 2,3 };
    _list<int> l;
    l.push_back(1);
    l.push_back(1);
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.deleteDuplicates();

    int i = 0;
    for (auto it = l.cbegin(); it != l.cend(); ++it)
    {
        assert(*it == answers[i++]);
 //       cout << *it << ' ';
    }

    //  testing "prev" pointers with reversed list
    i = answers.size() - 1;
    l.reverse();
    for (auto it = l.cbegin(); it != l.cend(); ++it)
    {
        assert(*it == answers[i--]);
   //     cout << *it << ' ';
    }

    cout << "\nproblem2_test2 passed" << endl;
}

void problem3_test3()
{
    /*
    Input:  [1,1,1,2,3,3,3,3,3]
    Output: [2]
    */
    vector<int> answers = { 2 };
    _list<int> l;
    l.push_back(1);
    l.push_back(1);
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(3);
    l.push_back(3);
    l.push_back(3);
    l.push_back(3);
    l.deleteDuplicates();

    int i = 0;
    for (auto it = l.cbegin(); it != l.cend(); ++it)
    {
        assert(*it == answers[i++]);
     //   cout << *it << ' ';
    }

    //  testing "prev" pointers with reversed list
    i = answers.size() - 1;
    l.reverse();
    for (auto it = l.cbegin(); it != l.cend(); ++it)
    {
        assert(*it == answers[i--]);
     //   cout << *it << ' ';
    }

    cout << "\nproblem3_test3 passed" << endl;
}