#include <iostream>
#include <random>
#include "accumulate.h" 

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
    f(std::forward<Fargs>(fargs)...);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;

    return time / std::chrono::milliseconds(1);
}

int main() {
    unsigned int vec_size = 120257005;

    std::vector<int> v(vec_size);

    random_fill(v.begin(), v.end()); 

    auto t = measure_performance(DSTL::parallel_accumulate<std::vector<int>::const_iterator, int, std::plus<int>>, v.cbegin(), v.cend(), 0, std::plus<int>());
    auto tt = measure_performance(std::accumulate<std::vector<int>::const_iterator, int>, v.cbegin(), v.cend(), 0);

    std::cout << "parallel_accumulate time: " << t << std::endl;
    std::cout << "std::accumulate time: " << tt << std::endl;

    auto aa = DSTL::parallel_accumulate(v.cbegin(), v.cend(), 0);
    auto aaa = std::accumulate(v.cbegin(), v.cend(), 0);
    std::cout << (aa == aaa);
    return 0;
}