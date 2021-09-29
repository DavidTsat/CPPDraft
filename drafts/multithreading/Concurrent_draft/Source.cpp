#include <iostream>
#include <atomic>
#include <cassert>
#include <chrono>
#include <mutex>
#include <future>
#include <vector>
#include <random>
#include <array>
#include <iterator>

std::size_t fib(std::size_t n) {
	if (n <= 1) {
		return n;
	}
	std::size_t x = fib(n - 1);
	std::size_t y = fib(n - 2);
	return x + y;
}

std::size_t p_fib(std::size_t n) {
	if (n <= 1) {
		return n;
	}

	std::future<std::size_t> x = std::async(std::launch::async, fib, n - 1);
	std::future<std::size_t> y = std::async(std::launch::async, fib, n - 2);
	x.wait();
	y.wait();
	return x.get() + y.get();
}


template <typename RI>
void merge(RI p, RI q, RI r) {
	std::vector<RI::value_type> l_(p, q+1);
	std::vector<RI::value_type> r_(q+1, r+1);
	
	l_.push_back(999999);
	r_.push_back(999999);

	int i = 0, j = 0;
	while (p != r+1) {
		if (l_[i] <= r_[j]) {
			*p++ = l_[i++];
		}
		else {
			*p++ = r_[j++];
		}
	}
}

template <typename RI>
void merge_sort(RI p, RI r) {
	if (p < r) {
		RI q = p + (r - p) / 2;
		merge_sort(p, q);
		merge_sort(q + 1, r);
		merge<RI>(p, q, r);
	}
}

template <typename RI>
void p_merge_sort(RI p, RI r) {
	if (p < r) {
		RI q = p + (r - p) / 2;
		std::thread t(p_merge_sort<RI>, p, q);
		merge_sort(q + 1, r);
		t.join();
		merge<RI>(p, q, r);
	}
}


template <typename It>
void check_sorted(It begin, It end) {
	It seq = begin;
	++seq;
	while (seq != end) {
		assert(*seq++ >= *begin++);
	}
}

#define M 500
#define N 500

using mat = std::array<std::array<int, N>, M>;
using vec = std::array<int, N>;

vec mat_vec(const mat& m, const vec& v) {
	vec y{0};
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			y[i] += m[i][j] * v[i];
		}
	}
	return y;
}

vec p_mat_vec(const mat& m, const vec& v) {
	vec y{ 0 };
	for (int i = 0; i < M; ++i) {
		std::thread t([&m, &v, &y, &i] {
			for (int j = 0; j < N; ++j) {
				y[i] += m[i][j] * v[i];
			}
			});
		t.join();
	}
	return y;
}

int main() {
	mat m;
	vec v;

	std::random_device rnd_device;
	std::mt19937 mersenne_engine(rnd_device());
	std::uniform_int_distribution<int> dist(-10, 20);

	auto gen = [&dist, &mersenne_engine]() {
		return dist(mersenne_engine);
	};

	for (int i = 0; i < M; ++i) {
		generate(m[i].begin(), m[i].end(), gen);
	}
	
	generate(v.begin(), v.end(), gen);
	

	/*
	for (mat::const_iterator row_it = m.cbegin(); row_it < m.cend(); ++row_it) {
		for (auto item_it = (*row_it).cbegin(); item_it < (*row_it).cend(); ++item_it) {
			std::cout << *item_it << ' ';
		}
		std::cout << std::endl;
	}

	std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout));
	std::cout << std::endl;
	*/

	auto started = std::chrono::high_resolution_clock::now();
	vec vv = mat_vec(m, v);
	auto done = std::chrono::high_resolution_clock::now();
	std::cout << "single threaded: " << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << " ms" << std::endl;

	
	auto started1 = std::chrono::high_resolution_clock::now();
	vec vv1 = p_mat_vec(m, v);
	auto done1 = std::chrono::high_resolution_clock::now();
	std::cout << "multithreaded: " << std::chrono::duration_cast<std::chrono::milliseconds>(done1 - started1).count() << " ms" << std::endl;
	
	/*
	std::copy(vv.cbegin(), vv.cend(), std::ostream_iterator<int>(std::cout));
	*/
	/*
	std::vector<int> v(100000);


	/*
	for (auto c : v) {
		std::cout << c << ' ';
	}
	std::cout << std::endl;
	std::cout << std::endl;
	*/

	/*
	auto started = std::chrono::high_resolution_clock::now();
	p_merge_sort<std::vector<int>::iterator>(v.begin(), v.end() - 1);
	auto done = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << " ms" << std::endl;
	
	/*
	for (auto c : v) {
		std::cout << c << ' ';
	}
	std::cout << std::endl;
	*/

	//check_sorted(v.cbegin(), v.cend());
	/*
	auto started = std::chrono::high_resolution_clock::now();
	std::size_t s = fib(40);
	auto done = std::chrono::high_resolution_clock::now();
	std::cout << "time: " << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << " " <<  s << std::endl;


	auto started1 = std::chrono::high_resolution_clock::now();
	std::size_t s1 = p_fib(40);
	auto done1 = std::chrono::high_resolution_clock::now();
	std::cout << "time: " << std::chrono::duration_cast<std::chrono::milliseconds>(done1 - started1).count() << " " << s1 << std::endl;
	*/
	//return 0;
}