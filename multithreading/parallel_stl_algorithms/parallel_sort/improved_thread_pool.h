#pragma once
#pragma once
#include <thread>
#include <future>
#include <functional>
#include <type_traits>
#include <memory>
#include "threadsafe_queue.h"
#include "thread_pool.h"

class improved_thread_pool {
	std::atomic_bool done;
	threadsafe_queue<function_wrapper> pool_work_queue;
	using local_queue_type = std::queue<function_wrapper>;
	static thread_local std::unique_ptr<local_queue_type> local_work_queue;
	std::vector<std::thread> threads;
	join_threads joiner;

	void worker_thread() {
		local_work_queue.reset(new local_queue_type);
		while (!done) {
			run_pending_task();
		}
	}
public:
	improved_thread_pool() : done(false), joiner(threads) {
		unsigned int thread_count = std::thread::hardware_concurrency();
		try {
			for (unsigned int i = 0; i < thread_count; ++i) {
				threads.push_back(std::thread(&improved_thread_pool::worker_thread, this));
			}
		}
		catch (...) {
			done = true;
			throw;
		}
	}
	~improved_thread_pool() {
		done = true;
	}

	void run_pending_task() {
		function_wrapper task;
		if (local_work_queue && !local_work_queue->empty()) {
			task = std::move(local_work_queue->front());
			local_work_queue->pop();
			task();
		}
		else if (pool_work_queue.try_pop(task)) {
			task();
		}
		else {
			std::this_thread::yield();
		}
	}

	template <typename FunctionType>
	std::future<typename std::result_of<FunctionType()>::type> submit(FunctionType f) {
		using result_type = typename std::result_of<FunctionType()>::type;
		std::packaged_task<result_type()> task(std::move(f));
		std::future<result_type> res(task.get_future());
		if (local_work_queue) {
			local_work_queue->push(std::move(task));
		}
		else {
			pool_work_queue.push(std::move(task));
		}
		return res;
	}
};

thread_local std::unique_ptr<improved_thread_pool::local_queue_type> improved_thread_pool::local_work_queue;
