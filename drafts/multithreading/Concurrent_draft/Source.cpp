#include <iostream>
#include <atomic>
#include <cassert>
#include <chrono>
#include <mutex>
#include <future>
#include <vector>
#include <random>

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


template <typename T, typename RI>
void merge(RI p, RI q, RI r) {
	std::vector<T> l_(p, q+1);
	std::vector<T> r_(q+1, r+1);
	
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

template <typename T, typename RI>
void merge_sort(RI p, RI r) {
	if (p < r) {
		RI q = p + (r - p) / 2;
		merge_sort<T>(p, q);
		merge_sort<T>(q + 1, r);
		merge<T, RI>(p, q, r);
	}
}

template <typename T, typename RI>
void p_merge_sort(RI p, RI r) {
	if (p < r) {
		RI q = p + (r - p) / 2;
		std::thread t(p_merge_sort<T, RI>, p, q);
		merge_sort<T>(q + 1, r);
		t.join();
		merge<T, RI>(p, q, r);
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

int main() {
	std::vector<int> v(100000);

	std::random_device rnd_device;
	std::mt19937 mersenne_engine(rnd_device()); 
	std::uniform_int_distribution<int> dist(-50000, 50000);

	auto gen = [&dist, &mersenne_engine]() {
		return dist(mersenne_engine);
	};

	generate(v.begin(), v.end(), gen);

	/*
	for (auto c : v) {
		std::cout << c << ' ';
	}
	std::cout << std::endl;
	std::cout << std::endl;
	*/

	auto started = std::chrono::high_resolution_clock::now();
	p_merge_sort<int, std::vector<int>::iterator>(v.begin(), v.end() - 1);
	auto done = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << " ms" << std::endl;
	
	/*
	for (auto c : v) {
		std::cout << c << ' ';
	}
	std::cout << std::endl;
	*/

	check_sorted(v.cbegin(), v.cend());
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
	return 0;
}