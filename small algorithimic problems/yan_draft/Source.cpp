#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>
#include <iterator>

class A {
	int* x;

public:
	A() : x(new int[100]) {};
	A(const A&) = delete;

	~A() noexcept(false) {
		delete[] x;

		if (true) {
			throw  std::runtime_error("runtime errrror");
		}
	}
};

template <typename ForIt>
std::size_t max_len(ForIt b, ForIt e) {
	std::size_t len = 0;
	while (b != e) {
		std::size_t temp_len = 0;
		while (b != e && *b++ == 1) {
			++temp_len;
		}
		if (temp_len > len) {
			len = temp_len;
		}
		while (b != e && *b == 0) {
			++b;
		}
	}
	return len;
}

bool onog(std::string a, std::string b) {
	std::sort(a.begin(), a.end());
	std::sort(b.begin(), b.end());

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	return a == b;
}

template <typename ForIt>
bool test_par(ForIt b, ForIt e) {
	int c = 0;
	while (b != e) {
		if (*b == '(') ++c;
		else --c;
		if (c < 0) {
			return false;
		}
		++b;
	}
	return c == 0;
}

bool open_par_valid(const std::vector<std::string>& all_pars, const std::string& curr_str, int i, char empty_sp) {
	int n = (int)curr_str.size() / 2;

	std::string ss = curr_str;
	std::string copy_s = curr_str;
	std::sort(copy_s.begin(), copy_s.end());
	auto p = std::equal_range(copy_s.begin(), copy_s.end(), '(');
	auto q = std::equal_range(copy_s.begin(), copy_s.end(), ')');
	auto z = std::equal_range(copy_s.begin(), copy_s.end(), '_');
	auto remains_op = n - (p.second - p.first);
	auto remains_cl = n - (q.second - q.first);
	auto empty_spaces = (z.second - z.first);

	if (remains_op <= 0) return false;

	if (remains_op == 1 && empty_spaces == remains_cl) {
		ss[i] = '(';
		std::transform(ss.begin(), ss.end(), ss.begin(), [empty_sp](char& c) {return c == empty_sp ? ')' : c; });
		return std::find(all_pars.cbegin(), all_pars.cend(), ss) == all_pars.cend();
	}
	if (remains_op > 1) {
		return true;
	}
	return false;
}

bool last_str(const std::string& s) {
	auto p = s.cbegin();
	auto q = s.cbegin();
	std::advance(q, 1);
	while (q != s.cend()) {
		if (*p++ != '(' && *q++ != ')') return false;
	}
	return true;
}

std::vector<std::string> all_par(int n) {
	if (n < 2) return {};
	std::vector<std::string> all_pars;

	while (true) {
		std::string s(2 * n, '_');
		s[0] = '(';
		s[s.size() - 1] = ')';

		for (int i = 1; i <= s.size() - 2; ++i) {
			if (open_par_valid(all_pars, s, i, '_')) {
				s[i] = '(';
			}
			else {
				s[i] = ')';
			}
		}

		if (std::find(all_pars.cbegin(), all_pars.cend(), s) == all_pars.cend()) {
			all_pars.push_back(std::move(s));
		}

		if (last_str(all_pars.back())) break;
	}

	return all_pars;
}

void generate_pars(std::vector<std::string>& p, std::string s, int open_pars, int close_pars, int n) {
	if (s.size() == 2 * n) {
		p.push_back(s);
		return;
	}
	if (open_pars < n) {
		generate_pars(p, s + '(', open_pars + 1, close_pars, n);
	}
	if (close_pars < open_pars) {
		generate_pars(p, s + ')', open_pars, close_pars + 1, n);
	}

}

std::vector<std::string> generate_pars(int n) {
	std::vector<std::string> p;

	generate_pars(p, "", 0, 0, n);

	return p;
}

/*
You are given an array of k linked - lists lists, each linked - list is sorted in ascending order.

Merge all the linked - lists into one sorted linked - list and return it.



Example 1:

Input: lists = [[1, 4, 5], [1, 3, 4], [2, 6]]
Output : [1, 1, 2, 3, 4, 4, 5, 6]
Explanation : The linked - lists are :
[
	1->4->5,
	1->3->4,
	2->6
]
merging them into one sorted list :
1->1->2->3->4->4->5->6
Example 2 :

	Input : lists = []
	Output : []
	Example 3 :

	Input : lists = [[]]
	Output : []
*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class Solution {
public:

	ListNode* mergeKLists(std::vector<ListNode*>& lists) {

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

		delete l;
		if (!is_empty) {
			l_prev->next = nullptr;
			return ll;
		}
		else {
			return nullptr;
		}

	}
};

/*
You are given two non - empty linked lists representing two non - negative integers.The digits are stored in reverse order, and each of their nodes contains a single digit.Add the two numbersand return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.



Example 1:

Input: l1 = [2, 4, 3], l2 = [5, 6, 4]
Output : [7, 0, 8]
Explanation : 342 + 465 = 807.
Example 2 :

Input : l1 = [0], l2 = [0]
Output : [0]
Example 3 :

Input : l1 = [9, 9, 9, 9, 9, 9, 9], l2 = [9, 9, 9, 9]
Output : [8, 9, 9, 9, 0, 0, 0, 1]
*/

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


 /**
  * Definition for singly-linked list.
  * struct ListNode {
  *     int val;
  *     ListNode *next;
  *     ListNode(int x) : val(x), next(NULL) {}
  * };
  */

/*
Given head, the head of a linked list, determine if the linked list has a cycle in it.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer.Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.

Return true if there is a cycle in the linked list.Otherwise, return false.
#include <vector>
#include <algorithm>


class Solution {
public:
	bool hasCycle(ListNode* head) {
		std::vector<const ListNode*> story;
		while (head && head->next) {
			if (std::find(story.cbegin(), story.cend(), head) != story.cend()) {
				return true;
			}
			story.push_back(head);
			head = head->next;
		}
		return false;
	}
};
*/

class Solution {
public:
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
};
/*
Given the head of a singly linked list, reverse the list, and return the reversed list.
*/
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
public:
	ListNode* reverseList(ListNode* head) {
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
};

int main() {
	std::vector<std::string> all_pars = generate_pars(4);
	std::cout << std::endl;
	for (const auto& a : all_pars) {
		std::cout << a << std::endl;
	}


	/*std::vector<int> v{ 0,0,0,1,1,1 };


	std::cout << max_len(v.begin(), v.end()) << std::endl;

	std::string a("David");
	std::string b("Ddviaa");
	std::cout << onog(a, b) << std::endl;*/


	//	char a[] = { 0xA, 0xB, 0xC, 0xD };
	//	short s = *(short*)((short*)a +1); //// ?????????????
	//	std::cout << sizeof(short) << ' ' << sizeof(char) << std::endl;
	//	//for (auto aa : a) {
	//	//	std::cout << (int)aa << ' ';
	//	//}
	////	std::cout << std::endl;
	////	std::cout << (short) 0xC << std::endl;
	////	std::cout << std::endl;
	//	std::cout << s << std::endl;
	//	std::cout << std::bitset<sizeof(char)*8>(s) << std::endl;
	//	std::cout << std::bitset<sizeof(short)*8>(s) << std::endl;
	return 0;
}