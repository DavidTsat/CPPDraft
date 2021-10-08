#pragma once
#include <iterator>
#include <algorithm>
#include <vector>
#include <list>
#include <thread>
#include <future>
#include <chrono>
#include "threadsafe_queue.h"
#include "thread_pool.h"

namespace DSTL {
	/*
	template <typename T>
	int partition(std::vector<T>& A, int p, int r) {
		T x = A[r];
		bool changed = false;
		int i = p - 1;
		for (int j = p; j <= r - 1; ++j) {
			if (A[j] <= x) {

				++i;
				std::swap(A[i], A[j]);
			}
		}
		std::swap(A[i + 1], A[r]);
		return i + 1;
	}

	template <typename T>
	void _quick_sort_(std::vector<T>& A, int p, int r) {
		//if (std::distance(p, r) > 0) {
		if (p < r) {
			int q = partition(A, p, r);
			_quick_sort_(A, p, q - 1);
			_quick_sort_(A, q + 1, r);
		}
	}

	template <typename T>
	void quick_sort(std::vector<T>& A) {
		_quick_sort_(A, 0, A.size()-1);
	}
	*/

	template <typename RandIt>
	RandIt partition(RandIt p, RandIt r) {
		typedef typename std::iterator_traits<RandIt>::value_type value_type;
		const RandIt start = p;
		value_type x = *r;
		bool i_changed = false;

		RandIt i{};
		for (RandIt j = p; j <= r - 1; ++j) {
			if (*j <= x) {
				if (!i_changed) {
					i_changed = true;
					i = start;
					std::swap(*i, *j);
					continue;
				}
				++i;
				std::swap(*i, *j);
			}
		}

		if (!i_changed) {
			i = start;
			std::swap(*i, *r);
			return i;
		}
		else {
			std::swap(*(i + 1), *r);
		}
		return i + 1;
	}


	template <typename RandIt>
	void _quick_sort_p_(RandIt p, RandIt r) {
		if (std::distance(p, r) > 0) {

			std::thread t_left;

			RandIt q = partition(p, r);
			if (q != p) {
				t_left = std::thread(_quick_sort_p_<RandIt>, p, q - 1);
			}
			_quick_sort_p_(q + 1, r);
			if (t_left.joinable()) {
				t_left.join();
			}
		}
	}

	template <typename RandIt>
	void _quick_sort_(RandIt p, RandIt r) {
		if (std::distance(p, r) > 0) {
			RandIt q = partition(p, r);
			if (q != p) {
				_quick_sort_(p, q - 1);
			}
			_quick_sort_(q + 1, r);
		}
	}

	enum run_policy { sequential, parallel };

	template <typename RandIt>
	void quick_sort(RandIt p, RandIt r, run_policy policy) {
		if (policy == run_policy::parallel) {
			_quick_sort_p_(p, --r);
		}
		else {
			_quick_sort_(p, --r);
		}
	}

	template <typename T>
	std::list<T> parallel_quick_sort(std::list<T> input) {
		if (input.empty()) {
			return input;
		}
		std::list<T> result;
		result.splice(result.begin(), input, input.begin());
		T const& pivot = *result.begin();
		auto divide_point = std::partition(input.begin(), input.end(), [&](T const& t) {return t < pivot; });
		std::list<T> lower_part;
		lower_part.splice(lower_part.end(), input, input.begin(), divide_point);
		std::future<std::list<T>> new_lower(std::async(&parallel_quick_sort<T>, std::move(lower_part)));
		auto new_higher(parallel_quick_sort(std::move(input)));
		result.splice(result.end(), new_higher);
		result.splice(result.begin(), new_lower.get());
		return result;
	}

	template <typename T>
	std::list<T> sequential_quick_sort(std::list<T> input) {
		if (input.empty()) {
			return input;
		}
		std::list<T> result;
		result.splice(result.begin(), input, input.begin());
		T const& pivot = *result.begin();
		auto divide_point = std::partition(input.begin(), input.end(), [&](T const& t) {return t < pivot; });
		std::list<T> lower_part;
		lower_part.splice(lower_part.end(), input, input.begin(), divide_point);
		auto new_lower(sequential_quick_sort(std::move(lower_part)));
		auto new_higher(sequential_quick_sort(std::move(input)));
		result.splice(result.end(), new_higher);
		result.splice(result.begin(), new_lower);
		return result;
	}

	template <typename RandIt>
	struct sorter {
		struct chunk_to_sort {
			//RandIt data_begin, data_end;
			std::pair<RandIt, RandIt> data_bounds;
			std::promise<bool> promise;

			chunk_to_sort(const std::pair<RandIt, RandIt>& r) : data_bounds(r) {}
			chunk_to_sort(std::pair<RandIt, RandIt>&& r) : data_bounds(std::move(r)) {}
		};
		threadsafe_queue <chunk_to_sort> chunks;
		std::vector<std::thread> threads;
		const unsigned int max_thread_count;
		std::atomic<bool> end_of_data;
		
		sorter() : max_thread_count(std::thread::hardware_concurrency() - 1), end_of_data(false) {}
		~sorter() {
			end_of_data = true;
			for (unsigned int i = 0; i < threads.size(); ++i) {
				threads[i].join();
			}
		}

		void try_sort_chunk() {
			std::shared_ptr<chunk_to_sort> chunk = chunks.try_pop();
			if (chunk) {
				sort_chunk(chunk);
			}
		}

		bool do_sort(RandIt p, RandIt r) {
			
			if (std::distance(p, r) <= 0) {
				return true;
			}
			RandIt q = partition(p, r);
			
			if (q != p) {
				chunk_to_sort left_chunk({ p, q - 1 });
				std::future<bool> done = left_chunk.promise.get_future();
				chunks.push(std::move(left_chunk));
			
				if (threads.size() < max_thread_count) {
					threads.push_back(std::thread(&sorter<RandIt>::sort_thread, this));
				}

				while (done.wait_for(std::chrono::seconds(0)) != std::future_status::ready) {
					try_sort_chunk();
				}
			}
			
			chunk_to_sort right_chunk({ q + 1, r });
			do_sort(right_chunk.data_bounds.first, right_chunk.data_bounds.second);

			return true;
		}

		void sort_chunk(std::shared_ptr<chunk_to_sort> const& chunk) {
			chunk->promise.set_value(do_sort(chunk->data_bounds.first, chunk->data_bounds.second));
		}

		void sort_thread() {
			while (!end_of_data) {
				try_sort_chunk();
				std::this_thread::yield();
			}
		}
	};

	template <typename RandIt>
	struct sorter_tp {
		thread_pool pool;

		bool do_sort(RandIt p, RandIt r) {
			if (std::distance(p, r) <= 0) {
				return true;
			}
			RandIt q = partition(p, r);

			if (q != p) {
				std::future<bool> done = pool.submit(std::bind(&sorter_tp::do_sort, this, p, q - 1));
				
				while (done.wait_for(std::chrono::seconds(0)) != std::future_status::ready) {
					pool.run_pending_task();
				}
			}

			do_sort(q + 1, r);

			return true;
		}
	};

	
	template <typename RandIt>
	void parallel_quick_sort_with_intergrated_tp(RandIt p, RandIt r) {
		sorter<RandIt> s;
		s.do_sort(p, --r);
		return;
	}

	template <typename RandIt>
	void parallel_quick_sort_with_tp(RandIt p, RandIt r) {
		sorter_tp<RandIt> s;
		s.do_sort(p, --r);
		return;
	}
}