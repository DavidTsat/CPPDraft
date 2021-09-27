#include <iostream>
#include <atomic>
#include <cassert>
#include <chrono>
#include <mutex>
#include <future>

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


int main() {
	auto started = std::chrono::high_resolution_clock::now();
	std::size_t s = fib(40);
	auto done = std::chrono::high_resolution_clock::now();
	std::cout << "time: " << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << " " <<  s << std::endl;


	auto started1 = std::chrono::high_resolution_clock::now();
	std::size_t s1 = p_fib(40);
	auto done1 = std::chrono::high_resolution_clock::now();
	std::cout << "time: " << std::chrono::duration_cast<std::chrono::milliseconds>(done1 - started1).count() << " " << s1 << std::endl;

	return 0;
}