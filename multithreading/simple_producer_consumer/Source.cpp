#include <iostream>
#include <atomic>
#include <cassert>
#include <chrono>
#include <mutex>

#define MAX 100
int b;
int buffer[MAX];
int fill_ptr = 0;
int use_ptr = 0;
int count = 0; // initially, empty
int loop = 100000;

std::mutex m;
std::condition_variable empty, full;

void put(int value) {
	assert(count == 0);
	buffer[fill_ptr] = value;
	fill_ptr = (fill_ptr + 1) % MAX;
	++count;
	//std::cout << "fill_ptr: " << fill_ptr << std::endl;
}

int get() {
	assert(count == 1);
	int tmp = buffer[use_ptr];
	use_ptr = (use_ptr + 1) % MAX;
	
	--count;
//	std::cout << "use_ptr: " << use_ptr << std::endl;

	return tmp;
}

void producer() {
	for (int i = 0; i < loop; ++i) {
		std::unique_lock<std::mutex> u(m);
		while (count == 1) {
			empty.wait(u);
		}
		put(i);
		std::cout << "producer: " << i << std::endl;
		full.notify_all();
	}
}

void consumer() {
	for (int i = 0; i < loop; ++i) {
		std::unique_lock<std::mutex> u(m);
		while (count == 0) {
			full.wait(u);
		}
		int tmp = get();
		std::cout << "consumer: " << tmp << std::endl;
		empty.notify_all();
	}
}

int main() {
	std::cout << "parent begins\n";
	std::thread t1(producer), t2(consumer);

	std::thread t3(producer);

	t1.join();
	t2.join();
	t3.join();
	return 0;
}

