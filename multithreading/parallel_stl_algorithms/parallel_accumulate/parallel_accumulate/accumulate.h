#pragma once
#include <numeric>
#include <iterator>
#include <future>
#include "thread_pool.h"

namespace DSTL {

    template<typename Iterator, typename T>
    struct accumulate_block {
        T operator()(Iterator first, Iterator last) {
            return std::accumulate(first, last, T());
        }
    };

    template <typename Iterator, typename T>
    T parallel_accumulate(Iterator first, Iterator last, T init) {
        const unsigned long length = std::distance(first, last);
        const unsigned long block_size = (unsigned long)length / std::thread::hardware_concurrency();
        if (!length) {
            return init;
        }

        unsigned long const num_blocks = (length + block_size - 1) / block_size;
        std::vector<std::future<T>> futures(num_blocks - 1);
        thread_pool pool;
        Iterator block_start = first;

        accumulate_block<Iterator, T> a;
        for (unsigned long i = 0; i < (num_blocks - 1); ++i) {
            Iterator block_end = block_start;
            std::advance(block_end, block_size);
            futures[i] = pool.submit(std::bind(a, block_start, block_end));
            block_start = block_end;
        }

        T result = init;
        T last_result = a(block_start, last);

        for (unsigned int i = 0; i < (num_blocks - 1); ++i) {
            result += futures[i].get();
        }
        result += last_result;
        return result;
    }
}