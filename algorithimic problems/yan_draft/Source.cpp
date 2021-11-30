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

bool search(std::vector<int>& nums, int target) {
	int k = nums.size() - 1;

	std::nth_element(nums.begin(), nums.begin(), nums.end());

	for (int i : nums) {
		std::cout << "AAAAA:  " << nums[i] << std::endl;
	}
	return std::binary_search(nums.begin() + k, nums.end(), target);
}



class Solution {


public:
	int _binary_search(std::vector<int>& nums, size_t begin, size_t end, int target) {

		size_t count = end - begin;
		size_t mid = begin + (size_t)(end - begin) / 2;
		size_t begin_cp = begin;

		/*
		if (target < nums[begin] || target > nums[end] || nums.empty()) {
			return -1;
		}
		*/
		while (count) {
			if (target >= nums[begin] && target <= nums[mid]) {
				end = mid;
				auto dist = end - begin;
				mid = begin + size_t(dist / 2);
				count = size_t(dist);
				continue;
			}
			else if (target >= nums[mid] && target <= nums[end]) {

				begin = mid + 1;
				auto dist = end - begin;
				mid = begin + size_t(dist / 2);
				count = size_t(dist);
				continue;
			}
			else {
				return -1;
			}
		}
		return nums[mid] == target ? mid - begin_cp : -1;
	}

	int search(std::vector<int>& nums, int target) {
		size_t left = 0;
		size_t mid = (size_t)nums.size() / 2;
		size_t end = nums.size() - 1;

		size_t count = nums.size();


		if (nums[end] > nums[left]) {
			return _binary_search(nums, left, end, target);
		}


		while (count >= 0) {
			if (nums[left] < nums[mid]) // left sorted
			{
				size_t i = _binary_search(nums, left, mid, target);
				if (i != -1) return left + i;
				left = mid + 1 > end ? end : mid + 1;
			}

			else if (nums[mid] < nums[end]) // right sorted
			{
				size_t i = _binary_search(nums, mid, end, target);
				if (i != -1) return mid + i;
				end = mid < 1 ? left : mid - 1;
			}
			else {
				// 2 elems
				if (nums[left] == target) return left;
				if (nums[end] == target) return end;
				return -1;
			}
			mid = left + (end - left) / 2;
			count = end - left;
			if (mid <left || mid >end) {
				return -1;
			}
		}

		return -1;
	}
};

/*
class Solution {
public:
	int guessNumber(int n) {
		int num = n;
		//  int res = guess(num);
		int res;
		int low_bound = 0;
		int up_bound = n;

		while ((res = guess(num)) != 0) {
			if (res == -1) {
				up_bound = num;
				num -= (up_bound - low_bound) / 2;

			}
			else if (res == 1) {
				low_bound = num;
				num += (up_bound - low_bound) / 2;
			}
		}
		return num;
	}
};
*/
bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
	//1. find row by first column
	//2. find value in that row
	int row_pos = 1;
	int left_bound = 0;
	int step = 1;
	bool found_row = false;
	// int right_bound = matrix[matrix.size()-1][0];
	 //target > matrix[row_pos][0] && target < matrix[left_bound][0]
	if (matrix.size() == 1) {
		return std::binary_search(matrix[row_pos].cbegin(), matrix[row_pos].cend(), target);
	}
	if (target < matrix[0][0] || target > matrix[matrix.size() - 1][matrix[matrix.size() - 1].size() - 1] || matrix.size() == 0) {
		return false;
	}

	while (target < matrix[left_bound][0] || target > matrix[row_pos][0]) {
		if (target > matrix[row_pos][0]) {
			row_pos += (matrix.size() - left_bound) / 2;
			left_bound = row_pos - 1;
		}
		else if (target < matrix[left_bound][0]) {
			row_pos -= (row_pos) / 2;
			left_bound = row_pos - 1;
		}
	}

	if (target > matrix[row_pos][0]) {
		return std::binary_search(matrix[row_pos].cbegin(), matrix[row_pos].cend(), target);
	}
	return std::binary_search(matrix[left_bound].cbegin(), matrix[left_bound].cend(), target);
}

/*
int upper_bound(const std::vector<int>& v, int t) {
	size_t count = v.size();
	//size_t i = 0;
	size_t step = count/ 2;
	size_t mid = step;

	while (count != 0)
	{
		if (t == v[mid])
		{
			break;
		}

		//count -= std::min(count, i + 1);
		if (t > v[mid])
		{
			count -= (step + 1); //?????
			if (count == 0) {
				break;
			}
			++mid;
			step = (count - 1)/ 2;
			mid += step;
			//count -= std::min(count, (v.size() - i) / 2);
		}
		else
		{
			count -= (step + 1);
			if (count == 0) {
				break;
			}
			--mid;
			step = (count - 1)/ 2;
			mid -= step;
		//	count -= std::min(count, i / 2);
		}
	}

	return mid;
}
*/


