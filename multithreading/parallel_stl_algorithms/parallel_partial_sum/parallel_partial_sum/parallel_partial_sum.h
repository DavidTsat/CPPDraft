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

	template <typename InIt, typename OutIt>
	void parallel_partial_sum_improved(InIt begin, InIt end, OutIt out_begin) {
		using value_type = typename std::iterator_traits<InIt>::value_type;

		auto dist = std::distance(begin, end);
		unsigned chunks_number = std::thread::hardware_concurrency();
		unsigned chunk_length = unsigned(dist / chunks_number);

		if (chunk_length == 0) {
			std::partial_sum(begin, end, out_begin);
			return;
		}

		{
			struct process_chunk {
				/*
				void operator()(InIt begin, InIt last,
					std::future<value_type>* previous_end_value,
					std::promise<value_type>* end_value)
				{
					try
					{
						InIt end = last;
						++end;
						std::partial_sum(begin, end, begin);
						if (previous_end_value)
						{
							auto addend = previous_end_value->get();
							*last += addend;
							if (end_value)
							{
								end_value->set_value(*last);
							}
							std::for_each(begin, last, [addend](value_type& item)
								{
									item += addend;
								});
						}
						else if (end_value)
						{
							end_value->set_value(*last);
						}
					}
					catch (...)
					{
						if (end_value)
						{
							end_value->set_exception(std::current_exception());
						}
						else
						{
							throw;
						}
					}
				}
				*/
				void operator()(InIt chunk_begin, InIt chunk_end, OutIt out_chunk_begin, std::future<value_type>* previous_last_value, std::promise<value_type>* current_last_value) {
					
					
					try {
						std::partial_sum(chunk_begin, chunk_end, out_chunk_begin);

						std::reverse_iterator<OutIt> out_chunk_end_reversed = std::make_reverse_iterator(out_chunk_begin);
						std::advance(out_chunk_begin, std::distance(chunk_begin, chunk_end));
						std::reverse_iterator<OutIt> out_chunk_begin_reversed = std::make_reverse_iterator(out_chunk_begin);

						if (previous_last_value) {
							const value_type& prev_last_val = previous_last_value->get();

							*out_chunk_begin_reversed += prev_last_val;
							current_last_value->set_value(*out_chunk_begin_reversed);

							std::for_each(++out_chunk_begin_reversed, out_chunk_end_reversed, [&prev_last_val](value_type& v) { v += prev_last_val; });
						}
						else if (current_last_value != nullptr){
							current_last_value->set_value(*out_chunk_begin_reversed);
						}
					}
					catch (std::exception& e) {
						std::cout << e.what() << std::endl;
						current_last_value->set_exception(std::current_exception());
					}
					
				}
			};

			std::vector<std::thread> chunk_workers;
			std::vector<std::future<value_type>> previous_last_values;
			previous_last_values.reserve(chunks_number);
			std::vector<std::promise<value_type>> current_last_values(chunks_number);

			join_threads joiner(chunk_workers);

			InIt chunk_begin = begin;
			InIt chunk_end = chunk_begin;
			OutIt chunk_out_begin = out_begin;

			for (unsigned i = 0; i < chunks_number; ++i) {

				std::advance(chunk_end, chunk_length);

				chunk_workers.emplace_back(process_chunk(), chunk_begin, chunk_end, chunk_out_begin, i == 0 ? nullptr : &previous_last_values[i-1], &current_last_values[i]);
				
				std::advance(chunk_out_begin, chunk_length);
				std::advance(chunk_begin, chunk_length);
				
				previous_last_values.push_back(current_last_values[i].get_future());
			}
			assert(chunk_begin == chunk_end);

			std::partial_sum(chunk_begin, end, chunk_out_begin);
			const value_type& lv = previous_last_values.back().get();
			std::for_each(chunk_begin, end, [&lv](value_type& v) {v += lv; });

		//	process_chunk()(chunk_begin, end, chunk_out_begin, &previous_last_values.back(), nullptr);
//			chunk_workers.emplace_back(process_chunk(), chunk_begin, end, chunk_out_begin, &previous_last_values[chunks_number - 1], nullptr);

	//		std::partial_sum(chunk_begin, end, chunk_out_begin);
		}

		/*
		InIt chunk_begin = out_begin;
		std::advance(chunk_begin, chunk_length);
		InIt chunk_end = chunk_begin;
		std::advance(out_begin, chunk_length - 1);


		std::advance(out_begin, chunk_length);
		std::for_each(chunk_begin, end, [&out_begin](typename std::iterator_traits<OutIt>::value_type& v) {v += *out_begin; });
		*/
	}


    template<typename Iterator>
    void parallel_partial_sum_(Iterator first, Iterator last)
    {
        typedef typename Iterator::value_type value_type;

        struct process_chunk
        {
            void operator()(Iterator begin, Iterator last,
                std::future<value_type>* previous_end_value,
                std::promise<value_type>* end_value)
            {
                try
                {
                    Iterator end = last;
                    ++end;
                    std::partial_sum(begin, end, begin);
                    if (previous_end_value)
                    {
                        auto addend = previous_end_value->get();
                        *last += addend;
                        if (end_value)
                        {
                            end_value->set_value(*last);
                        }
                        std::for_each(begin, last, [addend](value_type& item)
                            {
                                item += addend;
                            });
                    }
                    else if (end_value)
                    {
                        end_value->set_value(*last);
                    }
                }
                catch (...)
                {
                    if (end_value)
                    {
                        end_value->set_exception(std::current_exception());
                    }
                    else
                    {
                        throw;
                    }
                }
            }
        };
        unsigned long const length = std::distance(first, last);
        if (!length)
            return;
        unsigned long const min_per_thread = 25;
        unsigned long const max_threads =
            (length + min_per_thread - 1) / min_per_thread;
        unsigned long const hardware_threads =
            std::thread::hardware_concurrency();
        unsigned long const num_threads =
            std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
        unsigned long const block_size = length / num_threads;
        typedef typename Iterator::value_type value_type;
        std::vector<std::thread> threads(num_threads - 1);
        std::vector<std::promise<value_type> > end_values(num_threads - 1);
        std::vector<std::future<value_type> > previous_end_values;
        previous_end_values.reserve(num_threads - 1);
        join_threads joiner(threads);
        Iterator block_start = first;
        for (unsigned long i = 0; i < (num_threads - 1); ++i)
        {
            Iterator block_last = block_start;
            std::advance(block_last, block_size - 1);
            threads[i] = std::thread(process_chunk(),
                block_start, block_last,
                (i != 0) ? &previous_end_values[i - 1] : 0,
                &end_values[i]);
            block_start = block_last;
            ++block_start;
            previous_end_values.push_back(end_values[i].get_future());
        }
        Iterator final_element = block_start;
        std::advance(final_element, std::distance(block_start, last) - 1);
        process_chunk()(block_start, final_element, (num_threads > 1) ? &previous_end_values.back() : 0, 0);
    }
}