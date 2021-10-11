#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>
#include <thread>
#include <future>
#include <cassert>

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

	template <typename It, typename Match>
	It find(It begin, It end, Match m) {
        
        struct find_in_chunk {
            void operator()(It chunk_begin, It chunk_end, Match m_, std::promise<It>* res, std::atomic<bool>* done) {
                try {
                    for (; chunk_begin != chunk_end && !done->load(); ++chunk_begin) {
                        if (*chunk_begin == m_) {
                            res->set_value(chunk_begin);
                            done->store(true);
                            return;
                        }
                    }
                }
                catch (...) {
                    res->set_exception(std::current_exception());
                    done->store(true);
                }
            }
        };
        std::atomic<bool> done = false;
        std::promise<It> res;
        std::vector<std::thread> threads;
        join_threads j(threads);

        auto range_length = std::distance(begin, end);
        auto thread_max_count = std::thread::hardware_concurrency() - 1;

        unsigned chunk_length = unsigned(range_length / thread_max_count);
     
        threads.reserve(thread_max_count);
        
        It& chunk_begin = begin;
        for (unsigned i = 0; i < thread_max_count; ++i) {
            It chunk_end = chunk_begin;
            std::advance(chunk_end, chunk_length);
            
            std::thread t(find_in_chunk(), chunk_begin, chunk_end, m, &res, &done);

            threads.push_back(std::move(t));
            chunk_begin = chunk_end;
        }

        find_in_chunk()(chunk_begin, end, m, &res, &done);
        
        if (done) {
            return res.get_future().get();
        }
        else {
            return end;
        }
	}
}