// bin search
int upper_bound(const std::vector<int>& v, int t) {
	size_t left = 0;
	size_t right = v.size() - 1;
	size_t mid = (v.size() - 1) / 2;

	while (left != right && mid < v.size()) {
		if (v[mid] == t) {
			return mid;
		}

		if (t < v[mid]) {
			right = --mid;
			mid -= (right - left + 1) / 2;
		}
		else {
			left = ++mid;
			mid += (right - left + 1) / 2;
		}

	}

	if (mid >= v.size()) {
		mid = v.size() - 1;
	}

	//return v[mid] == t ? mid : --mid;
	return mid;
}

int upper_bound_(const std::vector<int>& v, int t) {
	int i = upper_bound(v, t);
	if (v[i] == t) {
		return i;
	}
	std::cout << "Not found! " << i << " : " << v[i] << std::endl;
	return i;
}

bool searchMatrix_(std::vector<std::vector<int>>& matrix, int target) {
	//1. find row by first column
	//2. find value in that row


	if (matrix.size() == 1) {
		int r = upper_bound(matrix[0], target);
		return target == matrix[0][r] ? true : false;
	}
	int row_pos = 0;
	std::vector<int> v;
	for (const std::vector<int>& vv : matrix) {
		v.push_back(vv[0]);
	}
	auto it = std::lower_bound(v.cbegin(), v.cend(), target);
	if (it == v.cbegin()) {
		return std::binary_search(matrix[0].cbegin(), matrix[0].cend(), target);
		/*
		 int g = upper_bound(matrix[0], target);
		 if (matrix[0][g] == target) {
			return true;
		 }
		 */
	}
	int ind = std::distance(v.cbegin(), it);
	if (it != v.end() && matrix[ind][0] == target) {
		return true;
	}
	--ind;
	//return std::binary_search(matrix[ind].cbegin(), matrix[ind].cend(), target);

	int g = upper_bound(matrix[ind], target);
	if (matrix[ind][g] == target) {
		return true;
	}
	return false;
	/*
	if (it == v.cend()) {
		return false;
	}
	if (*it == target) {
		return true;
	}
	int id = std::distance(v.cbegin(), --it);
	int r = upper_bound(matrix[id], target);
	if (matrix[id][r] == target) {
		return true;
	}
	if (id != 0) {
		--id;
	}
	else {
		return false;
	}
	r = upper_bound(matrix[id], target);
	if (matrix[id][r] == target) {
		return true;
	}
	return false;
	/*
	int i = matrix.size();
	if (!v.empty()) {
		i = upper_bound(v, target);
	}
	if (i < matrix.size()) {
		 bool found =  std::binary_search(matrix[i].cbegin(), matrix[i].cend(), target);
		 if (found ) {
			 return true;
		 }
		 --i;
		 if (i < matrix.size() && i != 0) {
			 return std::binary_search(matrix[i].cbegin(), matrix[i].cend(), target);
		 }
	}
	return false;
   */

}

/*
int _lower_bound_(const std::vector<int>& v, int t) {
	size_t count = v.size();
	size_t step = count / 2;

	//int shifted_right = 0;
	int pos = 0;
	int pos1 = 0;
	while (count != 0)
	{
		pos = pos1;
		step = count / 2;
		pos += step;
		if (t > v[pos]) //shift right
		{
			count -= step + 1;
			pos1 = ++pos;
		}
		else if (t == v[pos])
		{
			return pos;
		}
		else
		{
			count = step;
		}
	}
	return pos;
}
*/
int _lower_bound_(const std::vector<int>& v, int t) {
	size_t count = v.size();
	size_t step = count / 2;

	int pos = 0;

	while (count != 0)
	{
		step = count / 2;
		pos += step;
		if (t > v[pos]) //shift right
		{
			count -= step + 1;
			++pos;
			continue;
		}
		else if (t == v[pos])
		{
			return pos;
		}
		else
		{
			count = step;
		}
		pos -= step;
	}
	return pos;
}
template<class ForwardIt, class T>
ForwardIt _lower_bound_(ForwardIt first, ForwardIt last, const T& value)
{
	ForwardIt it;
	typename std::iterator_traits<ForwardIt>::difference_type count, step;
	count = std::distance(first, last);

	while (count > 0) {
		it = first;
		step = count / 2;
		std::advance(it, step);
		if (*it < value) {
			first = ++it;
			count -= step + 1;
		}
		else
			count = step;
	}
	return first;
}

int search1(std::vector<int>& nums, int target) {
	int i = _lower_bound_(nums, target);
	return (i < nums.size() && nums[i] == target) ? i : -1;
}

using namespace std;
#include <algorithm>
#include <numeric>


void print_vec(std::vector<int>& v) {
	for (int vv : v) {
		cout << vv << ' ';
	}
	cout << endl;
}
class Solution2 {
	inline bool check_cond(const vector<int>& nums, const vector<int>& r, int t) {
		//if ((r[0] + r[1] + r[2] + r[3]) != t) return false;
		//return (r[0] + r[1] + r[2] + r[3]) == t;
		bool b = r.size() == 4 && (r[0] + r[1] + r[2] + r[3]) == t;
		return b;
		//	return b && std::adjacent_find(indices.cbegin(), indices.cend()) == indices.cend();
	}

