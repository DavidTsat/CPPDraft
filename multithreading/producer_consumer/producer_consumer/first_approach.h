#pragma once
#include <queue>
#include <iostream>
#include <thread>
#include <future>
#include <cassert>

/*
* First approach to the producer/consumer problem
*/
class producer_consumer {
	using data_type = int;
	std::queue<data_type> buffer;
	constexpr static unsigned MAX_SIZE = 10;
public:
	// 1. Without any synchronization. Just the idea
	data_type prepare_data() {
		static data_type data = 0;
		std::cout << "producing data: " << data << std::endl;
		return data++;
	}

	void use_data(data_type data) {
		std::cout << "consuming data: " << data << std::endl;
	}

	void produce() {
		while (true) {
			assert(buffer.size() < MAX_SIZE, "buffer overflow!");
			data_type data = prepare_data();
			buffer.push(data);
		}
	}

	void consume() {
		while (true) {
			assert(!buffer.empty(), "buffer unferflow!");
			data_type d = buffer.front();
			buffer.pop();
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
