#pragma once
#include "thread_safe_queue.h"
#include <iostream>
#include <thread>
#include <future>

/*
* forth approach to the producer/consumer problem
*/
class producer_consumer {
	using data_type = int;
	threadsafe_queue<data_type> threadsafe_buffer;
	constexpr static std::size_t MAX_SIZE = 10;
public:
	producer_consumer() : threadsafe_buffer(MAX_SIZE) {} 

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
			data_type data = prepare_data();
			threadsafe_buffer.push(data);
		}
	}

	void consume() {
		for (int i = 0; i < 1000; ++i) {
			std::shared_ptr<data_type> d = threadsafe_buffer.wait_and_pop();
			use_data(*d);
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