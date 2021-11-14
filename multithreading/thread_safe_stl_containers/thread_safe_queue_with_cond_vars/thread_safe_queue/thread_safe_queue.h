#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class threadsafe_queue {
	const std::atomic<std::size_t> MAX_DATA_SIZE;
	std::mutex data_queue_mut;
	std::queue<T> data_queue;
	std::condition_variable data_empty_condition, data_full_condition;
public:
	threadsafe_queue(std::size_t MAX_SIZE = 0) : MAX_DATA_SIZE(MAX_SIZE) {}
	threadsafe_queue(const threadsafe_queue& r, std::size_t MAX_SIZE = 0) : MAX_DATA_SIZE(MAX_SIZE) {
		std::lock_guard<std::mutex> data_queue_lock(data_queue_mut);
		data_queue = r.data_queue;
	}
	void push(T new_value) {
		std::unique_lock<std::mutex> data_queue_lock(data_queue_mut);
		if (MAX_DATA_SIZE) {
			data_full_condition.wait(data_queue_lock, [this]() {return data_queue.size() < MAX_DATA_SIZE; });
		}

		data_queue.push(new_value);
		data_empty_condition.notify_one();
	}
	void wait_and_pop(T& value) {
		std::unique_lock<std::mutex> data_queue_lock(data_queue_mut);
		data_empty_condition.wait(data_queue_lock, [this]() {return !data_queue.empty(); });
		value = data_queue.front();
		data_queue.pop();
		if (MAX_DATA_SIZE) {
			data_full_condition.notify_one();
		}
	}
	std::shared_ptr<T> wait_and_pop() {
		std::unique_lock<std::mutex> data_queue_lock(data_queue_mut);
		data_empty_condition.wait(data_queue_lock, [this]() {return !data_queue.empty(); });
		std::shared_ptr<T> v(std::make_shared<T>(std::move(data_queue.front())));
		data_queue.pop();
		if (MAX_DATA_SIZE) {
			data_full_condition.notify_one();
		}
		return v;
	}
	bool try_pop(T& value) {
		std::unique_lock<std::mutex> data_queue_lock(data_queue_mut);
		if (data_queue.empty()) {
			return false;
		}
		value = data_queue.front();
		data_queue.pop();
		if (MAX_DATA_SIZE) {
			data_full_condition.notify_one();
		}
		return true;
	}
	std::shared_ptr<T> try_pop() {
		std::unique_lock<std::mutex> data_queue_lock(data_queue_mut);
		if (data_queue.empty()) {
			return std::shared_ptr<T>();
		}
		std::shared_ptr<T> v(std::make_shared<T>(std::move(data_queue.front())));
		data_queue.pop();
		if (MAX_DATA_SIZE) {
			data_full_condition.notify_one();
		}
		return v;
	}
	std::size_t size() const {
		std::lock_guard<std::mutex> data_queue_lock(data_queue_mut);
		return data_queue.size();
	}
};