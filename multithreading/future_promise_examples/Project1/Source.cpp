#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <numeric>
#include <map>
#include <unordered_set>
using namespace std;

/*
class A {
	int* x;

public:
	A() : x(new int[100]) {};
	A(const A&) = delete;

	~A() noexcept(false){
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
	auto remains_op   = n - (p.second - p.first);
	auto remains_cl   = n - (q.second - q.first);
	auto empty_spaces =     (z.second - z.first);

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
		

		while (count >=0) {
			if (nums[left] < nums[mid]) // left sorted
			{
				size_t i = _binary_search(nums, left, mid, target);
				if (i != -1) return left + i;
				left = mid + 1 > end ? end : mid + 1;
			}
			
			else if (nums[mid] < nums[end]) // right sorted
			{
				size_t i = _binary_search(nums, mid, end, target);
				if (i != -1  ) return mid + i;
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
	if (target < matrix[0][0] || target > matrix[matrix.size() - 1][matrix[matrix.size() - 1].size()-1] || matrix.size() == 0) {
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



// bin search
int upper_bound(const std::vector<int>& v, int t) {
	size_t left = 0;
	size_t right = v.size() - 1; 
	size_t mid = (v.size()-1) / 2;

	while (left != right  && mid < v.size()) {
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
		mid = v.size()-1;
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

*/

template <typename T>
void print_vec(const std::vector<T>& v) {
	for (const T& vv : v) {
		cout << vv << ' ';
	}
	cout << endl;
}
class Solution2{
	inline bool check_cond(const vector<int>& nums, const vector<int>& r, int t) {
		//if ((r[0] + r[1] + r[2] + r[3]) != t) return false;
		//return (r[0] + r[1] + r[2] + r[3]) == t;
		bool b =  r.size() ==4 && (r[0] + r[1] + r[2] + r[3]) == t;
		return b;
	//	return b && std::adjacent_find(indices.cbegin(), indices.cend()) == indices.cend();
	}

	void find_quads(vector<vector<int>>& res, vector<int>& nums, int t) {
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
		std::sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size() - 3; ++i) {
			//int64_t sum_ = (int64_t)nums[i];
			//int64_t sum2_ = (int64_t)nums[i];
	
		//	std::vector<int> indices(4);
			if ((nums[i] > 0) && (nums[i] > t)) {
			//	cout << "1111111\n";
				return;
			}
			for (int j = i + 1; j < nums.size() - 2; ++j) {
			//	sum2_ += nums[j];
				int64_t sum_j = (int64_t)nums[i] + nums[j];
				if ((nums[j] > 0) && (sum_j > t)) {
				//	cout << "222222222\n";
					break;
				}
				for (int k = j + 1; k < nums.size() - 1; ++k) {
				//	sum2_ += nums[k];
					int64_t sum_k = sum_j + nums[k];
					if ((nums[k] > 0) && (sum_k > t)) {
				//		cout << "3333333\n";
						break;
					}
					for (int q = k + 1; q < nums.size(); ++q) {
						/*
						indices[0] = i;
						indices[1] = j;
						indices[2] = k;
						indices[3] = q;
						*/
						int64_t sum2_ = sum_k + nums[q];
						if ((nums[q] > 0) && (sum2_ > t)) {
						//	cout << "4444444444\n";
							break;
						}
						if (sum2_ < t) {
							
							continue;
						}
						if (sum2_ == t) {
							std::vector<int> r = { nums[i], nums[j], nums[k], nums[q] };

							//	print_vec(r);
								//	std::sort(indices.begin(), indices.end());
								//auto rr(r);
							//    std::sort(r.begin(), r.end());
								//	std::cout << (r == rr) << endl;
							auto pos = std::find(res.cbegin(), res.cend(), r);
							if (pos == res.cend()) {
								//if (check_cond(nums, r, indices, t)) {
								res.push_back(std::move(r));
								//std::cout << nums[indices[0]] << ' ' << nums[indices[1]] << ' ' << nums[indices[2]] << ' ' << nums[indices[3]] << std::endl;
								//res.push_back(indices); // move
								//res.push_back({nums[indices[0]], nums[indices[1]], nums[indices[2]], nums[indices[3]] }); // move
							}
							else if (nums[q] > 0) {
								break;
							}
						}
					}
				//	sum2_ -= nums[k];
				}
			//sum2_ -= nums[j];
			}
			//sum2_ -= nums[i];
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

static const int PRIMES[26] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101 };



long long hash_function(const std::string& str) {

	long long  h = 1;
	for (const auto& c : str) {
		int offset = c - 'a';
		h *= (long long)PRIMES[offset];
	}
	return h;
}
long long hash_function(const std::string& str, int i, int p) {

	long long  h = 1;
	for (int ii = i; ii != i+ p; ++ii) {
		int offset = str[ii] - 'a';
		h *= (long long)PRIMES[offset];
	}
	return h;
}

struct str_wrap {
	string s;
	str_wrap(const string& s_) : s(s_) {}
	bool operator==(const str_wrap& r) const {
		return s == r.s;
	}
};

template <>
struct std::hash<str_wrap>
{
	size_t operator()(str_wrap s_) const
	{
		/*
		//sort(s_.s.begin(), s_.s.end());
		size_t hash_ = 0;
		for (char c : s_.s) {
		//	cout << "char: " << c << ' ' << "int: " << int(c) << ' ';
			hash_ ^= c;
		}
	//	cout << hash_ << endl;

		return hash_;
		*/
		return hash_function(s_.s);
		//return std::hash<string>()(s_.s);
	}
	size_t operator()(const string& s, int i, int p) const
	{
		/*
		//sort(s_.s.begin(), s_.s.end());
		size_t hash_ = 0;
		for (char c : s_.s) {
		//	cout << "char: " << c << ' ' << "int: " << int(c) << ' ';
			hash_ ^= c;
		}
	//	cout << hash_ << endl;

		return hash_;
		*/
		return hash_function(s, i, p);
		//return std::hash<string>()(s_.s);
	}
};

class SolutionAnag {
	/*
	bool is_anagram(const string& a, const string& b) {
		map<char, int> a_set;
		map<char, int> b_set;

		for(const char& c: a) a_set[c]++;
		for(const char& c: b) b_set[c]++;

		return a_set == b_set;
	}
	*/

	/*
	inline bool is_anagram(string a, string b) const {
		sort(a.begin(), a.end());
		sort(b.begin(), b.end());
		return a == b;
	}
	*/
	vector<string> sort_strs(const vector<string>& str) const {
		vector<string> res;
		res.reserve(str.size());
		std::transform(str.cbegin(), str.cend(), back_inserter(res), [](string s) {sort(s.begin(), s.end()); return move(s); });
		return res;
	}
public:
	
	vector<vector<string>> groupAnagramsBad(vector<string>& strs) {
		vector<vector<string>> res;

		vector<string> sorted_res = sort_strs(strs);
		//	res.reserve(strs.size());
			//  vector<bool> covered(strs.size(), false);
			//  auto it = strs.begin(); 
		vector<string>::iterator it = strs.begin();
		while (it != strs.end())
		{
			auto it_pos = distance(strs.begin(), it);
			
			if (it->empty())
			{
				it++;
				continue;
			}

			vector<string> current_anagrams;
			current_anagrams.reserve(strs.size() / 2);
			//res.push_back({ move(*it) });
			current_anagrams.push_back(std::move(*it));
			//*it = "!";
			//covered[it_pos] = true;
			auto it_sec = ++it;
			auto pos = distance(strs.begin(), it_sec);
			while (it_sec != strs.end())
			{
			//	&& sorted_res[it_pos] == sorted_res[pos]
			//	if (*it_sec != "!" && sorted_res[it_pos] == sorted_res[pos])
				if (!it->empty() && sorted_res[it_pos] == sorted_res[pos])
				{
					current_anagrams.push_back(move(*it_sec));
					//res.back().emplace_back(move(*it_sec));
					//*it_sec = "!";
					//   covered[pos] = true;
				}
				++pos;
				++it_sec;
			}
			res.push_back(std::move(current_anagrams));
		}
		return res;
	}
	// solution with hash & map
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		vector<vector<string>> res;

		map<size_t, vector<string>> table;

		for (auto it = strs.begin(); it != strs.end(); ++it) {
			string sorted_it(*it);
			sort(sorted_it.begin(), sorted_it.end());
			table[std::hash<std::string>()(sorted_it)].push_back(move(*it));
		}
		for (auto& anags : table) {
			res.push_back(move(anags.second));
		}
		return res;
	}
	
	
	// solution with unordered_map :: hash may be collision
	vector<vector<string>> groupAnagrams1(vector<string>& strs) {
		vector<vector<string>> res;
		unordered_set<str_wrap, hash<str_wrap>> table;

		for (auto it = strs.begin(); it != strs.end(); ++it)
		{
			table.insert(*it);
		}
		
		/*
		auto c = table.bucket_count();
		for (unsigned i = 0; i < table.bucket_count(); ++i) {
			vector<string> buck;
			for (auto bucket_begin = table.begin(i); bucket_begin != table.end(i); ++bucket_begin) {
				buck.push_back(bucket_begin->s);
			}
			if (buck.empty()) continue;
			res.push_back(buck);
		}
		*/
	//	std::cout << "myset's buckets contain:\n";
		for (unsigned i = 0; i < table.bucket_count(); ++i) {
			if (table.bucket_size(i) == 0) continue;
		//	std::cout << "bucket #" << i << " contains:";
			vector<string> buck;
			for (auto local_it = table.begin(i); local_it != table.end(i); ++local_it) {
			//	std::cout << " " << local_it->s;
				buck.push_back(local_it->s);
			}
			res.push_back(buck);
		//	std::cout << std::endl;
		}

		return res;
	}
};

class SolutionAnagrams {
public:
	/*
	bool isAnagram(string s, string t) {
		sort(s.begin(), s.end());
		sort(t.begin(), t.end());
		return s == t;
	}
	*/
	bool isAnagram(string s, string t) {
		map<char, int> m_s;
		map<char, int> m_t;

		auto s_i = s.begin();
		auto t_i = t.begin();

		while (s_i != s.end() && t_i != t.end())
		{
			++m_s[*s_i++];
			++m_t[*t_i++];

		}

		return s_i == s.end() && t_i == t.end() && m_s == m_t;
	}
};
#include <string_view>
#include <set>

class Solution4 {
	inline bool is_anagram(string a, string& b) const {
		sort(a.begin(), a.end());
	//	sort(b.begin(), b.end());
		return a == b;
	}

	bool isAnagram(string_view s, string_view t) {
	//	cout << s << " vs " << t << endl;

		map<char, int> m_s;
		map<char, int> m_t;

		auto s_i = s.begin();
		auto t_i = t.begin();

		while (s_i != s.end() && t_i != t.end())
		{
			++m_s[*s_i++];
			++m_t[*t_i++];
		}

		return s_i == s.end() && t_i == t.end() && m_s == m_t;
	}
public:
	vector<int> findAnagrams1(const string& s, string p) {
		vector<int> res;

		auto s_size = s.size();
		auto p_size = p.size();

		sort(p.begin(), p.end());

		//	string_view s_view(s);
		//	string_view p_view(p);

		if (p_size > s_size) return {};

		for (unsigned i = 0; i != s_size; ++i) {
			auto i_end = i + p_size;
			if (i_end > s_size) break;
			//	string_view ss = s.substr(i, p.size());
			if (is_anagram(s.substr(i, p.size()), p))
				//     if(true)
			{
				res.push_back(i);
			}
		}
		return res;
	}
	vector<int> findAnagrams(const string& s, string p) {
		vector<int> res;

		auto s_size = s.size();
		auto p_size = p.size();
		if (p_size > s_size) return {};

		map<char, int> s_map;
		map<char, int> p_map;

		auto p_i = p.begin();
		auto s_i = s.begin();

		while (p_i != p.end())
		{
			++p_map[*p_i++];
			++s_map[*s_i++];
		}

		if (s_map == p_map) res.push_back(0);

		//sort(p_sorted.begin(), p_sorted.end());
		//auto p_sorted_end = unique(p_sorted.begin(), p_sorted.end());

		//auto p_sorted(p);
	//	sort(p_sorted.begin(), p_sorted.end());
		//string p_(p_sorted.begin(), unique(p_sorted.begin(), p_sorted.end()));
	//	set<char> p_set(p.begin(), p.end());

		

	//	auto p_hash = hash<string>()(p_sorted);
		//auto p_hash = hash_function(p_sorted);

		for (size_t i = 0; i < s_size-p_size; ++i) {
			auto it = s_map.find(s[i]);

			--it->second;
			if (it->second == 0) {
				s_map.erase(it);
			}
			

			++s_map[s[i + p_size]];
			if (s_map == p_map) {
				res.push_back(i+1);
			}
			/*try {
				int& remove_entry = s_map.at(s[i]);
			}*/
			//	string_view ss = s.substr(i, p.size());
		//	string ss_sorted = s.substr(i, p_size);

			//auto ss_sorted(ss);
		//	sort(ss_sorted.begin(), ss_sorted.end());
		//	auto ss_sorted_end = unique(ss_sorted.begin(), ss_sorted.end());
			//if (ss_sorted_end == ss_sorted.end()) --ss_sorted_end;
		//	string s_(ss_sorted.begin(), ss_sorted_end);
		// 
			//auto ss_end = unique(ss.begin(), ss.end());
		//	set<char> ss_set(ss.begin(), ss.end());
		// 
		//	auto hash_ss = hash_function(ss_sorted, 0, distance(ss_sorted.begin(), ss_sorted_end));
			//auto hash_ss = hash<string>()(ss_sorted);
	// 
			//cout << "AAAAA " << p_ << "   " << s_ << endl;
			//cout << "AAAAA " << p_ << "   " << s_ << endl;
			//if (p_hash != hash_ss || (p_hash == hash_ss && !is_anagram(ss_sorted, p_sorted))) continue;
			//if (p_hash != hash_ss) continue;
			//cout << "AAAAA\n";
			//if (!is_anagram(ss_sorted, p_sorted)) continue;
			//if (p_map == s_map)
			//res.push_back(i);
		
		}

		//cout << "AAAAA: " << hash<str_wrap>()(p) << endl;
		return res;
	}
	/*
	vector<int> findAnagrams(const string& s,  string p) {
		vector<int> res;

		auto s_size = s.size();
		auto p_size = p.size();

		sort(p.begin(), p.end());

	//	string_view s_view(s);
	//	string_view p_view(p);

		if (p_size > s_size) return {};

		for (unsigned i = 0; i != s_size; ++i) {
			auto i_end = i + p_size;
			if (i_end > s_size) break;
		//	string_view ss = s.substr(i, p.size());
			if (is_anagram(s.substr(i, p.size()), p))
				//     if(true)
			{
				res.push_back(i);
			}
		}
		return res;
	}
	*/
};

/* perebor
int maxArea(vector<int>& height) {
	int max_area = 0;

	for (auto left = height.cbegin(); left != height.cend(); ++left)
	{
		auto right = left;
		advance(right, 1);
		while (right != height.cend()) {
			int len = distance(left, right);
			int area = len * min(*left, *right++);
			max_area = max_area < area ? area : max_area;
		}
	}
	return max_area;
}
*/
template <typename T>
struct value_index {
	pair<T, int> p;

	value_index() = default;
	value_index(const value_index<pair<T, int>>& p_) : p(p_) {}

	value_index(const pair<T, int>& pp) : p(pp) {}
	value_index& operator++()
	{
		p.second++;
		return *this;
	}

	value_index operator++(int)
	{
		value_index v(*this);
		p.second++;
		return v;
	}
	bool operator<(const value_index& r) const {
		return p.first < r.p.first;
	}
	bool operator>(const value_index& r) const {
		return p.first > r.p.first;
	}
	bool operator==(const value_index& r) const {
		return p.first == r.p.first;
	}
};

int get_max_area(const vector<value_index<int>>& sorted, const vector<value_index<int>>::const_iterator it, int dist) {
	return 0;
}

int maxArea(const vector<int>& height) {
	int max_area = 0;
	auto first = height.cbegin();
	auto last = --height.cend();

	while (first < last)
	{
		max_area = max(max_area, min(*first, *last) * distance(first, last));

		if (*first < *last)
		{
			++first;
		}
		else
		{
			--last;
		}
	}

	return max_area;
}
/*
	while (first != last)
	{
		int dist = distance(first, last);
		int area = min(*first, *last) * dist;
		max_area = area > max_area ? area : max_area;

		int next_first = *(first + 1);
		int next_last = *(last - 1);

		int max_first = min(next_first, *last);
		int max_last = min(*first, *(last - 1));

		if (max_first > max_last) {
			max_area = min(*first, *(first + 1)) > max_area ? min(*first, *(first + 1)) : max_area;
			++first;
			continue;
		}
		else if (max_first < max_last) {
			max_area = min(*last, *(last - 1)) > max_area ? min(*last, *(last - 1)) : max_area;
			--last;
			continue;
		}
		else {
			if (*first >= *last) {
				max_area = min(*first, *(first + 1)) > max_area ? min(*first, *(first + 1)) : max_area;
				++first;
			}
			else {
				max_area = min(*last, *(last-1)) > max_area ? min(*last, *(last - 1)) : max_area;
				--last;
			}
		}
	}
	return max_area;
	
}*/
		/*
		int dist = distance(first, last);
		int area = min(*first, *last) * dist;
		max_area = area > max_area ? area : max_area;

		int next_first = *(first + 1);
		int next_last = *(last - 1);

		int max_first = min(next_first, *last);
		int max_last = min(*first, *(last - 1));

		if (max_first > max_last) {
			if (first != height.begin()) {
				int area_ = min(*--first, *first);
				max_area = area_ > max_area ? area_ : max_area;
				
			}
			continue;
		}
		else if (max_first < max_last) {
			if (last != height.begin()) {
				int area_ = min(*--last, *last);
				max_area = area_ > max_area ? area_ : max_area;
			}
			continue;
		}
		else {
			if (*first >= *last) {
				if (first != height.end()) {
					int area_ = min(*++first, *first);
					max_area = area_ > max_area ? area_ : max_area;
				}

			}
			else {
				if (last != height.begin()) {
					int area_ = min(*--last, *last);
					max_area = area_ > max_area ? area_ : max_area;
				}
			}
		}
	}
	return max_area;
}
		/*
		// finding next step
		if (*++first > *--last) {
			++last;
			continue;
		}
		--first;
		++last;

		if (*++first < *--last) {
			--first;
			continue;
		}
		--first;
		++last;
		//else {
		//	++last;
		//	++first;
			if (*first >= *last) {
				++first;
				continue;
			}
			--last;
			continue;
		//}
	}
	return max_area;
	/*
	vector<value_index<int>> v(height.size());
	unsigned i_ = 0;
	for_each(v.begin(), v.end(), [&i_, &height](value_index<int>& e) {e.p.first = height[i_]; e.p.second = i_++; });

	stable_sort(v.begin(), v.end(), [](const value_index<int>& l, const value_index<int>& r) { return l.p.first > r.p.first; });

	auto it2 = --height.end();
	for (auto it = height.begin(); it != height.end(); ++it) {

		/*
		int area = min(*it, *it2) * distance(it2, it);
		if (area > max_area) {
			cout << min(*it, *it2) << " : " <<  distance(it2, it) << endl;
			max_area = area;
		}
		
	//	if (area > max_area) max_area = area;
		//auto it2 = lower_bound(v.begin(), v.end(), value_index<int>({ *it, (int)(it - height.begin()) }));
		auto it2 = find(v.begin(), v.end(), value_index<int>({ *it, (int)(it - height.begin()) }));
		if (it2 == v.end()) continue;
		for (auto it3 = v.begin(); it3 >= it2; ++it3) {
			int area = min(it3->p.first, it2->p.first) *( max(it3->p.second, it3->p.second) - min(it2->p.second, it2->p.second));

			if (area > max_area) max_area = area;

		}
	}
	return max_area;
	*/
	/*
	vector<value_index<int>> v(height.size());
	unsigned i_ = 0;


	
	for_each(v.begin(), v.end(), [&i_, &height](value_index<int>& e) {e.p.first = height[i_]; e.p.second = i_++; });

	stable_sort(v.begin(), v.end(), [](const value_index<int>& l, const value_index<int>& r) { return l.p.first > r.p.first; });

	for (auto it1 = height.begin(); it1 != height.end(); ++it1) 
	{
		for (auto it2 = it1+1; it2 != height.end(); ++it2)
		{
			
			int dist = it2 - it1;
			int min_height = min(*it1, *it2);
			int area = dist * min_height;
			if (area > max_area) 
			{
				max_area = area;
			}
		}
	}
	return max_area;
	//return get_max_area(v, ++v.cbegin(), v.size() - 1);
	/*
	auto first = v.cbegin();
	auto second = v.cbegin();
	//  auto second = first;
	advance(second, 1);
	int d2 = height.size() - 1;

	//set<int> dists;

	while (second != v.cend() && d2 > 0)
	{
		set<int> dists;
		for (int d1 = height.size() - 1; d1 >= d2; --d1) {
			for (auto second1 = v.cbegin(); second1 != second + 1; ++second1) {
				for (auto second2 = v.cbegin(); second2 != second1+1; ++second2) {
					int dist = max(second1->p.second, second2->p.second) - min(second1->p.second, second2->p.second);
					if (dist == d1) {
						// d1 * second1->p.first;
						dists.insert(d1 * second1->p.first);
					}
				}
			}
		}
		if (!dists.empty()) return *--dists.cend();
		++second;
		--d2;
	}
	*/
	//max_area = *--dists.cend();
	//return max_area;
//}
			/*
			for (auto second1 = v.cbegin(); second1 != second+1; ++second1) {
				for (auto second2 = v.cbegin(); second2 != second1+1; ++second2) {
					int dist = max(second1->p.second, second2->p.second) - min(second1->p.second, second2->p.second);
					dists.insert(dist * second1->p.first );
			//		dists[dist] = second1->p.first;
					//dists.insert({ dist, second1->p.first });
					//dists.push_back({ dist, second1->p.first });
				}
			}
			*/
			//	return *dists.begin();
				/*
				for (int d1 = height.size() - 1; d1 >= d2; --d1) {
					int c = dists[d1];
					if (c) {
						return d1 * c;
					}
					/*
					auto f = find_if(dists.cbegin(), dists.cend(), [&d1](const pair<int, int>& a) {return a.first == d1; });
					if (f != dists.cend()) {
						return d1 * f->second;
					}

				}
				*/

		
		/*
		set<int> areas;

		for (int d1 = height.size() - 1; d1 >= d2; --d1) {

			int dist = max(second->p.second, first->p.second) - min(second->p.second, first->p.second);
			if (dist == d1) {
				areas.insert(d1 * second->p.first);
			}
		}
		if (!areas.empty()) {
			return *areas.begin();
		}
		++second;
		++first;
		--d2;
		*/
		

		/*
		for (int d1 = height.size() - 1; d1 >= d2; --d1) {
			for (auto second1 = v.cbegin(); second1 != second; ++second1) {
				for (auto second2 = v.cbegin(); second2 != second1; ++second2) {
					int dist = max(second1->p.second, second2->p.second) - min(second1->p.second, second2->p.second);
					if (dist == d1) {
						return d1 * second1->p.first;
					}
				}
			}
		}
		*/

		/*
		for (auto second1 = v.cbegin(); second1 != v.cend(); ++second1) {
			for (auto second2 = second1; second2 != v.cend(); ++second2) {
				for (int d1 = height.size() - 1; d1 >= d2; --d1) {
					int dist = max(second2->p.second, second1->p.second) - min(second2->p.second, second1->p.second);
					if (dist == d1) {
						areas.insert(d1 * second->p.first);
					}
				}
			}
		}
	
		
		for (auto first = v.cbegin(); first != second; ++first) {
			for (int d1 = height.size() - 1; d1 >= d2; --d1) {
				int dist = max(second->p.second, first->p.second) - min(second->p.second, first->p.second);
				if (dist == d1) {
					areas.insert(d1 * second->p.first);
				}
			}
		}
		for (int d1 = height.size() - 1; d1 >= d2; --d1) {
			for (auto first = v.cbegin(); first != second; ++first) {
				int dist = max(second->p.second, first->p.second) - min(second->p.second, first->p.second);
				if (dist == d1) {
					areas.insert(d1 * second->p.first);
				}
			}
		}
		*/
		
		/*
		if (!areas.empty()) {
			return *areas.begin();
		}
		
		auto first = v.cbegin();
		int d1 = height.size() - 1;\\\\\\\\\\\\\\\\\\\\\

		while (first != second && d1 >= d2)
		{
			int m_area = 0;

			int dist = max(second->p.second, first->p.second) - min(second->p.second, first->p.second);
			if (dist == d1)
			{
				max_area = d1 * second->p.first;
				return max_area;
			}
			++first;
			--d1;
			
		}*/
	//}
	

	/*
	bool dec_d = false;
//	bool inc_sec = false;

	while (second != v.cend() || d != 0)
	{
		auto first = v.cbegin();
		while (first->p.first >= second->p.first)
		{
			for (auto first_sec = first; first_sec != second; ++first_sec) {

				int dist = max(second->p.second, first_sec->p.second) - min(second->p.second, first_sec->p.second);
				if (dist == d)
				{
					max_area = d * second->p.first;
					return max_area;
				}
				//++first_sec;
			}
			++first;
		}

		if (dec_d) {
			dec_d = false;
			++second;
			++d;
		}
		else {
			dec_d = true;
			--d;
			//++second;
		}
		
	}
		/*
		//  if (--d == 0 || ++second == v.cend()) break;

		  //--d; 
		if (--d == 0) break;
		int next_area1 = d++ * second->p.first;

		int next_area2 = 0;
		if (--second != v.cbegin())
			next_area2 = d * second->p.first;
		++second;

		int next_area3 = 0;
		if (++d != v.size())
			next_area3 = d * second->p.first;
		--d;

		if (++second == v.cend()) break;
		int next_area4 = d * (second--)->p.first;

		int c = max({ next_area1, next_area2, next_area3, next_area4 });
		if (c == next_area1) {
			--d;
			continue;
		}
		
		if (c == next_area2)
		{
			--second;
			continue;
		}
		if (c == next_area3) {
			++d;
			continue;
		}
		else {
			++second;
			continue;
		}
		*/
	//}
//	return max_area;
//}
int main() {
	auto t1 = chrono::high_resolution_clock::now();
	//vector<int> v{ 1, 8, 6, 2, 5, 4, 8, 3, 7 };
	vector<int> v{ 3846, 7214, 9316, 9869, 2423, 4235, 4921, 5878, 9832, 5302, 4298, 4312, 8571, 531, 3206, 7504, 8321, 9385, 657, 3095, 1486, 8099, 1635, 2735, 1160, 228, 3388, 1557, 7094, 4465, 8611, 3020, 6142,
		182, 4742, 2507, 3284, 2005, 7686, 6688, 3987, 3137, 781, 5463, 3098, 3637, 9384, 7166, 7751, 6068, 5560, 9329, 8846, 6705, 6672, 7069, 8478, 7126, 1758, 1313, 7419, 1087, 9752, 4609, 4133, 821, 6526, 897,
		4482, 7483, 4920, 6017, 938, 882, 9106, 6324, 7766, 8094, 6619, 8662, 3577, 1415, 8896, 1432, 1104, 95, 4291, 1289, 5920, 8682, 9432, 6298, 3931, 1803, 401, 6743, 69, 7138, 2465, 5315, 6997, 4722, 2557,
	//	4915, 7727, 2196, 9478, 1355, 8706, 5934, 1019, 984, 5214, 800, 8195, 4819, 8201, 1796, 3767, 4032, 40, 4107, 4219, 2593, 4688, 9805, 966, 5597, 5426, 5532, 2747, 9954, 1749, 3301, 153, 807, 759, 6921, 5094,
	//	1780, 9993, 8560, 9992, 5660, 7071, 9204, 3621, 192, 4119, 9603, 9674, 9420, 706, 8089, 4300, 8636, 2108, 6314, 3537, 6891, 532, 1810, 9538, 162, 9776, 9457, 89, 7941, 165, 4397, 8630, 4089, 9710, 1275, 3187, 7333, 5428, 1965, 7125, 1097, 5741, 5652, 2158, 1601, 4160, 5353, 7806, 6324, 322, 8684, 2245, 4585, 7469, 6817, 3629, 3305, 2182, 5236, 535, 900, 4492, 3610, 3898, 437, 2581, 2529, 8729, 3421, 6821, 4662, 1850, 3793, 3449, 3546, 7550, 9002, 2793, 7530, 6107, 5866, 2012, 7023, 199, 6029, 535, 333, 4237, 9118, 3929, 5695, 2813, 1645, 80, 6919, 3373, 13, 7123, 3286, 8928, 3191, 4770, 9441, 8278, 9669, 6089, 2489, 2956, 3970, 4345, 6127, 8328, 3535, 4321, 3468, 7923, 9811, 842, 7326, 2076, 1600, 1995, 7744, 7854, 9774, 1029, 7859, 2425, 592, 6966, 3952, 2699, 4060, 1388, 3463, 5428, 3653, 6696, 7254, 585, 8262, 886, 5626, 8555, 9638, 5954, 727, 2972, 1862, 26, 6140, 4892, 6756, 6241, 5886, 2674, 5324, 6967, 6528, 6986, 8020, 5651, 5867, 6374, 5550, 8676, 5024, 4149, 4837, 6774, 965, 7857, 7761, 7804, 7323, 8312, 545, 2232, 5001, 6498, 3920, 1374, 8504, 7776, 9789, 6135, 9623, 2727, 1211, 7427, 7440, 5792, 5730, 4246, 5545, 3914, 7909, 223, 5042, 3857, 6793, 7682, 9552, 3402, 9218, 5161, 9195, 9495, 9556, 2127, 9430, 8839, 30, 9458, 367, 8485, 2541, 9537, 7740, 8888, 7762, 6237, 9955, 6230, 4430, 9572, 7342, 713, 10, 6198, 9655, 7546, 1508, 5874, 1213, 422, 1611, 5046, 3878, 1585, 5181, 4527, 7680, 1898, 5003, 123, 9517, 9365, 4746, 3095, 6184, 3058, 1015, 9829, 4127, 4448, 8240, 4212, 8040, 6251, 2753, 4846, 185, 1285, 2205, 3927, 7895, 5306, 2109, 4533, 1135, 3344, 7144, 4610, 8898, 9550, 2607, 6203, 7170, 6082, 6151, 8410, 1147, 4885, 5976, 2895, 8551, 2828, 199, 4196, 2361, 2115, 8340, 9120, 3777, 5619, 763, 1750, 9836, 441, 4556, 9446, 4950, 1424, 8502, 5408, 5596, 5897, 5387, 948, 7572, 8922, 5718, 9148, 6146, 8230, 3913, 7817, 3257, 8853, 5649, 4090, 4716, 7382, 3324, 2894, 8391, 4260, 5519, 651, 6612, 3844, 4548, 4493, 6954, 5894, 6774, 9223, 6376, 8795, 3360, 8826, 9362, 12, 4145, 718, 5485, 5970, 7820, 6876, 9220, 7889, 4587, 9424, 9759, 8738, 6098, 8536, 9442, 4419, 4337, 313, 3516, 4787, 6385, 7604, 1054, 1633, 5734, 2734, 5921, 3006, 5343, 3581, 1973, 6189, 190, 4127, 4026, 3952, 4085, 3053, 7065, 311, 3601, 5767, 7906, 9958, 9269, 4539, 2166, 267, 5569, 3261, 4114, 5961, 708, 5307, 1863, 6531, 6962, 608, 1865, 7571, 6040, 5180, 5550, 2419, 5860, 3430, 3125, 6315, 6772, 976, 6340, 9290, 2382, 3871, 5779, 9309, 9469, 8350, 5137, 9493, 6943, 8341, 8013, 2184, 6157, 8740, 4193, 251, 4025, 4730, 8695, 3825, 6582, 2636, 3058, 7980, 4048, 1990, 5075, 2668, 3283, 9909, 9256, 3584, 5956, 3194, 7371, 3825, 8403, 3359, 8849, 9015, 5638, 7008, 2008, 4896, 2980, 8978, 5856, 2578, 2397, 659, 9364, 9527, 2075, 456, 1239, 7744, 3154, 6226, 8245, 6333, 1327, 6291, 1064, 45, 5225, 3642, 4600, 349, 6252, 2191, 479, 4823, 5318, 7256, 2370, 6608, 5018, 8472, 6014, 9016, 2590, 2810, 6169, 6192, 6214, 4851, 8525, 3323, 2426, 8892, 3277, 2356, 6501, 9196, 3396, 5234, 9335, 7878, 5136, 6070, 238, 2570, 3301, 1526, 3783, 5322, 2824, 8780, 1161, 6471, 3292, 5834, 1328, 5954, 7033, 979, 6621, 3427, 5582, 2149, 7813, 5537, 2876, 6540, 6698, 63, 9866, 4047, 4163, 162, 7455, 6773, 2912, 1407, 6476, 4956, 9775, 4689, 8620, 8758, 431, 8426, 7087, 8761, 1514, 7322, 4111, 2126, 9374, 284, 3370, 9360, 4724, 3894, 9743, 3114, 3944, 293, 7923, 8860, 9771, 5804, 6732, 3289, 8437, 5038, 7518, 8683, 2377, 4834, 6649, 4306, 705, 3699, 251, 5295, 8387, 3320, 568, 1100, 6312, 1584, 9920, 6545, 8669, 6752, 1913, 3004, 309, 5494, 9105, 7776, 3591, 4075, 3604, 4331, 7908, 1979, 9074, 985, 3904, 8041, 5651, 9556, 7557, 2522, 1226, 4424, 3700, 2033, 1234, 8658, 4792, 7056, 9454, 5247, 7166, 3775, 9235, 5750, 6329, 6426, 2303, 6809, 6775, 8310, 4693, 4862, 6667, 3162, 8646, 9731, 1361, 8302, 7375, 746, 3241, 9884, 9063, 9241, 2670, 3179, 9476, 9325, 9448, 2371, 343, 1919, 6701, 4705, 340, 640, 5195, 7551, 7945, 4211, 1277, 4230, 1940, 8045, 9306, 4175, 6152, 3730, 1898, 6313, 1163, 4484, 4183, 5585, 8555, 3035, 272, 6829, 3230, 1137, 3569, 7868, 4673, 8353, 197, 3367, 3251, 7336, 3468, 3362, 590, 7884, 7773, 1783, 3165, 1277, 1804, 9593, 6132, 8179, 7722, 7855, 2070, 3388, 3173, 7582, 2308, 8124, 8621, 9915, 1534, 1137, 5547, 8205, 2088, 35, 4920, 2460, 9324, 5950, 1357, 5555, 6618, 9074, 7283, 1135, 8725, 591, 5502, 1554, 6699, 9593, 6237, 6808, 3699, 4566, 2673, 8475, 8309, 2825, 8544, 2248, 7755, 1063, 3113, 1260, 714, 4703, 3647, 6838, 2987, 7765, 8468, 4209, 6288, 3859, 3272, 3688, 4571, 9990, 2639, 7520, 6306, 4732, 1080, 5188, 3394, 5510, 2291, 3646, 1912, 6891, 7018, 831, 2874, 106, 4760, 8091, 6154, 3864, 6833, 6830, 8883, 6946, 1045, 4234, 386, 6918, 850, 9052, 4437, 9068, 6362, 5338, 7033, 5735, 2770, 7368, 8065, 6535, 416, 111, 2733, 719, 8310, 3658, 2648, 890, 3688, 3875, 8068, 7847, 3116, 7626, 5128, 5655, 2784, 7030, 6822, 6589, 6734, 9213, 1643, 8120, 6671, 2222, 593, 9452, 7929, 4279, 9160, 5462, 4912, 1138, 2697, 5197, 8945, 3950, 7480, 5872, 863, 1244, 2064, 5003, 4523, 3501, 779, 4586, 6957, 3933, 1982, 1992, 1782, 9684, 5280, 6822, 2325, 5544, 1582, 4765, 5136, 1273, 2851, 996, 4098, 7855, 7313, 8287, 8836, 2906, 7483, 2722, 7878, 5842, 61, 9657, 2062, 5644, 466, 9570, 2387, 3919, 8842, 7539, 4149, 883, 225, 8706, 8049, 2082, 9242, 407, 6673, 5368, 4666, 7194, 3693, 9793, 8506, 8872, 781, 4890, 4642, 7529, 5441, 2906, 7792, 5207, 7466, 8164, 5568, 6691, 7598, 3842, 6575, 4144, 3956, 8146, 9035, 4536, 8752, 49, 2225, 8697, 9108, 3478, 5537, 2442, 8768, 9545, 6391, 9476, 2977, 3271, 7271, 7009, 2769, 9762, 8268, 2545, 4822, 6927, 2857, 5535, 7678, 4831, 8042, 5954, 4131, 7650, 5336, 2750, 4262, 9515, 255, 5407, 6662, 4895, 8692, 652, 8403, 9643, 2354, 2887, 2612, 7217, 1632, 3097, 6742, 1556, 126, 9555, 7454, 4385, 2303, 7308, 3212, 8022, 8348, 1628, 4040, 403, 9946, 4850, 392, 17, 7569, 1089, 4099, 74, 8543, 8587, 8932, 3746, 7618, 9706, 5771, 9799, 1195, 4468, 7531, 9994, 2266, 8531, 9761, 1065, 587, 5277, 6526, 7600, 643, 3588, 1671, 8292, 7361, 928, 6845, 8764, 4245, 1968, 6975, 9530, 6445, 6354, 8956, 7367, 5124, 7220, 3318, 1584, 3887, 9983, 1510, 8245, 9261, 2717, 2151, 9317, 9191, 7138, 2414, 6230, 4719, 5622, 3881, 9915, 7078, 3527, 92, 8560, 6141, 5857, 7146, 9061, 7233, 7201, 2883, 6333, 7025, 936, 2966, 4000, 4838, 4287, 8255, 9816, 8824, 9903, 2185, 7888, 5107, 6693, 1576, 383, 9652, 8018, 2698, 4692, 4462, 6679, 4212, 6167, 9035, 4299, 6083, 4878, 4303, 2339, 154, 2631, 3489, 3213, 4296, 4381, 9582, 8893, 5642, 5353, 2080, 6844, 4556, 5844, 8031, 3163, 6087, 4042, 2006, 6480, 9586, 8527, 1526, 92, 7302, 1712, 7336, 4390, 1777, 1649, 4675, 5696, 1351, 9725, 5137, 6480, 6299, 4086, 7808, 3531, 6284, 1597, 4091, 8823, 7639, 2494, 9721, 1083, 5398, 7796, 2000, 1669, 7245, 8607, 962, 5542, 1152, 618, 9701, 9501, 9813, 2680, 3076, 7156, 6105, 9209, 5305, 8827, 7577, 8247, 7791, 653, 848, 6365, 5085, 4687, 2767, 2653, 7926, 1558, 3767, 7044, 1239, 5318, 8611, 6536, 5761, 8622, 2251, 7050, 8990, 2989, 7986, 6989, 4591, 5946, 241, 7430, 9058, 8724, 1005, 2054, 7439, 5010, 4321, 5527, 7882, 1941, 5651, 1578, 3352, 3522, 4510, 228, 8451, 2180, 5277, 9314, 2158, 1429, 411, 5643, 4843, 2106, 2082, 62, 8405, 8267, 3853, 9817, 1543, 6318, 7462, 9959, 3331, 5868, 7164, 3197, 6888, 3221, 3479, 6688, 4769, 3791, 406, 8050, 633, 5939, 1265, 3263, 4801, 1454, 2514, 2785, 5463, 5665, 8090, 3499, 4828, 9002, 3910, 1472, 3987, 898, 9059, 6064, 654, 1309, 5706, 5459, 218, 4132, 500, 1562, 904, 7696, 6067, 5112, 582, 6924, 8920, 9951, 9241, 222, 8767, 1731, 5544, 123, 2759, 9895, 5767, 374, 9222, 1624, 1671, 1544, 8654, 5033, 6213, 1435, 8544, 4514, 8042, 6251, 8540, 2428, 1124, 5654, 2881, 1367, 1807, 2285, 407, 8432, 5078, 1933, 6410, 164, 6598, 4657, 2174, 8965, 3255, 6319, 1290, 101, 5622, 9986, 9732, 1518, 1354, 6477, 1186, 2604, 323, 1126, 4520, 3552, 6499, 7790, 6726, 2099, 9480, 7450, 9756, 404, 2690, 4830, 6390, 7091, 4804, 4079, 8285, 4993, 5412, 9887, 1624, 8246, 2308, 3218, 9325, 9280, 4472, 3514, 9609, 2728, 7468, 8292, 8203, 3715, 7123, 6468, 5543, 4947, 3787, 572, 4851, 2257, 1444, 2572, 116, 2149, 4222, 9411, 1045, 563, 202, 8719, 8564, 3473, 3786, 7961, 1451, 8412, 7781, 2756, 3368, 6579, 4211, 9, 3495, 1036, 8696, 4791, 1104, 2156, 1213, 9826, 2680, 8516, 8940, 2406, 7181, 7477, 1774, 9088, 6688, 2942, 7581, 8726, 6195, 6871, 8474, 3210, 2695, 3480, 9098, 7955, 1778, 653, 1432, 9008, 9149, 4801, 2750, 5198, 5787, 8816, 7219, 7308, 4065, 5157, 2586, 6805, 4555, 4910, 5433, 2329, 3178, 9226, 5665, 4213, 1311, 1342, 9826, 4753, 2802, 7546, 1298, 8465, 369, 6916, 6298, 7714, 6455, 4442, 9687, 8491, 6938, 2050, 6850, 965, 2148, 5418, 3613, 882, 3089, 7731, 5140, 2391, 8320, 4670, 9307, 9324, 6106, 5599, 7084, 6180, 2034, 5220, 1629, 2432, 632, 1689, 6668, 8042, 1637, 3582, 4201, 6199, 7675, 9714, 9924, 9803, 776, 3949, 8669, 7788, 7020, 5627, 4733, 6105, 3495, 8158, 3940, 4448, 6408, 6924, 9168, 5408, 2403, 5894, 8664, 9919, 1926, 8921, 5625, 7772, 6647, 8810, 6100, 3299, 1390, 8300, 9007, 4248, 2384, 2912, 7088, 5961, 8633, 3912, 7691, 2845, 6236, 217, 1557, 1185, 558, 3141, 1389, 4558, 2960, 2898, 7543, 7662, 71, 5649, 4468, 2586, 7934, 4379, 9840, 4214, 6991, 4634, 4108, 3844, 3409, 3551, 1286, 9638, 1507, 3961, 4158, 5346, 1393, 3674, 7570, 5038, 3384, 5685, 4199, 8327, 4800, 4413, 2916, 9482, 8868, 4009, 7774, 2004, 1915, 913, 8773, 9217, 1620, 248, 4126, 1666, 5335, 8201, 8730, 9465, 9706, 1872, 3417, 1437, 1731, 8360, 8504, 3961, 9998, 9305, 4312, 3516, 4873, 2614, 4607, 5379, 6977, 6698, 1369, 9413, 2362, 5160, 3377, 9740, 2190, 4279, 198, 8120, 5346, 7727, 2752, 8442, 5453, 7218, 1740, 9129, 6907, 6093, 1645, 3246, 7387, 9208, 1768, 2694, 5353, 4098, 8831, 4122, 6031, 7704, 2337, 3335, 23, 2065, 3553, 5795, 4186, 4813, 5616, 6849, 5830, 7091, 4647, 3033, 5885, 3483, 7522, 590, 9360, 4170, 6779, 2440, 4181, 2351, 6068, 1954, 2460, 7921, 2788, 7535, 2983, 2490, 7964, 396, 2365, 7701, 5126, 1454, 450, 4425, 6596, 9814, 7902, 2485, 261, 9062, 2994, 1536, 5610, 9803, 2404, 8447, 938, 2010, 1078, 3663, 5972, 4961, 8078, 4781, 7871, 5898, 7890, 986, 9047, 3773, 2104, 9086, 4593, 356, 4675, 838, 804, 9363, 7194, 5065, 7916, 6932, 3642, 4741, 8870, 5850, 5864, 4858, 9402, 5095, 7647, 3570, 6853, 9927, 6656, 4535, 1523, 4251, 2874, 3993, 4801, 4631, 3184, 2078, 5360, 3947, 8126, 7390, 9443, 6025, 8241, 3321, 5779, 2181, 3933, 6181, 4737, 33, 4444, 3615, 595, 5244, 1236, 9815, 8366, 2619, 4736, 7411, 8349, 3697, 5481, 6536, 6124, 417, 5543, 8446, 358, 6195, 2576, 6503, 4981, 6952, 6200, 3988, 2084, 5060, 6482, 2212, 418, 4060, 5635, 7782, 129, 4556, 4103, 6069, 9956, 3116, 5733, 385, 6671, 8563, 4823, 7710, 4248, 3410, 479, 9033, 209, 4203, 1818, 6568, 5774, 7916, 1312, 6008, 7036, 2840, 6642, 6113, 9270, 4089, 362, 4572, 5449, 5785, 6168, 4997, 1527, 6718, 4703, 550, 9839, 2754, 1430, 3077, 9079, 3974, 2597, 9997, 4581, 8810, 4030, 1646, 7251, 4987, 3665, 1019, 6984, 1828, 1432, 7709, 3469, 8628, 112, 4560, 9157, 582, 6703, 277, 4311, 2408, 538, 5264, 4196, 8083, 1709, 6329, 2275, 2330, 455, 2628, 7228, 3249, 853, 4383, 1644, 4874, 3663, 7851, 3812, 5469, 9422, 2388, 4682, 6638, 866, 5812, 6393, 1381, 7779, 1664, 6100, 3980, 2150, 1169, 1568, 2865, 2035, 9293, 5318, 8643, 9302, 7411, 2703, 5470, 3828, 726, 1032, 9843, 5977, 6436, 1530, 1936, 1803, 2810, 3867, 6987, 8318, 3774, 6260, 6260, 7862, 5907, 3411, 7834, 1799, 7246, 7066, 9822, 4595, 8276, 4644, 9524, 4466, 39, 6120, 5996, 6107, 4477, 1506, 4431, 1446, 2275, 6865, 8724, 4094, 6791, 8235, 5353, 356, 2141, 8541, 9212, 9113, 2445, 5690, 5206, 7372, 790, 5881, 2791, 2659, 2600, 3759, 9966, 2262, 6867, 5149, 6524, 2333, 6780, 3544, 4553, 3083, 1010, 6720, 1852, 2023, 3375, 3133, 8031, 433, 5448, 4302, 7795, 8499, 6530, 8909, 4274, 9513, 934, 3128, 5257, 6568, 8201, 8375, 4468, 4086, 4178, 9859, 998, 6127, 2504, 4233, 2792, 8128, 9735, 3554, 388, 7686, 1805, 6258, 5516, 6703, 8938, 9407, 373, 3973, 170, 5809, 3529, 1845, 4502, 9968, 6261, 8433, 7680, 5435, 9926, 3703, 8144, 554, 5573, 9539, 1610, 9166, 6439, 2811, 9032, 8409, 392, 2698, 911, 9726, 7976, 8605, 7975, 1075, 6736, 5496, 5800, 5317, 8006, 5605, 4570, 4969, 6969, 5347, 1645, 1259, 250, 3241, 8537, 6225, 2246, 3433, 5124, 6490, 1216, 6759, 3618, 3066, 3174, 763, 2883, 9392, 1727, 25, 1551, 5968, 5214, 3197, 271, 6816, 7652, 3187, 2349, 5259, 3916, 905, 8688, 5515, 9434, 4006, 3315, 8018, 9826, 5961, 3065, 7332, 1294, 787, 5849, 9785, 4988, 8406, 1783, 8656, 8815, 8848, 9375, 5457, 125, 7867, 9022, 7965, 487, 8458, 3139, 2529, 7513, 611, 8141, 3728, 7656, 5978, 750, 7116, 5609, 7399, 2445, 7567, 7477, 4316, 2423, 2032, 5327, 644, 7280, 6100, 8858, 9241, 3545, 142, 4782, 411, 1556, 1808, 3706, 6420, 7902, 3050, 9682, 1130, 4069, 6815, 5915, 8346, 1591, 8618, 5079, 5388, 2042, 2476, 586, 3143, 9856, 1752, 8456, 8696, 7919, 4256, 4656, 6462, 8915, 3247, 5425, 4899, 7785, 3785, 8740, 3113, 9758, 8827, 1218, 5315, 2927, 6092, 2011, 7938, 3451, 9566, 432, 7320, 9366, 9025, 4166, 4209, 5755, 585, 8538, 8607, 9646, 3560, 731, 3443, 5432, 9887, 1796, 6203, 7847, 3182, 7209, 7586, 2239, 2280, 1749, 3105, 2195, 3845, 4195, 7085, 9789, 2203, 1192, 8731, 5309, 1192, 9524, 9212, 2036, 8703, 1031, 192, 5191, 5308, 6608, 4596, 3721, 906, 4195, 3699, 8670, 7868, 7051, 9206, 6273, 7626, 3001, 1542, 742, 4170, 5610, 6143, 4284, 4946, 6318, 5942, 5282, 9873, 9793, 1867, 4597, 1462, 6673, 1184, 6025, 2946, 2676, 1618, 3087, 2445
	//, 8719, 3079, 6352, 4954, 1448, 7949, 2947, 1633, 1194, 4714, 9176, 8731, 5537, 5688, 6139, 6290, 127, 7832, 9841, 6934, 6281, 1966, 1815, 4300, 4780, 9909, 8608, 4602, 8429, 1316, 1511, 1199, 8553, 2504, 2497, 7556, 2109, 202, 7044, 805, 9380, 7608, 5726, 1345, 9353, 1209, 3170, 3531, 3261, 5801, 2507, 197, 1789, 7222, 7703, 3713, 144, 2057, 4302, 5313, 9478, 7222, 3558, 1543, 8312, 9960, 5826, 6645, 6614, 1171, 4487, 933, 6289, 8137, 9753, 2611, 6637, 8453, 3616, 6904, 324, 8388, 2033, 5576, 1870, 9435, 4190, 2279, 2466, 3148, 6220, 9369, 5345, 6643, 5446, 982, 9147, 8936, 655, 9930, 2047, 2742, 1035, 6778, 8393, 9257, 5488, 579, 839, 9041, 6380, 3979, 1982, 6360, 9998, 3668, 8901, 8771, 5827, 1382, 7635, 9353, 989, 4772, 7608, 1750, 9995, 4136, 4459, 3050, 6521, 9208, 7638, 4092, 9321, 7293, 2893, 1715, 1172, 1759, 7997, 1745, 2238, 3427, 6699, 1091, 3702, 4356, 7949, 4688, 3384, 5316, 2863, 6788, 299, 2774, 3434, 2430, 7820, 2519, 5013, 4151, 8119, 6054, 1145, 1002, 5905, 7265, 3018, 9251, 1324, 9940, 5270, 7011, 9183, 3530, 5254, 8378, 554, 3649, 1112, 3953, 9830, 9491, 9446, 9178, 2289, 1203, 8461, 6471, 5710, 1880, 2155, 6304, 6500, 6154, 4917, 1160, 8632, 8178, 7099, 3638, 5312, 5534, 7174, 1942, 6493, 5472, 739, 3940, 350, 8, 6037, 5875, 3017, 9398, 1884, 6451, 4149, 7394, 7450, 3761, 4791, 8361, 6484, 4283, 8199, 1516, 8363, 9587, 2824, 513, 603, 7630, 6854, 3835, 8831, 2571, 909, 1726, 8193, 6652, 7275, 808, 5705, 6667, 7147, 8294, 7631, 2014, 2009, 6708, 5819, 9834, 2023, 8792, 4182, 5833, 6208, 4741, 6210, 3517, 9351, 8168, 7406, 5015, 7595, 5800, 4024, 1493, 8434, 9281, 1062, 7243, 3155, 4774, 6237, 9199, 7262, 9055, 2455, 4831, 5189, 3355, 8261, 5516, 6609, 9660, 9226, 4588, 4663, 3247, 2458, 9382, 444, 4010, 5324, 8835, 2726, 1828, 9764, 2435, 9119, 1967, 39, 1415, 3740, 3631, 7523, 9049, 9231, 7179, 9166, 7896, 3396, 9924, 7213, 8386, 6603, 4845, 1002, 9053, 4212, 6465, 1004, 8687, 8392, 6397, 6905, 2019, 6373, 5265, 2816, 2063, 9855, 4696, 3119, 4831, 9168, 2119, 5705, 207, 3420, 5481, 4389, 9467, 852, 2461, 6965, 3797, 2070, 4856, 5297, 4316, 1356, 1730, 3980, 6172, 4171, 7628, 8622, 3787, 2088, 1061, 3729, 4006, 9735, 190, 8727, 3063, 2063, 4101, 5729, 9069, 3843, 3108, 2955, 6925, 4807, 5237, 6355, 8604, 6189, 9698, 2510, 6098, 1984, 6746, 384, 5575, 2332, 8947, 3520, 2739, 2584, 2503, 762, 1239, 1800, 7929, 8504, 7512, 3711, 1480, 2869, 8147, 2306, 357, 603, 6390, 370, 2866, 7141, 5295, 5516, 4360, 6858, 7619, 8833, 322, 5924, 8485, 459, 7058, 2350, 4752, 4612, 6058, 484, 7358, 1704, 5257, 2921, 7847, 9168, 6881, 8559, 7308, 8268, 532, 8084, 8362, 2207, 3125, 5026, 7771, 7233, 1861, 3934, 6196, 7291, 5062, 4812, 607, 4593, 8903, 2620, 3375, 6416, 4824, 2011, 3615, 769, 5480, 6103, 1953, 3195, 3815, 9044, 1586, 9285, 3645, 6627, 3070, 6005, 8892, 1043, 8345, 8762, 3812, 1462, 5226, 5258, 5703, 9560, 1441, 4160, 6170, 3024, 2305, 2095, 7642, 1732, 9303, 5460, 6270, 6951, 7389, 8146, 704, 4837, 9943, 6620, 7987, 108, 5051, 8589, 3509, 2138, 1351, 1030, 4789, 2252, 4210, 6254, 4951, 2525, 3577, 5588, 3479, 7375, 919, 1514, 7000, 3689, 1089, 8671, 9353, 8805, 4811, 9793, 6243, 8780, 1903, 6068, 371, 4833, 7119, 564, 7773, 4455, 5882, 524, 1009, 4258, 8540, 5011, 2018, 9812, 4443, 3912, 5584, 3020, 0, 8200, 8506, 5422, 2346, 6827, 6083, 6941, 5614, 4126, 763, 1255, 9822, 9763, 1598, 1040, 6922, 6535, 4792, 2811, 4902, 2239, 5100, 4191, 8618, 417, 2944, 1815, 7553, 3999, 4524, 5995, 962, 8698, 1278, 4158, 3593, 7170, 9000, 6529, 6611, 7920, 1330, 9256, 8846, 7250, 4513, 1407, 7947, 6222, 9523, 1895, 1066, 6998, 4325, 691, 5441, 5152, 5477, 3602, 190, 5850, 3195, 8628, 3936, 5353, 5875, 1947, 1844, 9633, 4117, 2983, 2741, 3927, 2552, 4419, 1392, 1938, 7502, 2792, 9152, 8956, 7973, 6114, 3989, 9131, 8991, 9443, 9994, 4209, 8953, 3134, 4520, 7758, 9744, 1245, 6159, 1446, 7546, 4762, 5622, 1687, 9086, 4591, 9517, 3440, 9483, 4906, 7890, 2175, 9482, 2333, 100, 9331, 3149, 6331, 9316, 2794, 6260, 1143, 4363, 311, 7260, 6409, 2449, 9917, 5048, 2411, 9071, 4718, 8738, 733, 1793, 7584, 4323, 2041, 7601, 6380, 3435, 343, 5738, 992, 7923, 1578, 7700, 9505, 2865, 1947, 9035, 8656, 5499, 8985, 2665, 4587, 8266, 1224, 9041, 9802, 4349, 9889, 1108, 318, 8187, 555, 7378, 3078, 5970, 4303, 6622, 75, 1626, 4762, 9819, 5787, 1700, 4581, 6679, 1745, 3623, 8828, 6723, 7741, 4346, 652, 5329, 96, 4414, 5496, 5813, 117, 4717, 2459, 3061, 4617, 8205, 9335, 3053, 297, 9549, 9927, 1718, 5013, 6161, 1186, 2332, 7697, 277, 6437, 5452, 4723, 508, 2610, 5838, 3328, 7149, 8144, 7722, 1190, 9536, 1670, 1607, 8594, 2972, 996, 4114, 2237, 5314, 3948, 3296, 9922, 1415, 2716, 6262, 4688, 339, 4320, 4130, 4173, 2797, 9407, 3156, 7075, 6387, 310, 2021, 4467, 7292, 657, 7427, 6583, 9802, 1245, 585, 6621, 9746, 8031, 3911, 2082, 8959, 8270, 5700, 6022, 5034, 9399, 6791, 8834, 1521, 9333, 9523, 6868, 4187, 889, 4396, 3274, 5726, 4147, 8527, 3407, 2171, 336, 8711, 3446, 6110, 6706, 522, 7311, 1986, 4250, 9579, 3923, 5419, 6176, 3674, 571, 4563, 4113, 8331, 1810, 7300, 7652, 1741, 9724, 6564, 4864, 7109, 808, 3625, 2199, 3715, 7132, 5582, 8084, 2687, 7081, 5625, 8529, 9338, 2273, 3402, 3437, 4571, 2766, 354, 3339, 378, 8389, 2403, 3985, 6519, 9596, 9679, 8689, 5171, 1539, 6875, 5323, 833, 8516, 6793, 8932, 121, 3857, 1122, 7588, 1161, 2871, 2941, 9965, 7834, 6707, 685, 3015, 6684, 3850, 5131, 9181, 8778, 8773, 9211, 1446, 7374, 328, 3930, 6837, 4497, 3112, 9432, 9774, 6652, 7453, 9048, 1337, 6939, 5237, 1948, 5804, 4241, 289, 6794, 7747, 1051, 4037, 6271, 4755, 3014, 9083, 332, 1078, 3725, 4369, 9665, 2373, 7626, 4064, 8105, 6112, 1618, 3317, 9429, 2170, 5265, 7120, 8684, 1224, 2361, 6697, 8017, 8772, 635, 8559, 8984, 4688, 6032, 4105, 2449, 4810, 2595, 9633, 1194, 8405, 1134, 8175, 4722, 5043, 2477, 8504, 8562, 5446, 5087, 8431, 568, 9533, 3926, 1910, 6360, 2566, 3187, 2672, 2582, 3106, 4794, 3218, 2142, 8071, 16, 5153, 223, 2954, 3782, 9839, 2040, 4775, 6634, 9704, 9895, 8663, 2632, 6946, 9908, 6120, 1432, 1011, 2044, 8969, 4202, 2634, 8440, 3375, 4241, 6557, 7813, 2067, 6194, 9237, 2692, 2369, 1531, 4813, 917, 4234, 8324, 3260, 8287, 3635, 3390, 6485, 4746, 1966, 911, 6966, 6726, 3933, 6428, 8174, 9211, 4271, 5759, 5046, 7296, 3561, 7065, 6161, 1475, 3597, 1192, 5998, 1708, 4329, 2874, 1993, 348, 8347, 3774, 3157, 806, 9175, 6110, 2190, 8177, 6077, 2567, 9824, 5149, 5287, 9100, 3213, 4763, 5658, 5452, 5979, 5769, 7056, 1246, 3634, 4524, 1655, 9222, 923, 4801, 1150, 3722, 9989, 8552, 6047, 8489, 4371, 5395, 7021, 129, 1644, 7979, 6291, 5503, 7017, 4373, 4616, 9749, 2355, 3633, 7992, 8067, 5209, 3635, 5286, 9906, 405, 7381, 1645, 7293, 92, 1765, 4400, 458, 2800, 8678, 9937, 1217, 7195, 5379, 1446, 2337, 1428, 1538, 5526, 2373, 1377, 351, 9722, 9133, 1211, 4156, 6218, 2091, 4905, 2942, 8462, 1699, 1210, 4235, 98, 9850, 759, 4142, 3717, 2559, 8355, 629, 3392, 5748, 9747, 411, 2029, 1931, 7736, 7353, 16, 168, 8290, 7383, 5637, 8141, 9204, 8461, 1, 5173, 6680, 4286, 9261, 3229, 3541, 2701, 3527, 3779, 7853, 7348, 6646, 170, 3974, 8722, 9754, 7363, 7631, 1641, 1879, 7846, 8705, 4376, 1244, 6498, 4026, 1126, 3274, 8931, 5649, 8487, 900, 8889, 7550, 5945, 170, 78, 2787, 6533, 961, 6985, 5388, 3791, 3922, 6033, 5215, 6170, 3875, 3916, 1507, 7580, 9116, 8078, 4544, 5511, 7064, 7455, 7525, 6145, 2279, 9285, 9845, 3000, 9429, 1871, 917, 2067, 4888, 8267, 681, 715, 375, 3380, 4143, 5210, 2823, 573, 9652, 9784, 1796, 1892, 3625, 2902, 122, 9793, 6054, 600, 4262, 552, 1183, 5676, 9217, 2075, 1327, 8155, 7010, 1156, 5940, 1206, 171, 1261, 5311, 5314, 4987, 7189, 3310, 4027, 1622, 7418, 1570, 1656, 7112, 1490, 3926, 1477, 3876, 8171, 4629, 8306, 7396, 3866, 8947, 3388, 6111, 160, 1257, 9602, 3579, 2742, 9817, 7952, 2241, 6526, 6830, 700, 8884, 5947, 7434, 3811, 2990, 254, 1411, 3694, 9163, 52, 1538, 7714, 4925, 7263, 2598, 1753, 3977, 597, 7983, 7140, 7038, 310, 7231, 3069, 6600, 8693, 6216, 9058, 5906, 4041, 2517, 7741, 8681, 6733, 3070, 7421, 8548, 6438, 2393, 2639, 6037, 1309, 8259, 5625, 2623, 9201, 9751, 5346, 3327, 4381, 8966, 809, 8633, 321, 6588, 8189, 3604, 7132, 6868, 3330, 6592, 6722, 3964, 2498, 3202, 270, 647, 3100, 4490, 9999, 4262, 5005, 4755, 7792, 3443, 8248, 7641, 8035, 7970, 4533, 2836, 3693, 5153, 5249, 5030, 7592, 2975, 9856, 1370, 8969, 2263, 8969, 3193, 8994, 7643, 4538, 6188, 345, 2279, 1246, 5540, 2598, 5481, 7686, 6489, 2854, 9525, 9600, 4267, 2171, 7742, 3601, 4446, 3903, 5371, 616, 3455, 7888, 3861, 6395, 6661, 5708, 203, 8696, 6824, 4704, 8135, 7400, 8128, 5244, 495, 1639, 9774, 8681, 5976, 7879, 5247, 8436, 5890, 4320, 723, 1539, 9544, 850, 1591, 5721, 5302, 4485, 2971, 5674, 2811, 306, 909, 354, 3436, 7968, 3753, 1512, 5427, 7725, 8817, 6380, 9633, 4138, 9649, 7043, 1137, 4785, 1734, 6913, 2523, 4733, 6465, 5365, 7859, 8847, 7295, 2503, 8263, 9189, 8697, 3708, 702, 9344, 5595, 1792, 9893, 6043, 1819, 859, 105, 1568, 6973, 5462, 3177, 5613, 6882, 9719, 5973, 3242, 3839, 4993, 5739, 463, 3354, 8888, 8984, 9976, 7767, 1238, 1410, 5433, 9707, 6157, 3662, 2479, 2514, 6094, 2227, 8671, 720, 1476, 241, 9905, 6552, 195, 5557, 1814, 9107, 5701, 7002, 5593, 9073, 3217, 7312, 3049, 3321, 9902, 8842, 9143, 1150, 5308, 6661, 1716, 3433, 2106, 9318, 5109, 5253, 9055, 4577, 9539, 9592, 8953, 4692, 3792, 9003, 1938, 1981, 7858, 8285, 3386, 9351, 6723, 3193, 6813, 2733, 7994, 7447, 5809, 7539, 7491, 2964, 1870, 5802, 8284, 270, 7939, 1235, 6077, 5742, 6347, 2939, 3206, 1265, 9883, 27, 5544, 7261, 5961, 745, 8116, 6401, 417, 372, 9890, 5528, 3782, 5649, 8909, 584, 6585, 6346, 4698, 5531, 5932, 2114, 5269, 6712, 7281, 8337, 2171, 1184, 7332, 3560, 7722, 5193, 7108, 9349, 1831, 6206, 3739, 6862, 847, 433, 8019, 2143, 5180, 6380, 8950, 5268, 5546, 7122, 3945, 9826, 1985, 6549, 1388, 938, 9606, 2230, 2854, 8664, 9246, 7500, 4195, 4614, 4344, 8936, 8683, 368, 4692, 7428, 8693, 6373, 4751, 7601, 6419, 4067, 4635, 1490, 2645, 9532, 9302, 1945, 9451, 5632, 2842, 7380, 8018, 8043, 9158, 1560, 5510, 2728, 5048, 8921, 857, 45, 6496, 1112, 625, 9801, 9224, 637, 3236, 5673, 9035, 6285, 4434, 6775, 3951, 606, 2091, 3633, 5204, 9467, 2487, 3839, 6156, 2690, 9888, 3104, 5544, 1473, 880, 4491, 5492, 3448, 9395, 6458, 8824, 3815, 2075, 7132, 2220, 3842, 3758, 4901, 245, 1141, 4146, 546, 1001, 4972, 9423, 80, 7793, 1066, 2317, 7614, 834, 4781, 7554, 8311, 1350, 7060, 2405, 2222, 4939, 2534, 8631, 7994, 1983, 1987, 1159, 2464, 250, 1996, 8975, 688, 6680, 9700, 493, 6678, 466, 467, 804, 9625, 3918, 3030, 2079, 4727, 9863, 6367, 7066, 8116, 3453, 2066, 4926, 1510, 9174, 9254, 1944, 8619, 643, 4252, 6274, 641, 6513, 324, 2262, 4637, 1094, 9819, 5571, 2064, 3755, 1584, 1707, 5564, 3189, 757, 6785, 1200, 2833, 4430, 370, 7109, 8867, 9256, 2241, 346, 4658, 253, 2264, 6072, 3505, 1634, 6325, 5118, 5569, 3305, 659, 6283, 3347, 6225, 4613, 2048, 4324, 9507, 3110, 5862, 2495, 8281, 6459, 6333, 7022, 6120, 2767, 8234, 9669, 2029, 7561, 9387, 2080, 6295, 7173, 2515, 2894, 325, 5785, 2796, 1292, 5383, 9109, 3067, 8734, 5071, 5100, 2333, 405, 3403, 2721, 7790, 5827, 41, 9384, 6642, 6083, 2506, 5937, 3020, 7227, 5203, 9688, 2613, 1026, 7170, 973, 6863, 6042, 1760, 245, 4722, 4129, 5614, 1037, 7698, 1173, 8937, 6646, 2998, 4222, 5725, 7518, 6857, 3123, 7001, 4938, 9576, 6907, 8500, 1037, 7195, 3730, 1232, 5752, 5075, 5105, 5546, 6279, 7116, 2054, 943, 7704, 8382, 4186, 1268, 4537, 722, 6584, 1941, 7628, 508, 9314, 4848, 7732, 1183, 8610, 1889, 4024, 4696, 7085, 3362, 4378, 4438, 9732, 824, 5706, 9137, 8527, 6021, 8906, 4229, 5785, 3534, 7724, 875, 3703, 3316, 2801, 185, 5614, 3495, 5056, 8860, 7407, 6516, 2753, 4544, 4849, 4280, 3670, 7486, 7086, 4968, 7959, 1617, 7756, 9213, 8454, 6822, 1736, 2341, 1742, 567, 5351, 8678, 7919, 94, 6274, 5526, 8707, 6686, 8205, 6539, 9055, 3678, 534, 7824, 5071, 7807, 8892, 4941, 8848, 9708, 7426, 6986, 445, 2737, 9092, 77, 3886, 9502, 3021, 8862, 1196, 7688, 546, 8184, 3515, 2316, 7637, 5174, 9385, 48, 7379, 1208, 8398, 4641, 4294, 5924, 8188, 8167, 3437, 935, 5134, 3899, 5068, 4130, 3691, 8381, 7118, 5425, 4382, 2532, 3234, 5289, 6523, 8124, 4815, 4138, 76, 1212, 976, 9315, 4695, 1634, 4278, 9011, 4798, 5238, 7195, 518, 5377, 2309, 6000, 853, 5053, 8406, 2326, 3193, 4785, 9465, 5245, 2751, 6134, 7265, 3425, 6873, 594, 1251, 7809, 9146, 2540, 2203, 3588, 3915, 2706, 3118, 4678, 2549, 6370, 1817, 8891, 9149, 3839, 8587, 7146, 2672, 5337, 9661, 9628, 2078, 27, 2387, 3619, 2874, 2455, 7405, 472, 961, 4464, 2979, 6688, 2211, 851, 6233, 5269, 2084, 4454, 4380, 2179, 1117, 1453, 6768, 5916, 2578, 9582, 7782, 5278, 784, 3962, 3108, 8572, 3361, 4855, 7646, 7611, 6584, 4446, 2861, 194, 2112, 8151, 2428, 5230, 2743, 3626, 4904, 4610, 6571, 3174, 1834, 8870, 5252, 8483, 6181, 5455, 6391, 1367, 8313, 7802, 7703, 5776, 6776, 4638, 4215, 935, 7235, 3096, 7706, 496, 2165, 6219, 520, 4209, 6462, 2345, 1964, 1671, 9393, 2173, 7813, 2470, 7888, 339, 7756, 2376, 7834, 2049, 1846, 4207, 259, 5021, 5425, 6898, 1591, 6534, 4234, 1457, 5463, 4367, 4942, 8604, 9461, 9467, 7590, 9193, 3179, 2276, 7293, 1766, 5376, 801, 1689, 1656, 3261, 6741, 701, 4620, 8315, 1794, 3001, 4741, 5216, 6646, 7217, 3546, 2411, 1317, 3155, 1463, 2961, 3539, 4975, 6136, 4058, 3847, 5895, 7000, 4030, 1342, 1671, 4240, 3424, 8137, 2807, 2761, 9182, 7513, 5578, 4913, 2329, 6774, 2925, 3774, 1959, 5134, 5543, 1519, 4152, 6780, 9277, 1660, 3889, 7278, 2251, 945, 2381, 4389, 907, 1582, 8378, 9005, 1833, 4384, 1240, 8485, 7483, 2807, 6522, 3939, 7122, 6698, 4439, 1786, 5760, 6330, 4919, 8772, 5144, 6491, 9953, 6644, 8715, 3201, 1022, 7986, 9735, 4874, 2759, 4583, 2675, 7169, 6615, 3563, 4424, 1251, 2636, 6460, 5881, 7410, 6148, 537, 3950, 295, 2912, 2690, 6941, 3853, 1180, 7502, 4237, 6856, 7907, 4620, 4828, 2755, 5382, 2433, 4329, 291, 135, 9387, 8327, 7247, 416, 2150, 9441, 1474, 1750, 3603, 394, 6719, 1440, 3268, 2363, 9321, 2586, 5171, 1602, 8134, 1400, 5719, 6968, 1499, 8451, 6566, 4942, 367, 1849, 343, 364, 4089, 909, 9245, 4778, 9109, 1825, 6066, 2340, 3488, 541, 6591, 8738, 9274, 3184, 7450, 2231, 4545, 8550, 5833, 1204, 5962, 575, 7077, 4327, 6277, 7630, 5367, 470, 2464, 9163, 4290, 148, 3138, 1554, 3636, 3889, 4306, 5944, 5702, 2925, 718, 9697, 1006, 2405, 5996, 4313, 9218, 4475, 3561, 5962, 5257, 4783, 9016, 6552, 4396, 235, 3411, 5938, 7129, 9088, 5056, 902, 2556, 6079, 8276, 3325, 7762, 391, 1777, 1562, 1019, 6050, 9300, 4998, 6114, 5757, 2355, 4563, 5772, 8990, 4397, 8956, 9162, 4922, 1117, 8702, 9851, 3545, 3088, 8951, 5151, 9490, 5726, 8376, 9339, 5088, 1619, 5806, 1710, 3157, 6127, 9664, 6653, 1379, 7193, 5731, 4472, 136, 5791, 9252, 4308, 9620, 2241, 8958, 5480, 3663, 4415, 9053, 632, 4895, 553, 8949, 540, 858, 3368, 5033, 8952, 1199, 8896, 9208, 248, 691, 9223, 910, 8155, 2380, 9550, 7093, 3066, 4942, 1765, 5724, 6407, 9036, 1527, 8137, 3299, 5995, 4230, 2617, 6018, 4234, 2690, 7962, 1876, 6474, 4609, 2905, 7306, 7836, 8167, 5396, 7878, 7636, 2551, 314, 2249, 552, 9065, 348, 1939, 8126, 5772, 1369, 8917, 9600, 8605, 4214, 7406, 986, 3554, 438, 197, 9468, 6471, 1916, 7175, 4377, 126, 529, 6639, 7091, 2324, 8339, 7334, 8210, 3233, 8292, 7995, 5683, 2862, 9222, 7393, 3411, 9475, 3246, 9640, 9848, 5539, 724, 7218, 6894, 9741, 7481, 3414, 8274, 7109, 2014, 3697, 4747, 3056, 9894, 6520, 6517, 2762, 6836, 1977, 53, 547, 6036, 7082, 7047, 3568, 8840, 8934, 1294, 6578, 5169, 8197, 188, 6397, 3567, 4463, 4173, 2606, 5809, 5658, 4690, 5197, 3423, 7488, 7954, 9441, 1971, 5067, 6423, 1299, 4569, 5266, 5666, 4944, 4416, 1666, 4295, 4027, 2931, 5348, 7857, 8540, 8840, 1472, 719, 7382, 4697, 2060, 4244, 2077, 6306, 6587, 3168, 7994, 9869, 2053, 7500, 8168, 4474, 7141, 7489, 2765, 9122, 857, 3025, 8427, 2688, 4076, 4777, 7579, 6402, 5095, 9087, 7245, 7417, 8975, 3504, 2700, 6903, 6659, 8162, 9341, 6713, 6374, 7207, 955, 3814, 5908, 5919, 1028, 7148, 6651, 9669, 1418, 9864, 359, 7942, 4097, 3868, 1569, 3737, 8256, 874, 2806, 5046, 6693, 7707, 703, 4011, 4040, 7052, 3085, 5678, 5381, 7052, 1273, 6560, 7921, 3698, 3797, 5409, 3164, 6531, 2651, 8272, 2029, 6005, 9572, 6493, 5939, 9990, 2660, 4154, 782, 9557, 5290, 6079, 8590, 9038, 6433, 4159, 5912, 7773, 5663, 5881, 6554, 6155, 4259, 2628, 4459, 4803, 1666, 4017, 3582, 7296, 778, 4655, 4789, 6994, 6961, 4017, 4517, 4809, 9095, 1665, 5777, 3701, 967, 2392, 3796, 3113, 8134, 1257, 7350, 2078, 6175, 8532, 7567, 666, 7403, 7274, 5215, 6557, 5307, 985, 5702, 6213, 617, 6891, 2166, 6297, 5657, 8857, 3984, 3226, 9167, 8283, 8944, 4391, 6187, 4000, 1621, 4585, 9616, 7985, 2636, 7322, 9996, 9437, 9365, 5297, 6146, 1382, 9211, 2434, 7345, 918, 9586, 5917, 5671, 6314, 5093, 8961, 4339, 4688, 377, 4454, 4860, 3840, 2317, 3682, 3117, 5410, 7938, 7184, 5252, 4540, 9721, 1233, 316, 3660, 7315, 3975, 4557, 9052, 2359, 6181, 9551, 9894, 3214, 2532, 2311, 5933, 3565, 2061, 1732, 5995, 8114, 8336, 3150, 3182, 2079, 3264, 4959, 6066, 9694, 921, 1109, 7696, 6393, 1032, 2445, 6315, 6833, 3769, 2841, 3144, 5860, 6831, 8493, 1432, 3133, 5397, 4122, 7386, 5282, 138, 3389, 7676, 2834, 3163, 2452, 9827, 4355, 175, 1934, 452, 6080, 2789, 4621, 2864, 8811, 5604, 2316, 7141, 9355, 5228, 8554, 4143, 8047, 8706, 1544, 8448, 4185, 9426, 851, 4314, 835, 5917, 7210, 4145, 6129, 1383, 4285, 1864, 4643, 5867, 9715, 1244, 693, 7863, 5278, 8113, 6379, 6765, 8650, 2712, 1974, 5248, 9117, 1744, 8240, 4856, 6444, 1016, 4329, 2567, 6151, 5336, 1257, 7752, 4724, 1091, 390, 6980, 6647, 829, 5438, 2523, 1388, 8264, 1871, 9633, 2368, 504, 9635, 4573, 4222, 3561, 9865, 4272, 7050, 5299, 8838, 7375, 2507, 1949, 1846, 5106, 4188, 2634, 2746, 4122, 1495, 7581, 7718, 7586, 547, 9969, 6216, 8101, 4592, 8189, 8621, 3922, 5553, 4170, 1600, 9103, 3698, 4642, 2293, 4148, 8295, 6120, 5338, 1887, 3641, 5374, 9429, 901, 5638, 5192, 8420, 2326, 2955, 3033, 4338, 9791, 7823, 1755, 6192, 3745, 8010, 738, 7355, 3384, 3910, 8186, 2787, 9268, 7003, 4828, 790, 9671, 90, 8512, 1592, 5214, 3945, 9608, 9056, 2473, 425, 7405, 5618, 6968, 7052, 365, 9654, 7304, 9137, 1187, 4454, 185, 5419, 3008, 5928, 4351, 2166, 631, 9396, 7621, 3649, 4786, 7861, 5941, 3042, 2529, 6336, 1655, 8635, 2561, 176, 3473, 7124, 3064, 8112, 401, 9650, 4728, 9812, 2844, 2082, 1221, 1999, 6023, 1184, 4718, 824, 7441, 6524, 634, 3089, 6113, 8921, 23, 7886, 7761, 8591, 7145, 6429, 2775, 6371, 2799, 6891, 2819, 141, 755, 1550, 4336, 7098, 3127, 4046, 5178, 993, 1644, 6005, 4279, 3342, 7413, 4505, 9115, 9685, 4261, 7775, 8676, 7843, 5475, 2280, 454, 6204, 3597, 2811, 2248, 8938, 8497, 6678, 9165, 9782, 7479, 5853, 1874, 8088, 1825, 2059, 3360, 9747, 3316, 5885, 682, 8939, 5144, 6391, 923, 2279, 1145, 9411, 6917, 5891, 6047, 1271, 2788, 663, 8195, 1969, 885, 5541, 8954, 6234, 2493, 6992, 6720, 4581, 119, 1231, 4070, 6011, 4130, 725, 7586, 2264, 6926, 9721, 4697, 9979, 7568, 6949, 2537, 2593, 3141, 2819, 122, 2021, 3940, 3598, 9607, 4344, 2314, 2646, 8759, 3015, 4870, 8911, 7748, 2536, 3870, 2820, 7214, 3991, 9358, 176, 5460, 687, 4685, 8548, 3711, 361, 3727, 8182, 7619, 8091, 9078, 870, 3877, 8450, 3572, 8902, 4932, 8274, 5177, 7184, 5979, 9539, 514, 5105, 7565, 5312, 4646, 5753, 7244, 4758, 5199, 5755, 507, 8884, 8778, 4671, 2936, 9532, 9327, 6301, 1980, 2624, 912, 2936, 522, 1174, 5698, 5675, 7210, 2361, 9565, 2517, 3506, 950, 3159, 2848, 8265, 5333, 5503, 8453, 7081, 6680, 2562, 8075, 5658, 2519, 1895, 5787, 8221, 3240, 6316, 2688, 858, 9843, 3177, 9007, 5406, 6276, 8973, 559, 956, 5174, 4550, 4582, 3108, 2202, 3059, 3263, 5455, 9346, 7710, 7029, 4952, 981, 8903, 3151, 6223, 356, 3832, 2804, 4169, 4578, 8816, 4281, 4339, 2866, 5151, 1727, 5353, 6870, 3527, 1591, 6904, 3698, 2080, 8232, 2485, 7925, 2990, 5492, 4269, 6229, 1771, 110, 666, 9680, 3821, 3183, 5048, 3655, 8944, 2553, 3389, 9787, 8391, 3389, 1549, 6963, 1637, 6915, 9709, 417, 5864, 4310, 6560, 4184, 5777, 6581, 7666, 8153, 5533, 1082, 3299, 7467, 6210, 3182, 1159, 3799, 554, 755, 8708, 7666, 9824, 7830, 3682, 3569, 9524, 3287, 2219, 1539, 5848, 3967, 4270, 9826, 7959, 3545, 4701, 6967, 5646, 2588, 6495, 6752, 5873, 236, 3812, 3823, 777, 9234, 2164, 5071, 1242, 2131, 2001, 9220, 4019, 776, 8238, 9021, 2053, 2893, 2507, 9174, 9643, 3676, 9812, 4924, 7816, 9631, 4455, 5449, 673, 5928, 5466, 8952, 6594, 9929, 9758, 3836, 6318, 7056, 8546, 7732, 4450, 8551, 1137, 16, 5840, 818, 8172, 2802, 1526, 9409, 7369, 8451, 9209, 1689, 5815, 2018, 2797, 8885, 2368, 4726, 7469, 5690, 2995, 7324, 278, 3374, 5331, 735, 5550, 3047, 7233, 2238, 3441, 5176, 7139, 3713, 2642, 1210, 7969, 8161, 8437, 4901, 3353, 3848, 915, 9147, 3160, 2808, 6665, 6856, 5617, 6992, 4746, 701, 939, 5795, 7529, 9510, 9974, 9235, 2504, 7286, 1890, 7797, 5153, 1660, 335, 557, 419, 2929, 7047, 9249, 298, 9845, 6799, 4649, 5861, 544, 3611, 7558, 3535, 917, 4246, 2416, 5952, 6741, 6887, 8035, 3237, 5464, 1819, 6497, 1382, 461, 7295, 9040, 73, 4423, 4368, 3753, 7184, 3232, 9147, 2599, 5394, 8581, 2381, 6228, 3438, 1284, 7772, 3444, 582, 8418, 4985, 4187, 5740, 7296, 5630, 6289, 9754, 3337, 9952, 4366, 6101, 2148, 3808, 1178, 1380, 2562, 2045, 730, 4399, 6630, 1970, 6585, 6509, 8210, 6928, 5830, 5902, 106, 8698, 8625, 5004, 9836, 8455, 530, 7765, 9665, 9491, 2115, 8039, 6251, 9192, 8790, 7017, 5212, 1649, 7976, 8495, 8917, 777, 3153, 1668, 22, 8030, 4572, 5397, 9316, 1003, 1665, 5354, 8276, 3597, 6182, 6370, 7169, 5258, 1060, 3032, 7179, 1606, 9356, 8209, 1033, 5510, 3837, 2347, 5042, 4474, 1670, 7688, 4793, 2468, 6690, 3292, 4868, 510, 9179, 1365, 332, 8864, 855, 1860, 3764, 3779, 2236, 2197, 6247, 8933, 5599, 1893, 7701, 9859, 3466, 2856, 9263, 8333, 4669, 7670, 1959, 8994, 705, 8308, 9031, 5981, 6562, 682, 9907, 7503, 4299, 7537, 6774, 1073, 6317, 9868, 7121, 2017, 3557, 1650, 3746, 6711, 3499, 9562, 1008, 2441, 330, 7789, 8244, 2026, 7442, 3274, 4388, 9023, 3593, 7662, 1097, 9015, 889, 5921, 4390, 9851, 9723, 5996, 9509, 5968, 4304, 4638, 3540, 8680, 1531, 6543, 373, 3642, 9559, 4306, 7774, 2402, 6603, 6360, 1966, 8631, 9098, 6523, 1026, 5325, 8594, 4591, 8632, 9358, 194, 9540, 1681, 4038, 5380, 4980, 9387, 1271, 5025, 4409, 8093, 7927, 6703, 3960, 7210, 8649, 9924, 8325, 7661, 3434, 3092, 9858, 9009, 7440, 8460, 38, 2708, 1928, 6585, 8100, 9710, 4283, 2392, 3100, 4185, 1997, 4494, 4484, 5746, 5979, 2314, 1456, 5447, 1326, 5290, 5990, 7711, 4169, 8988, 3149, 5496, 2007, 6620, 8215, 8077, 22, 2290, 6498, 7201, 9255, 155, 6285, 7099, 5553, 9973, 7946, 3505, 9265, 2734, 1917, 289, 5789, 1315, 9135, 369, 1564, 4393, 3260, 5254, 5261, 9721, 6793, 8774, 3196, 2727, 268, 7299, 3235, 8974, 1228, 5905, 7954, 9174, 8016, 9796, 1899, 1379, 3205, 4093, 9174, 2514, 944, 7486, 5523, 6125, 7436, 5855, 4255, 36, 7126, 1724, 218, 6921, 1725, 4284, 1921, 9330, 696, 1504, 939, 5110, 3006, 1147, 5363, 9909, 506, 5002, 7635, 5884, 4499, 3202, 180, 5627, 2680, 5116, 8085, 1723, 7393, 3022, 7898, 6330, 6610, 1164, 9341, 1061, 1464, 4060, 2204, 9968, 5897, 1509, 7199, 7730, 2443, 8027, 1735, 1112, 3317, 9997, 6782, 3900, 6519, 7258, 2273, 3091, 6904, 1075, 1938, 6289, 2645, 9330, 4619, 8487, 5206, 7417, 164, 4954, 6246, 9083, 5067, 7092, 34, 7555, 5334, 2742, 989, 2304, 1753, 3412, 7207, 1056, 8805, 803, 4292, 1726, 4099, 4546, 5556, 4585, 2533, 401, 4445, 6339, 3346, 1154, 6791, 1549, 5373, 7158, 9769, 5892, 7363, 6419, 1754, 4055, 2292, 1196, 7167, 2537, 3156, 3591, 446, 3331, 7493, 29, 9701, 1598, 518, 7611, 5626, 674, 7785, 2658, 6006, 9009, 5201, 2379, 3116, 2940, 2255, 3542, 4512, 9469, 4796, 9323, 3925, 449, 4948, 8741, 935, 9714, 4065, 841, 7999, 2099, 3262, 1016, 8444, 7949, 6287, 3444, 4005, 9133, 477, 3308, 2763, 7357, 2740, 8529, 1121, 6350, 4976, 9693, 1123, 5025, 576, 5325, 6399, 1714, 8092, 5535, 6519, 9879, 6616, 7282, 7126, 6029, 5056, 5505, 1485, 5875, 3516, 4281, 1491, 5691, 2822, 4876, 7191, 3262, 1696, 7718, 8471, 1978, 9614, 7324, 4274, 5120, 9670, 6647, 4528, 5937, 6972, 8519, 9107, 3633, 9599, 7740, 5373, 9717, 2368, 4306, 2306, 915, 6166, 3920, 5549, 8616, 2120, 3645, 6091, 8145, 9738, 4312, 2647, 8164, 4485, 5592, 8298, 3707, 318, 4407, 9756, 7155, 9084, 3184, 2439, 2688, 3214, 9903, 8198, 650, 7536, 6351, 2771, 3360, 1998, 2926, 5571, 316, 5135, 1012, 7745, 5115, 2371, 6111, 9053, 9491, 5326, 9636, 8176, 9949, 7884, 322, 167, 2010, 5797, 506, 6909, 5026, 1477, 303, 8188, 4131, 9672, 6202, 6851, 6332, 7378, 6362, 5561, 5704, 4550, 6071, 4496, 7457, 2559, 5821, 1436, 5694, 5873, 3014, 123, 6376, 7430, 5318, 7906, 9386, 7057, 9598, 401, 4319, 504, 6901, 4849, 6974, 7493, 7489, 3243, 5880, 8078, 3469, 3759, 4878, 2745, 8228, 359, 6439, 3564, 1049, 6741, 1751, 7627, 2324, 6361, 149, 2630, 9199, 170, 3895, 8604, 6007, 9648, 3088, 5784, 8787, 7899, 1762, 8974, 1724, 5234, 9388, 4048, 5778, 5838, 5258, 4889, 9608, 2195, 2118, 265, 2437, 9335, 6433, 8247, 116, 6288, 3584, 3119, 84, 7626, 4175, 625, 9461, 4185, 948, 6948, 3315, 7853, 6462, 4005, 4322, 9553, 3146, 721, 4332, 6772, 4012, 5561, 5311, 7038, 7493, 6409, 5512, 3189, 7353, 2364, 8562, 9564, 1705, 1922, 5599, 8171, 1551, 1739, 1632, 3175, 8405, 3106, 9706, 5402, 8661, 8499, 7236, 3210, 5026, 801, 4496, 1992, 7478, 6495, 5071, 9872, 9240, 1945, 4981, 3805, 7992, 5990, 2099, 6206, 1214, 3769, 4257, 7360, 1608, 8117, 748, 9126, 2630, 6978, 4560, 9039, 7642, 7351, 6261, 25, 7393, 5620, 1014, 9373, 6340, 7741, 6259, 745, 6123, 9200, 2350, 1147, 3790, 2966, 4274, 722, 7615, 2514, 5990, 8461, 8566, 7311, 5684, 6043, 478, 3181, 9675, 1527, 3471, 7136, 3513, 7122, 3359, 5263, 5990, 3604, 7715, 2453, 7791, 8729, 7882, 7605, 5470, 8667, 7049, 6195, 217, 7016, 7051, 5921, 1887, 6373, 9846, 1721, 1404, 815, 3225, 5923, 7036, 2468, 4405, 5741, 4299, 7791, 9314, 2735, 3799, 7518, 4962, 9559, 2710, 7163, 239, 3954, 1842, 6147, 9105, 8118, 2011, 5092, 6682, 7679, 2467, 4150, 1114, 2421, 7228, 9121, 4496, 4188, 3583, 9499, 4807, 7960, 977, 6804, 306, 9747, 4704, 9992, 5327, 926, 2980, 5475, 4917, 9213, 3296, 1552, 696, 3687, 120, 8635, 1228, 4833, 2111, 3537, 2173, 5978, 4736, 9582, 3245, 3070, 2982, 9804, 579, 3068, 9719, 7278, 3354, 2682, 1351, 5321, 3881, 6364, 6086, 2508, 676, 1076, 3437, 9155, 6959, 768, 129, 8957, 9682, 796, 9236, 9103, 1084, 1727, 5617, 3521, 1550, 3992, 9575, 6167, 6734, 7841, 7626, 1539, 6508, 565, 9248, 705, 37, 1904, 3056, 7031, 5007, 5109, 4092, 4181, 9334, 7915, 6448, 4853, 4013, 1750, 3474, 4358, 5560, 528, 2640, 3240, 5315, 9658, 4857, 9546, 1703, 8348, 149, 9547, 1300, 3695, 3430, 6606, 7757, 3600, 5545, 603, 8345, 3909, 9598, 5364, 7271, 8861, 8523, 47, 865, 2346, 9721, 5885, 3296, 4085, 9223, 3045, 3553, 4761, 3430, 3189, 8290, 3528, 6087, 7553, 9330, 2464, 7035, 7973, 9854, 9497, 7750, 932, 9946, 9470, 1326, 9231, 9476, 8499, 8576, 5079, 2801, 377, 6726, 9855, 9681, 2902, 6473, 3344, 9221, 4927, 7625, 7007, 3494, 1316, 6592, 5, 9154, 7356, 2254, 3027, 5145, 5775, 1645, 1500, 39, 4399, 200, 4231, 5870, 468, 8291, 1025, 418, 1843, 5009, 6118, 7198, 396, 4370, 6152, 7506, 6532, 1351, 8692, 5081, 292, 4760, 9860, 9902, 5782, 947, 5247, 3024, 8129, 167, 1922, 4270, 9963, 2576, 7910, 687, 3595, 7590, 4778, 5032, 7190, 6824, 9153, 5455, 9791, 8569, 8899, 4336, 1461, 4987, 6810, 7211, 4595, 3751, 3402, 3543, 9137, 2067, 7341, 8857, 510, 9447, 4542, 1191, 4462, 7325, 6194, 3576, 9911, 3684, 3268, 2027, 1698, 5157, 3704, 9369, 6117, 9299, 2115, 9859, 2385, 1900, 7819, 8190, 872, 6438, 183, 375, 8280, 9067, 3748, 1074, 8793, 6133, 3461, 7826, 802, 1908, 14, 740, 7189, 1036, 6678, 4521, 9823, 2822, 5186, 1988, 889, 3112, 6076, 8661, 3515, 2168, 8868, 1499, 30, 858, 5401, 7409, 5474, 4935, 9087, 5847, 5231, 2768, 9707, 7832, 7097, 4812, 3208, 8098, 379, 8913, 8114, 8204, 3541, 503, 2327, 9716, 5400, 4971, 3626, 3260, 8764, 5507, 1666, 5890, 1806, 2396, 3583, 9460, 5355, 7910, 9222, 3372, 3280, 7508, 948, 2256, 661, 9914, 6643, 1226, 5410, 1185, 7967, 3325, 5583, 7770, 45, 1678, 6192, 9851, 5821, 6333, 7333, 2001, 9325, 508, 2324, 7825, 3098, 8681, 9608, 2028, 9993, 3921, 3963, 2805, 918, 581, 4639, 3496, 5536, 100, 4166, 1160, 959, 565, 3272, 9141, 2031, 9398, 5734, 1535, 8185, 7252, 973, 1362, 7541, 2455, 5934, 2856, 3387, 9281, 9293, 9501, 148, 8874, 850, 5533, 4419, 9816, 4233, 1783, 6797, 6830, 8675, 2368, 3232, 5697, 7823, 5347, 6772, 3726, 7229, 5305, 2983, 5765, 6300, 5955, 3256, 2705, 5092, 9727, 3844, 651, 9412, 9210, 5511, 8398, 1819, 8373, 496, 6003, 9769, 5346, 6781, 6166, 9286, 4545, 3531, 1078, 7175, 9892, 3315, 4482, 5099, 2500, 1030, 6956, 4444, 6137, 8016, 2733, 7631, 3337, 6510, 5139, 8645, 6580, 1171, 1912, 8420, 7024, 9356, 2761, 1005, 5231, 1929, 3795, 4181, 2792, 4696, 66, 7772, 2326, 2626, 1240, 7730, 2620, 5830, 6968, 9167, 6678, 3445, 632, 9045, 5960, 2718, 1872, 2928, 6257, 6678, 8620, 9157, 2616, 3114, 9351, 1202, 4554, 4736, 8781, 291, 3316, 9010, 1479, 3882, 9876, 3429, 6507, 897, 1138, 8110, 7565, 6510, 4005, 5452, 5049, 1593, 9786, 6862, 4607, 9468, 8193, 9782, 1502, 577, 1777, 9629, 5580, 2235, 2415, 2526, 1680, 588, 8107, 7375, 595, 3032, 2608, 2337, 6208, 3880, 3304, 1252, 3122, 1127, 4265, 4176, 105, 4401, 9540, 323, 5007, 1925, 7488, 1298, 8110, 2462, 6961, 5054, 7645, 5551, 663, 2819, 145, 7406, 8290, 364, 3821, 5883, 524, 9759, 62, 8611, 2807, 4403, 893, 8512, 2693, 7376, 4793, 3537, 3924, 6266, 5640, 4381, 3326, 7343, 8760, 5683, 1379, 2242, 591, 1616, 7525, 1237, 1471, 7955, 486, 1901, 6272, 5824, 1265, 556, 1835, 1760, 4284, 2636, 1290, 8021, 6149, 6363, 5582, 2536, 5967, 1248, 6591, 6782, 6336, 1792, 5864, 4745, 7880, 5918, 3914, 3872, 2572, 2631, 3698, 7814, 2335, 8388, 6640, 361, 3686, 5893, 407, 9371, 7026, 4269, 5693, 7306, 6832, 8587, 2157, 2918, 4071, 2568, 7838, 3946, 6958, 735, 3870, 652, 8739, 6377, 2242, 159, 4622, 8784, 9889, 5259, 4424, 7934, 3775, 7886, 1062, 3865, 6062, 2034, 9853, 6315, 300, 5658, 574, 5210, 6950, 7983, 3022, 3425, 3276, 332, 2746, 8253, 9714, 8156, 7876, 4551, 5232, 4026, 5535, 2545, 3089, 5200, 9726, 4267, 5485, 2903, 6525, 3075, 9217, 8312, 6126, 8164, 4808, 1887, 9662, 6471, 9253, 33, 3291, 1186, 9081, 1061, 3906, 7833, 5375, 3659, 4415, 2469, 5429, 7870, 1767, 5086, 8537, 6365, 6118, 693, 2361, 6481, 8949, 9168, 7688, 9658, 513, 8176, 3476, 6101, 3269, 4262, 5636, 9365, 5862, 787, 569, 1225, 879, 5243, 7840, 7877, 3781, 2801, 8149, 5127, 1272, 9340, 3184, 4621, 1122, 7170, 3685, 4343, 9294, 1316, 1653, 6792, 7036, 7666, 9268, 8101, 2559, 3874, 6121, 8901, 1351, 5598, 588, 9494, 2300, 8491, 5120, 2178, 4215, 6272, 536, 4396, 4069, 9859, 307, 5601, 8376, 6534, 3181, 2829, 7909, 8323, 6480, 8914, 6763, 7835, 8997, 817, 5767, 7923, 6160, 7386, 2130, 9531, 9201, 1995, 3500, 4687, 2369, 849, 1829, 56, 5616, 4203, 3460, 2965, 8646, 6126, 6479, 6254, 370, 8317, 2000, 2089, 1861, 8977, 9633, 7283, 8686, 4661, 846, 7129, 2244, 5407, 3481, 1743, 5703, 4815, 1573, 3103, 8272, 14, 1578, 2035, 2439, 1190, 703, 617, 2700, 4246, 3292, 2092, 2246, 4662, 1419, 5603, 2547, 7585, 3875, 4685, 490, 7873, 361, 9543, 514, 9874, 4310, 6240, 6219, 5435, 4862, 3410, 198, 8494, 5710, 8049, 8541, 1767, 72, 2322, 9113, 4415, 1638, 2734, 2599, 7116, 4530, 7761, 8901, 5244, 7897, 6832, 8567, 2938, 1024, 7685, 9394, 4163, 5754, 7347, 4054, 4716, 4784, 1031, 8619, 6735, 1691, 9396, 6567, 1372, 3716, 836, 5526, 7083, 6491, 2036, 6056, 6064, 860, 9837, 5375, 944, 6101, 1723, 3358, 5028, 9333, 6935, 3970, 7675, 9100, 2893, 7404, 9404, 1497, 4464, 1321, 2208, 2149, 2353, 9479, 4327, 7378, 3210, 2091, 4979, 7498, 6849, 2624, 1499, 3539, 1104, 4090, 6367, 1379, 7965, 5308, 2062, 6698, 4766, 2228, 3728, 3116, 6340, 1587, 7374, 2380, 3499, 1843, 1492, 6233, 8431, 4491, 1457, 1091, 5039, 5175, 821, 5224, 2451, 543, 3345, 3125, 1019, 498, 807, 2103, 2912, 2840, 3115, 988, 2510, 5194, 607, 2869, 9092, 3264, 9938, 1344, 7974, 3276, 8898, 368, 8962, 6723, 6587, 3686, 7724, 2364, 773, 6444, 7733, 1352, 9649, 167, 2225, 9314, 8421, 2179, 2036, 3555, 3658, 7323, 2523, 6000, 2255, 4555, 6858, 2027, 2476, 8362, 1759, 2788, 8376, 9350, 5836, 3920, 4694, 1802, 5588, 7949, 2456, 260, 1140, 7909, 5647, 6038, 4981, 6471, 7047, 4290, 3438, 7957, 7828, 7208, 2680, 3028, 5533, 6106, 375, 2240, 7782, 7326, 6347, 380, 512, 2755, 5186, 7365, 1771, 5206, 7707, 2213, 6851, 4195, 491, 9792, 2821, 444, 5906, 7846, 4731, 9997, 3414, 8199, 5880, 465, 8045, 7184, 2508, 754, 3653, 3946, 1220, 5282, 1905, 780, 9278, 6202, 5327, 7492, 8143, 8714, 2780, 569, 8242, 6702, 5755, 8186, 6960, 9453, 8185, 5704, 3465, 2395, 1702, 7019, 4318, 3656, 6402, 1203, 6931, 55, 589, 3978, 2699, 3681, 8096, 9911, 1370, 6913, 7724, 6343, 3442, 5516, 4980, 9996, 6772, 9078, 3849, 2024, 9265, 4069, 4218, 3429, 5710, 1523, 3761, 4004, 6119, 1190, 264, 5619, 8478, 1124, 8688, 3996, 6663, 3006, 4985, 3242, 4237, 4474, 2072, 6168, 9546, 3913, 5603, 2122, 367, 6868, 7564, 7408, 7373, 1657, 8481, 8211, 7615, 5613, 6908, 8327, 3416, 4382, 115, 8162, 3657, 3263, 4607, 7653, 2439, 6417, 9373, 4942, 2862, 5297, 5570, 5163, 7505, 8544, 1014, 4089, 6709, 74, 3347, 8231, 6104, 2704, 9586, 9090, 1839, 7238, 9802, 2561, 479, 8847, 2193, 7901, 2929, 186, 1071, 3279, 6096, 1236, 2764, 7309, 5499, 1944, 5256, 6023, 8313, 7425, 5247, 2554, 82, 9173, 8987, 6961, 7906, 1991, 4847, 1936, 4875, 6133, 1221, 6517, 8489, 4973, 827, 2433, 9063, 4675, 7881, 5291, 5546, 8925, 8129, 1506, 7996, 4254, 9035, 9599, 1894, 3450, 3344, 8282, 9727, 5449, 9841, 5332, 1871, 8155, 7756, 709, 4133, 5614, 9549, 8600, 289, 380, 8426, 693, 5586, 1489, 3125, 3920, 5641, 4801, 2610, 3017, 9994, 304, 7024, 9231, 4718, 8983, 9243, 5795, 9239, 6205, 210, 4863, 5870, 1996, 5079, 3188, 7258, 6157, 4419, 3331, 2463, 4514, 3930, 8024, 7822, 3122, 6779, 1336, 969, 1032, 4408, 3179, 3366, 8272, 1319, 3612, 935, 3148, 8536, 482, 9908, 698, 3704, 8307, 3394, 3666, 9714, 617, 9065, 1331, 4055, 8279, 6141, 7876, 9415, 2403, 3081, 942, 3271, 9294, 3863, 9634, 2427, 2694, 7389, 4182, 476, 5533, 2049, 5552, 6831, 2559, 2634, 6818, 343, 3543, 355, 2680, 193, 1639, 2654, 8567, 4786, 6828, 8528, 2043, 3001, 797, 4758, 6777, 8067, 1653, 2625, 6697, 7470, 2548, 8190, 3390, 62, 9298, 1764, 6634, 945, 731, 5731, 4098, 5941, 5003, 9456, 8375, 8359, 9729, 4441, 6042, 8435, 8270, 8790, 1950, 4299, 5685, 7430, 2701, 4535, 3722, 9832, 3944, 7772, 9157, 8577, 9542, 4346, 7686, 7238, 4381, 6557, 2097, 5701, 8385, 4919, 4292, 3930, 4452, 4163, 7728, 7221, 3496, 162, 4551, 7568, 9660, 3457, 9442, 8908, 5523, 9239, 6072, 9011, 3180, 5704, 5705, 4259, 3787, 1914, 7699, 7164, 8285, 1736, 1946, 1183, 9232, 2934, 1974, 3619, 6584, 5959, 3166, 3030, 7162, 3811, 4320, 4980, 1966, 8780, 7240, 3832, 5647, 9006, 7793, 3353, 1839, 8272, 751, 5151, 7832, 8270, 6998, 337, 8675, 4663, 5533, 6101, 122, 9652, 4602, 7120, 4300, 6854, 5766, 5496, 8047, 7826, 6728, 2493, 4025, 9149, 2781, 3737, 1755, 7644, 6333, 5596, 1337, 7703, 7797, 812, 8815, 7404, 5800, 5320, 1807, 2754, 6584, 1081, 3547, 9111, 1597, 7490, 4283, 6798, 6923, 793, 6342, 9417, 4157, 8765, 9110, 8976, 5430, 9820, 1851, 6319, 3422, 6058, 2521, 7723, 3908, 3766, 2835, 1890, 177, 5774, 6741, 2581, 6584, 948, 3705, 6981, 7136, 2525, 2348, 7968, 9114, 839, 9617, 5940, 2529, 6524, 2778, 4774, 2774, 85, 6415, 4356, 6879, 5371, 2583, 5329, 3682, 924, 3903, 6702, 9, 6306, 2983, 6495, 4381, 7509, 8506, 9772, 3803, 6341, 315, 4039, 9790, 8006, 861, 5847, 6168, 6586, 3255, 302, 4539, 5126, 1176, 1853, 1834, 734, 6098, 1037, 5271, 9715, 9889, 7473, 7492, 1772, 8075, 1436, 2979, 4204, 5540, 903, 1040, 2253, 1629, 3560, 4049, 6445, 3554, 4660, 5653, 8707, 4781, 76, 3894, 9059, 9886, 1409, 4182, 6556, 4449, 9286, 5933, 628, 4195, 6018, 9060, 203, 68, 5796, 3088, 4070, 5842, 894, 7237, 39, 2345, 9952, 9837, 3541, 7386, 4025, 7574, 7777, 8635, 4897, 3402, 7521, 9088, 1428, 3412, 8959, 1889, 8697, 417, 8594, 791, 3188, 3149, 7284, 5872, 1856, 2014, 9485, 1009, 3668, 4877, 9575, 1483, 1665, 8794, 3358, 1721, 4275, 4942, 3295, 629, 3571, 4901, 3337, 1112, 9306, 2360, 8903, 2129, 1669, 7497, 4340, 6235, 4239, 9703, 8965, 7410, 5440, 8920, 9856, 9573, 5851, 466, 5833, 5578, 6540, 2939, 1843, 3141, 2001, 3566, 7175, 6454, 3269, 2462, 6828, 259, 8307, 3837, 9818, 9384, 6290, 2491, 4020, 2819, 6545, 7022, 693, 3451, 5709, 5329, 670, 8872, 2209, 3493, 7751, 3575, 8277, 331, 9734, 9882, 3774, 1389, 6168, 4197, 2448, 5656, 5806, 4556, 1028, 1023, 8302, 257, 6395, 5561, 7151, 168, 6967, 7083, 9860, 1484, 5524, 4112, 1870, 2218, 198, 6002, 4008, 7671, 9335, 5160, 8281, 9030, 7594, 7692, 1158, 6214, 5909, 6654, 606, 129, 7363, 4815, 6727, 1739, 6390, 364, 9665, 5903, 1093, 3445, 6428, 8477, 533, 6441, 6968, 2264, 9400, 3651, 9195, 2897, 6891, 1808, 4246, 9969, 2237, 9433, 2978, 6335, 1244, 6816, 4046, 1373, 8019, 7796, 5490, 9962, 4638, 1309, 5870, 3893, 6872, 9205, 2076, 1441, 1486, 4896, 6421, 3262, 7998, 9989, 6771, 44, 5769, 6381, 6672, 5529, 3249, 1497, 5413, 2372, 6213, 9822, 4512, 1194, 3690, 2717, 1735, 7605, 3650, 86, 9797, 6919, 6700, 7730, 8838, 8281, 2438, 6074, 7665, 1127, 6672, 3183, 8123, 5831, 3225, 5552, 3007, 4871, 1575, 7030, 8876, 6772, 4596, 9209, 5573, 3348, 460, 6502, 8057, 1768, 7605, 678, 6509, 9072, 5361, 1885, 9125, 2872, 4143, 9730, 1737, 303, 458, 5859, 7992, 9794, 9429, 2089, 5345, 1228, 6490, 4458, 4417, 8860, 2129, 729, 3893, 1489, 8748, 2103, 5654, 5942, 1084, 7800, 8997, 9496, 2488, 8774, 5204, 8933, 4189, 80, 8879, 8982, 1654, 6931, 4927, 6959, 8674, 6727, 5967, 7147, 8729, 4016, 5968, 883, 2323, 9459, 2966, 2598, 253, 2697, 2998, 7606, 2713, 5670, 1387, 9142, 4077, 8095, 2081, 9669, 7771, 1465, 1734, 6033, 8692, 6281, 8585, 8404, 5858, 6838, 8078, 2700, 2728, 8992, 9084, 7577, 7339, 6853, 5649, 6234, 585, 6448, 5400, 5542, 2273, 4268, 1197, 2407, 5809, 2708, 2042, 3353, 2017, 3232, 8223, 4752, 4594, 5150, 7189, 5903, 644, 5407, 6793, 7735, 8002, 3081, 8202, 3302, 6501, 927, 6988, 2732, 7999, 9103, 2135, 5763, 8106, 6179, 1885, 2836, 8670, 10000, 7358, 3041, 8661, 5987, 3754, 4762, 2923, 6890, 656, 7828, 5777, 8080, 2870, 3968, 6403, 1488, 2201, 6218, 9351, 8798, 7952, 2016, 5265, 9298, 5917, 1010, 6962, 8898, 7042, 1195, 1531, 2257, 6865, 9163, 7447, 3936, 2014, 2993, 4236, 787, 1305, 3389, 3333, 5071, 1828, 1660, 1798, 6006, 3910, 5888, 544, 7541, 6501, 901, 2968, 3056, 4635, 3709, 2813, 4730, 9625, 5629, 5479, 2770, 670, 62, 2692, 9310, 5974, 323, 3548, 3143, 4008, 6232, 7940, 4469, 9457, 2021, 3392, 2767, 1229, 4229, 1731, 6105, 1762, 3407, 157, 2288, 1708, 236, 5733, 1310, 972, 1231, 5145, 1129, 4025, 8287, 3777, 6552, 9279, 2915, 9749, 4455, 3313, 8916, 8504, 4391, 2667, 4851, 488, 8774, 5771, 1188, 1510, 6039, 5452, 1277, 3304, 9544, 1660, 3906, 7224, 9219, 6515, 1251, 7383, 6353, 4414, 9118, 8471, 6402, 177, 7300, 5236, 3128, 2972, 8044, 6119, 6571, 5140, 5869, 2233, 5808, 8690, 6887, 2537, 2277, 5111, 9328, 5571, 3667, 2420, 8705, 6504, 4513, 3613, 9399, 8501, 1547, 2029, 4078, 3508, 312, 4775, 3163, 7361, 6076, 8418, 2680, 7680, 4172, 6606, 3055, 1805, 2619, 9378, 2480, 359, 9933, 5175, 5719, 9875, 6643, 6113, 244, 1227, 7924, 3396, 2566, 2682, 1361, 8462, 9700, 2287, 7719, 3150, 9086, 1258, 5399, 170, 2784, 8046, 4299, 7675, 1091, 151, 6198, 6903, 7077, 9809, 3800, 6920, 6113, 4980, 3272, 6458, 5550, 8423, 3802, 2663, 9580, 5793, 1764, 8172, 7075, 6606, 2132, 5655, 5850, 7477, 3318, 1141, 4330, 6906, 4856, 5011, 8068, 5903, 6945, 8372, 8595, 9345, 5814, 5264, 458, 6243, 7735, 9471, 7413, 1100, 9575, 8645, 4093, 8226, 3428, 8286, 8419, 919, 9844, 1197, 4183, 904, 9225, 415, 2559, 1907, 1955, 1192, 7319, 3328, 2848, 9347, 6636, 3358, 3680, 6702, 6562, 8057, 8281, 6552, 5247, 6001, 2442, 4442, 9457, 986, 6136, 2140, 8220, 4602, 9767, 52, 1166, 3162, 902, 3992, 3590, 2674, 234, 3859, 865, 1818, 8211, 4764, 3978, 4063, 1942, 1208, 7619, 341, 7094, 9201, 8989, 5104, 6301, 1132, 1894, 1018, 6951, 4558, 1258, 8032, 6164, 4938, 6310, 9927, 3526, 5692, 3290, 8199, 1212, 6071, 3521, 2826, 5276, 206, 6689, 3622, 8980, 2193, 1383, 1849, 8599, 134, 840, 461, 3662, 6231, 8909, 3307, 3654, 2171, 8341, 784, 4199, 3107, 7813, 4393, 1820, 1204, 8648, 202, 3235, 4186, 1750, 5056, 1131, 4508, 2203, 5354, 5229, 8712, 6766, 8107, 8668, 3112, 6895, 4510, 5493, 4062, 7130, 8216, 3796, 4347, 3814, 2071, 6556, 6321, 5199, 76, 5178, 1563, 9253, 1510, 9746, 661, 7117, 1003, 4704, 1090, 353, 3332, 1963, 9027, 364, 2368, 9665, 3188, 7593, 7444, 4016, 9084, 9619, 3864, 255, 7542, 3639, 6325, 2116, 7933, 4361, 9781, 3612, 11, 22, 968, 4496, 6958, 8230, 4427, 4181, 3603, 7805, 5233, 9438, 994, 6449, 7615, 8235, 4038, 1219, 4237, 1344, 640, 618, 1736, 8610, 6534, 6035, 8496, 4376, 9351, 5456, 8248, 6543, 2800, 486, 4560, 699, 1937, 1591, 8454, 3800, 8369, 6986, 8727, 5633, 214, 3698, 9824, 3789, 8385, 6700, 8478, 8301, 4970, 2537, 9033, 572, 3222, 9420, 5544, 841, 458, 3938, 7820, 2310, 7921, 929, 4944, 1320, 1480, 3233, 2508, 6488, 6556, 614, 9498, 9918, 1655, 9162, 7247, 8139, 3437, 1298, 2619, 6384, 7115, 4519, 4898, 2775, 3137, 1592, 7120, 2641, 3852, 371, 7548, 7028, 9555, 5347, 1782, 9798, 88, 8263, 8287, 2750, 3628, 3368, 574, 1445, 1391, 5920, 3693, 7220, 2053, 2556, 3380, 3765, 4625, 8783, 1749, 1304, 5582, 2406, 5773, 4739, 3333, 1473, 7793, 1342, 6917, 5824, 9278, 2774, 5706, 7239, 1321, 7999, 5542, 992, 3538, 7219, 8206, 3051, 981, 9927, 7323, 2189, 930, 3252, 5838, 2832, 7747, 9180, 3579, 1534, 507, 350, 4370, 2521, 5645, 2589, 2130, 8885, 5230, 6896, 510, 7490, 5508, 4337, 9556, 586, 1020, 2356, 4674, 7762, 2605, 4161, 89, 2629, 803, 3074, 339, 2064, 3545, 5314, 2551, 669, 8394, 8525, 4456, 2610, 8723, 8866, 8814, 1455, 110, 661, 9197, 6600, 1815, 8461, 7004, 3810, 3956, 3395, 5825, 2023, 9240, 5751, 1541, 6999, 51, 2122, 8743, 2195, 2954, 7823, 7426, 484, 1943, 4039, 5424, 1273, 2046, 7664, 4739, 4769, 4385, 663, 5868, 5261, 3798, 2818, 5178, 885, 7061, 5369, 6837, 5047, 3585, 2142, 3644, 7590, 8722, 7880, 5477, 6426, 3189, 5903, 6774, 1588, 9457, 8154, 5343, 1313, 5905, 6984, 6511, 4694, 6617, 9782, 1253, 5411, 9660, 1493, 187, 1899, 5809, 7767, 9146, 7533, 6259, 8898, 3623, 6423, 9480, 4245, 255, 3373, 9251, 4126, 7427, 6726, 4447, 6865, 8314, 275, 4719, 6962, 7532, 4899, 7764, 9475, 8731, 3266, 7119, 569, 6125, 6940, 3126, 1859, 5458, 9005, 6990, 7533, 5508, 4373, 3918, 7638, 7936, 944, 6593, 648, 1080, 5475, 8028, 7980, 9399, 7003, 118, 790, 4024, 3101, 9727, 411, 6392, 1990, 590, 3829, 6218, 3748, 7661, 4084, 2235, 1212, 1164, 6280, 6618, 1405, 781, 8608, 1618, 8965, 7487, 7173, 9081, 3171, 1633, 3398, 7061, 2501, 8779, 1773, 8506, 7176, 5197, 192, 5876, 3638, 3622, 4701, 9219, 3049, 924, 1333, 2315, 3925, 9017, 8057, 2204, 2011, 241, 5229, 1690, 9534, 2713, 5341, 4102, 3212, 7982, 9428, 6391, 1064, 295, 2770, 1874, 7921, 6242, 9938, 9319, 5662, 1002, 5207, 4948, 3335, 4695, 5068, 21, 2719, 2, 7992, 8609, 3692, 9937, 2032, 1752, 8448, 7303, 1422, 428, 6387, 1457, 9899, 9977, 4671, 8522, 4557, 7676, 8687, 2017, 8043, 5613, 2342, 7542, 5284, 2111, 6849, 2314, 5358, 5588, 3455, 6065, 2918, 6605, 2933, 3598, 7565, 9067, 3197, 2401, 8280, 8361, 4865, 1704, 770, 515, 7202, 3118, 9116, 2468, 2419, 9099, 4884, 7171, 6763, 3422, 6706, 2660, 2189, 7042, 3695, 6664, 5026, 3335, 7411, 4752, 1186, 3756, 6819, 7605, 4044, 9211, 2461, 5023, 2832, 3958, 134, 5106, 4759, 7491, 5967, 8346, 6104, 6501, 1927, 783, 8649, 9941, 3703, 9780, 2101, 9994, 8955, 3518, 6320, 9594, 450, 9076, 68, 5821, 3908, 6991, 7519, 7443, 495, 608, 7772, 4221, 3259, 718, 8971, 9534, 2380, 4646, 9785, 3021, 7984, 2481, 7719, 560, 3261, 5093, 5140, 3657, 6385, 2568, 5823, 8253, 4019, 3207, 5860, 3342, 6089, 5190, 2556, 8358, 7465, 7069, 7637, 5052, 4674, 7955, 7119, 6831, 162, 5795, 6801, 5610, 762, 9313, 4972, 4203, 4414, 3298, 1242, 2833, 3626, 6993, 3224, 5318, 7234, 5281, 4486, 8300, 8627, 1294, 3019, 4762, 6671, 9090, 6380, 6693, 8107, 7113, 1281, 3797, 6380, 6724, 5258, 521, 9864, 143, 4175, 2065, 431, 1911, 8730, 2725, 5269, 3985, 3891, 9806, 6998, 7570, 6397, 7287, 768, 9215, 5626, 2141, 9859, 8171, 5167, 536, 1220, 9843, 956, 775, 4939, 2334, 7537, 6323, 5110, 1575, 192, 5119, 3333, 1162, 710, 304, 1478, 8689, 8730, 6225, 6583, 2890, 9292, 3500, 7104, 2800, 9801, 6095, 4005, 2667, 6191, 3274, 231, 2838, 7387, 3482, 3026, 6247, 8092, 9278, 6042, 5591, 6252, 2464, 4705, 5216, 589, 1113, 9695, 7215, 4170, 5069, 2062, 9561, 9588, 3557, 4312, 2413, 4489, 6740, 3581, 3298, 4595, 7625, 8903, 4417, 8473, 2410, 8891, 8098, 429, 5170, 8934, 7920, 9786, 317, 3842, 5226, 6034, 6567, 2921, 4986, 248, 1804, 6454, 8880, 2282, 4393, 9974, 4456, 4063, 8818, 6555, 4254, 743, 337, 255, 2721, 8464, 6000, 3004, 7805, 3896, 1704, 358, 8656, 4134, 257, 5362, 1746, 6492, 614, 4404, 6476, 5069, 8667, 301, 1843, 5016, 3338, 5389, 8861, 2181, 9432, 4370, 1197, 7170, 1158, 7509, 2381, 8631, 6786, 8452, 7486, 1524, 6639, 6650, 1936, 591, 8474, 7638, 8981, 1738, 2349, 9155, 9638, 8353, 7077, 130, 7562, 6760, 1302, 420, 2831, 4395, 4411, 4389, 6729, 8146, 146, 8806, 6, 4168, 8943, 8615, 8532, 7954, 2594, 1089, 9087, 6895, 3768, 5775, 8735, 4225, 8977, 6861, 447, 205, 7502, 614, 4588, 1798, 5470, 1953, 1146, 2052, 5064, 9347, 6660, 7411, 2870, 338, 8431, 9738, 5158, 6692, 1321, 1201, 1866, 2084, 2312, 6921, 3687, 8782, 9760, 8043, 3868, 6638, 7468, 7595, 9817, 9072, 5547, 8482, 9546, 922, 3856, 2671, 344, 5303, 6428, 6768, 2678, 8028, 380, 3513, 2154, 6196, 4365, 813, 3404, 758, 2471, 8417, 929, 1933, 7708, 7139, 3695, 6038, 4795, 3102, 325, 9399, 2030, 1925, 5007, 3600, 7324, 929, 2563, 2995, 9149, 
	//	5841, 66, 7196, 5275, 2095, 307, 2887, 674, 1726, 4112, 1074, 2824, 881, 7326, 1288, 2666, 9069, 2145, 5049, 8018, 4136, 5481, 670, 9901, 5770, 7107, 6038, 8560, 8010, 2898, 3378, 2709, 7879, 6804, 7746, 7163, 5122, 2445, 6619, 7988, 7074, 8829, 7939, 8653, 1193, 4837, 792, 5471, 4007, 1940, 815, 3008, 8151, 2898, 5294, 3363, 2733, 8104, 6893, 3465, 7465, 1390, 342, 6987, 2770, 6540, 7432, 4876, 1707, 8034, 5298, 9909, 3298, 3256, 4304, 2878, 883, 7030, 5320, 726, 1241, 8191, 3443, 722, 1904, 3284, 979, 9636, 9593, 3064, 1182, 5966, 9666, 2487, 7227, 1388, 8486, 4588, 7657, 8495, 9761, 8172, 1627, 8225, 6469, 8825, 4882, 5463, 5131, 2315, 5602, 2883, 2358, 1386, 6555, 2635, 5330, 1552, 5997, 9739, 3564, 5459, 9269, 1813, 5983, 7247, 328, 2781, 6046, 1310, 1584, 6677, 5006, 3128, 9720, 692, 6374, 507, 4464, 3251, 8463, 4511, 3176, 1849, 2565, 6, 6816, 3184, 1981, 7386, 8222, 8611, 111, 5956, 7158, 3709, 8079, 726, 5474, 190, 6555, 6299, 6754, 4193, 423, 3934, 2566, 1289, 6992, 9078, 6576, 9471, 1110, 1012, 6670, 4300, 6201, 4741, 7576, 2426, 9299, 7662, 9100, 9894, 4130, 1446, 3625, 7191, 2795, 8151, 9634, 6849, 8290, 1854, 8390, 1094, 196, 8931, 9962, 1370, 8429, 3761, 5381, 9038, 3103, 216, 8555, 9220, 4433, 5783, 5034, 8412, 7301, 5274, 1842, 5909, 6101, 247, 7540, 410, 1542, 430, 2220, 4855, 8248, 8168, 7306, 1288, 3166, 1299, 1315, 5612, 3610, 2306, 2378, 9706, 1282, 3332, 6003, 9385, 6147, 3437, 6202, 3953, 1493, 4703, 706, 147, 460, 1265, 2000, 231, 7124, 9938, 6296, 1054, 6745, 3867, 9028, 6503, 9944, 8389, 3142, 1056, 7183, 6236, 5896, 7156, 4512, 3778, 6648, 8355, 2336, 3157, 516, 5430, 4698, 8822, 6014, 6178, 2366, 3585, 5322, 8353, 1799, 3644, 7484, 6508, 5718, 177, 1667, 5495, 5987, 1279, 185, 9815, 8660, 9369, 1753, 6517, 9546, 9305, 7604, 1362, 2940, 9474, 1886, 8294, 9238, 2149, 968, 759, 6034, 3592, 6866, 3662, 8559, 9989, 6163, 4850, 4624, 2290, 1943, 299, 5042, 2381, 4636, 8143, 5952, 7427, 2583, 2300, 520, 2455, 1728, 6921, 8523, 9263, 8877, 5145, 544, 8721, 3492, 3286, 7455, 383, 2103, 2737, 7213, 7066, 6400, 2105, 8121, 8402, 7496, 2188, 1472, 6401, 4077, 2329, 3384, 5485, 9544, 6733, 7468, 1341, 5290, 7136, 4697, 7471, 8027, 4330, 2928, 8560, 7354, 9538, 503, 5395, 9905, 7810, 1680, 7509, 4177, 4890, 6699, 3219, 3988, 3976, 5592, 7315, 6391, 6257, 2375, 7121, 3707, 3517, 8797, 1526, 7392, 9618, 1231, 9983, 5467, 4271, 7816, 2302, 7367, 9968, 6760, 8946, 372, 7255, 6447, 14, 549, 4056, 1709, 2832, 3361, 4018, 7040, 5910, 1106, 7931, 5758, 8668, 225, 7968, 8720, 849, 5676, 6082, 6334, 2508, 9170, 2256, 7553, 4206, 8211, 3163, 444, 1208, 6693, 9987, 3797, 930, 1087, 3801, 8403, 8606, 82, 313, 7934, 388, 6796, 4255, 107, 2065, 9390, 3192, 2634, 8308, 1474, 7002, 271, 2234, 8291, 5737, 1586, 192, 8935, 6312, 313, 5884, 4953, 5606, 2715, 7857, 2695, 6996, 3289, 4479, 9603, 3996, 2996, 5875, 1065, 8470, 3818, 2649, 6879, 3304, 1260, 9772, 7705, 867, 3527, 7469, 7595, 5529, 1716, 1424, 2724, 3404, 3530, 8335, 2746, 9853, 3943, 3927, 9250, 1797, 5204, 4374, 3153, 526, 5004, 7214, 8549, 9718, 5127, 3879, 3233, 9857, 9225, 779, 5374, 9966, 9052, 3681, 9066, 2969, 9145, 421, 4984, 9620, 8571, 8051, 7074, 9479, 2712, 2901, 1926, 1812, 9247, 5496, 5978, 2487, 2419, 8701, 3291, 4632, 5902, 5631, 785, 5281, 6874, 9734, 9774, 9480, 3018, 5424, 4539, 7609, 8865, 1744, 7379, 3288, 168, 7784, 3778, 7814, 6308, 6672, 8510, 4923, 2623, 5567, 7605, 3997, 2543, 2452, 8309, 3118, 6657, 2082, 3911, 9156, 7154, 7769, 6476, 9247, 3264, 1949, 4555, 9482, 9757, 5204, 616, 2055, 9041, 2419, 5833, 6274, 7617, 9091, 271, 7257, 1869, 8899, 9756, 9889, 4721, 5394, 9828, 2642, 3071, 7562, 7441, 4059, 5567, 9510, 1766, 328, 7346, 7713, 7217, 3732, 1540, 9569, 3322, 5561, 480, 3215, 5670, 3967, 7459, 5813, 3812, 1051, 6084, 5975, 5770, 25, 1535, 4208, 5713, 6806, 8233, 5430, 4065, 7990, 8230, 4157, 657, 7250, 4513, 469, 9798, 8712, 883, 1589, 2041, 1589, 8650, 6478, 4740, 4896, 4446, 9563, 1969, 8041, 5279, 1761, 1676, 6206, 9291, 8081, 3215, 9657, 9106, 1664, 1718, 1742, 6499, 5228, 3093, 3699, 1056, 1786, 8052, 49, 777, 8548, 8419, 3213, 4799, 8347, 578, 5318, 9070, 3091, 3373, 230, 2212, 7019, 6023, 215, 5973, 1438, 2496, 5579, 2910, 70, 6379, 6363, 3287, 7533, 7968, 1843, 9783, 316, 3572, 1763, 6789, 8880, 7133, 1174, 2666, 6107, 3422, 5039, 829, 9255, 7694, 6581, 9480, 5368, 854, 1266, 8847, 3588, 6343, 3716, 2086, 4053, 7304, 8337, 7687, 1874, 1798, 9316, 9907, 9775, 8126, 6349, 9885, 5312, 4371, 5767, 6689, 5523, 4527, 4758, 567, 1417, 7718, 668, 5804, 187, 2860, 6236, 7770, 4619, 4722, 3628, 8713, 9834, 7472, 1608, 2077, 8345, 5739, 9495, 894, 8477, 5293, 4551, 8606, 9508, 1307, 1678, 3312, 7540, 3808, 8964, 2880, 5141, 7590, 8304, 5137, 3171, 6294, 9123, 4528, 7031, 3982, 9244, 4257, 3988, 3581, 8000, 7410, 4966, 9999, 6219, 4011, 4442, 1171, 2536, 4247, 9469, 5302, 4488, 1281, 2909, 3364, 1865, 2618, 4401, 9325, 9674, 5916, 4218, 3815, 8654, 9653, 348, 2012, 5037, 1930, 3204, 3839, 5670, 8500, 3021, 1198, 4988, 6989, 5092, 8333, 877, 9684, 5060, 730, 972, 2773, 8010, 7838, 6843, 4061, 3677, 1778, 515, 5401, 2583, 8149, 1123, 2786, 8305, 1350, 6644, 8287, 4152, 3332, 827, 1938, 9761, 8218, 9030, 9630, 1161, 5437, 8713, 2923, 3848, 6196, 9922, 3143, 1259, 125, 8927, 735, 3907, 3192, 7770, 6948, 4602, 9957, 5008, 6744, 6544, 5229, 5227, 3809, 9672, 4114, 9342, 4797, 2529, 7409, 705, 3998, 6633, 1786, 128, 9035, 5756, 4715, 2340, 7182, 2225, 5439, 3200, 9031, 488, 6753, 1280, 3048, 8486, 9137, 3413, 2278, 9302, 7391, 5978, 9826, 2484, 865, 5981, 1619, 8303, 5202, 7016, 8591, 6231, 6066, 5285, 5377, 1839, 194, 2239, 5608, 2497, 6341, 4135, 7983, 7769, 9661, 902, 8124, 9008, 9837, 5099, 3845, 9509, 4712, 6441, 7361, 1532, 8504, 6565, 9377, 5034, 8295, 4847, 5403, 5895, 6855, 3367, 3611, 7979, 3805, 3518, 8697, 1666, 1992, 2521, 9702, 9091, 9089, 491, 396, 1792, 6543, 9420, 4994, 2242, 6869, 9006, 9311, 3360, 2229, 7596, 4431, 7011, 7590, 3868, 4832, 991, 5475, 1547, 4742, 6582, 7184, 92, 2813, 7561, 9102, 5588, 2707, 8837, 6306, 5309, 1103, 2866, 1423, 8264, 304, 3611, 1877, 3982, 7993, 7881, 6329, 9862, 7330, 3158, 8601, 670, 31, 1943, 8558, 4273, 5179, 2898, 2976, 1370, 2817, 7868, 5794, 5720, 8980, 1644, 9840, 6805, 8159, 6059, 3279, 8157, 5626, 4390, 1354, 1833, 2612, 366, 4046, 1523, 4889, 2948, 6335, 3316, 1267, 6809, 8967, 9658, 3574, 3544, 4015, 532, 2838, 4311, 5991, 3870, 888, 2186, 1259, 7324, 6018, 2386, 9765, 9789, 8086, 5318, 4219, 1065, 3878, 3790, 4788, 8784, 1693, 1864, 1716, 8219, 4977, 9021, 7680, 5538, 5214, 2699, 8643, 4871, 1091, 1229, 7999, 1657, 3283, 6112, 1523, 9329, 6013, 7558, 3691, 3901, 8380, 5614, 799, 6598, 1743, 6378, 8652, 8409, 9391, 2559, 2149, 1872, 6677, 3320, 9204, 1002, 86, 7085, 7704, 7806, 8452, 842, 3226, 3821, 1593, 2218, 6181, 8000, 234, 9285, 2248, 4697, 262, 176, 3362, 2541, 5067, 9835, 7606, 4899, 8474, 1960, 5708, 1486, 9693, 3917, 7832, 3925, 1676, 6447, 1278, 4423, 2055, 2181, 5207, 2583, 1983, 3340, 6882, 349, 8379, 5023, 1721, 6127, 4370, 6657, 7505, 5008, 7358, 623, 1376, 7794, 3617, 1591, 9823, 3036, 1905, 4808, 6724, 1190, 9715, 7391, 6086, 8001, 7936, 5529, 57, 2234, 2523, 5184, 890, 6551, 2519, 1915, 4209, 2230, 3620, 3089, 1544, 8488, 5293, 1242, 2271, 2326, 3839, 5546, 1425, 1562, 5142, 9055, 3898, 2323, 7340, 8224, 2033, 7617, 2983, 354, 5677, 1226, 3196, 5025, 8723, 8131, 9505, 6396, 5912, 5295, 5478, 8639, 2348, 9676, 8239, 4746, 8980, 8492, 8470, 651, 1481, 7529, 1292, 728, 9479, 3469, 128, 2396, 8124, 7497, 7602, 3167, 8552, 1009, 9758, 2680, 9194, 9714, 5238, 5335, 7860, 161, 6609, 1690, 6912, 5801, 3142, 461, 3200, 8134, 3085, 4331, 1549, 5161, 2282, 6535, 7196, 587, 5947, 6127, 7758, 1764, 2983, 575, 5395, 1029, 8296, 6654, 45, 8197, 9849, 3291, 7266, 1131, 1696, 2689, 5144, 5429, 4193, 9937, 2330, 4128, 6502, 2624, 7862, 713, 4800, 8467, 4966, 6881, 18, 7468, 8216, 5406, 975, 9766, 7697, 2833, 1331, 5825, 683, 5179, 5266, 6340, 4360, 9204, 8255, 1503, 787, 3474, 554, 6139, 9461, 252, 546, 7451, 8424, 9050, 9059, 9039, 7034, 9622, 2931, 668, 6516, 9888, 2551, 383, 4001, 6364, 7501, 9806, 7875, 8805, 2675, 2633, 5931, 1729, 4469, 1246, 926, 6236, 7958, 6446, 2006, 3377, 7128, 5132, 5832, 3857, 9926, 6591, 1707, 4530, 3332, 4284, 5009, 7452, 9416, 8931, 628, 5238, 2428, 3744, 5101, 2643, 7144, 8514, 2063, 8597, 5206, 6384, 5119, 3644, 9787, 5029, 6874, 9773, 6968, 3765, 2285, 4053, 8640, 4750, 698, 9246, 8394, 6199, 8947, 6244, 3849, 9459, 7504, 2672, 4706, 2168, 6051, 8970, 2984, 8375, 6986, 4031, 2059, 6142, 6783, 844, 4850, 4182, 4584, 8635, 8278, 9335, 1604, 4470, 2829, 1914, 5863, 5248, 3103, 3280, 433, 5213, 5530, 7072, 9453, 9080, 4176, 9453, 9856, 3144, 3406, 9393, 4901, 2389, 9694, 1297, 9027, 9056, 1779, 7438, 4613, 9661, 8433, 3714, 2473, 9390, 1092, 5448, 1826, 6413, 661, 265, 9507, 3838, 92, 4138, 927, 3551, 7196, 8713, 6690, 1199, 425, 3687, 9432, 1145, 8726, 3803, 1265, 1849, 9072, 5721, 1089, 7269, 4785, 396, 6275, 9527, 7862, 4921, 3479, 6175, 6368, 6719, 3573, 3184, 6006, 9457, 5274, 5534, 1117, 2967, 3596, 6962, 3224, 821, 7996, 3557, 8624, 6707, 2163, 3375, 1282, 3828, 3927, 818, 2356, 9468, 4999, 6203, 465, 6204, 9992, 2276, 325, 1645, 2090, 4757, 7201, 6670, 7604, 5583, 3318, 941, 7144, 277, 1390, 4617, 4809, 8163, 2423, 8346, 6578, 9267, 8301, 6681, 1783, 8481, 4957, 3107, 1748, 3802, 8408, 1850, 2684, 8170, 2627, 3482, 6977, 1770, 4251, 8539, 6212, 4631, 3594, 7030, 3341, 3515, 4611, 4034, 8277, 3182, 7197, 4693, 9567, 6596, 2344, 778, 844, 8930, 369, 4671, 554, 6131, 9207, 8560, 8927, 3287, 31, 3133, 6016, 8377, 7497, 9669, 1482, 3279, 3269, 2469, 6512, 9157, 2828, 9773, 7271, 1764, 6405, 7107, 5672, 2075, 1819, 9376, 7406, 6095, 852, 191, 6745, 3659, 6667, 7455, 2281, 9270, 6145, 3806, 7820, 6345, 6073, 6293, 9381, 2390, 2733, 1830, 4991, 5819, 7394, 1535, 4668, 9175, 9684, 1945, 2438, 3242, 4590, 4031, 7892, 4539, 7521, 8523, 5868, 7256, 2555, 7275, 5405, 3133, 2079, 1018, 6027, 5680, 1299, 7991, 3827, 3536, 4245, 7738, 9842, 3076, 438, 8474, 5303, 7351, 8423, 593, 7321, 8663, 7318, 9242, 6348, 2782, 9127, 3251, 3219, 5444, 448, 9256, 6320, 4796, 7804, 7969, 4739, 6139, 842, 7061, 3659, 2341, 3001, 7614, 5698, 965, 7607, 6371, 5872, 9613, 5, 5051, 9371, 9036, 5447, 1921, 4201, 9038, 4358, 1043, 1498, 4094, 961, 74, 5998, 9991, 4849, 9723, 6404, 4630, 3529, 5598, 4891, 8272, 7843, 4680, 9407, 1037, 5157, 8339, 2094, 1100, 1888, 7736, 8528, 9954, 3259, 4909, 742, 445, 6492, 6135, 5892, 1236, 7559, 4392, 7152, 2256, 1589, 8827, 89, 4985, 9030, 9340, 3139, 6178, 8951, 9174, 4926, 2000, 2444, 6714, 1991, 4534, 7394, 9459, 1830, 4538, 3211, 9806, 6177, 8990, 7642, 9406, 5071, 1790, 6059, 2474, 4108, 7746, 2358, 3413, 2550, 6045, 4337, 2901, 3351, 84, 3547, 3613, 2735, 6638, 9958, 9758, 4921, 4238, 9425, 1598, 6396, 2053, 6610, 6304, 4340, 7549, 9404, 7248, 8944, 1925, 2172, 1500, 1384, 3414, 9770, 1778, 4308, 9400, 3231, 4343, 1725, 3676, 357, 4216, 9453, 3552, 3317, 529, 2876, 1990, 4193, 9891, 8178, 4403, 4268, 917, 9801, 2108, 6075, 8058, 6155, 7123, 6962, 7428, 583, 2242, 2093, 9407, 216, 6122, 8953, 4243, 2402, 3892, 693, 4655, 4006, 8228, 3405, 9153, 2029, 2708, 537, 1307, 1099, 6048, 6524, 903, 3107, 2163, 6175, 1269, 7412, 5157, 8329, 4716, 1963, 1438, 5163, 3112, 8055, 375, 2761, 9516, 1776, 2193, 4169, 3626, 7471, 6840, 2033, 7073, 2332, 4284, 2121, 4655, 6, 1573, 4038, 5743, 4941, 2883, 1172, 9999, 2071, 4665, 6756, 4264, 7108, 9023, 7887, 8288, 5462, 236, 4320, 7352, 9689, 7434, 9403, 4617, 6368, 4582, 2047, 1804, 5527, 6760, 4237, 8329, 1920, 8371, 7170, 7043, 5982, 3901, 2821, 4605, 976, 3692, 2589, 2760, 4251, 5384, 6826, 3903, 6766, 8517, 9627, 6187, 2037, 6623, 1138, 5895, 2556, 3089, 5584, 8920, 7103, 3339, 9511, 9861, 7844, 158, 541, 3839, 778, 6181, 6618, 4780, 2854, 1198, 655, 5048, 2271, 1865, 2816, 9862, 4237, 8583, 2376, 7936, 9427, 4736, 9747, 4157, 5344, 8431, 1176, 1213, 8985, 1621, 3033, 1887, 2425, 3665, 7038, 5406, 2748, 2074, 9400, 325, 2059, 6579, 3884, 7888, 5630, 9310, 990, 2351, 2949, 1905, 2067, 7618, 3619, 9430, 6768, 4031, 5418, 5303, 2527, 4563, 73, 8517, 426, 6661, 6079, 9068, 8454, 6846, 378, 4103, 5342, 7072, 3531, 7919, 3385, 5787, 3422, 7877, 8320, 1204, 9526, 2277, 30, 1130, 9933, 114, 8193, 2627, 53, 9971, 3227, 9725, 3222, 4068, 5235, 7838, 8824, 2404, 1170, 2084, 9211, 7927, 724, 7247, 1247, 8010, 4372, 1986, 2881, 4440, 9972, 3544, 1474, 292, 8547, 4800, 2225, 9228, 1692, 5989, 4568, 672, 6695, 2170, 4805, 4042, 1506, 3168, 2298, 6512, 3771, 3384, 4543, 1634, 6705, 4915, 5867, 9435, 6698, 9096, 8314, 2063, 1388, 21, 3893, 1101, 9076, 5893, 636, 5762, 919, 1629, 3894, 4666, 855, 9167, 3211, 5849, 2824, 2514, 5773, 6430, 6537, 519, 6939, 8702, 6095, 3086, 8267, 8164, 7740, 6213, 9523, 5351, 6190, 4780, 2687, 6425, 2031, 9960, 7073, 1518, 7947, 9685, 7007, 2810, 7831, 3095, 5717, 9101, 885, 2512, 2526, 3015, 3392, 8769, 2906, 194, 1366, 7289, 6236, 6774, 433, 6277, 3788, 3615, 5337, 7407, 5927, 6034, 2688, 6470, 3673, 7593, 2972, 2205, 7327, 8106, 3623, 2719, 9850, 2917, 7441, 779, 2015, 749, 6776, 8670, 8072, 7409, 1824, 4184, 7801, 1249, 6688, 680, 9562, 9896, 5029, 3689, 9935, 9918, 9328, 8571, 8119, 9809, 866, 5215, 1012, 7853, 3564, 7488, 4628, 3365, 2867, 2514, 6048, 8829, 1033, 6534, 3460, 3982, 4870, 9423, 3063, 4159, 6662, 3737, 5317, 8049, 199, 8693, 9482, 284, 3797, 9681, 1903, 3436, 1868, 9804, 2362, 9492, 9746, 2571, 4751, 483, 5262, 1783, 4809, 9761, 9705, 3501, 3201, 2352, 6676, 3636, 3315, 2405, 6529, 3961, 3336, 449, 6617, 6727, 7742, 704, 1423, 8872, 6231, 3083, 507, 4066, 2016, 3825, 2474, 6147, 7966, 2466, 3324, 680, 9486, 347, 4558, 857, 7483, 5479, 720, 680, 9835, 6224, 2355, 8949, 5778, 3446, 6331, 7161, 8064, 9152, 2364, 9936, 3424, 530, 3141, 6403, 2911, 3700, 1995, 5936, 7228, 8822, 3919, 453, 1534, 9480, 440, 8705, 4414, 8278, 8470, 4296, 497, 7741, 1652, 1805, 3881, 6685, 6939, 8404, 2313, 1901, 9467, 2728, 5536, 7948, 1267, 945, 1717, 8440, 7716, 9524, 5434, 6582, 3362, 1410, 9995, 89, 125, 139, 931, 7289, 4391, 3829, 8655, 8737, 1976, 4024, 3756, 5170, 6492, 3440, 8753, 706, 2813, 7152, 2134, 1661, 2305, 6008, 2728, 139, 7199, 7720, 5364, 6947, 53, 3684, 6670, 2047, 2449, 2531, 5692, 8311, 3211, 2375, 3930, 3456, 7831, 2717, 4118, 4992, 5797, 1872, 7744, 8792, 2536, 7214, 927, 2156, 117, 5878, 1020, 7315, 8100, 9656, 8029, 3204, 4427, 6530, 1623, 1756, 7949, 3475, 6260, 8581, 5383, 7229, 3442, 7979, 1271, 1926, 8037, 6718, 4957, 9823, 3225, 7439, 3701, 3084, 9358, 4469, 6603, 9994, 7518, 982, 6272, 352, 7534, 3334, 9986, 7974, 4163, 8191, 3024, 9976, 1944, 6072, 6649, 8270, 2229, 3962, 7166, 4056, 3589, 745, 1605, 9252, 3425, 8169, 6178, 742, 4273, 3772, 349, 866, 5091, 2099, 4720, 9099, 6810, 1388, 6676, 9551, 7810, 4742, 2232, 1193, 8376, 1257, 9575, 4243, 6490, 6186, 7306, 5095, 3944, 5077, 5618, 2328, 4679, 5173, 2310, 664, 4736, 814, 6660, 9367, 3424, 3431, 9923, 6159, 6007, 9628, 1736, 5312, 4613, 7152, 9818, 4382, 9028, 4715, 7446, 4047, 1756, 8930, 5690, 8237, 2440, 7853, 355, 5215, 1945, 5454, 1657, 8703, 2649, 4181, 4077, 8126, 2151, 6852, 8178, 3452, 5995, 7200, 6694, 8477, 1437, 2243, 2201, 3327, 9224, 1650, 1438, 7733, 6478, 9823, 2476, 8689, 1433, 6442, 6826, 2204, 5510, 9570, 4453, 6002, 8042, 986, 3067, 7870, 7458, 5173, 4694, 3204, 5255, 3040, 3728, 4533, 8590, 3074, 9803, 198, 5651, 1116, 5907, 263, 1920, 6166, 8807, 3608, 4103, 7943, 9094, 4042, 3185, 1303, 7558, 6100, 6364, 9481, 358, 756, 6946, 4463, 6645, 831, 1185, 4777, 9247, 6944, 5867, 4432, 2741, 2823, 453, 1678, 5085, 4865, 6953, 1090, 1092, 945, 6709, 9006, 6998, 9844, 6057, 960, 2239, 5841, 7996, 1084, 3134, 4088, 9260, 4362, 2763, 6296, 1391, 1157, 3631, 4906, 2671, 160, 5026, 7729, 5037, 3340, 4716, 6366, 6770, 9037, 6605, 5624, 4081, 1669, 6647, 7514, 3358, 4001, 9935, 4493, 4281, 118, 8227, 6882, 1216, 4198, 753, 6974, 403, 9436, 8339, 7077, 8128, 838, 1545, 1983, 9183, 3176, 4266, 7226, 8099, 8537, 2471, 3562, 7636, 5945, 8345, 4725, 2480, 6545, 7032, 9682, 6793, 7399, 2264, 8337, 9077, 667, 889, 2271, 6904, 1477, 2341, 8267, 345, 9285, 9011, 6683, 852, 4279, 2620, 2541, 4607, 1399, 9589, 135, 7498, 2558, 5677, 8767, 3613, 3923, 5005, 6500, 2714, 5983, 9552, 3593, 5360, 1851, 3396, 8092, 1869, 6290, 8505, 1902, 3540, 2742, 2373, 8844, 4763, 6132, 3062, 3104, 1739, 4546, 6687, 7494, 133, 6190, 2647, 1419, 9464, 9466, 4968, 3258, 5033, 7146, 8820, 349, 6744, 1417, 3144, 8854, 636, 7756, 3520, 2125, 5034, 9606, 9493, 3989, 4340, 953, 8313, 5627, 2381, 501, 7467, 1648, 8366, 3425, 4526, 4355, 5250, 6062, 933, 9262, 7602, 1815, 4240, 3076, 9312, 6667, 6390, 3965, 4327, 2078, 6160, 48, 4069, 409, 9564, 7994, 4380, 2648, 6193, 2635, 1110, 2295, 4034, 4288, 8024, 3956, 385, 4880, 929, 1578, 4313, 9521, 5870, 5202, 1007, 1796, 9984, 2805, 8382, 4629, 6721, 6728, 7258, 9682, 8895, 20, 4969, 2905, 5610, 451, 4554, 2130, 5871, 2111, 9492, 1641, 5188, 8619, 321, 5970, 2619, 6318, 5264, 5773, 7731, 361, 8628, 3874, 4767, 8967, 2592, 312, 2127, 7184, 4717, 6474, 2362, 3764, 8351, 3621, 8467, 8560, 4096, 4954, 321, 1289, 1753, 6401, 9369, 210, 5357, 9945, 8402, 9323, 7750, 6847, 1754, 5744, 9897, 3142, 6278, 2801, 3336, 269, 1210, 4189, 1291, 2780, 4833, 6506, 4716, 8757, 2147, 926, 2396, 6612, 747, 2850, 1219, 6962, 3147, 677, 275, 7218, 8618, 6153, 5295, 2334, 3837, 9157, 1925, 2567, 6949, 9640, 7056, 5900, 9424, 8719, 2770, 9814, 9327, 3038, 8973, 5326, 7959, 7857, 122, 5687, 1378, 8084, 1504, 6893, 232, 8445, 1404, 8784, 641, 6185, 3479, 121, 4557, 4593, 4126, 3364, 1817, 9281, 753, 5478, 8820, 5320, 9262, 6417, 6735, 3221, 5776, 7394, 7483, 7131, 820, 6684, 3868, 1460, 8707, 8081, 412, 7218, 4836, 6026, 5923, 5718, 318, 7498, 4669, 1879, 1429, 8131, 6315, 770, 5930, 267, 9288, 196, 343, 8739, 3608, 3501, 1118, 7178, 6530, 7256, 3550, 4790, 6458, 4193, 2772, 2158, 7548, 5229, 4565, 8842, 4241, 9595, 7142, 1867, 8616, 5714, 5412, 5127, 9080, 2394, 8166, 8642, 5611, 5002, 3932, 5598, 1451, 562, 7658, 4971, 9642, 5480, 445, 1116, 7738, 8331, 1417, 3884, 7754, 8494, 3760, 7798, 5014, 720, 5586, 5145, 3490, 8478, 3229, 1664, 4651, 3435, 7355, 8829, 6526, 9634, 4997, 2436, 659, 905, 4380, 6872, 8579, 5203, 5160, 3449, 5762, 9947, 7457, 8263, 3254, 6387, 2658, 2525, 1532, 8638, 3975, 6114, 5289, 8168, 5900, 6711, 848, 8023, 8384, 8419, 3915, 7882, 8800, 3737, 4043, 2713, 5782, 8917, 1196, 5206, 9244, 6584, 6786, 9105, 8954, 5398, 2775, 4304, 8324, 1189, 1479, 2335, 9830, 525, 2087, 1027, 4934, 2310, 3572, 7244, 606, 8442, 6883, 9683, 5619, 9989, 5087, 4033, 6460, 9951, 1310, 1790, 1283, 141, 9596, 9650, 9943, 8023, 9891, 4902, 1594, 148, 7546, 6714, 7363, 467, 4279, 3954, 2613, 844, 8974, 5225, 8377, 6793, 8752, 3016, 6412, 5969, 9348, 7915, 9226, 4762, 2621, 3232, 9001, 4412, 9686, 9240, 5669, 2919, 2911, 6654, 9588, 2791, 4965, 2337, 5450, 1067, 8933, 4709, 4916, 1794, 4471, 660, 6171, 7808, 5415, 539, 4476, 5395, 2238, 5430, 4590, 8725, 8498, 6722, 3066, 2730, 8950, 8666, 9253, 3664, 6854, 2392, 614, 1977, 6943, 8948, 9356, 3606, 6554, 9002, 5349, 7367, 2384, 6398, 5346, 8145, 3497, 3055, 90, 2152, 1226, 747, 9544, 533, 9552, 404, 897, 7002, 4835, 5558, 9808, 906, 208, 8697, 1793, 9632, 7930, 1385, 3672, 5316, 94, 9020, 1528, 1116, 7203, 5393, 803, 5472, 7940, 7879, 9810, 7625, 1205, 5134, 2831, 1531, 6910, 797, 7717, 3789, 248, 7545, 6795, 8734, 8828, 3882, 8446, 663, 3418, 7465, 8436, 2896, 8522, 7452, 9620, 9217, 8338, 4691, 1467, 4874, 6350, 2270, 9482, 9800, 9407, 8765, 2805, 1453, 7857, 1142, 2042, 6911, 5808, 2656, 3865, 8507, 1464, 7963, 1236, 2510, 6099, 9648, 1373, 8961, 8931, 1640, 6497, 7402, 1955, 5468, 6792, 9901, 8713, 2140, 1966, 5762, 7254, 885, 740, 2298, 6919, 163, 1934, 4489, 1341, 5316, 2825, 9801, 6236, 9212, 7198, 8936, 5252, 8002, 7226, 949, 1357, 9429, 6758, 5474, 6655, 4706, 9669, 1074, 6473, 7843, 8434, 1301, 1988, 9883, 9737, 3548, 4180, 5160, 5045, 4846, 9088, 7675, 172, 2176, 7530, 654, 4091, 540, 7187, 9861, 3811, 9232, 3843, 3117, 2306, 9387, 4279, 6834, 6869, 9906, 6573, 9265, 8078, 7161, 7987, 8634, 1049, 5495, 6497, 775, 4407, 7073, 8756, 1573, 726, 9004, 6960, 2670, 9012, 5429, 2873, 6241, 6067, 389, 979, 3478, 4905, 8010, 1797, 51, 9749, 5818, 720, 304, 2321, 4231, 1705, 2618, 4798, 1132, 9680, 369, 3770, 1886, 6053, 363, 212, 8112, 9465, 1971, 2760, 2846, 565, 5092, 2933, 5830, 7452, 2484, 6207, 6157, 1391, 9803, 8594, 5979, 7193, 9306, 5641, 1321, 519, 8076, 4653, 6833, 7637, 6050, 7968, 1295, 19, 4975, 4572, 5609, 8506, 8972, 8855, 4843, 2167, 54, 1362, 8338, 3592, 4794, 5714, 7422, 2455, 8084, 9094, 869, 9151, 1962, 275, 9058, 5115, 2525, 1138, 592, 9761, 1245, 2101, 2925, 7564, 7196, 4589, 2363, 2334, 4782, 554, 9832, 9134, 4094, 4244, 5980, 5173, 7195, 5819, 1987, 5098, 5366, 8297, 8963, 8550, 6414, 9114, 7597, 3779, 2445, 6364, 8098, 6319, 2724, 1652, 6139, 1793, 253, 4239, 7971, 4092, 526, 532, 9646, 7252, 1286, 5669, 3332, 6071, 4954, 6153, 7296, 9251, 2348, 7995, 8208, 1583, 3770, 5586, 2252, 7475, 1570, 7100, 4491, 5425, 8868, 2935, 3912, 2167, 2807, 9224, 2316, 7705, 3429, 7780, 6957, 5227, 9421, 9194, 1718, 4597, 161, 2852, 9730, 899, 5646, 3588, 9199, 7089, 9419, 2967, 9933, 3212, 7867, 4160, 977, 4314, 5092, 6510, 1891, 8721, 6357, 5511, 4959, 9238, 8684, 1848, 9645, 8906, 8117, 1310, 2647, 9670, 1699, 9750, 4843, 1441, 2492, 7132, 5572, 7331, 1156, 3676, 7645, 9077, 6804, 5583, 3525, 7708, 9453, 3868, 4735, 88, 3791, 7083, 4077, 1034, 7870, 5034, 2481, 8626, 4610, 5098, 3136, 7575, 855, 2464, 5480, 9033, 5091, 8458, 215, 266, 3091, 5576, 5670, 3860, 4140, 2818, 1498, 2770, 3459, 689, 3892, 3949, 7554, 6005, 3120, 3648, 4375, 2853, 1012, 2430, 5284, 6743, 6109, 3625, 1778, 7382, 8804, 7471, 5184, 2553, 6532, 8012, 4023, 1911, 6741, 6020, 6934, 3810, 8206, 7152, 5912, 6156, 2398, 2874, 4152, 1231, 2275, 7282, 6438, 5478, 12, 877, 1560, 3986, 2072, 353, 1646, 7672, 9027, 7794, 2039, 1891, 1167, 6546, 2, 2622, 1886, 6941, 2297, 8974, 7935, 9704, 4509, 4115, 3978, 1257, 1734, 8998, 312, 5966, 4742, 8362, 6198, 1231, 3573, 9887, 5377, 5921, 3070, 3204, 550, 7335, 7057, 1112, 4554, 184, 5920, 4237, 2045, 5028, 1193, 1046, 6082, 7007, 5014, 2862, 912, 8515, 9805, 6855, 2311, 7169, 557, 6342, 8611, 1845, 3087, 4520, 8372, 7279, 768, 7255, 2019, 7745, 9108, 5616, 5839, 2469, 7638, 253, 5585, 570, 1265, 4212, 1081, 2008, 6321, 6344, 2782, 2436, 9242, 6913, 7573, 4181, 9151, 7277, 1187, 9046, 93, 3130, 4540, 632, 875, 3243, 4923, 9649, 1425, 2686, 2327, 6635, 3103, 1867, 5443, 9203, 3442, 3297, 7018, 4974, 6782, 5836, 1583, 2617, 6992, 5311, 6685, 9568, 6224, 7260, 9058, 1357, 3526, 2667, 2537, 6721, 3802, 723, 7391, 4800, 5037, 2738, 8266, 3916, 7835, 4778, 311, 4718, 5620, 4641, 2405, 7275, 6553, 4803, 469, 8444, 6640, 3011, 2379, 4564, 6752, 3324, 3213, 5091, 7121, 8650, 6298, 610, 7557, 4910, 8749, 5127, 3875, 3082, 114, 4204, 8262, 2138, 6927, 3881, 2036, 9762, 3085, 9097, 629, 2462, 6249, 2983, 6046, 7307, 2204, 6571, 2529, 7178, 7003, 933, 1937, 1482, 3004, 5246, 7144, 6497, 567, 5043, 1518, 8644, 6948, 1735, 7439, 7545, 5069, 1851, 8692, 7449, 8525, 4758, 3389, 979, 8508, 3441, 1587, 1064, 3293, 6504, 2531, 3804, 4805, 1741, 8863, 7957, 6465, 3560, 8245, 8291, 2620, 9038, 3329, 1834, 7650, 5439, 3786, 7928, 705, 3484, 9946, 6056, 1348, 9887, 3813, 7610, 5649, 3448, 400, 8061, 9900, 8662, 5010, 9508, 9737, 3223, 5245, 2417, 4195, 7394, 6601, 6504, 7105, 8097, 5676, 9215, 1864, 4992, 3054, 6893, 3308, 8802, 3685, 3085, 7768, 9160, 9651, 8130, 5051, 8822, 964, 2209, 7582, 2803, 1008, 6886, 5097, 1401, 3961, 4369, 3940, 3840, 1738, 3802, 3185, 257, 4322, 5515, 9248, 3245, 3783, 9259, 2832, 7, 9804, 8588, 4796, 4771, 8781, 4746, 9925, 327, 6648, 7059, 2552, 3182, 1897, 9719, 1805, 3416, 6258, 2105, 6544, 2345, 8723, 9181, 4872, 849, 3328, 1695, 6375, 9743, 5541, 4609, 612, 4879, 1218, 5196, 640, 9482, 3751, 8894, 3648, 9575, 3623, 1199, 1315, 75, 3179, 2836, 6349, 3912, 4107, 7774, 616, 8348, 7486, 1114, 1866, 3384, 6209, 8706, 9581, 1590, 530, 2882, 5794, 9679, 8488, 2694, 4829, 6802, 8391, 5336, 5844, 4294, 2264, 4374, 1920, 1018, 2481, 776, 8797, 880, 5461, 1079, 6272, 4718, 6208, 2525, 4245, 4764, 856, 9092, 2745, 5068, 2237, 4260, 7282, 2596, 5368, 7604, 5770, 7598, 3865, 5672, 4393, 9703, 7805, 6603, 3836, 2031, 9146, 1751, 7689, 3974, 619, 5748, 6486, 5992, 7118, 2911, 6153, 8171, 3004, 1966, 4250, 4117, 6366, 7607, 9437, 4150, 4442, 2705, 2691, 8381, 6, 1023, 48, 5469, 7097, 2632, 1367, 9164, 1294, 430, 8703, 2136, 2018, 2194, 3564, 5747, 2851, 5075, 5207, 9380, 7334, 4558, 787, 1101, 9327, 2243, 9110, 1910, 4230, 7441, 9417, 7353, 7905, 9556, 4472, 6490, 1907, 7255, 8743, 2827, 5795, 1267, 9520, 7304, 1469, 4814, 398, 6804, 6839, 3450, 9840, 8349, 5684, 7532, 9862, 6052, 3253, 5539, 1186, 5290, 9676, 4575, 705, 2539, 9570, 4761, 9919, 8861, 1166, 8273, 8188, 6619, 6532, 6740, 6948, 4052, 7440, 7772, 8435, 9381, 1291, 4413, 920, 4471, 9796, 2200, 2926, 1027, 5610, 8620, 2307, 8291, 8047, 2989, 598, 5835, 3727, 4149, 449, 33, 9506, 4650, 7490, 4379, 9500, 7412, 372, 5915, 276, 6731, 2318, 5774, 902, 6182, 5895, 4680, 6765, 9129, 2593, 5330, 1853, 8052, 6117, 4796, 6841, 236, 3967, 9692, 5304, 4144, 6762, 7024, 9421, 868, 9157, 1769, 1849, 5394, 8579, 5871, 8644, 9313, 2848, 9421, 7617, 4520, 8203, 9083, 2740, 8521, 613, 5957, 3525, 1579, 6823, 5189, 5914, 356, 8530, 2476, 7918, 4492, 3105, 8423, 4166, 7652, 6388, 8344, 3570, 1507, 6934, 232, 3982, 2131, 2616, 2944, 1803, 9953, 8345, 5985, 3802, 9093, 8980, 8503, 1101, 8090, 7667, 7151, 3521, 4255, 9092, 3123, 3771, 6345, 209, 1433, 6975, 3382, 2122, 4819, 1555, 909, 8751, 517, 1015, 964, 4794, 5736, 4637, 5806, 2095, 6838, 752, 5833, 7720, 4169, 6295, 5312, 4636, 7495, 7408, 285, 3804, 6415, 7707, 9762, 1652, 3801, 6144, 1963, 2105, 8775, 2642, 8287, 6511, 2880, 4641, 3968, 6626, 4106, 8328, 9609, 941, 437, 3073, 5817, 4029, 4725, 2303, 7801, 9993, 2781, 6541, 9211, 7231, 147, 3276, 9424, 9360, 479, 6094, 3386, 7889, 7250, 4479, 2414, 724, 1719, 2134, 7575, 3557, 4032, 5646, 9611, 3160, 7612, 2220, 6759, 8385, 4443, 5952, 3819, 5044, 3250, 7843, 160, 5551, 6186, 6082, 6594, 5946, 6545, 3033, 6204, 5593, 9777, 1472, 7634, 4955, 9637, 2665, 4560, 3415, 9030, 4363, 1726, 4977, 6450, 2220, 3654, 1218, 8586, 6464, 1129, 7321, 3729, 9074, 9714, 198, 2974, 9018, 8623, 4664, 1010, 259, 2218, 1157, 7963, 5721, 5508, 3330, 2296, 1347, 4916, 6072, 3599, 3005, 8650, 6214, 642, 5617, 5445, 8436, 4593, 5503, 8414, 4751, 6066, 1473, 1348, 9357, 827, 3481, 8271, 812, 2737, 3958, 2931, 9410, 2964, 248, 6472, 3778, 553, 5839, 988, 2922, 5265, 30, 8252, 4872, 4455, 6138, 2271, 4581, 7839, 2673, 2074, 6235, 552, 5813, 7018, 2366, 424, 722, 1696, 6084, 4824, 3588, 1339, 7965, 6818, 1049, 2769, 6611, 8155, 7683, 8552, 1339, 6020, 9870, 7225, 8573, 6451, 7413, 8864, 6800, 3309, 1487, 9875, 7504, 455, 2029, 6369, 5785, 617, 1503, 4148, 7621, 272, 7330, 761, 8651, 4473, 1866, 9966, 4702, 3429, 7609, 4775, 9996, 4298, 5495, 3801, 9740, 8695, 7240, 2374, 4906, 9829, 8261, 3005, 3336, 6083, 6258, 9800, 7961, 9258, 3894, 4525, 8839, 1931, 5503, 4203, 232, 2722, 6185, 7402, 627, 403, 2810, 8577, 2761, 1916, 1334, 5196, 4590, 167, 4303, 5758, 7485, 4545, 3802, 9527, 1548, 619, 969, 8673, 8579, 6335, 9694, 3636, 4802, 7968, 6845, 9231, 3293, 6500, 167, 9258, 831, 4681, 9921, 8083, 4678, 6581, 8655, 6158, 6902, 6068, 1623, 2297, 2676, 3311, 8927, 2602, 5935, 5380, 7627, 3759, 4988, 3171, 8171, 8972, 6009, 4451, 8610, 9472, 2916, 2246, 5560, 9021, 4256, 1386, 9907, 2920, 3290, 2559, 6417, 8389, 8290, 3871, 9519, 282, 3750, 78, 965, 4429, 1084, 2165, 7673, 5804, 453, 9564, 4634, 7037, 7481, 2906, 9650, 2154, 4132, 5336, 2132, 1958, 4507, 5887, 2282, 550, 9758, 1624, 2390, 1115, 7749, 8692, 6239, 9329, 9986, 4452, 2752, 6252, 6646, 5997, 3237, 1295, 8212, 3120, 522, 8907, 3216, 5931, 4023, 7772, 745, 3734, 6657, 9292, 4799, 3645, 8886, 14, 156, 7850, 4997, 7728, 1068, 1089, 5522, 4924, 5737, 5177, 1840, 3431, 5896, 8559, 5273, 4824, 4571, 9140, 3295, 2305, 5666, 1936, 2363, 555, 4815, 9091, 1885, 6151, 2058, 5665, 3662, 6457, 3994, 8006, 5786, 4542, 5777, 7986, 8671, 6418, 8569, 5567, 3811, 2245, 411, 5484, 8642, 2282, 7834, 1022, 4635, 3500, 9027, 7379, 9487, 9166, 8032, 4028, 7267, 4808, 6894, 453, 793, 4912, 8684, 9510, 5742, 2522, 5086, 8839, 1175, 8651, 6909, 9565, 3706, 4395, 9508, 8728, 7598, 1994, 3522, 9390, 3705, 115, 2811, 9387, 5179, 7107, 6620, 7144, 9708, 2751, 364, 7981, 8824, 9326, 9096, 8007, 2374, 8327, 2757, 4511, 7813, 6065, 148, 8126, 8215, 508, 8441, 5744, 8082, 3847, 7988, 7835, 2542, 6032, 6745, 7781, 1457, 2500, 4869, 5057, 9634, 894, 3184, 879, 9311, 157, 7607, 9763, 4375, 3516, 3231, 6103, 6800, 4303, 1199, 2397, 2385, 5308, 422, 657, 9387, 9814, 5858, 3807, 2945, 511, 1667, 9069, 1249, 7156, 4710, 7880, 1733, 5837, 2569, 3814, 3769, 5942, 793, 7128, 703, 6726, 2634, 9498, 7142, 6632, 9782, 8181, 7406, 2706, 7, 2882, 7789, 2784, 163, 8236, 2128, 3911, 4826, 5191, 527, 551, 776, 5035, 2851, 6768, 942, 1844, 279, 1399, 7169, 9572, 6728, 8483, 345, 2955, 9166, 3580, 1013, 2348, 34, 3849, 2058, 1464, 6874, 6955, 64, 7866, 5940, 5650, 196, 7654, 7622, 4132, 9711, 6470, 3552, 5946, 1810, 8224, 2056, 5935, 6533, 2213, 939, 7011, 6094, 8426, 9852, 8495, 7821, 6837, 1603, 5699, 4192, 154, 3460, 5477, 7778, 3245, 6316, 8773, 5405, 7352, 4807, 8571, 6331, 4157, 9643, 4250, 359, 4007, 9018, 9688, 9643, 4703, 4570, 270, 3573, 9988, 2013, 7062, 41, 2475, 9576, 1276, 2409, 1634, 745, 2233, 9528, 2284, 2531, 6067, 6899, 6209, 690, 6014, 8212, 5115, 6125, 4813, 2885, 2868, 8780, 1525, 4533, 5653, 1500, 9674, 2570, 3763, 6680, 9668, 7443, 4374, 9284, 1176, 4968, 1587, 745, 3696, 3067, 8815, 1759, 1771, 2553, 9858, 4848, 4419, 3634, 7434, 5328, 4118, 5508, 9128, 7312, 492, 6774, 2534, 7262, 2060, 4396, 8216, 8575, 5555, 620, 6200, 9533, 2517, 3236, 3408, 6925, 3718, 7863, 2841, 3718, 4449, 4457, 5990, 9721, 5770, 8446, 3210, 5549, 7708, 912, 9023, 5513, 8708, 6309, 1574, 5132, 8717, 6409, 17, 6354, 4116, 5257, 7295, 1031, 9540, 8394, 3134, 4333, 1467, 4052, 2129, 7173, 5161, 1532, 1293, 3549, 4487, 100, 220, 5078, 139, 7925, 7464, 9642, 8294, 5993, 5855, 3749, 7502, 7314, 2196, 9717, 6739, 1331, 2627, 1341, 5562, 2694, 5952, 5713, 4951, 477, 3552, 6895, 9265, 9901, 5082, 9032, 1106, 4024, 3495, 9424, 6661, 6490, 2117, 4507, 6770, 2422, 545, 9836, 6700, 3336, 41, 5345, 6326, 227, 3273, 6554, 7165, 4968, 6882, 2418, 2633, 1195, 8981, 9654, 52, 8793, 55, 3472, 4193, 8757, 7859, 1544, 7494, 1649, 7140, 2362, 7694, 8035, 4109, 7679, 9415, 1257, 4890, 2924, 3955, 9471, 5481, 5931, 7224, 1113, 5788, 1234, 3046, 8477, 6724, 5641, 5757, 3946, 7746, 9289, 1768, 225, 1170, 8422, 9227, 4085, 9441, 342, 4256, 2681, 1203, 1786, 7210, 8555, 7489, 6454, 7285, 966, 8460, 9997, 8499, 1262, 3461, 7671, 607, 9230, 2414, 8287, 6928, 312, 5010, 6473, 458, 6804, 7667, 4159, 6679, 6465, 3461, 7035, 8664, 6826, 829, 2932, 2317, 9931, 5716, 9051, 8350, 1459, 7329, 6910, 542, 1570, 9993, 1868, 6110, 810, 2853, 5939, 8724, 890, 6619, 5473, 3885, 8035, 7534, 622, 5190, 5662, 8997, 4685, 5061, 7445, 9390, 4972, 3168, 219, 8524, 5685, 5320, 7257, 195, 8527, 7382, 420, 3122, 972, 4235, 5457, 9021, 3713, 4641, 1983, 6008, 9077, 849, 6960, 78, 4848, 1835, 1352, 3741, 1435, 6949, 9770, 6835, 3136, 9788, 1044, 6088, 5321, 2359, 1522, 5580, 3237, 8024, 9004, 4326, 2822, 3613, 3419, 8210, 6185, 9604, 8801, 6384, 2853, 4957, 7424, 2829, 5387, 605, 746, 5592, 1420, 5088, 6988, 5275, 1146, 8095, 6129, 5439, 6396, 7276, 2590, 4934, 5832, 91, 1265, 375, 2145, 2394, 3879, 9037, 7934, 5312, 5308, 139, 4371, 1576, 545, 3762, 3763, 5653, 7369, 3686, 6189, 8158, 1422, 6959, 2097, 6311, 9879, 8280, 5695, 8011, 4286, 4332, 2360, 8186, 7372, 5948, 5118, 4827, 1412, 3442, 3531, 1512, 2078, 3026, 7607, 7471, 3288, 1270, 1555, 1994, 7493, 187, 8254, 6630, 6379, 6199, 5241, 9327, 8646, 4770, 761, 5515, 7596, 9514, 6096, 7192, 6421, 9187, 6952, 4436, 731, 6259, 522, 1180, 1510, 8165, 2242, 392, 5380, 5655, 784, 4681, 2208, 7936, 4507, 3878, 903, 9786, 5582, 5965, 1364, 7511, 613, 4685, 882, 3512, 5802, 385, 8529, 7274, 5688, 738, 8009, 4930, 9978, 7186, 640, 9407, 173, 5236, 4497, 5097, 3407, 2308, 6009, 1585, 4801, 5730, 5097, 6828, 6992, 2023, 7025, 9007, 158, 1012, 9497, 1300, 7092, 9868, 6354, 8768, 5464, 9840, 7821, 9047, 4578, 5489, 2795, 1968, 5475, 3774, 6997, 9260, 2797, 511, 4242, 8376, 4293, 17, 8262, 2714, 5211, 187, 460, 3037, 543, 8163, 8350, 7446, 5718, 1455, 7916, 8783, 3891, 1377, 8645, 2804, 9556, 5329, 3722, 3814, 6325, 5551, 7529, 7362, 3013, 982, 7887, 9569, 6372, 7758, 8985, 9506, 2685, 6855, 6513, 7742, 6280, 36, 451, 9348, 942, 8100, 3161, 8694, 3208, 6329, 2993, 5985, 1995, 9642, 6415, 5238, 5540, 7102, 8793, 8497, 3184, 1870, 2543, 6724, 6444, 5373, 1307, 2110, 3921, 7171, 7321, 6355, 6321, 4913, 4889, 6173, 3488, 6096, 1624, 2342, 9257, 1799, 2444, 1903, 2720, 1621, 4691, 3173, 4360, 9821, 7441, 7899, 5411, 4914, 3549, 4444, 6374, 4012, 1626, 4376, 3987, 9443, 4033, 4381, 8103, 6074, 911, 1045, 2135, 4185, 3468, 7558, 4422, 9382, 9987, 2570, 738, 5646, 7184, 5049, 8293, 3755, 6687, 6938, 867, 288, 7003, 5215, 3472, 1807, 3572, 486, 9254, 5836, 6808, 15, 1139, 5395, 2868, 5755, 7976, 683, 5510, 8650, 1721, 6318, 4413, 8053, 933, 3769, 7159, 41, 1834, 315, 4194, 1142, 7630, 6720, 251, 6019, 5383, 4702, 9356, 6483, 9562, 5564, 4014, 7097, 8782, 4740, 4428, 774, 5959, 4033, 5872, 338, 3719, 8857, 7388, 7710, 6989, 3501, 3256, 8113, 4002, 8467, 3319, 7339, 4146, 919, 6378, 9547, 5316, 8030, 4195, 9551, 8063, 1147, 8006, 5645, 6692, 9423, 4614, 177, 1246, 8064, 6199, 9257, 357, 2970, 7183, 3575, 7448, 1843, 8504, 7207, 8953, 6470, 6583, 8621, 7628, 1795, 495, 7878, 5469, 5535, 4520, 1597, 8002, 521, 3572, 5861, 3505, 8617, 1133, 8024, 5880, 1732, 9203, 3766, 9380, 2245, 7288, 6898, 9362, 4675, 9140, 2212, 725, 7441, 7194, 8840, 3924, 2208, 220, 605, 5681, 8944, 3989, 2690, 7324, 1003, 5829, 1108, 5016, 130, 3023, 9988, 3453, 260, 9180, 1441, 8658, 9058, 9225, 3404, 2851, 7937, 4529, 7813, 9025, 5838, 7855, 2173, 4890, 1666, 2979, 6325, 7703, 1769, 7112, 4659, 7387, 9309, 6976, 8100, 8734, 6049, 1621, 2199, 3305, 4219, 320, 9314, 2731, 4396, 209, 3077, 69, 5389, 6148, 7659, 2853, 156, 2855, 1116, 4688, 8458, 5939, 6734, 4724, 8955, 363, 570, 5282, 3725, 4517, 3487, 1875, 1094, 7481, 4501, 7807, 9846, 6625, 1008, 7395, 7364, 5989, 2814, 4093, 2150, 9104, 5410, 3663, 6831, 8081, 2696, 314, 979, 6730, 9404, 6007, 751, 3434, 9103, 7103, 5078, 6829, 227, 2574, 9351, 5330, 5631, 6599, 2952, 7980, 1365, 4738, 5152, 5383, 2418, 8379, 9022, 6874, 6241, 1912, 785, 9778, 4346, 9319, 6034, 5591, 4205, 7680, 1929, 1601, 9130, 3404, 1720, 8338, 8524, 6728, 3206, 6882, 5990, 9292, 6783, 6120, 3970, 3338, 1284, 2963, 1648, 566, 8309, 1932, 2898, 2204, 410, 1594, 6170, 6448, 1213, 5699, 1896, 601, 7593, 1380, 7039, 8698, 4388, 5099, 2529, 4695, 531, 4428, 5250, 1736, 1732, 3108, 5227, 7252, 3977, 8339, 5948, 7239, 2050, 3465, 8225, 2598, 5878, 8406, 3086, 4362, 9199, 4074, 9164, 7351, 5353, 1708, 7656, 7761, 960, 8354, 2151, 2271, 4561, 7890, 3814, 9145, 4933, 34, 5432, 1975, 8688, 136, 4637, 3622, 9314, 1862, 8054, 5648, 169, 6764, 3593, 3613, 5983, 6101, 7054, 1309, 9682, 6737, 7303, 2511, 5641, 9102, 2551, 9417, 4401, 8434, 707, 3313, 3297, 5521, 8462, 9504, 749, 4642, 1346, 8196, 5589, 6451, 9071, 1178, 4252, 1163, 9119, 3549, 8756, 2706, 8596, 7536, 6027, 856, 2540, 1327, 8410, 3878, 889, 1801, 6804, 5767, 3689, 2846, 5808, 4398, 6991, 6547, 2504, 6616, 2796, 1279, 8321, 3360, 9483, 7970, 1823, 9696, 1344, 2911, 1064, 270, 9505, 4293, 5889, 8987, 6695, 7958, 3691, 9281, 3208, 1953, 8722, 163, 6837, 448, 8758, 3949, 8982, 1097, 56, 6149, 4142, 7290, 8176, 7236, 321, 1714, 8914, 3567, 1201, 7417, 978, 8458, 9464, 1037, 2260, 5920, 5894, 8690, 4426, 6576, 7848, 3179, 5012, 8878, 9004, 1782, 8535, 7842, 919, 3693, 8517, 6724, 8423, 8773, 9464, 8739, 173, 6642, 8251, 1985, 450, 249, 2559, 2191, 5448, 6926, 9552, 1746, 4614, 8028, 595, 1180, 9245, 2403, 8286, 1355, 965, 7167, 3048, 7998, 9094, 3515, 1396, 940, 293, 190, 1858, 9096, 546, 3765, 5007, 7861, 1729, 5261, 3070, 8032, 4148, 14, 8591, 7981, 3215, 6479, 4713, 6716, 2093, 8031, 2359, 2628, 758, 3901, 6984, 9412, 4400, 7787, 3945, 7486, 7896, 9753, 2452, 9466, 6445, 971, 2504, 902, 1408, 4600, 3493, 3366, 7577, 9884, 9112, 5151, 5904, 8128, 1842, 162, 7842, 132, 9010, 1530, 5889, 4751, 4048, 9154, 682, 8509, 8860, 6273, 3595, 7907, 8453, 5736, 8577, 9303, 1416, 5625, 8385, 2015, 6053, 8904, 8875, 5915, 5113, 5578, 7120, 2042, 6173, 3175, 1053, 4327, 3827, 1909, 1353, 8396, 6655, 6003, 8001, 6501, 2364, 1637, 1856, 3604, 3086, 4532, 4222, 9958, 3826, 994, 7715, 3290, 9865, 3334, 4748, 6436, 3352, 8531, 987, 8553, 6011, 4019, 9820, 4339, 8588, 5299, 2991, 6178, 4903, 8833, 3782, 8145, 5590, 5980, 7415, 2238, 2894, 6737, 847, 773, 619, 9279, 9664, 5451, 4760, 5342, 5019, 2037, 2821, 7640, 4950, 1336, 8817, 1275, 9792, 976, 5468, 5187, 4394, 3457, 4932, 3937, 6865, 1545, 9993, 1717, 5771, 8604, 2976, 696, 3727, 2007, 6824, 4154, 5434, 9896, 6548, 2932, 4116, 1743, 2349, 9028, 5444, 7732, 6006, 5704, 1007, 5492, 3848, 702, 2100, 8432, 3160, 6321, 4718, 4072, 484, 5092, 522, 7187, 8760, 4888, 6874, 1190, 3597, 8271, 31, 6715, 7651, 3252, 4037, 4827, 986, 5133, 2213, 7714, 1601, 9644, 2551, 1613, 1732, 1126, 234, 3748, 9169, 6541, 8863, 5083, 3387, 1220, 788, 7484, 975, 6721, 7108, 89, 3838, 609, 3052, 4393, 4580, 5259, 2847, 1257, 9739, 2224, 8829, 3535, 4048, 4926, 3167, 3035, 897, 1101, 2855, 2024, 1326, 1183, 3076, 945, 7199, 9930, 2947, 8290, 9834, 9033, 5570, 4862, 6518, 8554, 3056, 8976, 3598, 1255, 53, 1960, 8315, 1922, 6228, 6699, 2374, 445, 5203, 9579, 1784, 5413, 3036, 3640, 7564, 6391, 2590, 5029, 4663, 6603, 4001, 8938, 138, 7603, 6451, 1830, 7777, 2810, 5069, 5969, 7527, 5384, 626, 4514, 1221, 2718, 4435, 5023, 6670, 3593, 4275, 8014, 4591, 8127, 9964, 1217, 8101, 4374, 9510, 2592, 5148, 8526, 9478, 6908, 833, 6845, 2542, 6629, 6361, 2138, 6375, 10000, 5916, 8810, 7749, 979, 535, 3487, 730, 3968, 8503, 7304, 940, 4290, 9854, 5902, 921, 9562, 7837, 1056, 7365, 3135, 8589, 9123, 8374, 3790, 3571, 8777, 3445, 6228, 1582, 9698, 2721, 5605, 3389, 5864, 6434, 1798, 4797, 5316, 196, 514, 3574, 6517, 5721, 8393, 6765, 709, 8570, 4851, 4895, 4589, 8887, 951, 3250, 8841, 9767, 8103, 3905, 157, 8284, 8480, 5679, 7478, 3632, 5300, 2887, 7761, 4133, 1675, 8146, 6965, 9628, 9830, 515, 7462, 7432, 2813, 815, 9512, 4817, 6655, 6816, 7486, 7825, 8985, 687, 2054, 8337, 3168, 8301, 1183, 2737, 9384, 6100, 2659, 5115, 773, 2760, 1369, 8042, 3247, 8755, 3726, 2295, 4529, 5943, 524, 2323, 9814, 438, 8166, 2497, 1558, 8630, 1246, 1079, 4358, 7292, 4175, 8840, 4424, 7089, 6011, 4481, 6941, 2042, 43, 8765, 9355, 6968, 6747, 1428, 153, 6953, 95, 2557, 9132, 5809, 7019, 2388, 9253, 4912, 7554, 5887, 5011, 9799, 9665, 2735, 4332, 3066, 4544, 8115, 3152, 7089, 8527, 2040, 1345, 5519, 7313, 6162, 9651, 8842, 2041, 8089, 6785, 1303, 6816, 421, 4407, 3544, 2192, 511, 3884, 1514, 302, 2376, 9247, 2050, 1246, 2545, 2169, 2301, 803, 6572, 23, 2739, 189, 4414, 3955, 5260, 1862, 1886, 8978, 4909, 1176, 4659, 6440, 2704, 7012, 7245, 2624, 6534, 104, 2551, 660, 9126, 6105, 6666, 2940, 8125, 560, 2794, 1290, 1938, 4964, 1753, 4018, 4185, 282, 3492, 651, 3681, 89, 9761, 4807, 8278, 3461, 9677, 5056, 8028, 9581, 3753, 5149, 765, 8444, 9771, 9915, 1096, 3983, 6997, 3243, 9537, 7713, 7857, 2800, 317, 4257, 7623, 428, 5649, 6828, 5855, 754, 3403, 8977, 6709, 5369, 4178, 4326, 1209, 5417, 3577, 1881, 1829, 408, 3932, 2912, 5157, 7959, 9899, 8839, 7768, 3117, 1581, 328, 8771, 9495, 7031, 449, 9890, 7685, 845, 6879, 3728, 8002, 4516, 6919, 1031, 4896, 9364, 4891, 796, 7065, 9042, 658, 1826, 9562, 7137, 1572, 201, 4226, 7479, 154, 3558, 8736, 7680, 119, 9648, 6992, 4092, 3652, 3982, 9873, 3496, 4964, 4329, 5940, 6129, 2987, 4670, 8498, 5165, 909, 1962, 2412, 3987, 5025, 281, 5794, 9306, 746, 7574, 3907, 4048, 9677, 4156, 9144, 8592, 3904, 3983, 7225, 8819, 294, 5942, 2426, 6460, 32, 981, 9682, 6214, 442, 5363, 9630, 740, 4225, 5949, 3663, 1782, 7707, 713, 4997, 7672, 333, 2020, 9687, 2866, 8340, 6661, 8042, 291, 1366, 1240, 5455, 2709, 8918, 3043, 2674, 5263, 4071, 1564, 8853, 2236, 4818, 3919, 5994, 5673, 1414, 4913, 8544, 2237, 9590, 868, 9457, 1785, 1470, 7463, 1981, 7977, 9278, 8212, 7932, 1729, 8798, 5089, 7945, 2051, 7019, 6971, 7467, 5098, 2623, 7348, 8792, 4483, 92, 9520, 5221, 2840, 1939, 2701, 5937, 3477, 4186, 4175, 204, 8029, 5929, 5945, 9687, 4955, 7078, 8940, 1632, 8640, 8437, 1677, 4105, 5539, 8046, 3972, 830, 2337, 8786, 7935, 7595, 9820, 1493, 137, 3313, 6103, 8276, 9570, 7618, 596, 3586, 3213, 5055, 8075, 7711, 9251, 2866, 5065, 7158, 7592, 7076, 4047, 5581, 3022, 6239, 6237, 7367, 3567, 8303, 954, 4973, 1353, 7839, 7887, 1175, 1940, 8514, 6279, 8248, 4322, 6920, 777, 9513, 4919, 3961, 9256, 8153, 6445, 3500, 7614, 1950, 1980, 6067, 3537, 8807, 4927, 6537, 8494, 9271, 3680, 7819, 273, 7109, 7768, 7856, 6439, 1401, 1670, 9447, 5832, 4070, 7977, 8973, 7534, 2356, 6992, 7666, 7848, 5027, 3012, 5223, 9846, 2790, 1989, 8339, 3824, 9390, 5210, 5236, 3656, 1824, 1417, 8532, 8938, 1754, 6645, 5607, 4567, 1569, 8759, 6964, 8251, 7003, 9374, 9804, 1026, 3573, 2878, 1341, 183, 9760, 1538, 5293, 2331, 6882, 9012, 9849, 1084, 2749, 1974, 1893, 9040, 2400, 7982, 7189, 7353, 3727, 426, 4072, 5741, 7676, 3126, 3968, 879, 4959, 30, 1014, 1467, 7963, 3582, 6748, 5914, 6186, 1086, 4138, 2789, 5029, 6101, 1271, 6072, 698, 2837, 6170, 2628, 2196, 3643, 8679, 687, 2885, 1539, 819, 2562, 1877, 7372, 1384, 8994, 7026, 7475, 8737, 8110, 674, 6189, 1104, 2876, 2031, 527, 4911, 4193, 1636, 5929, 3478, 703, 1571, 1053, 8019, 364, 6717, 9166, 6299, 5288, 3480, 8127, 5966, 990, 8305, 4510, 7760, 6648, 1587, 2868, 9916, 539, 1844, 6852, 5379, 7735, 3934, 4212, 9593, 6912, 6385, 9998, 570, 296, 5833, 6802, 6075, 4226, 8645, 8291, 1087, 76, 5738, 8201, 52, 453, 7049, 5448, 50, 6593, 6610, 7783, 8045, 3617, 8837, 9887, 421, 2270, 3675, 9234, 4855, 1335, 2190, 1207, 1867, 7320, 2092, 7566, 9721, 1017, 4062, 6477, 8604, 5622, 6978, 7509, 7955, 1727, 9351, 7859, 6917, 6003, 1388, 3056, 6950, 4825, 5344, 318, 4462, 2390, 8414, 771, 4269, 4884, 2646, 1325, 1468, 5318, 8211, 4285, 5629, 7641, 7362, 1614, 9761, 763, 8158, 4043, 5372, 6517, 9293, 3785, 958, 9391, 9643, 3995, 9435, 6128, 9525, 8114, 9322, 4831, 4591, 9075, 8799, 6265, 4433, 3580, 594, 338, 8035, 2257, 7131, 11, 3637, 778, 307, 3023, 6438, 4208, 1141, 6277, 2475, 8848, 8368, 8720, 6327, 992, 6015, 3113, 5154, 4149, 3057, 5553, 2576, 9863, 4796, 8218, 7119, 2237, 6307, 4955, 9349, 8945, 5536, 9674, 6200, 9295, 5176, 2886, 6094, 4283, 6687, 7391, 442, 5095, 711, 8994, 7717, 5691, 477, 6525, 7112, 8201, 959, 4848, 9082, 8645, 3602, 9818, 3598, 9109, 7640, 1452, 3489, 6044, 916, 5177, 8747, 8571, 3816, 3422, 390, 8211, 2242, 6421, 6672, 5825, 4011, 2195, 8869, 8135, 1259, 7581, 5252, 6339, 362, 5313, 5508, 2991, 1685, 4839, 6139, 1507, 6830, 3608, 9899, 529, 9342, 9935, 1204, 9040, 7751, 1590, 5545, 3729, 4749, 8071, 9185, 7260, 4677, 1984, 9207, 3306, 5434, 7771, 9989, 1398, 3592, 4604, 6267, 6034, 6890, 4392, 3618, 9547, 656, 7458, 2549, 1970, 5472, 5640, 9364, 9029, 2320, 3709, 8364, 8402, 392, 3293, 3733, 5627, 9471, 8515, 1252, 8448, 3219, 1794, 2426, 7991, 835, 8168, 5004, 7817, 3572, 7048, 3609, 5383, 6713, 2103, 3764, 8783, 4091, 8104, 1651, 1415, 3327, 5228, 8139, 160, 9986, 4233, 8675, 5115, 2993, 8826, 2979, 5598, 8270, 769, 491, 8693, 9631, 2436, 1300, 8262, 3458, 4940, 8568, 9747, 4144, 9109, 2558, 4200, 7985, 7681, 6225, 7372, 7596, 2075, 8269, 8153, 7183, 3908, 7021, 3352, 2505, 2163, 1615, 3615, 7969, 9124, 8323, 6101, 5679, 479, 3199, 2675, 3385, 4338, 5505, 7358, 7974, 5840, 9577, 9693, 2391, 1102, 3892, 4491, 7215, 6930, 21, 9779, 5307, 6865, 3401, 7134, 1184, 6152, 1730, 8186, 1364, 1525, 6416, 3815, 7373, 5455, 576, 3203, 8311, 244, 3022, 8613, 761, 6010, 1016, 3547, 3456, 8708, 9557, 5804, 8905, 3318, 2819, 9705, 3868, 9836, 5867, 8675, 5300, 6702, 6939, 4055, 2837, 2553, 8019, 8776, 3132, 6210, 926, 692, 8914, 7888, 1572, 6352, 729, 9761, 50, 7571, 7443, 7883, 2631, 10, 4372, 482, 8194, 2532, 6224, 8752, 6158, 3147, 8251, 2998, 187, 7703, 7730, 6894, 4850, 8761, 807, 53, 5199, 8864, 9200, 1165, 135, 8594, 5185, 8564, 419, 8075, 6599, 2942, 5725, 1990, 9609, 8085, 7683, 5695, 9491, 8497, 2255, 5568, 2537, 5737, 238, 8095, 7750, 2550, 2618, 5910, 720, 9685, 4462, 1170, 3182, 7146, 4879, 9910, 4854, 5573, 2676, 8480, 1742, 2672, 4214, 3608, 4598, 4495, 3565, 9231, 4342, 8230, 9220, 6457, 283, 8439, 2963, 3924, 6146, 3844, 3467, 4400, 4466, 6968, 6753, 4094, 9472, 2062, 9092, 6762, 3928, 8053, 8252, 9553, 1927, 5839, 5533, 9883, 474, 7839, 5711, 7777, 4905, 3024, 8240, 868, 5338, 742, 7393, 8822, 3510, 7249, 7021, 925, 996, 1566, 4385, 297, 2565, 6036, 4523, 4574, 6557, 1670, 6982, 2199, 1092, 1164, 3121, 632, 920, 6622, 8517, 9988, 1452, 4257, 9813, 5308, 8774, 9235, 9335, 4608, 8870, 5428, 8155, 3431, 3597, 8230, 9702, 5556, 9888, 2436, 5564, 3059, 4386, 2710, 4647, 6752, 6972, 5256, 7206, 1209, 6624, 3247, 4083, 4155, 4987, 6196, 6345, 7458, 8484, 8239, 9780, 3968, 5225, 7960, 1585, 8926, 5412, 2754, 475, 913, 3424, 2427, 3076, 8707, 4633, 1419, 6534, 3796, 3374, 4200, 5615, 3136, 2316, 1575, 6692, 3709, 5753, 292, 3805, 923, 8832, 8334, 5716, 1156, 3362, 3340, 6041, 7437, 143, 9905, 4838, 6818, 4012, 9547, 2649, 5108, 7778, 6760, 7396, 7031, 3277, 4083, 3271, 5688, 9286, 6190, 83, 4287, 6199, 6051, 7286, 5678, 9701, 7957, 873, 5208, 9452, 9009, 9602, 1098, 6591, 5879, 2800, 6201, 8295, 5393, 5336, 577, 7527, 557, 2767, 9932, 344, 519, 1629, 886, 1524, 2721, 1081, 8384, 3489, 4644, 8819, 3734, 396, 2241, 7846, 6738, 6452, 1222, 314, 9422, 7052, 4901, 8838, 3948, 3982, 3642, 8160, 4839, 9664, 9681, 7685, 1975, 2406, 3048, 827, 9009, 2439, 6167, 991, 6605, 8071, 9405, 3177, 6144, 3956, 1211, 3461, 2214, 9146, 7312, 2887, 2861, 4188, 6551, 9430, 4422, 5407, 8336, 6265, 2172, 1692, 8088, 1423, 2287, 892, 6276, 7494, 2043, 8302, 1428, 8120, 9504, 5018, 8066, 3568, 1510, 8463, 3061, 6325, 3613, 6056, 7089, 5438, 3311, 17, 2109, 2259, 8929, 5722, 9792, 5626, 2702, 7858, 66, 5458, 5926, 5114, 8721, 9905, 9699, 6749, 6456, 2516, 5569, 4777, 8915, 3074, 6296, 9688, 798, 2158, 1753, 2735, 5476, 6449, 5467, 9890, 8683, 9240, 2652, 8440, 6377, 9821, 2300, 6634, 7268, 2822, 6318, 8935, 14, 8398, 8360, 9980, 5378, 8522, 9265, 788, 5254, 8092, 7328, 8912, 3325, 4687, 7700, 2713, 8764, 3094, 9311, 5930, 5158, 9815, 245, 5492, 8263, 6348, 5331, 3261, 9147, 4708, 861, 9054, 4709, 9178, 1321, 2017, 4504, 3600, 7318, 721, 6470, 3784, 3904, 9997, 3600, 7204, 6461, 888, 3915, 2765, 2410, 51, 977, 853, 9889, 3053, 8308, 365, 7515, 5857, 5795, 6915, 7248, 5141, 9694, 5960, 4582, 5798, 6970, 8633, 7826, 5713, 1096, 135, 3362, 4229, 3487, 6535, 1795, 7566, 9751, 3447, 6153, 9517, 6089, 905, 8178, 2985, 7723, 5969, 6287, 1231, 3417, 2674, 7440, 1086, 8201, 1256, 6944, 7538, 8337, 5679, 1050, 1774, 8428, 1174, 7802, 1813, 7400, 1048, 6163, 206, 4718, 5925, 9762, 3152, 6995, 3527, 1972, 9703, 6080, 7261, 458, 7312, 1957, 6787, 2652, 4312, 800, 6946, 669, 7873, 704, 2870, 6427, 9440, 9292, 6618, 8391, 1517, 3263, 1465, 6667, 5303, 9937, 2730, 7838, 3759, 9181, 7998, 2960, 8182, 7689, 2909, 7914, 3652, 7081, 8443, 6075, 8510, 4206, 2580, 9349, 8430, 6900, 9592, 801, 5903, 5609, 8952, 8205, 6962, 5921, 4248, 7392, 3514, 9459, 3913, 2741, 4651, 9722, 2114, 8190, 9171, 9502, 3354, 5029, 3726, 5656, 6308, 7620, 518, 9776, 9102, 7899, 5391, 5728, 9664, 976, 183, 9800, 995, 3052, 4865, 3966, 4318, 6119, 4317, 8639, 3563, 7544, 1768, 8545, 5052, 4342, 1168, 5231, 357, 7023, 1847, 8181, 7534, 4576, 9042, 7393, 5388, 5381, 9076, 3908, 4072, 5112, 9454, 4064, 3502, 8476, 2430, 4858, 983, 7271, 454, 1111, 9565, 3042, 2052, 9156, 4862, 8719, 8249, 107, 7712, 2471, 2761, 7558, 9607, 5852, 3071, 2211, 5275, 1632, 6272, 4147, 2291, 8045, 5489, 2010, 5436, 3425, 1048, 1, 2847, 7375, 9363, 8243, 1107, 7428, 8037, 9172, 6653, 6224, 1177, 5973, 379, 4423, 6156, 1419, 4695, 323, 4407, 5208, 9683, 3903, 1040, 7378, 445, 9143, 7659, 7848, 9477, 8998, 8501, 1795, 101, 7388, 4197, 9838, 169, 8440, 8575, 598, 4753, 8764, 6414, 2992, 3383, 8315, 4665, 827, 7648, 3315, 1032, 4584, 5613, 382, 5494, 2068, 7612, 7906, 9232, 3988, 4211, 8630, 4634, 5699, 3149, 2603, 7966, 284, 9285, 4220, 4262, 8854, 2691, 2799, 7907, 1607, 9062, 6517, 3643, 3520, 8484, 1480, 9373, 7539, 9148, 9826, 9991, 6308, 8315, 8386, 7191, 7608, 3288, 8890, 9543, 9346, 7824, 2320, 7864, 2246, 4647, 3343, 1554, 4759, 3808, 3511, 6486, 2257, 3950, 5910, 9515, 2600, 7661, 1622, 5616, 9855, 752, 2674, 6811, 7797, 1164, 5210, 7068, 9686, 3451, 7366, 6862, 3525, 1931, 6645, 9467, 3149, 3005, 5044, 6580, 7334, 2938, 8619, 3814, 8952, 4308, 8799, 1047, 8929, 7533, 6226, 8659, 3397, 1625, 3865, 6795, 5294, 3001, 7893, 5370, 8816, 3417, 4021, 3079, 3510, 4807, 8926, 7828, 7817, 7603, 8067, 5083, 5209, 7676, 720, 4278, 7099, 5604, 7377, 6465, 6353, 2828, 8040, 9044, 7094, 9424, 2654, 2939, 6256, 9829, 8821, 4620, 3743, 2252, 107, 3337, 5187, 8998, 1642, 6757, 9092, 5415, 5632, 6502, 2343, 1073, 6878, 9102, 3752, 5938, 2575, 5547, 4298, 3695, 6800, 4755, 9783, 231, 6224, 3536, 7093, 9512, 3015, 8902, 1317, 9138, 3026, 3905, 5215, 152, 3444, 3963, 9719, 8902, 4691, 8954, 484, 3968, 8076, 4833, 2098, 7094, 6684, 761, 3290, 1784, 3683, 5529, 4191, 7599, 1478, 5747, 800, 8455, 7980, 1105, 9724, 1326, 5785, 6698, 9959, 2427, 6845, 9114, 8567, 8283, 7472, 3637, 6368, 8914, 6289, 1405, 3062, 9978, 6033, 2153, 9653, 5862, 9592, 9389, 1207, 5661, 3234, 4102, 3277, 1492, 7037, 6590, 4188, 8452, 4357, 968, 76, 6580, 6465, 3945, 3867, 5777, 5468, 4239, 5348, 112, 8934, 5425, 5847, 5838, 6485, 8572, 3106, 5385, 319, 4377, 9520, 3923, 6052, 8130, 7888, 8431, 6908, 1681, 1148, 9678, 3304, 9320, 8432, 824, 6820, 9990, 72, 5083, 4547, 7625, 9135, 3770, 7023, 9862, 5382, 4009, 9625, 2338, 773, 2073, 9502, 1119, 4220, 8493, 2513, 1203, 8174, 4461, 319, 4262, 4043, 6651, 2238, 7820, 1433, 823, 1921, 8165, 4657, 9393, 1720, 936, 4553, 4318, 8287, 8770, 5188, 7310, 8595, 9599, 5405, 9496, 303, 3699, 6642, 4486, 4088, 4567, 4439, 9835, 1119, 2598, 4006, 1271, 4207, 2787, 664, 2860, 583, 7419, 8229, 6956, 2560, 8343, 6503, 1220, 3652, 5450, 8186, 4795, 466, 5271, 7312, 2281, 9474, 4958, 1062, 3790, 891, 44, 493, 1551, 9198, 6930, 1223, 2446, 1717, 2465, 6329, 1453, 8210, 9096, 6397, 3638, 1820, 3471, 3175, 4115, 2261, 684, 4606, 4936, 8139, 9286, 4958, 1977, 9157, 4916, 1219, 910, 1411, 823, 3224, 864, 3946, 4340, 5457, 7924, 4017, 5631, 5973, 8493, 795, 3376, 329, 2230, 7672, 2770, 1163, 5580, 9988, 8736, 8586, 7523, 8370, 909, 1152, 4243, 6501, 9962, 2378, 9635, 4176, 3185, 6211, 9555, 5439, 8839, 8971, 3626, 4321, 98, 2711, 2386, 2152, 5731, 150, 8126, 365, 308, 2500, 5233, 8100, 2199, 4219, 5106, 2949, 1612, 714, 5152, 5307, 9736, 2544, 2732, 8936, 2302, 1036, 3762, 9807, 7166, 6368, 359, 4997, 9650, 7623, 5670, 3061, 6439, 5620, 5509, 8212, 2390, 1552, 2928, 1281, 5794, 6782, 9551, 9745, 3207, 854, 3981, 6652, 8640, 4933, 4691, 2462, 1910, 9702, 9123, 6426, 8063, 6954, 639, 6812, 3434, 3115, 2529, 7479, 3796, 1088, 265, 6353, 9481, 4587, 9375, 3799, 889, 4037, 1998, 5614, 3878, 646, 5183, 3262, 3862, 9440, 7126, 3422, 7403, 9695, 5350, 4435, 4181, 6575, 2868, 3935, 7253, 5782, 3841, 8741, 1418, 3235, 6535, 566, 7694, 5642, 8761, 3802, 3103, 6750, 5682, 9861, 8923, 6903, 2481, 7267, 8162, 4762, 8105, 6290, 7811, 5019, 5505, 7489, 567, 580, 8780, 6724, 8032, 2697, 1761, 375, 9450, 7706, 3027, 6666, 3826, 396, 9088, 2031, 5284, 1993, 3638, 9678, 4115, 5052, 9230, 7817, 1822, 4541, 269, 2168, 6399, 5985, 7133, 7455, 5626, 9885, 5774, 8335, 4350, 6550, 1090, 6968, 1451, 6149, 4549, 9092, 4982, 3032, 726, 1557, 5510, 2429, 5802, 65, 407, 5615, 9752, 7306, 7905, 7370, 2711, 9807, 5487, 798, 5688, 566, 4555, 2087, 5536, 9023, 4875, 7103, 2903, 6408, 2928, 8376, 2624, 2241, 4321, 630, 2324, 6899, 5703, 1597, 6737, 9234, 2632, 3255, 6632, 769, 1733, 9029, 8744, 1049, 4272, 1561, 723, 8015, 8866, 4837, 9119, 6865, 1183, 713, 1679, 1290, 6317, 1084, 4903, 2502, 7727, 3166, 6521, 4330, 7213, 1788, 2778, 7330, 2718, 2315, 392, 2729, 337, 7663, 4604, 4146, 3857, 5020, 8646, 1455, 6352, 1452, 9471, 7003, 7011, 6209, 9936, 3288, 4255, 1414, 4693, 1043, 3112, 1931, 8454, 2112, 2674, 1603, 5340, 7703, 1230, 2238, 3283, 7054, 7801, 1316, 2972, 6129, 5969, 9385, 1263, 8307, 8436, 748, 6157, 3817, 6528, 6201, 6114, 388, 3900, 281, 4071, 2473, 4468, 1599, 4022, 1272, 2592, 2706, 6961, 1380, 9623, 6283, 5323, 1209, 3167, 8410, 7009, 7714, 246, 8540, 1037, 5199, 2693, 3607, 8374, 9413, 2136, 3616, 8856, 8505, 5014, 7370, 6011, 2854, 3718, 7442, 8114, 3621, 2247, 6201, 7795, 6332, 2182, 59, 5354, 6593, 1881, 5031, 1628, 6834, 6187, 8069, 1890, 2297, 4204, 9564, 4254, 6260, 5847, 3605, 2576, 3188, 6750, 5952, 4905, 4225, 6167, 1530, 78, 8676, 9325, 9873, 1189, 558, 9623, 3039, 6896, 2648, 9726, 2886, 442, 6685, 4380, 7417, 6134, 9866, 8891, 2510, 357, 4255, 7000, 6953, 5990, 9273, 8347, 7382, 4649, 1879, 8765, 440, 8566, 680, 5041, 5816, 1611, 6075, 1590, 6156, 9389, 9295, 5509, 1876, 2463, 2966, 3699, 5227, 595, 561, 1809, 379, 9377, 4737, 5975, 5820, 9392, 6737, 7734, 7543, 7628, 2240, 9240, 988, 699, 560, 6382, 4596, 3855, 9632, 859, 1788, 6996, 1628, 9275, 226, 3064, 2384, 5944, 3526, 6584, 1950, 6834, 9669, 6488, 5338, 5149, 9244, 7657, 3370, 6089, 9974, 2385, 4169, 2515, 2598, 2055, 6920, 8514, 7459, 3447, 1270, 6098, 1569, 736, 521, 1324, 4401, 1647, 7092, 8170, 2150, 2666, 934, 1728, 3516, 2043, 5171, 6825, 3250, 9384, 7555, 5216, 8040, 2049, 3917, 1835, 8307, 9097, 297, 1354, 4503, 730, 9426, 4855, 4955, 2737, 6230, 1156, 7675, 9566, 6811, 1688, 8090, 2696, 5745, 2634, 7375, 7481, 1168, 285, 3328, 4115, 5350, 5409, 2843, 6969, 5740, 7631, 797, 1570, 1280, 376, 5253, 1584, 8141, 2418, 7067, 7908, 8265, 4931, 2117, 8204, 6194, 2655, 785, 7056, 6194, 5427, 1526, 9068, 5771, 7171, 5676, 2840, 5738, 3771, 6079, 660, 1102, 9872, 9502, 1818, 1414, 1870, 1670, 6718, 405, 1639, 6376, 8696, 2025, 8782, 3496, 5645, 175, 1049, 1695, 5765, 2889, 796, 1945, 5297, 4051, 5971, 6981, 6502, 6894, 9162, 6838, 8031, 4791, 7258, 6648, 2950, 158, 7849, 5200, 1108, 5772, 6055, 4525, 8923, 5893, 2085, 3739, 3512, 183, 1868, 6461, 4943, 4419, 9955, 4854, 9051, 8187, 4838, 1312, 3091, 3610, 8495, 1003, 6977, 9029, 486, 6803, 3432, 3089, 152, 5571, 2352, 4750, 2063, 8360, 3839, 7413, 4727, 4393, 7967, 2984, 5942, 41, 3353, 6035, 1958, 3356, 6430, 7974, 7272, 8731, 5732, 2319, 8003, 3136, 5664, 6404, 7269, 3812, 4383, 5307, 3677, 5887, 1598, 7802, 5494, 908, 9176, 791, 9540, 4191, 4444, 1962, 7110, 204, 2518, 7700, 2207, 8794, 8002, 5038, 6543, 124, 801, 6154, 9567, 1005, 5904, 7590, 6113, 4040, 7289, 7014, 1198, 6431, 4591, 6035, 7642, 3150, 5508, 4944, 1538, 7091, 5703, 5242, 3221, 3017, 9622, 6623, 29, 1101, 9966, 5623, 293, 9366, 7261, 5709, 8162, 8507, 7359, 1995, 4470, 133, 4082, 7002, 4217, 9292, 3273, 4395, 2374, 4208, 5453, 8577, 294, 4949, 8117, 6652, 247, 8583, 3543, 870, 9361, 4672, 4500, 9105, 5466, 8957, 4697, 3673, 8861, 6522, 4152, 3869, 9446, 32, 278, 5673, 4635, 2018, 6214, 8108, 3337, 1277, 8219, 3095, 7006, 983, 818, 1664, 9601, 3610, 7371, 7015, 9668, 1047, 2497, 6049, 1470, 3576, 705, 6729, 9794, 5734, 2732, 1699, 5683, 7214, 236, 1662, 2927, 6904, 6487, 9006, 3813, 5148, 3123, 2242, 8101, 1259, 5309, 5389, 1520, 6313, 3539, 9045, 871, 8355, 4185, 9153, 3766, 4497, 1810, 2247, 5069, 2135, 4468, 1020, 2119, 5378, 24, 8030, 7752, 3569, 2235, 1801, 1301, 2968, 6564, 5690, 5020, 1343, 3006, 4460, 7063, 5219, 6129, 2933, 7428, 7350, 5043, 7569, 3560, 1529, 562, 2434, 6292, 573, 1257, 4568, 2532, 4702, 5284, 4647, 2122, 8481, 2758, 2575, 4509, 9821, 4215, 803, 8735, 4564, 8634, 6955, 4616, 3796, 5116, 8040, 7108, 9394, 9406, 860, 1575, 5754, 7882, 3245, 6197, 2715, 8728, 5608, 370, 3738, 2640, 2811, 2672, 6853, 6165, 9576, 3385, 7560, 7187, 9966, 2571, 5298, 9251, 8650, 1428, 1173, 6527, 9161, 413, 7283, 5938, 8780, 4618, 4164, 1983, 6996, 4918, 2999, 5016, 8675, 4994, 3518, 5229, 547, 4459, 4553, 5007, 6593, 3747, 6811, 1975, 201, 8889, 832, 7308, 7432, 3041, 9770, 3678, 8370, 7609, 1860, 1291, 7575, 3457, 387, 988, 458, 4056, 6793, 5704, 5478, 273, 8287, 817, 2972, 7052, 3692, 8372, 2383, 7130, 2875, 7494, 8650, 8787, 4204, 7326, 3053, 6411, 6488, 6636, 9359, 7951, 7117, 2546, 2620, 1706, 7453, 2447, 4922, 320, 6528, 1352, 8508, 5345, 6187, 3039, 1086, 6961, 955, 3408, 2571, 196, 6087, 1144, 6783, 8553, 8811, 9065, 320, 1599, 5926, 8757, 9456, 5490, 1985, 5739, 512, 9241, 8961, 4066, 3426, 8997, 7975, 3538, 3861, 1879, 830, 8411, 7581, 6754, 6472, 254, 1814, 6001, 8704, 3227, 4495, 1530, 6749, 8870, 9047, 2249, 2904, 5427, 9839, 5310, 6143, 2832, 7082, 1049, 6520, 1810, 7578, 6305, 1754, 7039, 8480, 6942, 5664, 9407, 4401, 1361, 6850, 9678, 2811, 7055, 7643, 4833, 6882, 7001, 4058, 9615, 4961, 3, 3102, 6080, 2845, 2962, 6377, 5811, 841, 7270, 5121, 3008, 4732, 4755, 8874, 8333, 1785, 4409, 9060, 2324, 6361, 9512, 3739, 9323, 9609, 7594, 1706, 2242, 2793, 568, 250, 1606, 336, 4062, 9252, 3455, 3407, 8182, 2492, 6621, 5787, 8889, 762, 2134, 3364, 614, 1844, 4878, 8522, 2504, 7820, 8048, 8321, 8568, 2888, 853, 1355, 4053, 693, 2862, 9530, 6030, 5365, 9539, 5067, 8618, 6539, 2423, 1899, 9292, 3439, 7246, 1902, 1123, 826, 1363, 8450, 7211, 5348, 8418, 5483, 9414, 5690, 6980, 7330, 8369, 4700, 8827, 9809, 2991, 554, 1207, 7247, 6566, 7526, 9426, 6129, 5477, 907, 5332, 7077, 3011, 9286, 6349, 3857, 642, 2904, 5354, 3121, 4789, 2515, 3235, 7380, 7850, 4816, 4935, 6388, 2351, 3792, 6886, 2154, 8964, 8714, 9298, 9114, 2503, 823, 4057, 4435, 6018, 6102, 4823, 3365, 670, 6568, 6929, 1544, 9035, 5342, 7102, 3337, 619, 411, 2799, 8327, 6756, 4873, 5752, 8395, 3943, 966, 2098, 3537, 464, 4639, 6349, 4114, 3457, 1954, 8873, 6419, 1991, 737, 9453, 4356, 935, 8788, 4963, 4021, 7523, 9013, 4777, 3285, 3270, 5211, 9964, 8232, 9625, 9087, 9365, 6979, 7549, 425, 5878, 4843, 8139, 1184, 3848, 4498, 7059, 993, 4254, 1228, 1035, 5483, 3441, 5570, 1637, 9581, 733, 9993, 9285, 3798, 9445, 4441, 8226, 114, 2948, 2628, 801, 5609, 36, 9760, 4726, 7943, 4554, 4902, 3495, 520, 1050, 1141, 1537, 4055, 1958, 2510, 311, 8067, 6672, 6613, 9436, 5502, 2925, 6036, 1600, 403, 1436, 7331, 514, 2732, 9809, 8290, 7553, 2644, 4298, 7895, 3852, 6171, 7456, 9291, 2015, 9946, 646, 8311, 2191, 6330, 7411, 2601, 9267, 7672, 3788, 4671, 7431, 5559, 1179, 6565, 4092, 3858, 3101, 4989, 2689, 4685, 9784, 1554, 8111, 6595, 9480, 6945, 5167, 1864, 7983, 268, 8717, 6887, 8190, 7867, 3720, 151, 2687, 6846, 7555, 4898, 851, 1917, 3345, 1219, 1934, 7275, 6650, 6146, 221, 2325, 7869, 898, 4870, 589, 7422, 2005, 5451, 5911, 235, 7840, 2537, 3451, 5140, 120, 1371, 7181, 3725, 9255, 4403, 5589, 1381, 2123, 5337, 5594, 9843, 9558, 2295, 9312, 1227, 3404, 7461, 8450, 9387, 126, 1934, 4267, 4519, 9193, 1252, 6777, 2358, 5731, 8875, 6905, 2324, 1416, 9345, 3541, 2744, 8990, 2319, 8061, 3529, 2101, 2052, 6006, 8035, 9861, 3277, 1382, 1751, 8397, 468, 9757, 7920, 6022, 5980, 9611, 516, 1159, 4128, 852, 4982, 6610, 9623, 5365, 4131, 9418, 7248, 6070, 7672, 5449, 9998, 4757, 1175, 3912, 5648, 2288, 4639, 9103, 8433, 6488, 4983, 7080, 4130, 6079, 8461, 6577, 7975, 2800, 4850, 6119, 2681, 2155, 7391, 9564, 1121, 7884, 5206, 1145, 3750, 388, 560, 4313, 6902, 5977, 1516, 2279, 3891, 3581, 2665, 9138, 24, 8294, 5122, 1919, 688, 5548, 6637, 2834, 151, 2246, 7281, 3171, 3402, 1891, 6978, 2292, 5174, 7075, 6417, 2281, 2792, 1194, 9181, 8587, 3915, 1411, 8763, 2691, 6387, 4005, 1949, 9203, 7279, 8362, 5917, 5873, 2745, 994, 9100, 7400, 2496, 2789, 3374, 6306, 8719, 5162, 8484, 8132, 306, 5427, 2689, 2974, 8023, 1992, 1411, 6345, 4542, 2078, 6092, 6978, 2110, 3503, 1884, 5037, 8352, 7591, 3858, 2460, 8026, 5451, 4181, 3505, 7148, 8581, 7697, 1938, 7081, 4673, 7442, 6559, 5097, 1279, 9454, 711, 1459, 3433, 1697, 386, 5149, 90, 5319, 1541, 9174, 1589, 8661, 3522, 7580, 2540, 2340, 9640, 431, 5850, 1613, 7795, 4854, 6121, 6917, 1358, 1297, 6068, 7165, 7350, 8469, 561, 4581, 4213, 3290, 1298, 1194, 8985, 7781, 740, 9987, 6783, 6634, 3684, 1535, 6138, 3439, 4119, 5728, 1007, 7670, 8549, 2867, 8167, 1323, 6130, 7826, 2114, 4495, 4382, 9147, 3287, 8792, 1507, 7995, 3804, 1554, 3943, 9380, 4684, 8150, 3243, 815, 136, 9818, 7414, 201, 3381, 5913, 848, 4386, 2592, 7329, 2143, 8348, 6466, 576, 1680, 1588, 627, 7124, 4443, 1773, 7685, 2675, 8213, 9803, 3411, 923, 4507, 166, 5383, 7784, 8340, 679, 657, 6112, 9097, 1510, 3965, 5544, 1289, 4908, 5035, 9064, 3226, 7129, 9036, 2664, 655, 4696, 3558, 2767, 3367, 7513, 1697, 9097, 116, 3052, 1096, 8107, 9294, 8508, 592, 3832, 4009, 7374, 6988, 7489, 3606, 7371, 2909, 2148, 4726, 922, 9029, 3202, 2462, 4951, 1074, 7074, 7227, 60, 1540, 6202, 3819, 6842, 7679, 3939, 5007, 531, 1236, 2941, 1314, 2382, 7751, 4833, 5361, 311, 5992, 9007, 756, 283, 9532, 5927, 3892, 1399, 7998, 2510, 5942, 3239, 1228, 8488, 1465, 8409, 4058, 9219, 3242, 8112, 5908, 1982, 6750, 433, 6603, 7720, 2761, 97, 2826, 5483, 6603, 9620, 2992, 3250, 8014, 4411, 33, 2390, 1088, 4832, 3948, 8158, 4147, 4955, 9544, 5436, 159, 9917, 4184, 6209, 1642, 4210, 2672, 1862, 1535, 341, 2234, 5615, 5403, 4831, 9364, 2960, 5288, 5041, 9525, 1099, 7798, 9791, 4315, 6796, 6715, 7917, 1263, 2986, 7065, 4871, 7993, 1492, 8426, 4506, 7092, 1151, 7614, 5122, 6685, 7351, 8728, 8772, 7830, 4061, 2699, 5777, 7492, 7676, 6343, 8204, 2893, 1859, 6417, 928, 3883, 3755, 1836, 7219, 7671, 5427, 5879, 9813, 880, 4165, 1257, 6959, 6891, 2569, 8077, 6224, 2112, 4196, 5785, 507, 9886, 4291, 5319, 6202, 726, 2696, 8331, 2313, 7513, 3799, 6660, 9631, 1127, 1277
		};	
	///{ 1, 2, 1 } , { 1,8,6,2,5,4,8,3,7 }, {{1,0,0,0,0,0,0,2,2}, [2,3,4,5,18,17,6] [1,3,2,5,25,24,5]
	cout << maxArea(v) << endl;
	auto t2 = chrono::high_resolution_clock::now();
	cout << (t2 - t1) / chrono::milliseconds(1) << "ms to run.\n";

	/*
	const char* s1 ("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	const char* s2 ("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	//const char* s1 ("aaaaaaaabaaaaaaaa");
	//const char* s2 ("aaaaaaaa");
	
	Solution4 s;
	auto t1 = chrono::high_resolution_clock::now();
	vector<int> v = s.findAnagrams("ababababab", "aab");
//	vector<int> v = s.findAnagrams("cbaebabacd", "abc");
//	vector<int> v = s.findAnagrams(s1, s2);
	auto t2 = chrono::high_resolution_clock::now();
	cout << (t2 - t1) / chrono::milliseconds(1) << "ms to run.\n";
	cout << v.size() << endl;
	cout << endl;
	print_vec(v);

	//hash <string> h;
	/*
	cout << h("aab") << endl;
	cout << h("baa") << endl;

	cout << h("aab") << endl;*/
	//vector<string> vv({ "bluffed","excellently","neurology","nonrefillable","edmund","boyhoods","survivors","sexually","outnumbering","bolero","werewolf","debasing","dragnet","addams","monochromes",
//	"flippancy","hoots","digestion","profanity","cellist","enrols","crumble","elderberry","jayson","recopying","threats","exploded","cinnamon","hospitalized","ducat","memorialize","powerlessly","suaver","deservings","genuinely","calliope","oxidize","gamekeeper","slimming","daises","resisted","shanty","receivable","careering","transmigration","dooms","revisiting","financed","severs","hominy","pantomiming","bestride","seam","alibi","churchman","ovule","jaxartes","retirement","translated","pancaking","achiever","navigates","hazes","tubman","versatility","fergus","adjust","narcosis","hightail","mormon","hattie","chinning","teenager","tho","misbehaves","trustfulness","electioneers","emending","disenchanting","barometer","styluses","uruguay","houseboat","rungs","endwise","reinterpretation","gashes","koshers","nostalgic","hateful","bray","sutures","saudis","sentimentalizes","ayers","avoided","spiky","circumnavigated","tonic","dialects","disbursing","manitoba","potbellies","cauldron","whitened","fitter","attorney","doorbell","scrolled","noncontagious","overnight","rubbishes","stove","amortizing","periling","doublet","celina","whitfield","tonsures","overturns","missions","casuals","juxtaposing","sings","hesperus","panhandle","armando","bernays","trimmers","transom","grafts","columns","abelson","archway","infantries","orly","pock","selectors","lecterns","humps","kinked","bridles","essentials","instead","eliminating","mabel","zing","impersonation","cudgels","chang","artifacts","creon","clucking","skedaddled","spryer","footballs","honeys","wafer","knelt","flagstone","americanize","bohr","plottered","simone","conventional","definable","blackbirds","woodsier","carriage","residents","mezzanines","tenement","plymouth","wresting","islanders","malleable","attentively","irrelevancy","paulette","hillbillies","leech","cloaks","individualist","uncannier","patel","effusions","dungs","plugs","discompose","dacrons","teletypes","dismay","germany","travailing","loathes","devouter","chandelier","rinsed","denial","mil","outmanoeuvre","tugged","icings","reefer","dominicans","franz","destruct","bog","pinhole","jackknife","polytheists","chatted","tomfoolery","breeziness","beaked","tasman","possession","partying","shift","anodynes","pontificate","typefaces","mullions","reconnaissance","stanching","bedstead","belligerent","breakwaters","messerschmidt","instincts","sickle","quondam","limos","fosters","mentalities","minestrone","harrowed","folsom","travesty","compendiums","maladies","narrates","interlocks","humbleness","uplifted","slipknot","motorcyclists","restarted","iconoclast","forts","trumpery","cute","harpsichord","klutzier","ashtray","garlicking","sprayer","duodenal","parboiled","ultras","arkansan","metaphor","patterning","lorries","donetsk","coerced","constricted","murkiness","curtailing","bookish","tenacious","araucanian","unmask","forlorner","ills","bert","closures","cahoots","rotundity","sullying","pare","pretences","beggar","childproofs","educable","duct","posits","bushed","southward","echelon","approximates","spoonerism","waitresses","unman","isolation","suleiman","delight","skimping","rambles","redistrict","alderwomen","o","rejoiced","blot","backpedals","clearings","brontosauruses","laughingly","huckleberries","steinbeck","friskier","commander","skivvies","reality","intermingles","cumbersome","bribery","disagreeable","jersey","lamont","profiteered","shooters","transience","scraper","resignedly","grabbing","christies","piaget","executors","reproachfully","spasming","overproduction","incises","priesthoods","straightforwards","poesied","welled","bickered","drolleries","manures","daffy","segregate","waddles","cheerfully","overprinted","molester","lief","summarizes","vaccination","seminole","unlisted","rumping","ed","weir","manufacture","secretariat","fulminated","molybdenum","bakersfield","unpinning","heroism","violence","mistimed","alcoa","perter","manuscripts","separate","retractions","safes","atoll","grottos","boogieing","olga","frisking","grows","redeployment","helmholtz","durant","rankest","thespian","cheese","pilaf","thinness","contrast","parqueted","milkmaids","blackhead","breathlessly","bothering","decoration","arrogant","setups","contraptions","swirly","transgression","misses","handyman","snows","clinic","vatican","forecaster","haughtiness","bovine","strobe","ingram","maratha","descartes","billeting","treetop","aloud","globed","monument","argumentative","squeegee","especial","retrofits","artistes","propose","piraeus","horsetails","tailpipes","throughout","tarted","synods","unconcerned","weighting","duding","roe","undervalued","reachable","thicker","egging","dentistry","byte","distinguished","envisioning","filibusters","housewarming","matzot","dill","remarries","anatomical","kremlinologists","truancy","bostonians","limited","poorer","corniest","contradictory","three","temporaries","convivial","shirting","schisms","balconies","reinterpret","suturing","kumquats","oncology","unbidden","correlates","kowtows","flashest","neighborhood","rumbas","swathed","webb","birches","engages","promoters","outside","cheeriest","suffusion","propounding","bagels","amish","contrarily","xylophonists","familiarize","makes","testimony","crusaded","wildcatted","slackest","bovines","artier","plops","robbie","slosh","dinkier","airworthiest","carbohydrates","teammates","locoweed","stratagems","sarcoma","gougers","yuletide","rosemarie","upholster","sizzle","reminiscing","bluffers","shellac","heckled","hypothalami","showery","supposes","humbug","burnished","lopsided","imprisons","opine","leeches","generic","stimulated","soggily","aftershave","marvell","pekoe","microorganism","burlap","topples","misfire","scuttlebutt","tantrums","exits","eclecticism","alden","ilk","deltas","slack","effortlessly","operationally","offspring","staggers","alkalis","logger","spines","oscilloscope","tiniest","fluxed","collectively","leagues","procter","protruding","flukiest","underemployed","wetter","ignite","puddings","magnetosphere","solids","oceangoing","barrooms","refurnished","operational","mastering","white","organist","blackest","licentiates","marsupial","machinists","borderlands","dingies","kegging","dualism","cohen","existing","wheeler","uncleanly","umlauts","expiate","misspends","ebert","camber","adventured","weave","bounded","religiously","potluck","scions","millionths","goblet","witchery","dodge","sarasota","pier","membranous","stomaching","tallyhos","cohort","leveraged","makeshift","hexagon","thumped","zedong","versions","ultraconservatives","obeyed","pace","wicks","luncheoning","minerals","medications","moralizes","unites","rant","portents","apparelling","hums","farrowed","verve","boggiest","weal","josephus","perfects","beef","stairwell","comment","arrant","stature","kc","quoits","galls","adoption","reformulate","physicals","schroeder","scoundrels","delivered","crushed","rue","thrives","cerf","hijacker","inkier","vulvae","deterring","burgles","catechism","unhorse","reclined","dapple","angioplasties","sluggards","emceed","snobbery","accessory","cardiologist","browning","crosses","boasted","summonsing","gamble","overdue","scourge","dirges","cascades","precious","peacefuller","oysters","hoods","pirates","sauerkraut","whiskers","defames","repute","foolish","lactate","tharp","electrocutions","fating","freezers","invocation","dissenter","should","hells","homesickness","archdukes","preconceiving","scroungers","embellishment","massacre","upon","aerated","protuberant","sternly","meticulously","virulent","loch","enchant","raindrop","atrophies","magyar","interring","coachmen","exorcism","faintness","pointlessness","kawabata","installment","maliciously","vindicating","monkeying","uncanny","tangibles","blessed","forensic","arty","toppled","dilapidation","klutzes","moots","cottage","seismograph","diarists","aperitif","facing","filial","soundings","salsa","clear","cayenne","stilling","thighs","contrasting","cloistered","custodial","woodland","frillier","unrolls","landsat","chartres","toughly","saluted","verbose","transfiguring","zapped","iconoclasts","parkman","charlestons","spadework","okaying","numismatics","chestnuts","ghostwriters","nobelists","insouciant","vivisection","moods","edifices","relocated","wisdom","ignobly","namesakes","tapestry","schismatics","agra","blundering","sailboards","fruited","anticlimax","viewed","locus","barricading","rehearsed","irater","sibyl","steps","airsickness","blasphemous","swelling","salinger","veal","normalizes","gullet","inhabitant","slut","zinced","homing","headphone","chatters","winged","wingspread","kneecaps","tam","withdraws","repatriating","peter","isobars","dix","rekindled","snider","depends","mute","knowledgeably","mends","tides","stoutness","hempen","victoria","slaloming","buttons","grammars","astounding","memorandum","kenmore","solid","bandoliers","flowered","equivocation","assuredly","festers","helios","lebanese","impugned","shiftlessness","statement","announcer","vagueness","punctures","colonnade","exist","displeasing","diocletian","untold","unprintable","hereford","sidereal","joke","automatically","rendezvousing","surfed","surreptitious","depopulating","arching","massive","excise","beatles","rigorous","turnovers","impromptus","jezebels","glinted","leveraging","capsizing","voices","hitchhiking","ramon","wyeth","larva","unblushing","inanest","vacillate","contrives","kw","carboniferous","disinterred","predicated","song","andean","youths","previous","yours","supplicates","gompers","apprenticed","half","lactic","authenticating","charlatan","mendacious","flanks","hieronymus","dressy","owns","vestry","strobes","clapping","informers","sermoning","rifer","headstone","bobbing","forgiven","hypocritical","legation","adjusted","glibness","peeled","actuators","composition","payloads","abdication","delete","unnecessary","misprint","wooziest","cannibalistic","voiced","marooned","einstein","erratically","obsessions","impracticality","hoffa","rheumatics","handsets","tricked","afield","abdul","sounding","tray","massacring","iowan","grits","billy","purchases","profitably","resilience","eyed","vocabularies","golden","barking","riviera","helmsmen","cavorting","shrinks","hangmen","heliports","salve","assorting","neuroses","contribute","triathlon","adherents","gismo","sering","pulsate","hoarders","vacating","pulverization","destabilize","wore","eureka","gobs","raiding","valhalla","aureole","illustration","null","ageing","umbrellaing","characterize","ethel","bagging","lucas","nakedly","rinded","wainscottings","through","falter","clearness","smart","overspecializes","older","entourage","dawn" });
///	vector<string> vv2({ "nozzle","punjabi","waterlogged","imprison","crux","numismatists","sultans","rambles","deprecating","aware","outfield","marlborough","guardrooms","roast","wattage","shortcuts","confidential","reprint","foxtrot","dispossession","floodgate","unfriendliest","semimonthlies","dwellers","walkways","wastrels","dippers","engrossing","undertakings","unforeseen","oscilloscopes","pioneers","geller","neglects","cultivates","mantegna","elicit","couriered","shielded","shrew","heartening","lucks","teammates","jewishness","documentaries","subliming","sultan","redo","recopy","flippancy","rothko","conductor","e","carolingian","outmanoeuvres","gewgaw","saki","sarah","snooping","hakka","highness","mewling","spender","blockhead","detonated","cognac","congaing","prissy","loathes","bluebell","involuntary","aping","sadly","jiving","buffalo","chided","instalment","boon","ashikaga","enigmas","recommenced","snell","parsley","buns","abracadabra","forewomen","persecuted","carsick","janitorial","neonate","expeditiously","porterhouse","bussed","charm","tinseled","pencils","inherits","crew","estimate","blacktop","mythologists","essequibo","dusky","fends","pithily","positively","participants","brew","tows","pentathlon","misdiagnoses","paraphrase","telephoning","engining","anglo","duisburg","shorthorns","physical","enquiries","grudging","floodlit","safflower","asphalts","representing","airbrush","bedevilling","fulminations","peacefuller","hurl","unequalled","wiser","vinson","paglia","doggones","optimist","rulering","katmandu","flutists","sterling","oregonians","boosts","slaver","straightedges","stendhal","defaulters","stylize","chucking","adulterate","partaking","omelettes","monochrome","bitched","foxhound","tapir","vocalizing","manifolding","northerner","ineptly","dunce","matchbook","locutions","docudrama","sinkers","paralegal","sip","maliced","lechers","zippy","tillman","penknives","olympias","designates","mossiest","leanne","lavishing","understate","underwriting","showered","belittle","propounded","gristly","toxicity","trike","baudelaire","sheers","annmarie","poultices","therapeutics","inputs","bailed","minutest","pynchon","jinx","jackets","subsections","harmonizes","caesareans","freshened","haring","disruption","buckle","per","pined","solemnity","recombined","chamber","tangling","pitiful","authoritarians","oort","ingratiate","refreshed","bavarian","generically","rescheduled","typewritten","level","magnetism","socialists","oligocene","resentful","lambast","counteroffer","firefight","phil","attenuates","teary","demarcated","moralities","electrified","pettiness","unpacking","hungary","heavies","tenancies","tirade","solaria","scarcity","prettiest","carrillo","yodel","cantilever","ridiculously","tagalog","schismatics","ossification","hezbollah","downscaling","calking","tapped","girl","alba","lavishness","stepparents","integrator","overact","father","fobbing","pb","require","toes","sweats","prisoners","mbabane","hatch","motleyer","worlds","decentralize","ingrained","shekels","directorship","negotiating","hiawatha","busying","reciprocate","spinsterhood","supervened","scrimmage","decolonized","buildups","sedative","swats","despotic","driblets","redoubting","stoic","xeroxes","satellited","exteriors","deregulates","lawful","flunk","broached","energetics","moodily","popinjays","shoshone","misleads","abduct","nonevent","flees","harry","cleverness","manipulative","shoplifts","tom","junk","poniard","transmute","stricter","trochees","snack","relations","edger","culminate","implication","carjacked","kissers","federate","offsetting","sutures","wakened","axis","boxcars","grinds","scenting","cordoba","lumberyards","incendiary","antiphonal","decipherable","gilliam","redecorates","plum","nitpickers","linefeed","awakes","embittering","spewing","annul","filial","scarlet","connors","sanctum","scotsman","isobar","activity","overthrowing","unseasoned","tarantulae","outtake","diego","mars","stunted","hunted","sublimation","barbadian","barbarisms","epidemic","assesses","imposture","freaks","detroit","bloodiest","avails","prenatal","connecticut","guardsmen","betwixt","windsock","neutralized","psychoanalysis","rubberized","overproduces","narcissism","tallow","cringes","resinous","paintbrushes","duality","paints","deactivated","expertly","speedsters","coward","bass","psychiatrist","curies","betrays","bubble","mellow","showy","retarding","radishes","coy","unreservedly","larks","apportioned","flaccid","relabelling","alphabeted","anointment","helms","gillian","trophying","breakage","underbrush","directest","wingtips","pretence","preshrink","remarries","addle","brouhaha","mobbing","g","dings","gains","stockade","ouch","particulates","listens","habituation","kill","crouped","hyperbolae","hutching","stoney","rightness","davids","questioned","ethiopians","courtliness","delays","navahos","devils","keeling","accelerators","investigator","spindling","illegality","extremer","revlon","purity","bradly","jut","machs","liquidated","informant","smartly","disfigure","parliaments","croup","teletypes","impression","trainee","implications","embed","podiatrists","jewelled","brokenhearted","spaceman","unsteadier","kitchen","twirling","conurbations","pygmies","lourdes","watertight","reassessing","dempsey","matriarch","alas","abscissae","decanter","commentated","sandy","idler","soybean","cutoff","dictate","credibility","indeterminable","release","blank","curitiba","pericardia","probably","indisposition","hesitantly","duff","ratty","derivative","decals","explication","cockier","monoxides","hyperventilate","genially","polluter","divan","may","convalesces","morpheme","pupa","prospered","tagging","nerdier","detached","spearing","hilbert","russeted","amanuensis","periwinkles","jujube","guarantors","premises","descanting","baned","deviance","sidearms","lamentable","barristers","climes","succulence","mauve","oceanographers","migraine","bisexual","peruvians","fatheads","parsimony","pilaf","portly","conniving","insidiously","inventing","constabulary","cling","stunting","accessioned","deadliness","overthrow","expectorant","agamemnon","blindfold","striker","shrugging","jibes","appropriateness","annihilates","hairs","proselytes","goads","rankling","predominated","hart","enemies","culpability","drank","martinets","prospering","dominick","complemented","invention","foolscap","tolerances","lorelei","profits","awarer","ungodlier","victoriously","mistrusts","princes","drudge","moderator","transversed","disco","japed","loomed","incense","ponds","gumbel","disarranges","coaxes","technology","hyde","debentures","confidantes","hankered","savant","styes","croupy","unapproachable","cisterns","unto","duds","conglomerating","clio","negroid","looked","methodism","hilario","balloon","thesauruses","integuments","thermometer","slacks","wigwagging","gaping","incensed","misquotes","chocking","patrols","upcoming","insists","livings","thoth","uselessness","vibrated","potluck","starboard","uniquer","boone","scintillates","darker","massey","arbitrariness","miniaturized","rousseau","chiffon","consortia","coral","finesses","half","biked","unlikeliest","hilarious","acrid","twinkles","galileo","outsmarted","ostentation","cradle","frats","misidentifies","uncleaner","bacardi","smoothest","antwan","warren","jingling","stocks","daumier","paranoid","pantaloons","dishing","receive","underpays","kane","variation","beset","disobliged","dreadlocks","psychics","twofers","lieutenants","pebbling","interposes","shingles","profanes","machining","dysfunctions","wolfram","brut","nebraskan","truculently","copeland","devonian","fuller","silvia","philosophers","cali","adores","disquiet","savvies","minatory","blooms","radiotelephones","paradoxically","competitions","gandhi","weddell","occludes","retracing","kari","dead","lagoons","menfolk","abundant","enacts","conferences","procreation","steadier","cols","rabble","unquestioned","stupefying","whodunit","dizzier","paula","riposte","elixirs","discontented","zimbabweans","assemblage","unsalted","genders","caldwell","pulleys","pureness","kingston","vests","hearken","abuses","scull","hussar","solace","gondwanaland","surfacing","vivienne","subculture","reciprocal","expediencies","projectiles","segregationist","prickle","pooped","telecommutes","axes","scenery","peppery","parenthesizing","checked","trademarked","unreasonable","curtly","dynamically","vulcanize","airtight","blotch","edmund","stoicism","scrambles","whirled","chasing","millstones","helplessly","permalloy","remanding","duplicate","broadsided","readjustment","buggers","quaked","grapples","democrats","landfalls","apprehensively","turmoiling","railing","lothario","modishly","faggoted","deflecting","interment","dodo","recreants","baywatch","frescoes","temblor","brigade","handgun","bradstreet","caspar","godsend","cochleae","queered","unevenness","hairnet","millimeters","flawless","plumbing","disciplinarian","orbiting","foothill","serviettes","peseta","windmills","myrdal","provides","slowdowns","clouting","gainsays","dishpans","mediates","weaker","shoestrings","gerunds","potsdam","chips","disqualifications","focus","quarry","dwarfs","laurels","coverall","reconsidered","exploded","distending","bronzes","apollonian","sweeper","couperin","gourmets","irreconcilable","goldbricking","emotes","demilitarizes","lambkin","grouper","anyways","hugs","quizzed","misstatement","spectrums","frigates","plenipotentiaries","parasites","tacitly","savvying","treks","dissociating","departing","resins","psychiatric","tablespoonfuls","aught","makeup","copping","interwove","selling","fantasize","flamingos","smolders","stript","laverne","extremely","chattering","imminent","vaulting","slackly","pasteurizes","goody","pearls","conceptualization","fins","brogues","muskogee","naziism","stromboli","sunflower","tosca","luridness","booing","zaniness","creel","bootblacks","attendants","swordplay","impinging","premiere","sedimentation","traffickers","carrel","observatories","telltales","cuckolded","ampler","alternately","shovel","tasmania","whooping","methodologies","pickling","overseer","sunnier","sanchez","supervening","viscus","cramped","santayana","utopias","intimated","pianists","computerizing","interpolating","reggie","horseshoe","preeminent","qantas","standish","flagpoles","thievery","admiring","palefaces","overflows","gaea","monique","sheepskin","bestiaries","beethoven","fleming","convalescing","moldier","snobby","jewry","hoodwinking","hope","henri","listlessly","doggoning","anointed","notable","talented","uric","towards","flue","arbitrated","ingredients","academy","clutches","novelle","parallelling","confabbed","synthesized","frontally","underexpose","ulcerates","injuring","stimulant","catalytic","ogle","throatily","ions","chores","spyglasses","metabolic","statesmanlike","tingles","ossifies","forge","coiffing","transepts","autopsy","colorfast","winery","procyon","sequesters","amended","putted","huff","fliers","harpooning","protecting","shipboard","dwindled","collations","stonewalls","criticism","thigh","quarried","knelling","knitted","redeemable","berm","seventy","misguides","schlemiel","pawn","ineligibility","lathe","bosses","temperance","haywire","everglade","confections","gruelings","mindful","paracelsus","quarreled","furtively","airdropped","clodhopper","transmuting","whilst","moldavia","exploiting","chicories","unrolling","shorthand","antigens","satirically","earner","primmer","jolly","perch","nonplussing","circulars","hanks","fingerprinted","syllogism","adulate","nominally","telecasted","quelled","accustoming","backslide","culminates","spiraled","compactor","gatorade","cornballs","investor","cupboards","deign","induced","ewe","snoopers","supposed","glitters","overlie","ambassadorial","chancel","accumulations","strictest","thalami","shops","moos","applicators","corncob","dona","apostrophes","kibitzes","rinses","kemerovo","confide","clemenceau","centenarians","memorialized","windburn","nominate","obscene","equivocations","arts","karloff","projected","scorned","limping","lava","sanitaria","clementine","brandies","unionize","compacted","griming","trilogies","babysit","congas","glittery","pimientos","phototypesetter","multivitamin","carbohydrates","lode","photographs","iniquity","micrometer","freemasonry","burros","marchers","percentiles","werewolf","weightlifting","valedictories","gacrux","senselessly","stoppage","monolithic","handy","overspent","nymphomaniac","seasick","misogynistic","coltrane","coeval","inversion","darkliest","landfills","barbers","suppurate","cavern","submerge","illumination","hesitates","lashes","covenants","thomism","aneurism","disappointed","gnarls","sprint","abash","frightens","undoings","pa","helicopters","reexamines","vassal","blessing","devaluation","purports","urinals","adjudged","garaging","pacific","infomercials","whitewashed","fawned","baptisms","concede","cornflakes","fostered","clewed","tiller","dalmatians","signification","boneless","chunkiness","omar","paramedicals","professor","unionizing","scripted","anchors","tabloid","alton","redrafted","reflexive","luddite","lamb","bidirectional","seaports","christendom","gets","chaperoning","tchaikovsky","wasters","dioxin","nuke","apologized","queasily","fujiwara","prearranges","abdul","upraising","sparklers","signposting","comparison","sb","cherokees","ungentlemanly","typing","waisted","sputter","biographers","waltz","stanches","upbringings","smithereens","tutor","young","eloy","sourdoughs","clingier","hoisting","blazon","homosexuality","lorries","kippering","abacus","specks","congressional","auditing","lash","eternal","carve","facade","defrauds","neighbored","musses","dismount","lope","lawbreaker","deed","japes","repeal","factorization","impetuosity","sitters","disorganizing","fussing","vale","epitomized","executrixes","deprivations","woodcarvings","miscalls","skateboard","pedicured","cloakroom","vassaled","innumerable","knelt","cellulose","beams","uniform","metatarsals","meteorologist","column","burnishes","dentists","quids","toasts","tableland","archivist","gladiolas","replica","lording","viewed","polisher","trooping","indistinctly","resisters","flycatchers","toughed","regor","insolvent","ninnies","truckled","birthplaces","telescopic","abelson","puritanism","leanings","disturbingly","transmission","mortify","upshot","newlywed","adam","ballplayer","lockwood","quirking","blocs","theatre","palliatives","smudges","marvelled","ramble","offside","indissoluble","droplets","fencing","hubbard","estimation","incorrect","malarial","confucian","games","sacraments","trivets","gammas","nastiest","merrymakers","sealskin","overkilled","bosser","strafe","exclusives","bouldered","antiwar","guitarists","jerry","earthly","oscilloscope","edmonton","merger","laminated","surmountable","casually","backspaced","charcoals","overheating","caramel","oldened","asterisked","tun","peafowl","purplest","skippering","prep","congregating","glaringly","crummiest","noreen","bromide","nomenclatures","kristin","purportedly","vamoosing","busybody","crucify","capote","milliners","veils","windsurf","reconnecting","layering","ossified","noble","tiptoeing","smiles","swain","perihelion","bagels","obfuscation","spreadsheets","buddy","flints","planting","hogwarts","abusers","welfare","mouses","lament","auras","unrelieved","cougars","cattails","chubby","handstands","woolly","concealment","mediterraneans","judas","electrocardiographs","skulks","puttered","crimean","liven","odds","warehousing","lifeguard","deepness","clowns","blossomed","constriction","honest","noisemakers","whist","overcame","sulphured","vertebras","commiseration","jolted","adjourns","bungles","sonnies","housekeeper","buddha","bolsters","warlords","banjarmasin","militated","anywheres","lula","weirdos","raymond","sections","taoisms","pay","latest","bights","carousel","sups","lavatory","conciser","lon","beefburger","clinically","snakes","backslash","developmental","squibb","smote","mastectomy","genius","sallying","niagara","guild","altai","ascetics","marts","misbehaved","desired","pagodas","platypus","freemen","lovemaking","transfers","brewing","absorbents","unions","lite","wilder","popovers","yamaha","faultier","supplements","forsythia","rummy","propagation","motorbikes","velez","unequivocally","lend","silliness","idiosyncratic","disseminated","carter","washed","dizzying","bedsore","pawned","lr","nubile","galloped","subservience","marlin","chance","schooners","faction","clutters","transmits","weathercocks","illustrations","quell","senegalese","touchiest","psychs","joshes","shallots","garrottes","coifs","glaswegian","hydrated","smirch","strutting","arnold","coughing","tangier","olympics","overexposing","benefactor","reputably","snootier","smuggles","bogus","priories","chandra","diplomatics","muskrat","forbad","monasticism","outshone","farewell","thomas","epaulets","nectarines","affording","buckles","concordance","lebesgue","pawed","lackey","sweden","confirmatory","humble","wizards","controlling","scoffing","worthy","homely","lexical","batteries","chorusing","inboard","cotton","lustrous","devalued","herbart","travestied","veneered","maxillas","omelet","ptarmigans","alnilam","submerging","bucks","niceties","yong","gender","toileting","biding","caffeine","lubricant","dashikis","balm","filings","series","paraguayan","fatefully","craggier","oversexed","milkweed","passels","concretely","rapiers","channeled","multifaceted","tenth","conflagration","pivoted","horribles","tugs","fireman","hull","semifinalist","odorous","carats","uncomfortably","clappers","chaffinches","demagnetize","limits","ups","wimp","reserved","busyness","illuminate","autocratic","zips","sculley","vainest","conciliators","vacillations","daughter","beau","stashes","mini","shallow","divided","invert","caesurae","vibrantly","germination","winching","curmudgeon","hurts","battens","lovable","redistricted","neighing","nonexistence","foghorns","manifesting","retrofitting","fictitious","gracefully","shetlands","transistors","rectitude","shea","acquisitions","predetermines","huts","blintze","cortland","murdered","leninism","ninetieths","fractal","inveighs","compelled","ringer","mistiest","snorting","transportation","dictionaries","khyber","misspelling","bifocal","playmates","disputant","neuters","epidemics","vijayawada","ambles","splashdowns","cants","bandannas","millennia","glows","fowled","cupped","laramie","occupied","gelatine","scorches","sidelights","beagling","campused","doer","gunfighting","tsitsihar","marin","fireside","yellow","seagram","strap","arrivals","sixty","lipscomb","wares","awfullest","servants","dreamer","crockery","mahavira","brad","outpourings","dusty","shrubs","briefest","segments","cartilages","excommunicated","generator","placket","berate","emulations","suspicious","fortnights","sped","griding","panting","trimaran","suspend","retract","adversity","regimental","hammett","wallflower","tyrannize","cinemascope","ambassador","humerus","litter","trying","sinkable","descents","coveralls","region","landslid","bowed","zigzagging","upholstery","parch","scratchy","altitude","angling","scaldings","plussed","babel","cirrus","haberdasher","gayle","chillest","catboat","battling","bellini","extincts","appendices","unmade","footstool","deaths","secretively","erasmus","agra","soothsayers","stillest","despoils","affiliated","mumble","aleut","gyp","purchased","kory","cesspool","interacted","demarcates","fanciness","defines","absorbed","fireplugs","pluckiest","misstates","grenades","untidiness","ventricles","overexpose","dryad","tumbler","chengdu","thistledown","dork","unauthorized","holmes","downgrading","syphilises","trammelled","sending","afflict","ornithologist","serried","much","emoluments","wilfully","strayed","canada","dachshund","compost","glamorized","gerrymandering","senate","allots","arsonists","coloratura","borderlines","cartooned","evert","continents","profiteers","merritt","cyclical","quickens","funkier","dourer","salmonellae","seemingly","cheeky","showering","proses","imperturbably","gush","intolerable","wozniak","vegetables","neglectful","aesculapius","whimsicality","unfolds","conceited","junkyards","immanent","norbert","pollsters","ruse","gymnosperms","toothbrush","accommodate","multitudinous","blessedest","squeezers","portal","newspaperwoman","polytheistic","affectioning","rhiannon","holing","johanna","gregariousness","fishtail","tainting","wasteful","aeneas","flycatcher","salem","ventilator","sat","hiroshima","breed","housewarming","migrate","smocking","plethora","fathead","mussy","communion","foxhole","renters","telecommunications","obtusest","puncture","preparing","encyclopaedias","footholds","violets","megalomaniac","dakotas","accentuating","joanna","gentleman","dardanelles","aeration","gerrymander","liker","chatters","questioningly","guesswork","lunar","upgrading","mara","consultancy","sanguines","sunks","polyethylene","injected","aneurysms","caterwaul","eventfully","aquariums","yowl","valeria","suicides","emptiness","pajamas","uphill","myles","playfully","palestine","agape","chichi","vatican","exponentiation","shipper","planes","reprints","dieters","involving","dimwitted","cranach","homestretch","fitfully","fluoridation","esthetics","coworkers","cannibalize","lipids","heartsick","flatware","rage","hazier","overburdening","psychosis","wage","debasements","personalized","itaipu","valletta","rhythm","cyclic","hillocks","badlands","proffer","cretin","sexuality","hefts","rehabilitate","disfranchisement","skews","rundowns","unrolls","dividing","boomerang","gigglier","respects","layette","heads","devised","franny","therapists","ballsy","inkier","passer","capone","housebreak","rachel","portered","palpate","bugles","marionettes","werewolves","primitive","powerboat","polio","wylie","industrial","convenes","sweep","wear","peaks","trudging","manuring","yttrium","hometown","graving","latency","warrant","tinsmiths","preheats","withered","priestley","dipper","overtakes","thurber","softwood","renounced","turfed","immensely","pilgrim","neophyte","mendicant","trampolining","detachable","corralling","haydn","victimizing","pockmarks","goya","triumphs","sleet","whiplashes","inconsistent","slaked","handled","nissan","housecleaned","gentling","alexandra","dallying","kiddos","rayleigh","oxen","boarders","demonstrator","mollusk","micawber","earthshaking","burials","consecration","algeria","sinister","bloodcurdling","garrotted","byte","dungeon","ferrets","trunk","finery","dodos","staid","champagnes","gelt","hedonists","barrier","trikes","lock","scaly","hibernation","lopsidedly","snake","ellison","runabout","rhapsodizing","divinity","bugged","entomological","kazoo","powdered","smeared","shoestring","knocker","galbraith","clomp","rudders","infused","sale","silicone","underfoot","chirruped","beatific","preached","commingles","enchanters","nonflammable","vacillating","autistic","uganda","intruding","expatiating","coddles","attendant","races","paying","confuting","guyed","expanded","tolstoy","contestants","judd","comediennes","pansy","upstage","schoolmistresses","lesion","rollback","rapt","sicked","locomotion","flint","interactions","vaginae","intonation","comedic","totaled","sickles","immensities","leastwise","brothers","rinking","worksheet","impending","mussed","reinterpretation","backtrack","thrummed","devastate","plaiding","accusatory","rafts","stew","infringe","impulses","shuffleboard","decaffeinates","marquez","milksop","artisan","attlee","decide","italic","catalyst","squeamish","transmuted","coffer","sadness","forays","slipperier","bella","dandy","singletons","inflating","pittance","shearer","spilling","acid","mortgager","proverbs","wily","headwinds","murmured","humidified","cramping","herrick","phoneticians","boas","bucksaw","play","falters","overbites","dill","renovators","mush","clockworks","diaspora","favorites","stomachaches","flinch","boston","scrounges","hubert","utters","million","weekended","touchdown","reactor","postcards","brown","snide","banjoist","recourse","deuced","scurrying","chihuahuas","abutments","proliferate","carillonned","saucier","kaposi","amanda","fillet","demographics","eldon","skyed","abut","bernadette","downplays","alluvia","trappers","insofar","breathlessness","insistently","imitative","cede","embargoed","boisterousness","edicts","braise","impacted","ukrainian","lankiest","bounden","trilling","pinnate","unconvincing","kent","indulging","stagnant","piston","cookery","commits","caucasoid","fronds","bootless","clustered","giggled","lugubriousness","intents","elms","boorishly","stalemate","blaine","proportionality","sampson","ethnologists","francisco","headmistress","propel","knapsack","misapplied","ensnare","subtotal","intersected","maud","shooing","pouts","messed","schmidt","liberated","continuations","impossible","unsatisfied","flanneling","unscrupulous","comity","scopes","incised","venial","takes","auction","bashfully","bremen","televangelists","eyesight","ineptness","hecate","sweller","carrot","presidency","hook","nerveless","mastication","abstractnesses","precognition","indent","sombre","fieriness","quiescent","indispositions","shiftiness","caveatted","gulps","best","spread","chews","prevaricating","shoon","manicures","privier","yawns","surnames","solacing","tattering","contrail","downsizing","unnerve","avenger","misanthropists","retiring","roughest","canard","dowdiness","corinne","hilton","summon","whacky","luncheonettes","morals","hunches","ibices","waded","meany","valving","articulations","typefaces","born","wretches","reflexes","tickled","showier","reddest","scallop","rethought","registries","behaves","abnegates","sharping","helm","rapscallions","manifestation","elected","mulligan","unmanageable","exude","centerfolds","unbind","enshrine","skeptically","pained","yeah","frostbiting","nonessential","bakers","exorcist","tonalities","timmy","provisional","bugatti","whisper","nonfiction","snippet","quest","jabberer","mittens","metatarsal","quotient","sponsorship","ferociously","brig","meditation","scotch","mess","saith","appropriately","smithson","emacs","bookending","misses","warmonger","subvert","pretties","ficklest","inaugurated","teetotal","shipmate","irony","canaan","jeopardized","lanes","sloan","connexion","ideals","uprising","sited","lamebrains","patchwork","vocalizes","maura","taller","patronage","barbarians","midshipmen","granddaughter","grapefruits","sideways","mistreating","pensive","foreseen","manageability","lammer","affiliation","aguilar","aunts","ghats","tricycles","privileged","athlete","ls","colonnades","constrictors","stickied","ritualism","catharses","scrappiest","almoravid","tiaras","habituate","merino","witches","handbag","steamroll","conics","marion","forte","rectangles","australoid","gaborone","invidiously","fugues","nervelessly","p","plunderers","newspaperwomen","embolism","splendider","lathes","pleistocene","acceleration","caterers","hauled","fluent","severus","dubbed","rollicked","cal","hastily","scourged","homogenization","leakages","teaches","vocabulary","interpolate","bacterium","ambiguous","virtual","flory","apostrophe","bellamy","lushest","misconstrued","obsessives","romanticizes","feeblest","encodes","anthropologists","clinked","hammerstein","duckbill","expurgations","coroner","unclasping","inconsistently","default","skullcaps","inverses","toadstool","raga","cristina","malady","nonrenewable","zonal","suva","trothed","clarifies","moravia","waggles","flyspeck","blanker","overstays","admired","speckles","fumigates","languished","dieseled","president","tuition","escapees","meyerbeer","futilely","pills","afghans","homeboys","blankness","hackles","footman","spies","horsed","arctics","sunder","mcluhan","secures","withdrawn","bellicose","quibbles","chastens","episcopate","shenanigans","salinity","mending","handsome","tweed","ladle","condorcet","metric","tattletale","rashly","nurtures","contemplation","tucker","moroni","nickolas","mcclellan","phonics","copyright","overwhelms","swahilis","chessmen","amusingly","conjoint","abstrusest","canonicals","ono","callouses","jiggled","typecast","memoranda","tuxes","stalwart","ennobling","nuked","gaggle","followings","beeper","hacksawing","acclimatize","orient","declaims","rising","enamor","doxologies","waistcoats","gustatory","kitchening","overpower","subordination","bone","ricking","yenisei","harvesters","junior","elector","simulcasted","clarinettists","modulators","happily","critic","damage","ineffectual","arbitrates","portrayed","animists","monasteries","abductor","dissolve","befuddled","emergence","laments","naturally","ankle","glastonbury","woodpile","zoroastrian","near","orneriest","temperated","icon","stiffed","penis","reapplied","getting","specializes","bushy","complaisant","slocum","unreadier","stiffest","fives","clumsiest","engineers","plumped","waistline","judgeship","cryptographers","bordello","babar","monthly","possiblest","libeler","cartwheeling","stiffer","monickers","digraphs","salinger","carping","wrigglers","assyrians","sprawls","visits","saunaed","preambling","flairs","obtuse","unbounded","septuagenarians","syllabi","roulette","conjure","clones","aristocratic","orleans","discountenancing","primordials","expropriations","patellas","prurient","walloon","electroencephalographs","contribution","dwarfed","caryatides","billy","presumed","gnarly","chinchilla","shinning","gripped","sigurd","ruff","circumcising","shriveled","cysts","bernstein","storming","calibrations","suffuse","stodginess","brownian","colorblind","aberration","cornered","droppers","heartbreaks","becker","suffusion","ambassadorships","souses","arizonian","oarlocks","accountants","elephants","surer","citadels","betroths","gentian","individualism","venezuelan","tour","rancorously","cabral","constants","parochialism","fustian","coxswains","ironing","rusted","babbling","inapplicable","sedans","leukocyte","opaqueness","bluffs","tuneless","capsized","brochures","severance","hyperventilated","len","shortstop","adoringly","damming","credits","accentuates","lurch","illegitimacy","martens","bleeders","rankle","mortarboard","unify","remark","thermometers","provoked","bittersweet","dame","clarinets","workers","misinterpreted","surveillance","thickset","assaulted","intervening","swede","rustbelt","suns","gasoline","clifton","energized","indiscreetly","soundless","notepad","uneaten","cicatrixes","rhythms","inimitably","subjectively","drifter","snowdrop","moonstone","olga","sabled","eightieths","yonder","inaccurately","madams","flautist","surrealist","persimmons","davenport","retinues","markets","cursing","femora","sharpers","fishermen","cores","clarifying","lakes","sake","sync","impinged","smartness","retarded","grubby","okayed","rustles","croupiers","civilizing","suffocatings","blackmails","recessives","substantives","profitable","delicatessens","familiars","terence","frumpier","maximums","shiners","regals","stieglitz","newsagents","confirmation","inebriation","alva","snowplowing","crudity","tams","gobs","sourpusses","pursuant","busts","angrily","betaking","subsumed","uniformity","mote","censuring","sir","sifting","yachts","sexists","orientation","forewarned","brigs","gyro","knickknacks","retrains","klondiked","nonpluses","contemplative","sears","trammed","serializes","brigands","stratified","burial","sumter","malplaquet","upholsters","parenthesized","dinkies","classy","jugulars","contradicts","sunup","terracing","bulletined","postponements","teenier","afterburners","greenback","dependants","hardy","unbelievers","surrealistic","chaises","snapple","dowry","writhes","expurgates","magically","toolkit","boondoggled","timorously","fuselages","corine","deploying","neckerchiefs","oz","sequoya","waives","dives","reprocessing","clearly","discontinuations","mezzanines","antibiotic","likeness","squabbles","navigable","temples","described","libretto","tanking","perilous","drowsiness","pilferers","beakers","ingram","prevaricate","voiced","procrastinated","vanilla","salween","han","marquises","bewails","cocks","ledger","panty","dupont","typewriter","blackfoot","possession","conglomerated","collects","escutcheon","titting","condiments","smouldered","marquees","interjected","element","outlet","briefing","liquidator","shrieks","nanking","salting","reopens","glasgow","arabians","transgressing","reasoning","bleated","bearable","criticize","whereat","bureaus","dismounts","roxie","tussled","yeomen","equine","cyclist","hugely","felted","messy","desist","shenandoah","sushi","storeroom","hindquarter","opposed","benevolently","archives","luaus","diskette","chiefer","hangover","sparta","faxed","hedge","eddington","pins","bushiest","loco","rooking","lifer","trespassed","swears","husked","darrell","completed","shirring","interactively","places","injured","stolid","secondly","explores","committees","airwaves","littler","sprawling","hydroplaned","uglied","depended","mortared","gloaming","shinbones","outlaw","proselytize","moralling","worn","extricates","exclamatory","layperson","frolicsome","conjugates","arrest","guttural","paycheck","phyllis","alphonse","drumming","multiply","wed","actuating","sidled","sapient","fingers","wantonness","habitually","emulsion","handwork","indeterminate","prig","pareto","wartime","nuthatches","squalider","selflessness","chip","uvulars","debonair","replenishing","naughtiest","renounce","anemic","schoolgirl","dilation","slipping","tape","ginning","crucifixions","indecisiveness","formidably","pokes","resigned","chitchatted","holograms","coppices","dialects","vicissitudes","penologist","shirtwaist","heeds","hybridizes","calliope","likable","adequately","wight","heehawed","exhibits","undressing","seditious","collapses","perishes","peevish","foregoings","harsher","effectuate","halls","petitioned","afrikaners","bright","holidayed","subtitled","comfortable","whoa","aspens","mops","islams","valedictorians","jellies","jewel","gouging","leftmost","breaches","minimal","overcharged","porting","smith","predominates","motorbike","enigmatically","equable","trickery","streetcar","flautists","countrysides","disregarding","pakistanis","grapevine","chicana","maneuverable","diction","falsified","peppering","murmurs","abated","radiance","maharajas","pediments","entrants","friedman","discombobulated","misprints","reimbursements","andropov","fizzle","stress","sifters","establishments","chippers","boomed","describable","contused","moscow","stonewall","meander","kaleidoscopes","subcontract","physiognomies","bayeux","telegraphic","emotional","govs","crotches","jayne","morison","funguses","schlepped","rhubarbs","bump","banged","shrieked","petal","phooey","piercings","defending","lapidaries","muffle","halcyon","transmitting","smallest","tottered","bossily","ruling","sequencers","lowest","overtaxing","misalignment","plutonium","paroling","windsurfs","annals","nasser","gomorrah","dispute","intensity","unwillingly","witt","stockiest","addends","jacklyn","kind","giauque","reborn","discontinued","headdress","favorite","vivaces","keith","descriptions","secondarily","whinnier","kismet","underrates","restated","guessed","inestimable","irritable","managua","deft","blockbusters","ascribes","melodramatics","cormorants","deliquescent","unpins","twits","confers","bargained","tide","floundering","censorious","gouges","magistrates","reynolds","sequels","as","incinerator","swathes","candelabras","spelling","scratchier","dejecting","implementation","reaffirms","blanches","western","ebony","reason","appending","polluters","jove","gambits","corpuses","grittier","rhetoricians","distils","explicate","jansen","jolt","curing","medicine","tender","supplanted","andres","scrofula","glopped","indulgently","pilchards","scuffs","harmonize","hoagies","xmases","witness","caller","detail","mayo","misidentify","bath","disports","filets","cheapest","scorpions","prevent","promptness","looping","authenticating","cab","reamers","protestation","outgrown","devoting","naphthalene","quarrels","rambler","garment","councilor","chronic","acceptances","resurrection","southpaw","raceway","diffidence","uneventful","mecca","cheri","scarceness","nebraska","elfin","bookies","dietary","auditory","eggo","articulateness","steadying","boulders","impressing","misdo","greta","comae","horace","pedalled","tram","sahib","fetishists","dumbness","belonged","rotunda","moons","falconers","rail","dispels","redeemer","petitioners","forewent","onshore","precincts","detoxes","quintupling","befouling","knit","balls","eddy","poetess","divines","candor","tomcats","weapons","unsnaps","viaducts","chatted","susie","reconvened","condemns","thickeners","collect","rock","apothecary","clue","mulberries","territories","pups","earthing","pledged","coffers","wells","extractors","mistiness","sterility","microfilming","anesthesiologists","miss","volleys","nabs","foamier","wrested","minefields","empathizes","lakshmi","victualling","huffiest","shirrs","centralizes","inapt","besieging","babbitt","psychoanalysts","gybe","enlisting","discomfits","helicoptered","sukkot","skidded","avoirdupois","horsewhipping","khulna","plateaus","rwandan","emerson","copycatted","herald","bemuses","hesitate","gleefully","siestas","tonsure","generals","flunky","eyes","indivisibly","hydrangea","berne","gag","redesigned","insinuating","reenters","remote","douche","budget","afterlives","shootout","shortbread","eatables","omens","abelard","waxen","presaging","platforms","beachheads","redeveloped","praia","peppy","indonesians","plated","abouts","sunbathed","mobiles","playacted","files","verlaine","deceptively","townsmen","acetic","resorting","ritually","rhinestone","neologisms","opposition","cauterizing","sprinkling","theoreticians","khoikhoi","peahens","compensated","shrive","roughage","drastically","objector","manliness","lanyard","espied","saturate","canards","launderer","hightailed","hauler","frosty","blithely","astrophysicist","squirrel","derailing","huffily","suture","mahatma","egocentric","reverting","doctors","anubis","flatly","minuter","staterooms","delineate","rive","offbeat","principals","micra","invoices","menominee","cartographer","ujungpandang","notoriously","reapplying","totalled","whiskers","crassness","incoherently","grassiest","sponging","protects","numeration","preppy","ceased","powering","recreates","musicians","header","bounteous","negligently","berenice","trustfully","methinks","preface","disproportionately","comeuppances","firefighting","synced","disturbing","tuscan","robles","factored","aircraft","nazca","shrank","panhandler","oversleeps","huckleberry","countersank","hopper","paneled","kayaking","billowy","inhalers","sapped","rarefy","thunderclouds","rockets","imperiously","dregs","hockshops","stemming","nymphomaniacs","tightening","refreshing","ryder","persecutor","win","darted","benchmark","abuzz","incises","brunei","scuttled","astronauts","pizazz","covetously","maltreating","barbarism","manila","zuni","humanizes","microcosms","fellow","exonerate","geckoes","foregone","cuttings","butterflying","underflow","saintliness","slather","toddle","isobars","spelunkers","rigmaroles","offings","interning","representative","luann","pursuit","tennis","marijuana","reconvening","shapelessly","strum","kilts","brutalized","gloom","rajas","courses","poising","disclaimers","baluchistan","brief","recognizable","gore","outermost","ascertainable","pitfalls","posers","vegetable","inglorious","mottos","hurtle","heartbreak","chichier","bolshevist","cockscomb","delineates","spouted","asides","chrystal","presentiment","pekings","teargas","classes","foamed","distinguished","sherlock","purling","apace","goalies","specifiable","enfranchised","cycle","crunchiest","ericson","membership","sheraton","reaffirmed","lassie","readily","gunfire","archaism","bulged","watercraft","internal","dishonors","caviled","volcanic","blahs","instances","yammers","colombians","mussier","allegheny","contraband","heinrich","dogged","impossibility","syntactic","infuriate","max","specifically","brent","eugenics","ankhs","icelander","woodshed","emblazoning","thru","overhearing","ultrasuede","hillock","twitching","dishonoring","gridlocking","grouches","sequestering","pressurized","freeloads","ursula","carpet","formulation","aliens","warbling","frazzling","furnishes","abridged","theocracies","karamazov","abridgements","adipose","wideness","lacing","adversaries","prohibitions","nosy","inopportune","radiotherapists","extortionist","relabels","bullish","diagraming","bracing","scrounged","seniority","congregationalists","incompatibles","cavalcade","allergist","stippled","salaciousness","crazily","snuggles","deserve","squashiest","waterfowls","carjacking","trampolined","sister","swankier","kazakhstan","blaspheming","kidnappers","disorganizes","elongated","glopping","windbag","buckeye","rebellious","leaf","biographer","verily","downpours","baxter","qaddafi","suffocated","drowns","doses","rebated","amplifying","paprika","played","midwifed","nightfall","rocketing","solemnizing","pacifiers","alaska","snicker","small","hotshots","jumbos","leagued","subpoena","sivan","overbalanced","rasalhague","washbasin","imponderables","packers","consecrate","majorettes","clarendon","fain","pettifog","bessie","reword","genoa","storey","ezra","shutting","legitimately","obsequies","leggy","diodes","mechanizes","buggies","disavowal","jaunties","johnnie","ladyship","epiphany","probabilities","bucketing","tomboys","slackens","womanizer","venn","toddling","hustling","tattle","bikes","mouthe","daryl","succumb","geffen","honeymoons","denmark","caucasians","introverts","verdure","plausible","conjuror","insetting","aftermath","withers","miller","interdepartmental","decalogue","liquefies","recreated","holographic","median","pidgin","matchless","skinnier","milligram","psychic","titted","consecutive","reject","inhales","colossal","tintinnabulation","virgil","fiduciary","friday","resumptions","rambling","ilene","bordeaux","swaying","giacometti","succeeded","hobbies","photocopying","reinvests","chiselers","respire","dodoes","vaporous","gloried","unproductive","salami","argots","allege","mutinous","mirfak","keepers","hocked","primness","tubers","improvidence","soil","discontinuing","landslides","mollycoddling","smokier","corolla","ripper","splenetic","convening","twangs","snootiest","rousing","stablest","ordinarier","windiest","quizes","tallahassee","hutchinson","becomingly","attentively","sourcing","guppy","demands","lupins","ladders","liechtenstein","emancipated","toughness","maladjustment","bringing","clopping","acrylic","undervalues","bogy","juggles","proprietor","assertions","snobbishness","overcautious","bernie","pylons","enmity","westerns","hobbyhorse","edgy","probing","footsore","cagney","rumpling","engorges","holdover","lyman","ambiguously","boding","adulterous","intriguing","capstan","punitive","stiletto","monotony","weathercocking","torturing","sixtieths","inkling","nutritionist","akron","habits","eyries","ukraine","curlicues","sate","rosendo","seclude","commended","truthfulness","fender","shekel","unrelated","crouch","crueler","kiss","intimately","encumbered","shell","spotters","nosegay","goatherds","pasadena","dropouts","forgathers","predestination","gigglers","invulnerable","negros","workman","onomatopoeia","leaking","immediate","retraces","subheading","fanciers","wield","sacrosanct","sauerkraut","chinatowns","bimonthlies","mistrial","watchtowers","muddle","copernicus","nonuser","amassing","infantries","lead","tantalus","anemones","callahan","bombastic","noise","giantesses","damien","nietzsche","sects","limbs","attire","thickest","deducible","space","fenders","blackballs","slashing","signatories","bast","mousetrapping","motor","bothers","trunks","destine","coursing","kipper","dressmaker","ghanaian","sheathed","sward","mishandle","ferrari","georgian","nearsightedness","chestnuts","basketballs","suffered","yardarms","verses","apothecaries","tequilas","excavated","beauregard","floating","unruliness","certificates","tens","literate","watchfully","tartars","moaning","currant","instincts","codify","sachet","looks","bedrock","roundelay","candidacy","tragicomedies","hollyhocks","pummels","sheldon","swayed","misfired","botany","vane","retrospect","bully","divots","tailgating","outbreaking","varmints","sorcerer","terminal","stein","inland","suggesting","octavia","catalysts","cover","pulsated","incommensurate","northrop","cranked","preemption","sturdily","melons","unicorns","shadiest","mythology","kaboom","orate","soppings","fountainheads","chitchatting","jo","idealism","accordions","constrains","steakhouses","acquited","underlying","tunes","patagonian","untilled","thankfulness","pummeling","undergarment","rodger","walkout","casualties","slews","hiking","funded","catchall","critiquing","flirtatiously","soberly","cherry","disbelieve","longhorn","scuttle","yell","fit","discomforts","cheeriest","masterly","vapors","sulkiness","sign","obsequiously","tryout","stethoscopes","radiators","wrangled","subverting","grievances","typographical","oahu","kaolin","constellations","transnational","efrain","pylon","committal","disables","climatic","taoist","moldiness","scrutiny","mulatto","misstatements","brontosaur","viticulture","waistbands","sharks","trowel","hall","scuppers","stations","buggiest","sole","slyest","london","smokies","shuttlecocks","irreverently","sunfish","befogs","arraigns","uneasy","cadavers","brights","photojournalism","commissioners","gate","idealizes","chaparral","veronese","misguidedly","maker","biophysics","maced","excite","carousals","apes","cruel","bohemian","epigrams","allocate","goldie","grams","porfirio","wears","senecas","weirdly","synthesizer","creditor","chowed","smithies","omnivore","cocktail","isis","derailment","outspokenness","immigrating","snivel","outgo","stopwatches","vibrators","dustbin","gentlest","commune","unregulated","vaccinates","stern","coagulates","pyramidal","ill","intensifier","sweltering","maritza","needlework","stolidly","bantams","missive","relearning","honeycombs","straddles","portraits","active","ceiling","repackaging","malfunctions","bavarians","emanates","flaunts","revision","ceded","housebound","adulates","polarize","supine","bites","rescuer","exploratory","deadlock","abode","twingeing","libertarians","chan","beiderbecke","crannies","syncopating","crosspiece","titmouse","relationships","scumming","synchronizations","grandiloquence","hellenization","cavil","derision","normed","druggist","preternatural","arider","adapts","leopold","rhapsodize","conquests","succulents","overpaying","holiest","offering","jordanian","trains","saleable","credible","versus","graybeard","freedoms","moseley","ethical","sanctums","belched","cremated","persuasions","resonating","doggedness","emil","riddle","yeasts","eyelash","tremolos","keenness","romeo","gypsy","undistinguished","oliver","predicaments","joking","raconteur","sultanate","lodges","nonesuches","coopering","omelette","quito","quaffs","quadrilles","stream","compiles","camellias","oxide","malfunctioned","jaywalking","gherkin","dispatcher","aztlan","leonine","stallone","argonne","messieurs","envisaging","pairs","privates","scalawags","choreographed","duplicates","oath","celery","undue","engenders","jersey","policyholders","hermaphroditic","encrusts","jalopy","diversification","padre","ridding","waterbury","fluids","pillories","preciously","fraternity","contends","collegiate","overstep","corroborate","struts","halloween","leonardo","pharmacopoeias","methodically","rural","marquetry","stadium","climates","deviation","saks","dartboard","providential","reissued","bukharin","deadlocked","addicting","lawless","rumble","security","gags","tobogganing","hereford","stucco","minibikes","renovating","tanned","admonishments","mccoys","veblen","capitol","earliest","serf","snippiest","clothes","exhales","seesaw","obelisk","spacial","carolyn","vantages","loaf","robber","weepings","tactlessly","transition","iterates","peremptorily","pummelling","wiener","pooching","symbiotic","vine","cried","remorseless","engorged","crusaders","therapeutically","locust","prominently","shagging","biblical","unplumbed","remiss","grovel","disgustingly","lifers","branched","crept","marting","autobiography","suffragans","hark","anesthetizing","summoner","expectancy","semen","parents","canvasser","tenderfeet","dyspeptics","whigs","straightedge","running","sylph","poconos","textually","unabated","trickster","frieda","stagnates","waterloos","wring","punched","postage","ghostwritten","extirpate","transships","ricardo","rivera","reclines","maestri","clampdowns","negate","whiplash","authorizations","coruscating","brigantines","meredith","ringlets","gobbed","unpretentious","levelers","glowing","cursedest","retooling","dowagers","dolphins","poem","incognito","deice","sirs","impishness","apparitions","interlude","lottie","link","glassier","underbidding","patrolwoman","parapsychology","pilings","chemise","essen","flummoxes","disbelieves","bravo","slouches","penal","countersink","mole","absorbency","doings","conjuring","medial","ropes","iroquois","kirkpatrick","stigmatizes","pillorying","lunatics","scream","crossovers","splays","deportment","empire","flatcar","teaing","declassify","philippines","pear","berliner","goldenest","priced","khan","flo","mauls","dimmest","yells","puns","severed","erasing","foreordain","meddled","gel","misconducting","untouched","flickers","extraterrestrial","obituary","buffalos","prevaricator","hoorayed","parallelism","phoenix","totals","liaison","institutionalize","tupperware","disenchanted","organisms","pirouetted","kelvin","bewared","misdoings","sandra","malt","lavish","pimento","elizabethan","earplugs","bassinet","luminescence","mahabharata","oaten","coolant","cr","associated","policies","passport","exists","fertilizes","apprehensive","lara","move","beauteously","razed","aggregation","dainty","osborn","scoring","swift","climbs","schwarzkopf","economics","scrumptious","di","ferraro","microwaving","liverpudlian","influences","sandhog","relegates","potsherd","jaywalker","heston","quivers","privateers","refinement","incontrovertible","syriac","commodes","sanctioning","cooperates","tattles","pakistan","adz","fascinates","capitulating","unwarier","monarchy","ascertained","doping","percheron","wardroom","evaded","accession","loophole","restarting","dryer","derringers","handbill","brunswick","dealt","quiescence","changed","instigators","racked","dram","floorboards","slap","implicit","pigged","disestablishing","squishes","obtruding","willed","gusty","traumata","lighthouse","teen","spinster","sharpest","majors","fluoride","maleness","jared","repaint","jarlsberg","matisse","cicatrice","emerge","transgressions","impregnate","definers","supposings","evelyn","karl","centigramme","loner","relinquishment","claustrophobic","display","pubbed","dewberries","besieged","grosz","scanter","sublimely","ind","ophthalmic","schoolteachers","o","mannheim","hodgepodge","unison","overselling","yessed","blocked","agreement","tracery","promoter","handicaps","search","straw","opinionated","anorexics","koshering","orthopaedist","cranmer","tributary","annapurna","regrets","harrison","giants","kathy","randolph","chairwoman","anecdotes","arno","spaced","throat","mondale","devastated","sit","acquit","zincing","silenter","disenfranchise","aggravations","reamer","authentic","mythical","overburden","anaemic","emulation","shop","preoccupying","adjoined","sparks","receivers","aggravate","ministrations","thirteens","prejudged","rightly","august","leno","processors","commerce","marlboro","leveler","convinced","anthill","tethers","timurid","fatherless","unfeelingly","remodelled","schoolhouse","gorky","rummaged","gladioluses","blare","communicants","enameled","cleopatra","fissures","buttery","reverberates","pennon","uneconomic","permanently","entrenchment","propound","schoolboys","gobbling","kerosine","backpacks","invoked","broadly","mange","semaphoring","camerae","poured","brattiest","celestas","remonstrates","ngaliema","falseness","paraplegic","cramps","unitarian","dinghies","maddens","imbroglios","sergio","southwesters","chasten","fleischer","conjunction","museums","unnoticed","rebirths","compulsions","carotids","equitable","hypodermic","sizes","critique","spanking","intransigents","inset","peron","exterminating","protozoans","ideographs","louisville","stationed","tormentors","credence","curviest","misdemeanor","tranquilest","satisfy","subsistence","gina","montages","rifles","bequests","tendentiousness","impasses","chimney","register","salamanders","afternoon","expensive","defining","glandular","chagrined","voices","olympians","disapprovingly","editorship","shillings","validated","lame","rupees","wielded","voled","maxes","targeted","firebreak","substantially","domingo","outmaneuver","chalet","ulcered","anyplace","immaterial","placebo","untangles","ar","unnerved","frumps","incarcerating","misapprehension","fattiest","preventible","jennifer","tan","intercontinental","white","latticework","flowers","spitz","insurances","institutionalizes","praise","insuring","flinched","inclement","handsprings","codependents","armholes","smashed","cymbal","depresses","gentler","szymborska","everlasting","lice","kurile","reduction","atkins","pimpliest","grip","instil","extraditions","nonplussed","flatteringly","galahads","reprocesses","whimpers","gusted","sullen","mufflers","plinth","intones","tuned","revitalize","bataan","unearth","upping","naughtiness","enquiry","incorruptible","reassesses","rough","mitterrand","tranquilizing","occasioning","bevy","modify","brawniest","punt","brenton","circularity","juarez","purebreds","disparagement","produces","wallow","occurring","dickers","authoritarianism","leopard","stout","cottonwood","chichiest","moisturizers","pallet","summeriest","grilling","garlicked","very","enters","bewitched","collides","sc","fishbowl","alkaid","calicos","endorsements","clavicles","corralled","brocade","mortgaged","uncontroversial","undercharge","poise","plagiarisms","grebe","aggrieve","stubbly","croesus","echelon","ascribing","blackshirt","jeremiads","investigations","naturalized","cyclamens","fillers","paraguay","structural","ho","massive","lubavitcher","repletes","poisons","migration","sublimer","tutors","peiping","centenary","devoured","dare","want","entitling","church","paucity","midway","slops","sidekick","upbeat","stepson","behemoths","campground","windswept","sunbeams","monuments","costlier","shockproof","admirals","teach","fallout","defaulter","oxymorons","saunders","trinity","irrational","finns","yeats","tannest","hoarse","gazetting","strangled","suggester","prefabbing","jigsawed","vehemence","jointing","halfpennies","chumash","indecentest","riverfronts","dustpan","idlest","quieted","chaplains","ariosto","overprice","ginny","chronicle","lap","glassiest","delegate","patriots","multifariousness","warms","signifying","refashions","streetlights","customizes","bipartite","rankles","cracker","castries","erogenous","cleverer","peddle","wartiest","coven","refundable","resurgent","ton","xenakis","adulteress","prevaricators","saloons","counties","wanton","gleaned","stilettos","laundresses","rube","irritate","consults","remarkable","gunsmith","formosan","neutralizer","tanners","dissonances","hatcheries","bereaving","elevations","strumpet","loadstone","antibody","upstarted","wainscottings","gratefully","prepayment","spine","embitters","firehouse","nipple","abhorred","reveller","bowdlerized","bushiness","scrapes","surplussing","tylenol","garners","astonished","workplace","conway","deforesting","pyxed","transship","persons","bogging","trojans","areas","beatings","plays","denominators","aimlessly","ricochetting","scan","voluptuous","atrocious","epiglottises","modernize","tourmaline","nimbi","honester","sleuth","repartees","songs","uprooted","deacons","cains","unloosed","discourtesies","disclaim","permutation","colitis","acclimatisation","alcuin","hypothesized","crisply","beggars","critiqued","nuder","beat","jocked","daguerreotyping","shuttlecocking","skited","shellacking","jeeringly","recollected","gateway","duracell","militant","faithful","straddled","hairless","turret","supernatural","adjectivally","smouldering","patiently","inherited","pebbled","connery","equivocation","strews","fuzed","daniels","nostrils","petrochemical","obloquy","goldfinch","inamoratas","librettists","shaffer","dusters","urban","affirmatively","merrick","interoffice","uriah","lamasery","tamely","irish","disgruntles","commencing","grus","mightier","soddy","propositional","victoria","bemusing","illiterate","altruist","martyred","praiseworthy","puree","poring","disappoint","fencer","giggling","toffy","duran","william","christies","incisively","checkpoint","conceiving","tapestry","incarceration","alleged","salivated","loam","modal","assumed","purveyor","bonbons","exacerbated","leave","devour","pork","lapp","milking","converses","laces","crustaceans","drivelled","reprobate","outings","shrinks","saddening","pinch","unproven","shareholder","blacks","bisect","tied","bloodshed","profanity","kannada","sara","exhibitionist","roughened","condense","caption","yellowing","scrip","despicably","holdup","ruddied","interrogator","groggy","tops","telekinesis","cadaverous","perfidy","promulgate","carina","dusted","robbery","undresses","phalli","bilge","aggregating","megaphones","fatten","waste","resignation","indubitable","eject","kinkiest","tiffing","moping","kebob","poky","inquiringly","wove","countenanced","idle","mosley","enrico","motherboards","shantung","unbuttoned","spheroids","salvaged","respectively","westing","coccyxes","overdraw","treetop","juneau","stall","backer","cognomens","angelic","introductions","telecast","beep","towed","dukedom","spinoff","motto","tantalizingly","untiringly","tousle","impeccable","rolodex","slavs","kayaks","proposals","departure","hex","locating","bypassing","drawer","misused","cather","marmot","pattered","superlative","retrievable","frostiest","clamored","ethernet","mont","coexist","phalanx","complicating","basic","anthologists","yevtushenko","torture","ines","mullins","unfaithful","pecking","costumed","isidro","brotherhood","carlene","humblest","showeriest","portentous","puzzler","bailout","dropsy","diffuse","blindfolded","uproarious","upanishads","smooth","paunches","liquefaction","wiggle","rejection","particle","aeries","ceramic","undecided","compassing","appurtenances","gyrate","skinner","rostrum","retreated","composing","ares","tenements","roadrunners","misapprehending","mozzarella","thorazine","wallaby","liebfraumilch","frameworks","elroy","crams","reanimate","whistle","waving","flaunted","vocative","quiting","edelweiss","recompiling","superintendent","musician","pillioned","cobble","tee","scatting","beaufort","lyceum","putrefies","exonerated","playwright","constitutionals","neutrality","carbonated","thruway","redistricts","decadently","nicklaus","barbiturate","domicile","escalator","turncoats","geriatric","dittos","interceding","boozes","complimented","pomerania","literary","marxisms","handicapper","guises","sublimes","fountained","materialism","lentil","apt","workload","dudgeon","screwdriver","concerti","zoomed","ailerons","counseled","rediscovery","hothousing","goth","undecideds","symbolics","novokuznetsk","esteemed","lambkins","treachery","manacling","evaporated","curio","sanders","viola","equivocal","clumps","jujitsu","egress","portrayals","acclimated","graves","weirdness","caprice","film","romp","negotiable","fillies","tucking","troublemaker","communistic","extemporizes","flowery","forties","ghoulish","spaniels","merrill","sundown","emeries","mandrake","been","conceptions","knitting","kiddy","blink","lindy","doweled","disassembling","burger","genii","manges","oligarchs","caesuras","asphalting","collision","chatterer","gendarme","ruminating","safekeeping","wreaking","carbuncle","boor","inducement","belay","bangladesh","predeceased","marxism","humors","coppicing","empathy","roomer","upstreaming","bales","frontiers","dredges","timezone","mouthfuls","media","downwind","carollers","postludes","insurrectionists","infrequently","wee","syphilis","wanna","stutterers","peritonitis","mar","spartans","taprooms","memoir","blankenship","misbehaves","predictions","wino","exuding","paperbacked","concludes","southbound","uncompressed","opalescence","stoker","lawfulness","butlering","repudiations","maxima","extensional","sufism","zens","corkscrewed","beseeching","ariadne","commandments","toledo","strums","jangles","rommel","consanguinity","afire","punchy","yippee","cataleptic","cases","retrospection","insecurity","bequeathing","presently","assured","kirchhoff","collections","inquiries","extraordinarily","terkel","geed","klutz","campaigner","mainsail","upsurges","fortune","pods","fields","prejudiced","shredder","yugoslavia","pitches","guesstimate","dirty","negroes","psychological","baccalaureates","mount","mazarin","floppier","villain","preventing","mutual","perforce","scientist","initials","bisque","bloopers","occupying","repayment","stratifies","wiseacres","girlfriend","sisal","fleece","alphabetically","waxwings","castaway","minnelli","brainstormed","frostbelt","overwriting","leisure","entertainer","recast","deflates","grooves","concedes","conveys","contesting","thermostat","michael","constrict","posteriors","administer","shaped","brueghel","displeased","bronzed","lambskins","disadvantage","haiphong","weirds","misinform","absurdities","departmentalized","pinpricked","distances","electorates","dispensaries","motlier","rarefied","revokes","herzegovina","damaged","hume","discoloration","misjudgement","liberian","irking","tax","surfaced","perpetuation","shows","terminus","doritos","ensembles","tenderized","choristers","undertake","celebrant","finaglers","debora","sprinting","ladles","drawings","junket","burks","spelunker","atlases","ginsu","lovings","squirm","truncating","newcomer","conference","pena","narnia","adolfo","appraisals","ariel","hampton","crinkle","situations","juliet","digits","vex","preeminence","anchovies","debarred","weller","bathed","congenital","sandwiching","palliation","undeniably","settled","included","unorganized","staggers","oxnard","senator","salesmen","slightly","orlon","surreptitious","traditions","paige","annihilation","joyrode","qingdao","deadline","vaunted","hogwash","federals","chaotically","lettering","tunisians","indisposed","svelter","chaplaincy","preens","ascents","allegros","heaviness","socratic","vesper","sana","ascendent","tumult","biannually","welt","slaphappiest","addict","awing","silting","juggernaut","comedies","panmunjom","prizefights","heifer","ferocious","percale","inexpressible","thermostats","oneal","sunblocks","lusciously","bop","exigencies","griffins","loop","braves","reception","punches","popularizes","vivaciousness","serialization","actively","soggiest","thant","toshiba","rookeries","civilities","misconstruing","forgoing","pi","polygraph","aisled","compresses","browbeating","skywriters","scrimmaging","caparison","custer","sancta","shoppers","cattlemen","batty","espousal","trumpeter","fathomed","acquiting","residuals","seminole","penny","adapted","chanter","inescapable","citizenship","headwind","cowslips","nightshades","tameness","brownie","kramer","magnetosphere","skaters","defies","vowing","annexing","amortizations","sunburning","execution","cordite","patinas","defile","jeeps","stewardship","projection","macroscopic","endowment","vocalics","discussion","printable","baobabs","colfax","squirrelling","kaput","overabundance","burglarizing","culbertson","kyrgyzstan","voodooed","treacherous","muppet","elinor","moonshot","castaneda","gypsies","playpen","backfield","raffish","loudness","pinkies","dijkstra","chafed","bridgeport","phantasm","bronchus","soundproof","clinic","shelving","prostitution","foretold","amerindians","stairwells","exhaustively","kneads","inconstancy","negating","pinwheels","males","metrically","proverbially","ripes","recanting","diarists","thump","ads","ottawa","useless","properly","route","pusan","wafer","rubied","crankcases","regret","hannah","wiesenthal","load","rewinds","partnered","phenomenons","nominates","chubbiness","sensible","elba","incurring","reopening","earthquakes","bodyguard","record","matriculating","dive","sogginess","overgrows","bankrupt","quickened","rekindling","angularity","offends","oscillates","lives","ported","pompon","warehouses","manumitting","easterners","resound","demoralizing","knavish","sq","doorknob","allegorically","orphan","winded","chanukahs","hoeing","dogwoods","diphthongs","disemboweled","jasper","seraph","countermanding","sises","druid","manful","analysts","saints","disassociate","sniggers","battlefield","gustavus","optimism","combs","rebuttals","casablanca","frankie","marisa","logotypes","cloning","ridge","frye","instal","darvon","knackwursts","abutting","equivalently","tat","hermit","layettes","poxed","rustlers","enslaving","postmistresses","tucked","mig","wafted","proofreading","flypaper","toxicologists","carmine","harmoniously","corpses","policemen","gauche","encephalitis","prismatic","coronaries","fluoroscope","catapults","slothfulness","like","theorized","vulnerability","tighter","gnarlier","nefariousness","publicly","dissed","brandeis","jambing","conjunctivitis","blench","multiplicand","sumerian","nonmalignant","jaunted","accompanies","braved","jobless","languishing","towelled","realtor","vitalizes","coworker","trickling","climactic","snip","comprehend","bloat","balloted","avaricious","pivoting","blackmailer","recharged","decal","turboprop","reed","garb","magnums","hotbeds","outreaches","bishop","prophetically","exercising","sported","vivid","mushrooming","lydia","inadmissible","aviator","rastaban","protean","chlorofluorocarbons","improvises","organized","nicely","golfers","tsars","snuffle","wastebaskets","buffers","willemstad","parka","forecasted","substantiates","ptolemy","haberdashers","weedier","outstripped","horthy","mamboed","fireplaces","churchgoers","cringe","shout","staci","commercially","fungal","correctives","tearjerkers","execrates","push","woken","tin","employes","pushed","earwax","flakes","liturgies","global","open","pompoms","callow","barbarously","physicking","dermatology","overwritten","rewinding","proterozoic","simulcasts","domesticating","individually","muriel","rhyme","developer","crozier","anonymous","symbolism","priggish","archaisms","murderous","teeter","prop","abounded","epaulettes","germane","morbidity","sexiest","zworykin","lyly","limit","undertaking","reincarnate","nevermore","reefer","insisted","fables","spiraling","dispossesses","resembles","frippery","shortchanged","squiggled","shagginess","predecease","persecutions","wheal","frosted","scarifies","without","anticking","excellencies","embellished","mood","squashier","snouted","strategy","screams","chitchats","naughty","bailey","ambitiously","uninhabitable","staunches","impeccables","sidewise","digestible","haloed","antagonistically","chartism","evolving","weeknights","pothooks","heros","fishhooks","modicum","handspring","mainly","ousters","viburnums","criminology","finishing","analytically","apologies","christens","abstentions","mci","nacho","reports","monstrosities","nongovernmental","copacabana","leg","misconducted","irks","enjoining","unmentionable","starving","brayed","pummel","jiggle","spooned","pulsation","ambidextrous","dendrite","firewater","topmost","corpora","designate","legislator","schedar","portering","politicked","backdates","deluges","locales","schmuck","lyell","mikes","doorstep","perked","centenaries","sprucing","rainier","jesuits","proclamations","kremlin","salads","beauticians","eels","frying","godzilla","boatman","menopausal","heydays","newsier","incalculably","rubbers","looneys","vaccinate","glissandi","peyote","climax","stools","bloods","unintelligent","revivalist","conditioners","kidders","abscissas","lorrie","third","workhorse","setups","visioned","shorn","windmilled","stochastic","beebe","doubter","cropper","personages","bettye","overawing","flanks","nonviolence","kidnapper","yups","megaton","stevie","perusals","halters","emote","overprinted","phalanxes","deltas","formatting","virulently","wingers","pepperonis","everett","alta","riveting","varlets","wader","mesas","unlatched","unicycle","progeny","firebrand","chickens","yelped","re","elks","outflank","iniquitous","boleyn","births","news","modem","deacon","cuspid","namibian","milwaukee","sulfurous","celled","incubated","sparkle","dins","begonia","yodels","disconsolately","warty","kristine","flyover","perspiring","upton","eglantine","implements","jitterbugged","randomly","imminence","refocusing","tarzan","cockscombs","enrols","abilities","bulgarian","sporing","terming","fulminate","guevara","shuns","inked","truckload","audiences","fijian","swamps","inflict","disbelief","worrier","websites","footsteps","jaxartes","faggot","bring","bagging","systematically","sobbing","ranter","polished","navajoes","reuther","binging","sagittarius","kim","bookstore","keyboarding","dutchmen","backboards","alternatives","decided","depreciates","fates","sorted","adjacently","turnover","breaking","biospheres","gavottes","fulminates","hostessed","ergs","deputizes","millay","speeder","adhering","hagiographa","lugging","bustling","circumspect","romping","galleried","defy","ronda","robbie","kite","cervical","connectives","shaven","loanword","muesli","veterinaries","courtesans","sargon","goofing","nephritis","cuddliest","tided","avoiding","torched","donutted","dolling","furloughs","flavors","hyperspace","milk","quartet","sterning","autoworker","countersigns","ruskin","confectionery","splashy","distinctions","liquidation","rhomboids","efren","counter","rapture","lessened","predisposing","specializing","abductors","diagonally","alloy","infectious","bandit","incarnation","biology","kohl","quintessences","guthrie","parody","sours","obscured","ramification","undertakers","untold","greasing","thawed","crumbed","adoration","permanent","glass","fuzzes","intentness","wilkes","amaranths","embezzler","classed","mincemeat","reiteration","innocuously","calamines","unexceptional","eucharists","fratricide","microphones","salk","aspic","religions","surmount","cage","ostracism","inspected","stopped","sloping","gurgle","sic","helpers","carets","kneeing","appraiser","sedater","rubicon","plumb","twofer","cinematic","ballistics","criterions","walk","undisputed","slitted","bled","yowled","whets","reentry","mestizoes","noels","trestle","dodged","missouri","hoffman","thanksgivings","moder","damascus","batting","spoke","dotingly","penalize","biochemists","togae","unsaying","auschwitz","cameroon","reinserted","hellespont","enzymes","underworld","donning","downstream","yearnings","cozily","perceptive","wrings","congesting","forename","pooling","hectoring","gritty","armatures","liens","infinitesimally","consummations","austerely","knuckle","casualty","harpsichord","incoming","previewed","amniocentesis","situates","raffia","scaramouch","unenlightened","relationship","stirrups","sabbath","chirrup","tourney","pupas","tone","suffers","falling","burbank","collectibles","soaping","rehearsal","crosier","syphilitics","decrepitude","uncannily","axiomatically","modulated","middy","intoxicate","oklahomans","buckskins","divorce","distributes","hellenize","peters","locate","saar","verbals","keg","bombardier","bribing","grosses","sag","ivanhoe","hollered","paraphrases","grouch","importunes","underbids","diehard","selectman","slugging","caisson","carcinomata","supering","inhalators","spittle","approximates","heep","predecessors","inlay","indecency","strewed","multinationals","ogbomosho","wavy","managing","recombination","cottaging","toils","decriminalize","netherlanders","wannest","shinnying","sticks","kilos","franchised","toleration","vista","riping","timeworn","ticonderoga","ventriloquism","trapping","competitive","morton","pierrot","gallstone","milkweeds","viscountess","atonality","scuffles","hindustan","streaked","overreached","disproportionating","rudest","kilometers","storekeeper","fickler","finish","discerns","frilliest","horseradish","vermont","coeducational","fairground","cavalcades","calfs","cubbyholes","acrux","clop","poesy","tramps","disowning","scalloped","katelyn","ostracizing","warping","douay","infraction","nominations","housebroken","crossbeams","pulped","goodyear","notation","loathe","positional","widespread","belmopan","bias","breadfruit","problematical","gringo","quicker","academically","loon","alec","smile","hotels","grandstand","rape","walkway","nonliving","monarchic","napes","programmables","agonize","grandparents","cherished","libidinous","battalions","cram","readout","skylights","subsidy","landowners","sheering","yukking","reinterpret","dot","epithets","malaria","mixtures","calico","proofing","coped","candling","sensitiveness","facing","stye","gabby","campinas","hums","collectivize","ringlet","orator","racecourse","deejay","triviality","gall","laval","relabeled","forbade","quenched","irksome","microwave","sinkholes","edna","baited","joyfully","coherently","bloch","snuffboxes","mortified","perorations","rat","flossed","nicaraguan","mooring","wefts","braggart","suleiman","chastity","ronny","subcutaneous","woefully","cavalryman","bets","colgate","pizzas","elegiac","tame","unitarians","simone","lousy","resuscitators","presumptions","impress","seminars","armand","ionesco","mcveigh","catalan","technical","plumping","nurturing","cabbies","tenacity","drawling","boggiest","thai","headhunters","lodestar","brute","grayish","gushy","pancaked","politicize","college","algebras","medically","cleanings","nahum","sappier","mosaic","parmesan","spews","colludes","suzuki","squirmier","mcmahon","trouts","misdirecting","culturing","sledding","waifing","nilled","lees","blent","conformist","concord","sultriest","stigmata","scriptwriter","machismo","ceases","unthinkingly","confidence","refined","braises","lethargy","accusative","feminines","divisors","deportations","immunize","bloodhounds","quartos","astutely","scalped","rotundness","sayers","mineralogists","regent","paleontologist","iowans","inuit","unbidden","daugherty","chintziest","neared","compliance","blustery","cantor","adamant","manicurists","concepts","jefferey","undoubted","prosody","limos","circumvention","friend","fatuousness","freebie","calyx","maldivian","demagnetized","geologies","sacs","bedding","cozens","leafy","mullet","grungiest","mounting","bait","incredibly","relinquished","adulterers","erika","reneges","columned","consummates","falloff","stargazers","perfumes","grunting","toadying","expressible","affix","configuration","solemnest","latitude","bandoleers","reactivates","announcement","nudists","nunnery","dissimilars","hamilton","bigamists","moors","inessential","shrubbery","cockleshell","einsteins","pikes","preschooler","continued","punishable","liaising","walkmans","pythias","fluid","semaphored","pepped","gayness","boastful","sinewy","homophone","leveraging","disgorge","disabling","wildcat","barrings","agonized","banshees","combinations","parthenogenesis","outdo","prancing","selective","haling","octogenarian","iraqi","pause","retrofitted","closeouts","blotchy","lye","unforeseeable","overreach","telephonic","sultana","hygienically","kaitlin","attaching","infiltrate","programming","basque","mucking","potash","bifurcated","restrained","talker","mammon","keeping","bauer","capitalism","dreaded","trillionth","presupposes","gyration","living","affecting","directness","afterbirths","treatise","v","twanging","wardered","quirks","globally","tint","nearby","attestation","travails","woolgathering","callings","calypsos","wrens","routinized","spock","aqua","chive","fillmore","purulence","renewed","wildly","vamps","buchanan","geneticists","wreathing","singleton","trivialize","beginnings","fitness","outburst","full","retirement","unburden","halter","wessex","trustier","preeminently","dragnet","treats","nourish","chimps","aggravated","seen","incidentally","bathmats","scant","disrespectful","seepage","papyri","dialyzes","rescinded","philosophizing","telexes","remonstrating","thirds","mandates","schmaltzy","richardson","steward","landwards","shufflers","tingly","acrimonious","unpopular","solitaires","spiffy","subtotaled","meshes","saddle","extraneously","faunas","brads","crullers","requesting","zoe","wavelet","telegraphing","retraction","ashe","restoration","percentile","pompom","lighthouses","sympathized","shiner","motionless","regales","heaped","fringes","musing","mucky","maintainability","miscellaneous","baaed","shortest","ratification","pleat","butteriest","lane","springfield","yogurt","bidets","orientals","bombs","blubbers","stereoscopes","delusive","weighted","jingles","dante","overachieve","jetsam","upsurging","comb","cosmologists","sidetracking","maitreya","artichoke","decaf","seasonable","steamy","disparate","alphabetical","comprehending","circulation","uvulas","imposters","lucretia","mothball","numbering","appliance","unchecked","accost","coasters","slabbed","salver","countesses","meditating","depressives","drily","stratify","rarefying","toadstools","placing","shingled","purchasing","ina","mammoths","ceremonials","boastfulness","stigmatizing","implodes","armored","hemstitches","unmanned","cassette","rob","marrowing","indenturing","fourneyron","kabob","fixatives","herein","lancets","slammers","mg","sympathy","believe","unscramble","niacin","shari","refit","lankier","crazy","willingest","dourly","litmus","odyssey","personifying","freakier","ammeter","splatter","darwin","boogies","bivouac","timider","sleazily","consensus","goldbricks","precipitant","unheeded","alpacas","oozing","allotments","sootiest","nintendo","takeout","keillor","unsatisfying","generous","dunging","unbent","sovereignty","snuffled","mounding","micrometers","ingesting","apparition","stigmatize","hellhole","belligerent","mcintyre","pilloried","deploy","wooziest","punned","layman","bullpen","jukeboxes","immature","emit","beech","octopus","intransigence","aftertastes","queenly","bolled","phonologists","wiper","maidenhood","quart","undid","interlopers","dispensable","outcries","howell","indescribably","individualist","jags","primaries","metabolize","deviltries","amplified","polarization","vocalizations","wrinkle","churlishly","belled","subpoenas","photosensitive","soothes","infantryman","demobilize","worsening","drafty","blanching","spuds","tautest","tacos","throe","following","disruptions","leeches","measure","stubbing","mexicans","abolishing","plottering","sailfish","hales","spook","mercantile","fussbudgets","urning","vignettes","recriminates","humane","unreleased","frankincense","dinkiest","gyms","submersibles","gallbladders","unfair","rome","meticulousness","overfull","youngish","moseys","beholder","available","saltier","depravities","dustiest","tremble","accountant","clumsiness","imparting","rankin","stingy","joel","izod","undefended","trademarking","lasted","tabulated","diversion","baroda","hags","globing","firebomb","mozambican","inherit","philosophy","whomever","nettle","faulty","awakens","bethink","poll","meg","interscholastic","lilith","roiled","garland","mussels","supermarket","flares","satyr","underfunded","draftier","prevailing","avenging","punishing","inflammatory","copier","droplet","misinterpretation","multilateral","zoology","expletive","miscarriages","raiment","translating","tarpon","unbolt","muskellunges","watercress","macing","scurfier","olivier","doubters","changeovers","significance","catechise","rosined","ptomaine","corduroys","affected","fruitier","muddled","purl","spiffiest","lightweight","doomed","aeriest","twittering","vocabularies","resolve","franck","haunched","heath","rosemary","proofread","gray","cowpox","slanderous","palsying","revelation","basing","hind","wacs","wall","decries","intergalactic","burdock","styptics","jovially","using","ministers","idolaters","viewfinder","orthopaedic","linguists","freud","institutional","moneymaker","initiatives","beatriz","evidence","ecclesiastes","humped","buildings","kay","vice","northward","altman","neurotically","fateful","cowpoke","bureaucratically","irremediable","endemic","oxbow","les","propelled","protozoan","perforated","chainsawed","bush","curtseys","deductibles","womanlier","surf","dumbly","navels","hubbub","algerians","recompilation","alsatian","escher","cephalic","bus","decision","washrooms","enrolling","quipped","exhibited","dis","thoreau","jose","bombing","softly","practicals","unadvised","neuralgic","usurious","commentates","unexpurgated","condescending","effusions","remissness","aludra","frantic","repentance","stanks","ketches","semite","swaths","uzbekistan","jaws","steined","largess","minimized","chancelleries","convolutions","smetana","congenitally","ferry","confederations","hugest","dredged","woof","jounces","romero","iquitos","truckles","gus","dickies","wisecracks","reinaldo","inquired","intolerant","warden","enrich","mohammed","swaggers","mirroring","vulgarer","thalia","afraid","slurp","penologists","stardom","beehive","waffles","warble","have","hopelessness","droopiest","nehemiah","vividest","docudramas","rationalism","lysistrata","fights","ursa","stockades","marius","pronounceable","regroup","hayden","scarborough","snowplows","giovanni","sidesplitting","traffics","voters","regenerates","untimeliness","sleepy","unravelling","triad","token","itineraries","flagellation","conciliator","rabbited","humanization","recopied","manses","locked","combated","drumsticks","pocketbooks","chagrining","passageway","corinth","dehumanizes","hurdle","highbrow","mister","querulous","inveigles","outright","severity","imprints","inductee","requiem","gerrymanders","lunacies","screeching","handmade","tennyson","denial","stoking","vessels","moronic","extol","abilene","congolese","bobbles","chairmen","poked","careens","lucked","bewares","abloom","astounds","tournament","wayside","showiest","gondola","nimbus","raped","mercuries","circumnavigated","imbroglio","intimidate","snug","figging","barents","latinos","winced","adage","lupin","prepositions","plaintively","osman","prerecording","slaloming","cravings","vented","orangeades","snit","taunt","tushed","rejecting","subjugation","refinishes","deformities","mortising","hooligans","suffix","serengeti","harbin","skill","insinuations","arteriosclerosis","tavern","endemics","anarchistic","aftereffect","lorenz","streetwalkers","sociology","appendicitis","pipped","roebuck","lumbers","repairing","cryptograms","dictates","infections","airing","capillaries","give","brecht","broader","dander","gerontologists","snowfalls","shadow","prognosticate","carlton","overalls","paranoia","beastlier","pacifying","anomalous","disliking","sermoned","calcify","demolition","remount","immoderately","cassie","jellybean","nanjing","ruffles","vegetation","invisibility","fiascos","briar","rhinos","strictures","canvassers","salyut","barns","scorers","unintelligibly","seth","restructures","rhinestones","chancery","sandiest","foreshorten","towns","wicks","birdwatchers","barks","gaffs","flatfishes","rhythmic","riches","tsar","thirsts","fluked","vladimir","screwing","enunciate","pairwise","bowels","mizzen","keeled","belittles","outstations","enjoyments","reinforces","preponderated","minutiae","inspect","hickeys","squadding","deadbolts","cotswold","surged","creations","cagiest","mhz","staider","center","realistically","abandons","iodine","originate","leads","returning","leaked","izanagi","journalist","swapping","parsimonious","bilking","mongol","nauseatingly","villa","engagingly","perambulates","bah","tittered","approvingly","airfields","digested","crazier","dotson","opaques","irresolutely","braggarts","mooted","taproots","signify","dolts","cowper","dormouse","theodoric","pointedly","cascade","perpetrating","rejoiced","saddled","pencilling","flysheet","woodchucks","render","apostolic","usual","gaunted","kilohertzes","nonwhite","nodded","loath","tinkle","rubbling","tombing","boyish","tromp","pastured","stewarding","affirmative","consistently","reminiscing","vulgarities","opiate","teat","fuckers","substrate","potpie","sasses","latrine","lobs","directional","sakha","recline","palmettoes","tweet","failed","immaturely","eyeballs","beards","interestingly","quadrature","busily","birdcage","postulates","heps","microchips","grinned","libation","cerebrums","hairiest","vito","avid","thundercloud","sauntering","staving","mica","accusing","waived","concluded","dissident","censure","cumberland","caesarean","inhale","inventiveness","schusses","england","snaffled","demographic","landsat","observance","maneuverability","lacerate","cassettes","annulment","burglars","noncom","disadvantageous","pummelled","travel","chiaroscuro","newlyweds","rustic","spryly","sugariest","strafing","caveats","digs","swiss","communism","fallow","thymus","ascella","dabbed","unlocking","sorrel","skinflints","exclaiming","informed","louses","obligations","petrolatum","toga","castigation","fluster","chutney","mendocino","dispatching","mutiny","shrinking","marring","pollinates","twa","smirks","dimer","broaches","musketeer","stapler","zionism","newsboy","basilica","turbine","wasatch","misjudge","frigid","orgasm","convocations","michelle","furor","blockages","defenses","stroked","gruffing","incoherence","brutes","desperado","magnetic","sandblasters","eeyore","semis","nebula","barraging","alias","valeted","transcend","titanic","bibliophile","knowingest","facile","equivalent","garnisheed","nays","spritzed","sweetener","ensued","ail","matterhorn","sledge","documentary","extraction","portending","uglies","trainees","edinburgh","accreditation","mournfuller","trusties","expound","inveigled","pomaded","pickles","musicologist","torturers","skinniest","confute","forgetfully","deliriums","sunspots","kirchner","houseboats","sucks","ghoul","onrush","useable","congenial","aramco","gumdrops","podhoretz","harley","hunchbacks","bassoonists","stitch","steamboat","ellipses","execute","saliva","bared","begotten","inquisitively","trailer","briskets","curvature","outstript","pharaohs","spangle","ointment","staggerings","gibbering","curatives","rasmussen","matchmakers","powdery","bounces","art","secreted","clunkiest","pasteurize","gouda","light","omega","caliban","pillowing","insouciant","marketers","deception","protectively","steinway","castanet","hokusai","lunching","prejudge","easing","inchoated","divinely","vitalized","woodworm","journalese","austere","pipes","doodad","evenhanded","steal","appoints","returns","intransitive","declaimed","diastolic","axiomatics","genuflecting","accuser","cytology","welcome","pumices","noways","shade","unseasonable","woodsheds","stopgap","interlace","lumpiest","bengal","aspiring","galois","catechism","adventitious","tediousness","followed","smoothing","churl","simulate","polishing","mesh","dimensional","stabbing","golden","nit","fiords","banned","ishim","exempts","cherokee","seeker","boils","watershed","scherzo","melchior","mosques","gleamed","resolution","neurological","nemesis","shambles","suborning","summarily","kuznetsk","support","crummier","thawing","admonitory","cataloguing","perennially","abe","scooting","kit","cornbread","lodging","debarking","reupholsters","runs","cosigner","listed","stooges","cheddars","abscond","outselling","repulsively","larynxes","refunded","nanosecond","inherently","asseverate","ridiculed","insides","displaced","letterbox","harpy","indiscreet","bobsledding","maraca","fluctuate","enlarged","suppresses","essentials","blackguards","approves","spume","moister","raggedy","slewed","nook","whiner","lousiest","controverting","reconstructing","fnma","molls","paupers","taproot","moths","generalities","flatfooting","vs","bose","mesmerize","despatches","hiving","prosecutions","heaters","installed","piety","playrooms","oppose","fanfare","jeopardize","headfirst","ghent","innkeepers","israelites","gardenias","encircled","coyer","yearbooks","concentrate","cogitates","teethes","fleeted","weekdays","rainforest","defoliating","photo","malaysia","trend","shroud","thoraces","famishing","disembowels","senders","blaze","gale","gloomiest","morning","marabous","retrench","snyder","boos","breakneck","hostlers","indemnified","shiver","mil","thoughts","nile","selvaging","severest","colorado","rushes","overrates","dissembles","magnifying","solubles","entrepreneur","expressionism","stalemated","thirsty","parasite","bristly","schoolchild","calibrating","snob","hookworms","conciliates","progression","mismanage","hotelier","roxy","tut","stipulated","shiftiest","danubian","kaunas","whopping","ganglion","queuing","octane","tibiae","damneder","pronghorn","maim","vazquez","ironies","emotive","groupers","henpeck","subservients","recursively","blamed","meagerness","distracted","cheerless","semblances","hat","burps","mutate","convulsive","frederic","goblins","complainers","hobnobbed","coyote","debra","negligible","sepulchered","gearshifts","beelined","caking","acupuncturists","focussed","retread","ingrain","taupe","chloroforms","impales","regresses","llanos","blurriest","sisyphean","typesetter","budweiser","maxed","appendages","redistribute","gods","scabrous","roger","spacesuit","evacuate","moll","suitors","theocracy","shaft","motherlands","sights","earmarking","tranquilizes","inaugural","disheartening","skydiver","advise","cellophane","beheading","repasting","slavonic","wantonly","buffeting","triked","narmada","splotch","outsides","reigned","cronkite","hypertext","alleluias","broad","hogging","appreciatively","admonish","seconal","wolverines","incontinent","damion","amongst","accomplice","hitchhike","patrick","escapism","southerns","continuances","among","commit","capsizing","ballrooms","noumea","dick","somali","congruent","cozies","underclassmen","jeanine","husbanded","debris","protesters","galatea","hies","watermarking","clapboarding","manufactures","miffs","coops","reality","tailspin","sniper","rants","capacitor","excretions","polluting","incompatibility","receipted","wrongness","prevaricated","beige","boyfriend","humbled","pigging","hamburgs","parching","costume","minicams","womanish","yiddish","orally","schultz","tiptops","condor","prefixes","daddy","absconds","law","blued","mobile","scrupled","jacobin","decays","crud","remarkably","unhealthier","iberia","stepsons","restorer","chatterboxes","basilicas","suffices","starts","suggestively","emmett","intended","auspice","obsolescent","inexplicable","crushes","conversationalists","bouquet","installations","custody","hundredths","capriciously","newsed","reasonableness","thoughtlessness","socket","skipper","tempura","chumminess","resumption","blazoned","balking","reaches","morocco","fricasseed","tutelage","louis","countless","transfigure","sheratan","unclearest","blotched","steelier","gooks","necromancy","amortization","rumoring","gurgled","evaporate","ideological","bobtails","acrobatics","federation","anticipates","volley","ashen","busiest","chargers","hanoverian","joyrider","freeloader","savings","neutrinos","wigs","sexpots","evades","reliefs","deena","descending","markov","scanners","potters","anomaly","step","raspier","nantucket","happened","unsupported","bunion","sympathies","styron","bereavements","tristan","constabularies","ionizer","effervescence","gashes","mithridates","shale","cassias","sidetracks","thousandth","barons","nonevents","crackpot","indonesian","nourished","abortion","patriarchs","jinn","sodding","slouched","calumniates","sharpness","pettifogged","decedent","control","nostrum","kindliest","backfields","steadied","squinter","creed","chummier","precipices","premiums","unsheathing","mousiness","challengers","gilbert","transmigration","croon","leaves","furry","minutes","runyon","conjectural","kebab","gawks","ra","cacophonies","hustlers","stretching","forefeet","satanically","sofa","exclusively","provence","rembrandt","savageness","yogurts","servility","precursor","strut","deliriously","turks","unmasking","charioteered","forefront","suntanned","transmigrated","whizz","melodic","accelerations","codices","manuscript","hats","electrolysis","dolt","nyquil","diurnally","tellered","suppurated","bestiality","cottonseeds","ordovician","farmyard","billfold","northeasts","brightens","plagiarists","scooters","binged","melanges","fortifying","journeyed","hippos","warrantying","invariables","feedbags","values","yuletide","devilishly","enervated","caveatting","triplied","repackages","primly","buoyantly","mordant","termite","investigates","chechnya","rochambeau","unhooked","bedevil","communed","cornwall","mys","devoutly","changsha","competitors","unattached","zirconium","shearers","dislike","valentines","horton","barbara","factitious","froze","drizzles","descriptively","cums","milken","dissatisfaction","opuses","pointing","drilling","cooping","guff","carousers","aquarium","reunite","nauseating","creaking","whit","bounciest","endymion","decoding","disdain","damsels","citizens","discreditable","carillons","propinquity","fifths","extravagances","socialization","signposted","south","bloated","clued","clouts","pusillanimity","cimabue","praetorian","bladed","deathless","trustworthier","peel","bleeding","larding","cotter","mug","jays","override","wanting","wampum","wax","cancelled","foraging","deftly","krugerrand","spared","quaking","throw","rodent","picnicking","tagore","greer","kelly","indecencies","swimsuits","obadiah","moratoria","peabody","faultlessly","outtakes","suitcases","mississippian","wackos","freebooters","hobgoblin","neptune","door","jude","benefices","gannet","fagoting","neglectfully","revolutionize","haloing","mangroves","immorally","homerooms","belaying","profligate","nightmare","circulations","candy","infinitude","goodnight","vegans","mortise","stubbiest","motion","hotshot","keisha","pocketfuls","franks","palates","exhale","cardiopulmonary","swelled","remorseful","cracks","nabokov","blockbuster","shovelling","indistinguishable","mice","tartly","wretchedest","theorizing","mopeds","nauseated","comforters","splintered","aiming","quotation","transplantation","submersible","proceedings","orchestras","echoes","discreeter","innocently","lacy","recondite","requirements","kitsch","motorboats","auditorium","receptors","typeset","yucking","litters","confucianisms","expeditious","bestowal","faceting","bedevils","obscurity","cecilia","trumpeters","touched","memphis","repeals","thrifts","keynesian","martin","haunting","bostonian","lowenbrau","admission","stun","unionized","seaway","holly","vijayanagar","kiths","fluting","cadets","cabin","reactivation","foregrounded","airings","queue","unedited","pandemonium","steeplechases","close","spotter","quilt","confession","traditionally","unroll","groovy","toddled","visas","optic","appropriation","socials","menstruate","meadows","fumigators","prostrated","nibs","stressful","khorana","wakefulness","fount","sensor","radioactive","lajos","centigrammes","perspires","disguise","toed","outnumbering","psalms","subversives","hues","school","tunneling","lessie","educated","upend","eng","charbray","butterflied","wishers","cube","forecasts","leaven","havoline","fathered","naughtier","chittagong","update","framer","islets","scrimshawing","momentous","sacking","maxilla","verdigrising","servers","distortions","schlockier","pigskins","spouting","topologically","melt","tarot","permian","vouchsafe","spinners","ablatives","batsman","cabbed","slippery","evasions","ladyfinger","backstroked","yolanda","machine","celli","penalties","bur","guatemalan","contended","vargas","observably","dowdy","ugly","sandinista","queerer","lilly","bamboozles","fricassee","vipers","concretes","fart","triplicated","innuendo","municipality","tet","rejects","lentils","murmuring","intercessor","connector","pricks","bewitch","veracity","bivouacking","tommy","commodious","democracy","studies","numerate","effusiveness","west","thumbscrews","brainwashed","phekda","overemphasized","caiaphas","elusiveness","attacker","unites","theistic","lagrangian","pain","guzzlers","scold","cracked","oracled","musharraf","volcker","judases","berry","eighteen","dean","broadcaster","sheathes","become","voyages","cotillions","assurance","sumptuous","indefinites","bullock","astute","distilleries","great","gopher","feasted","duties","dullards","markups","adeptest","enthusiastically","gallivants","mainstream","peroxiding","lathered","reformatory","sum","idea","wyeth","bidder","puerility","unfortunately","evanescent","poetical","perambulators","picturing","stripe","blackbeard","pans","amend","dweeb","mortgagee","patna","earthworks","gabriela","straits","fifes","oddities","gerontologist","poppins","cymbals","wedder","shipping","gamine","aviation","outbounds","husbanding","phallic","gonna","spraying","doyen","aging","slyer","woodsy","apexes","prizing","recruited","supper","traduce","buts","reawakening","vibratos","qom","anticlimax","professionalism","oxbows","dumpies","danny","weaklier","spay","interrupting","adjusting","decenter","vengeance","samoset","sawdust","breathing","undersecretaries","concluding","adopts","foley","centimeter","filaments","stows","zests","sags","detoxed","amaryllises","justifiable","damply","hahs","blowguns","scalding","mongrel","cornflowers","adorn","grammars","rosy","luis","midwest","book","coruscate","tacoma","carnally","imp","motorcycles","escape","reincarnated","stickers","hank","bipedal","holidaying","seeking","stalagmites","totality","entitled","leghorn","pretenses","halfheartedly","infestations","stab","regimenting","awakening","temple","barber","cotes","efficaciously","doodler","semiannual","wrathed","pavement","accommodated","bostons","irritation","maladies","athletes","spidery","which","prehistory","revere","hasten","swirled","treads","masterwork","guzzle","aeolus","collied","cretan","powerboats","f","erma","prodigality","infuriates","chillings","nakedly","undergraduates","trundled","reportage","vaccinating","lucidness","discourage","abolish","follow","internships","buggier","ceramics","realists","sharped","rigs","extremism","mockery","swastikas","percolates","mires","recessional","preconceptions","curating","tastelessness","squattered","achieving","disagreeably","emend","breach","pregnant","argentinian","anthologizing","rectifying","burned","delicacies","bunkhouse","gyros","stockiness","strangulates","sudra","proportionals","inaugurations","downsizes","confucius","mirabeau","ententes","practice","scavenging","inlet","brashness","centuries","doffed","porosity","structuralist","phylum","ferrous","usurpation","apotheosis","bank","miked","peshawar","respires","videotape","lottery","mandible","piecework","occident","indiana","correspondents","bullrings","acquisitive","saturating","francine","unauthenticated","ellen","limitation","amputation","evasion","jeanette","mysteried","priscilla","falkland","cultures","mummification","cortes","codding","tapioca","taster","liberator","housemaid","rangoon","desegregate","vintages","la","tinkering","overtime","shiraz","coerces","gardeners","stakeout","hoedowns","thickenings","bobs","misfiring","scenically","pouting","emancipating","semites","deludes","incubation","hilariously","howard","sledgehammered","humidors","sciatic","pistil","inextinguishable","panchromatic","raspberry","consecrations","baronial","serbian","permanence","anthropology","deceasing","speedier","derisory","carefree","rebels","peeks","disinclining","backspin","beautification","unlearned","indeed","principle","disembowelling","diagrammatic","proofs","chinchillas","acrobat","cartographers","seethe","osaka","snow","spinnaker","conclusion","dumbing","libya","lizzie","numerates","cyclades","forenoon","bravado","decorates","taping","rounding","douching","beltways","so","wipes","to","untruest","detesting","cheered","pedestrianizes","medullae","evaporates","coleen","fixes","crushing","themistocles","coexists","imploded","bekesy","difficulty","maimed","remorselessly","somewhats","mongolism","unspeakably","commissioned","engorge","gives","unfettering","armature","trial","adjuster","tokens","applications","luzon","dorsals","fission","urgency","traversed","surrounding","hernias","dingoes","spain","wolfe","nabbing","adieux","klingon","bloc","belgrade","tidewaters","trustee","videocassette","bankrupts","dismemberment","redness","trickiest","nervous","rumpled","letitia","recriminating","sequoia","directorates","tumor","ascending","stylishly","salts","canons","sclerosis","rubble","provenders","chaplet","teensy","spray","washerwomen","injunction","saigon","sodas","bundling","jinnah","reuses","cowls","diviner","refocuses","outnumbered","saiths","andean","vital","chapt","transmutation","currycombed","baddest","pensacola","barbecue","mobil","fudging","peter","waterproofed","comedy","discords","subsided","capitulates","foreshadowed","impertinents","gigs","hallucinogens","perspicuity","calculi","allen","pierre","recompense","brickbat","swallowing","addictions","deputized","springboard","etchings","chivalrous","comparable","physicist","governance","grimly","sugarier","tersest","spying","consenting","waters","inseminate","leach","disordered","whales","adorable","possessor","paleface","salamis","reissues","tempter","imagined","censoring","reinforcing","leverages","cinch","sieve","hoarfrost","universe","essays","tyrannosaurs","eyebrow","sartorial","stigma","nonchalant","intricate","wineglasses","cry","perfectionist","screenings","mohammad","guarantees","speaker","socking","hashes","bluffer","glockenspiel","militantly","goaled","declined","commercialism","passkey","mallards","purdue","codicil","oared","milieu","despised","lowliest","atwood","babysits","dying","serviceable","amorously","aramaic","dec","piquant","rhenish","eagerest","testis","invalidated","stated","herculean","folding","long","underwritten","acquaintance","figuring","cuckold","variants","naiver","pinkest","preferences","bunions","compaq","conspicuously","disabused","dashboards","amperes","hammerings","supervise","corrodes","aquae","wiled","recriminate","online","sympathizing","mention","reelect","summations","cocteau","turnround","turnabouts","commemorating","localling","crowing","placer","wounds","flunkeys","whaling","shrivel","akita","censoriously","affidavit","closed","protein","syphilizing","flattering","isotropic","shivers","categorization","wifely","commonwealths","newtons","overcharges","midmost","undercharges","goaling","porpoises","dearly","swallowed","hospitalizes","cower","orienting","sailor","remunerated","gail","corina","excreting","backstroke","measlier","execrating","filmiest","bridgette","smackers","convection","nonskid","obscurely","roots","palindromes","combative","frightfully","edifices","arjuna","marsala","offsprings","talkers","logo","icarus","unwinding","fevers","pedantry","aberdeen","backfiring","backwaters","affiliate","maharajahs","miking","apostles","chaste","schneider","yukked","redolent","shame","packed","abolitionist","adversarial","golly","dumbed","broom","boons","earlobe","thinnest","emblazon","chrysostom","threat","descender","pithier","wretch","subliminal","actuates","glutted","devalue","festoon","belief","politics","nickel","despairingly","encyclopedias","airheads","naval","muffing","moot","belfries","porter","universals","guiding","spreader","televising","minis","strollers","campaigned","amalgamated","lepers","performing","agreeable","frond","cronies","armenian","omnipresence","shaves","cunts","disconcert","gannets","optimum","amatory","uncomprehending","threnody","nosed","disfavoring","reprimands","quoiting","coruscated","confuted","bleach","aloha","cooler","trading","abetting","intensifiers","mahayanist","pointer","dashingly","brutishly","cells","quintupled","muzzling","chic","karaoke","pellet","rockefeller","frigidaire","dillydallies","smooch","promptly","wetbacks","bandwagons","herbivore","proceed","meaningful","sulks","deming","spry","assorting","unsung","womanly","shamelessly","cornelia","pillbox","zimbabwean","douched","unashamed","pepsi","cowardice","grownups","reeducated","weed","fifteens","spurs","feral","industrialization","tempestuous","reinitialize","mummify","spaceships","otherwise","bow","patting","cauterized","poultry","richard","hill","respelt","pan","crabbing","thick","tablecloth","jogs","coagulated","infidelities","habit","zion","price","budged","breeze","inconsiderable","basses","nonabsorbent","omsk","hustle","sideline","discs","altruism","agent","catholicisms","dissected","snappers","molluscs","unscrupulousness","miscue","poverty","chewier","inane","metaphors","thrifty","irreparable","irritant","dragged","roam","note","pock","advent","alternators","swiping","cots","noemi","screech","tinning","hero","katowice","arithmetic","motivated","niggling","gleam","mammography","kansans","tampons","snuffed","philosophical","militate","squelched","loudlier","actives","idly","grotius","tranquillize","charade","spunks","transgression","faceless","rebelling","parachute","sharpened","undesirability","tithe","vibrancy","impasse","saddens","aboding","wake","downbeat","resin","pitchfork","fulfilment","displacements","regiment","cowing","killdeers","goldsmith","coaled","cameraman","corrupting","revisits","congeal","clorets","jeep","yawed","clayton","grease","grails","unconcerned","bhutan","gaudier","weakest","agrarians","phenomenon","dickering","electromagnet","syringed","emailed","carpets","galactic","sallies","sapience","milestones","jacobi","copenhagen","telexed","underhand","flannelled","burdensome","lessee","hashish","pulverized","parquet","beavered","profaned","lad","enchantresses","sobers","anatolian","woodcutting","pillion","toxins","ates","tractor","mommie","financier","hairpins","expropriating","boardinghouses","marceau","lithographs","waves","munificent","retardants","blarney","politicos","savaging","brittleness","pushing","underacts","vestiges","rotors","screwy","superiority","skydive","atlanta","hearst","multiracial","gulfs","dependents","fanfares","sharpeners","accumulate","horrified","fraternization","buffy","sermon","cattleman","grandpas","minx","roughness","tutsi","incinerated","quite","soupiest","naught","encampments","opals","implacably","chromatic","harbingers","naturals","firsthand","desirable","divulged","zoologist","parishes","microscopically","saltcellars","banishing","fezzes","elton","perversion","vassals","in","honorifics","blimp","blitzing","puckett","cuts","frontal","proselytized","hargreaves","northeastward","lingerers","percolation","camembert","brackets","seashores","dmitri","sensitive","acquiring","hurled","sensed","totem","pragmatists","sportier","tawniest","plenteous","caloocan","humus","testimonials","shirker","simon","vibraphones","chocks","smear","americans","secondary","zosma","quadrille","bobsled","infesting","invitational","causalities","friable","rumbled","sprucer","distressing","shadowing","uvular","ashtrays","abreast","treacled","enviousness","amigo","interviewed","explaining","see","dislocating","incitements","suite","procured","disinterment","anna","proportioning","reimposed","toughs","versified","historian","capon","heraldic","abrasively","henceforth","transducer","different","epidermises","falsifies","passions","renunciations","blurry","selfishness","scandalize","microphone","democratic","altair","succinctness","persistently","indirection","stock","existentialist","weaseled","strops","buxomest","quoited","teethed","derogating","account","saltest","guise","qualities","siliceous","escalated","declamations","cancels","polyphony","writes","zippiest","tiffs","testified","inadequately","subcontracted","called","nabob","stashing","adolescence","pumped","floral","tunisia","overestimate","visages","probed","vellum","crackdowns","spur","reestablishes","plywood","phones","comforting","superannuates","ba","imprimaturs","minimally","chennai","inhumanely","tamerlane","asimov","stonier","spiriting","weakling","rubbernecks","rose","pound","boa","despondency","initiate","crazing","uncommonly","privation","bleeped","scrimping","hobnail","theory","hiccup","subhuman","tarragon","misbehavior","horsemanship","mariners","skewered","suharto","courtly","vast","reconstructs","firmest","mortaring","embryos","hungarian","impinges","heppest","stripped","skywriting","sideswipe","evilly","tonsuring","wednesday","novellas","spunkiest","soprano","source","reran","gabbed","standoffs","cheers","stifle","vocalize","shillelagh","gifted","schizophrenics","falasha","stereo","technologists","configures","mutts","reverend","aboriginal","chumps","stylish","lycra","mississippians","coequal","woefuller","bobcats","thymi","unwrapping","sticklers","propelling","mixers","slouch","mormonism","ericka","policewoman","hohenstaufen","sprites","clacking","antigua","volvo","proms","berbers","parachutes","notarizing","cookbooks","parrying","sunshine","laburnums","jocosely","uplifts","rebuses","hodges","utilize","sloshes","bacchanalia","semi","pyramids","solemnized","recycles","treeing","woodbine","laths","welters","upcountry","shutdown","vasectomy","inchon","warhead","phobics","justifiably","welders","boycott","mimeographing","obsolete","streaming","paramilitary","envelops","saunter","prorates","glazing","racing","pig","outcome","located","nursemaid","extended","humanitarian","newscasting","verandas","mantes","taints","nowhere","overborne","jaime","rankest","rebating","kroger","slowness","esophagus","assessed","hardheaded","classification","softener","wastelands","approbations","levelheaded","jamming","facetiously","bushing","larboards","nicobar","lesotho","marionette","profiteering","addictive","congest","crests","durante","trawled","lodz","pernod","futurity","sexy","unpick","encapsulations","rubbled","theorists","lanker","clank","comparably","exes","gadget","lusaka","swish","disenchantment","marquesses","buncombe","bonaparte","pentathlons","blemish","beechnut","effortless","triceps","destruct","overthrown","dietaries","headquarter","plateau","fencers","loyalties","accuracy","descants","nonstandard","reliving","produced","pandemics","commemorate","hay","rowboat","actuaries","vigorously","accuse","upgraded","palavered","drugstores","vulgarizes","digitally","pesos","appraisers","sins","miter","module","hibachis","unseated","park","continent","rocks","footbridge","serenades","filleted","north","snoopier","vest","carnap","nightsticks","branch","seeks","supervises","musculature","sunburns","cavour","lumbermen","joyfullest","overlook","yellowed","backbit","tussles","sassafrases","judiciousness","firewalled","spoon","preheating","freckles","flabbergasting","distrusting","snitched","frontier","inappropriate","bork","instructional","noway","trustees","feasible","civilians","jitterbugging","sobbed","lolling","forester","mispronounce","little","bugger","jettison","hysterics","nightingale","transvestites","oates","purges","nonalcoholics","surpluses","wraith","prokofiev","fornicate","pharisee","writer","hydra","pleasured","alienation","ulcerous","kosygin","awarest","hawkish","brahmanisms","regretful","nifty","naivest","deliberates","architectures","undefinable","peloponnese","choirs","cooperation","photostat","misrepresenting","tuckers","ditch","milksops","dilbert","lesbianism","advertises","wordsworth","lavishes","disloyally","mongolians","arizonans","moistened","m","satirize","professorship","odom","overlong","dislodges","privileges","persians","dated","survivor","effie","informants","charming","termed","trendiest","disenchants","impressionable","squiggling","potshots","broods","adeline","cog","dunged","yang","slayings","llano","heathen","chatterley","lush","birthplace","alphabetizing","yucked","studs","spokespersons","overcoat","bubbly","liquids","referees","ostracized","levelled","salvation","conferred","shoeshines","bluenose","arbitrate","flatbeds","attempt","suavity","ombudsman","attributively","cheerful","vancouver","filliped","murdoch","pluralistic","tempests","enhancing","rostand","ebonies","chipped","bodice","causation","sharron","waxiness","lute","snoozes","dickered","gratifies","neuron","condemned","javelin","undisturbed","lauded","vetting","burrows","prolific","scarves","sorrowed","understatements","affabler","ampuls","malices","extemporizing" });
	/*
	SolutionAnag s;
	auto t1 = chrono::high_resolution_clock::now();
	//vector<string> v { "bat" , "nat", "tan" , "ate", "eat", "tea"  };
	vector<string> v{ "eat", "tea", "tan", "ate", "nat", "bat"};
	vector<string> vg({""});

	vector<vector<string>> anags = s.groupAnagrams(v);
	auto t2 = chrono::high_resolution_clock::now();
	cout << (t2-t1) / chrono::milliseconds(1) << "ms to run.\n";
	cout << anags.size() << endl;
	//print_vec(v);
	
	for (const vector<string>& anag : anags)
	{
		print_vec(anag);
	}
	
	//print_vec(vv);
	
	/*
	Solution2 s;
	//std::vector<int> v{ 1000000000, 1000000000, 1000000000, 1000000000};
	//std::vector<int> v{ 1,0,-1,0,-2,2 };
	//std::vector<int> v{ 5, 0, 7, 4, -2, 2, -3, 4, -1, -2, 8, 0, 2, 5, -2, -6, 2, -2};
//	std::vector<int> v{ -493, -482, -482, -456, -427, -405, -392, -385, -351, -269, -259, -251, -235, -235, -202, -201, -194, -189, -187, -186, -180, -177, -175, -156, -150, -147, -140, -122, -112, -112, -105, -98, -49, -38, -35, -34, -18, 20, 52, 53, 57, 76, 124, 126, 128, 132, 142, 147, 157, 180, 207, 227, 274, 296, 311, 334, 336, 337, 339, 349, 354, 363, 372, 378, 383, 413, 431, 471, 474, 481, 492 };
	//std::vector<int> v{ 0 };
	//std::vector<int> v{-499, -486, -479, -462, -456, -430, -415, -413, -399, -381, -353, -349, -342, -337, -336, -331, -330, -322, -315, -280, -271, -265, -249, -231, -226, -219, -216, -208, -206, -204, -188, -159, -144, -139, -123, -115, -99, -89, -80, -74, -61, -22, -22, -8, -5, 4, 43, 65, 82, 86, 95, 101, 103, 123, 149, 152, 162, 165, 168, 183, 204, 209, 209, 220, 235, 243, 243, 244, 248, 253, 260, 273, 281, 284, 288, 290, 346, 378, 382, 384, 407, 411, 423, 432, 433, 445, 470, 476, 497};
	//3032
	//std::vector<int> v{ -5, 5, 4, -3, 0, 0, 4, -2};
	std::vector<int> v{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 200};
	//std::vector<int> v{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
	//std::vector<int> v{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
	vector<vector<int>> z = s.fourSum(v, 200); //6189, 3032, -1926, 200, 8
	for (const auto& zz : z) {
		print_vec(zz);
		//std::cout << std::endl;
	}
	*/
	//solution s;
	// 
	
	//std::vector<int> v({-1,0,3,5,9,12 });
	/*
	std::vector<int> v({ -1 });

	std::cout << _lower_bound_(v, 2) << std::endl;
	std::cout << search1(v, 2) << std::endl;
	*/
//	std::cout << *_lower_bound_(v.cbegin(), v.cend(), 0)<< std::endl;
//	std::cout << std::binary_search(v.cbegin(), v.cend(), 1) << std::endl;

	//std::vector<int> v({ 5,1,3});
	//std::vector<int> v({ 3, 7, 9, 1, 2 });

	//std::vector<std::vector<int>> v {  {1, 3, 5, 7}, { 10, 11, 16, 20 }, { 23, 30, 34, 50 }};
	//std::vector<std::vector<int>> v{ {-10, -10},{-9, -9},{-8, -6},{-4, -2},{0, 1},{3, 3},{5, 5},{6, 8} };
	//std::cout << searchMatrix(v, -9) << std::endl;

	//std::vector<int> v({ -10,-9,-8,-4,0,3,5,6 });
	//std::vector<int> v({ -10, -9, 4, 7 });

	/*
	std::vector<std::vector<int>> tt {{1, 3, 5, 7}, { 10, 11, 16, 20 }, { 23, 30, 34, 60 }};
	//std::vector<int> v({ 1,10,23 });
	std::vector<int> v({ 1,3 });
	int target = 1;
	std::cout << "found: " << *std::lower_bound(v.cbegin(), v.cend(), target) << std::endl;
	std::cout <<  std::distance(v.cbegin(), std::lower_bound(v.cbegin(), v.cend(), target));
	std::cout <<  ":::::: " << upper_bound({1}, 4);
	*/
	//std::vector<std::vector<int>> ff{ {1},{3} };
	//std::cout << std::endl << searchMatrix_(ff, 4) << std::endl;
	/*
	int i = upper_bound(v, target);
	std::vector<std::vector<int>> matrix{ {1,3,5,7 }, { 10,11,16,20 }, { 23,30,34,60 } };
	if (i < matrix.size() && i != 0) {
		bool found = std::binary_search(matrix[i].cbegin(), matrix[i].cend(), target);
		if (found) {
			std::cout << "AAAAAAAAAAAA: " <<  true;
		}
		--i;
		if (i < matrix.size() && i != 0) {
			std::cout << "AAAAAAAAAAAA: " << std::binary_search(matrix[i].cbegin(), matrix[i].cend(), target);
		}
	}
	*/
	//	std::cout << s.search(v,4) << std::en-dl;

	//std::cout << s._binary_search(v, 2, 2, 10) << std::endl;

	/*std::vector<int> v{ 2,2,2,3,2,2,2 };
	std::cout << search(v, 0) << std::endl;*/
	

	//wow(4);
	
	/*
	std::vector<std::string> all_pars = generate_pars(4);
	std::cout << std::endl;
	for (const auto& a : all_pars) {
		std::cout << a << std::endl;
	}
	*/

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