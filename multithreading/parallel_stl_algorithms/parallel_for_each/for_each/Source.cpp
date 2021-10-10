#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>
#include <functional>
#include <thread>
#include <future>

template <typename ForIt, typename F>
inline void dfor_each(ForIt begin, ForIt end, F f) {
	for (; begin != end; ++begin) {
		f(*begin);
	}
}

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

/*
without futures and bind - most optimal
*/
template <typename ForIt, typename F>
F d_parallel_for_each(ForIt begin, ForIt end, F&& f) {
    auto range_length = std::distance(begin, end);
    auto thread_max_count = std::thread::hardware_concurrency() - 1;

    unsigned chunk_length = unsigned(range_length / thread_max_count);
    std::vector<std::thread> threads;
    join_threads j(threads);
    threads.reserve(thread_max_count);
   
    for (unsigned i = 0; i < thread_max_count; ++i) {
        ForIt chunk_end = begin;
        std::advance(chunk_end, chunk_length);
        std::thread t(std::for_each<ForIt, F>, begin, chunk_end, f);
        threads.push_back(std::move(t));
        begin = chunk_end;
    }
 
    dfor_each(begin, end, f);

    return f;
}

/*
using bind
*/
template <typename ForIt, typename F>
F d_parallel_for_each1(ForIt begin, ForIt end, F&& f) {
    auto range_length = std::distance(begin, end);
    auto thread_max_count = std::thread::hardware_concurrency()-1;

    unsigned chunk_length = unsigned (range_length / thread_max_count);
    std::vector<std::future<void>> futures;
    futures.reserve(thread_max_count);

    for (unsigned i = 0; i < thread_max_count; ++i) {
        std::packaged_task<void()> seq_for_each(std::bind(dfor_each<ForIt,F>, begin + i * chunk_length, begin + (i + 1) * chunk_length, f));
        futures.push_back(seq_for_each.get_future());
        std::thread t(std::move(seq_for_each));
        t.detach();
    }
    dfor_each(begin + thread_max_count * chunk_length, end, f);

    for (auto& future : futures) {
        future.get();
    }
    
    return f;
}

/*
without bind, using direct call
*/
template <typename ForIt, typename F>
F d_parallel_for_each2(ForIt begin, ForIt end, F&& f) {
    auto range_length = std::distance(begin, end);
    auto thread_max_count = std::thread::hardware_concurrency() - 1;

    unsigned chunk_length = unsigned(range_length / thread_max_count);
    std::vector<std::future<void>> futures;
    futures.reserve(thread_max_count);

    for (unsigned i = 0; i < thread_max_count; ++i) {
        std::packaged_task<void(ForIt, ForIt, F)> seq_for_each(dfor_each<ForIt, F>);
        futures.push_back(seq_for_each.get_future());
        std::thread t(std::move(seq_for_each), begin + i * chunk_length, begin + (i + 1) * chunk_length, f);
        t.detach();
    }
    dfor_each(begin + thread_max_count * chunk_length, end, f);

    for (auto& future : futures) {
        future.get();
    }

    return f;
}

template <typename ForwardIt>
void random_fill(ForwardIt f, ForwardIt l, int left_bound = -99999, int right_bound = 99999) {
    std::random_device rnd_device;

    std::mt19937 mersenne_engine{ rnd_device() };
    std::uniform_int_distribution<int> dist{ left_bound, right_bound };

    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };

    generate(f, l, gen);
}

template <typename F, typename... Fargs>
auto measure_performance(F f, Fargs&&... fargs) {
    auto start_time = std::chrono::high_resolution_clock::now();
    f(std::forward<Fargs&&>(fargs)...);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;

    return time / std::chrono::milliseconds(1);
}

int main() {

    std::vector<int> v(10000000);

    random_fill(v.begin(), v.end());
    auto vv(v);

    auto t1 = measure_performance(d_parallel_for_each<std::vector<int>::iterator,std::function<void(int&)>>, v.begin(), v.end(), [](int& i) {++i; });
    auto t2 = measure_performance(std::for_each<std::vector<int>::iterator, std::function<void(int&)>>, vv.begin(), vv.end(), [](int& i) {++i; });

  
    std::cout << "parallel time: " << t1 << std::endl;
    std::cout << "std::for_each time: " << t2 << std::endl;

    std::cout << (v == vv) << std::endl;
    std::cout << std::endl;
    return 0;
}