	void find_quads(vector<vector<int>>& res, const vector<int>& nums, int t) {
		/*
		print_vec(indices);
		if (check_cond(nums, indices, t)) {

			res.push_back(indices); // move
			print_vec(indices);
			return;
		}
		*/
		if (nums.size() < 4) {
			return;
		}
		for (int i = 0; i < nums.size() - 3; ++i) {
			//	std::vector<int> indices(4);
			for (int j = i + 1; j < nums.size() - 2; ++j) {
				for (int k = j + 1; k < nums.size() - 1; ++k) {
					for (int q = k + 1; q < nums.size(); ++q) {
						/*
						indices[0] = i;
						indices[1] = j;
						indices[2] = k;
						indices[3] = q;
						*/

						std::vector<int> r = { nums[i], nums[j], nums[k], nums[q] };
						//	print_vec(r);
							//	std::sort(indices.begin(), indices.end());
							//auto rr(r);
						//    std::sort(r.begin(), r.end());
							//	std::cout << (r == rr) << endl;
						if (std::find(res.cbegin(), res.cend(), r) == res.cend() && check_cond(nums, r, t)) {
							//if (check_cond(nums, r, indices, t)) {
							res.push_back(std::move(r));
							//std::cout << nums[indices[0]] << ' ' << nums[indices[1]] << ' ' << nums[indices[2]] << ' ' << nums[indices[3]] << std::endl;
							//res.push_back(indices); // move
							//res.push_back({nums[indices[0]], nums[indices[1]], nums[indices[2]], nums[indices[3]] }); // move
						}
					}
				}
			}
		}
		/*
		for (int i = 0; i < nums.size(); ++i) {
			std::vector<int> indices(4);
			for (int j = 0; j < nums.size() , j != i; ++j) {
				for (int k = 0; k < nums.size() ,  k != j , k != i; ++k) {
					for (int q = 0; q < nums.size() , q!= k , q != j , q != i; ++q) {
						indices[0] = i;
						indices[1] = j;
						indices[2] = k;
						indices[3] = q;
						std::vector<int> r = { nums[indices[0]], nums[indices[1]], nums[indices[2]], nums[indices[3]] };
					//	std::sort(indices.begin(), indices.end());
						std::sort(r.begin(), r.end());
						if (std::find(res.cbegin(), res.cend(), r) == res.cend() && check_cond(nums, r, indices, t)) {
							res.push_back(std::move(r));
							//std::cout << nums[indices[0]] << ' ' << nums[indices[1]] << ' ' << nums[indices[2]] << ' ' << nums[indices[3]] << std::endl;
							//res.push_back(indices); // move
							//res.push_back({nums[indices[0]], nums[indices[1]], nums[indices[2]], nums[indices[3]] }); // move
						}
					}
				}
			}
		}
		*/
		/*
		//while (true) {
			for (int i = 0; i < nums.size(); ++i) {
				if (indices.size() == 4) {
					std::sort(indices.begin(), indices.end());
					if (std::find(res.cbegin(), res.cend(), indices) == res.cend()) {
						find_quads(res, indices, nums, t);
						indices = {};
					}
					//indices.pop_back();
				}
				else if (indices.size() < 4) {
					indices.push_back(i);
				}
			}
		//}
		*/
	}
public:
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		vector<vector<int>> res;
		find_quads(res, nums, target);
		//find_quads(res, {}, nums, target);
		return res;
	}
};

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

/*
Given a string s, find the length of the longest substring without repeating characters.



Example 1:

Input: s = "abcabcbb"
Output : 3
Explanation : The answer is "abc", with the length of 3.
Example 2 :

Input : s = "bbbbb"
Output : 1
Explanation : The answer is "b", with the length of 1.
Example 3 :

Input : s = "pwwkew"
Output : 3
Explanation : The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
Example 4 :

Input : s = ""
Output : 0


*/
class Solution {
	bool contains(std::string::const_iterator b, std::string::const_iterator e, char v) {
		while (b != e) {
			if (*b++ == v) {
				return true;
			}
		}
		return false;
	}
public:
	int lengthOfLongestSubstring(string s) {
		if (s.empty()) return 0;
		int max_ = 1;

		for (auto i = s.cbegin(); i != s.cend(); ++i) {
			//  auto i_copy_b = i;
			auto i_copy_c = i;
			int temp_max = 0;
			// std::find(i, i_copy_c, *++i_copy_c) != i_copy_c
			while (i_copy_c != s.cend() && !contains(i, i_copy_c, *i_copy_c++)) {
				++temp_max;
			}
			if (temp_max > max_) {
				max_ = temp_max;
			}
		}
		return max_;
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