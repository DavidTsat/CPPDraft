#pragma once
#pragma once
#include <queue>
#include <iostream>
#include <thread>
#include <future>

/*
* second approach to the producer/consumer problem
*/
class producer_consumer {
	using data_type = int;
	std::queue<data_type> buffer;
	constexpr static unsigned MAX_SIZE = 10;

	std::mutex buffer_guard;
	std::condition_variable buffer_condition;
public:
	data_type prepare_data() const {
		static data_type data = 0;
		std::cout << "producing data: " << data << std::endl;
		return data++;
	}

	void use_data(data_type data) const {
		std::cout << "consuming data: " << data << std::endl;
	}

	void produce() {
		for (int i = 0; i < 1000; ++i) {
			std::unique_lock<std::mutex> buffer_guard_lock(buffer_guard);
			buffer_condition.wait(buffer_guard_lock, [this]() { return buffer.size() < MAX_SIZE; });

			data_type data = prepare_data();
			buffer.push(data);

			buffer_condition.notify_one();
		}
	}

	void consume() {
		for (int i = 0; i < 1000; ++i) {
			std::unique_lock<std::mutex> buffer_guard_lock(buffer_guard);
			buffer_condition.wait(buffer_guard_lock, [this]() {return !buffer.empty(); });
			data_type d = buffer.front();
			buffer.pop();
			buffer_guard_lock.unlock();
			buffer_condition.notify_one();
			use_data(d);
		}
	}
};

class join_threads {
	std::vector<std::thread>& threads;
public:
	explicit join_threads(std::vector<std::thread>& threads_) : threads(threads_) {}
	~join_threads() {
		for (unsigned long i = 0; i < threads.size(); ++i) {
			if (threads[i].joinable()) {
				threads[i].join();
			}
		}
	}
};

void test() {
	producer_consumer p;

	std::vector<std::thread> producer_threads;
	std::vector<std::thread> consumer_threads;

	join_threads j1(producer_threads);
	join_threads j2(consumer_threads);

	for (int i = 0; i < 10; ++i) {
		producer_threads.emplace_back(std::mem_fn(&producer_consumer::produce), std::ref(p));
		consumer_threads.emplace_back(std::mem_fn(&producer_consumer::consume), std::ref(p));
	}
}