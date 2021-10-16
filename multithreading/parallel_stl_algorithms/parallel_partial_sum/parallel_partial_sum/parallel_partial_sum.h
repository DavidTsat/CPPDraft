#pragma once
#include <iterator>
#include <thread>
#include <future>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <type_traits>
#include <chrono>

namespace DSTL {

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

	template <typename InIt, typename OutIt>
	void parallel_partial_sum(InIt begin, InIt end, OutIt out_begin) {
		auto dist = std::distance(begin, end);
		unsigned chunks_number = std::thread::hardware_concurrency();
		unsigned chunk_length = unsigned(dist / chunks_number);
	
		if (chunk_length == 0) {
			std::partial_sum(begin, end, out_begin);
			return;
		}

		{
			std::vector<std::thread> chunk_partial_sum_workers;
			chunk_partial_sum_workers.reserve(chunks_number);
			join_threads joiner(chunk_partial_sum_workers);

			InIt chunk_begin = begin;
			InIt chunk_end = chunk_begin;
			OutIt chunk_out_begin = out_begin;
		
			for (unsigned i = 0; i < chunks_number; ++i) {

				std::advance(chunk_end, chunk_length);

				chunk_partial_sum_workers.emplace_back(std::partial_sum<InIt, OutIt>, chunk_begin, chunk_end, chunk_out_begin);

				std::advance(chunk_out_begin, chunk_length);
				std::advance(chunk_begin, chunk_length);
			}
			assert(chunk_begin == chunk_end);

			std::partial_sum(chunk_begin, end, chunk_out_begin);	
		}

		InIt chunk_begin = out_begin;
		std::advance(chunk_begin, chunk_length);
		InIt chunk_end = chunk_begin;
		std::advance(out_begin, chunk_length - 1);

		std::mutex cv_m;
		std::condition_variable cv;

		for (unsigned i = 0; i < chunks_number/2; ++i) {
		
			std::advance(chunk_end, chunk_length);
			std::atomic<bool> last_element_updated = false;

			std::thread sum_propogater([chunk_begin, chunk_end, out_begin, &last_element_updated, &cv, &cv_m]() {auto it = std::make_reverse_iterator<OutIt>(chunk_end); cv_m.lock(); *it++ += *out_begin; last_element_updated = true; cv_m.unlock(); cv.notify_one(); while (it != std::make_reverse_iterator<OutIt>(chunk_begin)) *it++ += *out_begin; });
	
			if (i == chunks_number / 2 - 1) {
				std::advance(chunk_begin, chunk_length);
				if (sum_propogater.joinable()) {
					sum_propogater.join();
				}
				break;
			}
			std::advance(chunk_begin, chunk_length);
			std::advance(chunk_end, chunk_length);
			
			std::unique_lock<std::mutex> ul(cv_m);
			cv.wait(ul, [&]() {return last_element_updated == true; });
		
			std::advance(out_begin, chunk_length);

			ul.unlock();

			std::for_each(chunk_begin, chunk_end, [&](typename std::iterator_traits<OutIt>::value_type& v) {v += *out_begin; });

			std::advance(chunk_begin, chunk_length);
			std::advance(out_begin, chunk_length);
			
			if (sum_propogater.joinable()) {
				sum_propogater.join();
			}
		}

		std::advance(out_begin, chunk_length);
		std::for_each(chunk_begin, end, [&out_begin](typename std::iterator_traits<OutIt>::value_type& v) {v += *out_begin; });
	}


}