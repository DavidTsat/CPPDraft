#pragma once
#include <numeric>
#include <iterator>
#include <future>
#include "thread_pool.h"

namespace DSTL {

   /* template<typename Iterator, typename T>
    struct accumulate_chunk {
        T operator()(Iterator first, Iterator last) {
            return std::accumulate(first, last, T());
        }
    };*/


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

    template<typename Iterator, typename T, typename BinaryOperation>
    struct accumulate_chunk {
        void operator()(Iterator first, Iterator last, T& res, BinaryOperation op) {
            res = std::accumulate(first, last, T(), op);
        }
    };

    template<typename InputIt, typename T, typename BinaryOperation = std::plus<T>>
    T parallel_accumulate(InputIt first, InputIt last, T init, BinaryOperation op = std::plus<T>()) {
        const unsigned long length = std::distance(first, last);
        if (!length) {
            return init;
        }
        const unsigned chunk_minimal_length = 100;
        const unsigned num_chunks = std::thread::hardware_concurrency();
        const unsigned long chunk_size = (unsigned long)length / num_chunks;
        if (chunk_size < chunk_minimal_length) {
            return std::accumulate(first, last, init, op);
        }

        InputIt chunk_start = first;
        std::vector<T> results(num_chunks);
        {
            std::vector<std::thread> chunk_accumulaters(num_chunks - 1);
            join_threads joiner(chunk_accumulaters);

            for (unsigned i = 0; i < (num_chunks - 1); ++i) {
                InputIt chunk_end = chunk_start;
                std::advance(chunk_end, chunk_size);
                chunk_accumulaters[i] = std::thread(accumulate_chunk<InputIt, T, BinaryOperation>(), chunk_start, chunk_end, std::ref(results[i]), op);
                std::advance(chunk_start, chunk_size);
            }

            results[num_chunks - 1] = std::accumulate(chunk_start, last, T(), op);
        }

        return std::accumulate(results.cbegin(), results.cend(), init);
    }

   /* template <typename Iterator, typename T>
    T parallel_accumulate(Iterator first, Iterator last, T init) {
        const unsigned long length = std::distance(first, last);
        if (!length) {
            return init;
        }
        const unsigned num_chunks = std::thread::hardware_concurrency();
        const unsigned long chunk_size = (unsigned long)length / num_chunks;
        if (!chunk_size) {
            return std::accumulate(first, last, init);
        }
        
        std::vector<std::future<T>> futures(num_chunks - 1);
        thread_pool pool;
        Iterator chunk_start = first;

        accumulate_chunk<Iterator, T> a;
        for (unsigned i = 0; i < (num_chunks - 1); ++i) {
            Iterator chunk_end = chunk_start;
            std::advance(chunk_end, chunk_size);
            futures[i] = pool.submit(std::bind(a, chunk_start, chunk_end));
            chunk_start = chunk_end;
        }

        T result = init;
        T last_result = a(chunk_start, last);

        for (unsigned int i = 0; i < (num_chunks - 1); ++i) {
            result += futures[i].get();
        }
        result += last_result;
        return result;
    }*/
}