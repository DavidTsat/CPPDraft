#include <iostream>
#include <chrono>
#include <random>
#include <vector>

#include "parallel_partial_sum.h"

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
    std::vector<int> v(99999999);

    random_fill(v.begin(), v.end(), 1, 10);

   
    std::vector<int> vv(v);
    
 
    auto t1 = measure_performance(DSTL::parallel_partial_sum<std::vector<int>::iterator, std::vector<int>::iterator>, v.begin(), v.end(), v.begin());
	
    auto t2 = measure_performance(std::partial_sum< std::vector<int>::iterator, std::vector<int>::iterator>, vv.begin(), vv.end(), vv.begin());

    std::cout << "parallel partial_sum time: " << t1 << std::endl;
    std::cout << "std partial_sum time: " << t2 << std::endl;

    return 0;
}
