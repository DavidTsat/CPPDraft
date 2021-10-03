#pragma once
#include <thread>
#include <future>
#include <functional>
#include <concurrent_queue.h>
#include "threadsafe_queue.h"

class join_threads {
	std::vector<std::thread>& threads;
public:
	explicit join_threads(std::vector<std::thread>& threads_) : threads(threads_) {}
	~join_threads() {
		for (unsigned long i = 0; i < threads.size(); ++i) {
			if (threads[i].joinable()) {
				threads[i].join();
				std::cout << "joinged\n";
			}
		}
	}
};

class thread_pool {
	std::atomic_bool done;
	threadsafe_queue<std::function<void()>> work_queue;
	std::vector<std::thread> threads;
	join_threads joiner;

	void worker_thread() {
		while (!done) {
			std::function<void()> task;
			if (work_queue.try_pop(task)) {
				task();
			}
			else {
				std::this_thread::yield();
			}
		}
	}
public:
	thread_pool() : done(false), joiner(threads) {
		unsigned int thread_count = std::thread::hardware_concurrency();
		try {
			for (unsigned int i = 0; i < thread_count; ++i) {
				threads.push_back(std::thread(&thread_pool::worker_thread, this));
			}
		}
		catch (...) {
			done = true;
			throw;
		}
	}
	~thread_pool() {
		done = true;
	}

	template <typename FunctionType>
	void submit(FunctionType f) {
		work_queue.push(f);
		//work_queue.push(std::function<void()>(f));
	}
};