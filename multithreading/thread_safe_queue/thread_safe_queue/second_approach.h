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
	constexpr static unsigned MAX_SIZE = 1;

	std::mutex buffer_guard;
	std::condition_variable buffer_condition;
public:

	data_type prepare_data() {
		static data_type data = 0;
		std::cout << "producing data: " << data << std::endl;
		return data++;
	}

	void use_data(data_type data) {
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

void test() {
	producer_consumer p;

	std::thread producing_thread;
	std::thread consuming_thread;

	producing_thread = std::thread(std::mem_fn(&producer_consumer::produce), std::ref(p));
	consuming_thread = std::thread(std::mem_fn(&producer_consumer::consume), std::ref(p));

	producing_thread.join();
	consuming_thread.join();
}