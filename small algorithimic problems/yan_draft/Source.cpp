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