#pragma once
#include <queue>
#include <iostream>
#include <thread>
#include <assert.h>

/*
* First approach to the producer/consumer problem
*/

using data_type = int;
std::queue<data_type> buffer;
constexpr unsigned MAX_SIZE = 10;

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
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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

void test() {
	std::thread producing_thread;
	std::thread consuming_thread;

	producing_thread = std::thread(produce);
	consuming_thread = std::thread(consume);

	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	producing_thread.join();
	consuming_thread.join();
}