#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <list>

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
    std::list<int> v(2400007);

    random_fill(v.begin(), v.end(), 0,5);

   
    std::list<int> vv(v);
    std::list<int> vvv(v);
 
    auto t1 = measure_performance(DSTL::parallel_partial_sum_improved<std::list<int>::iterator, std::list<int>::iterator>, v.begin(), v.end(), v.begin());
	
   // auto t2 = measure_performance(std::partial_sum< std::list<int>::iterator, std::list<int>::iterator>, vv.begin(), vv.end(), vv.begin());

    auto t2 = measure_performance(DSTL::parallel_partial_sum_<std::list<int>::iterator>, vv.begin(), vv.end());

    auto t3 = measure_performance(std::partial_sum< std::list<int>::iterator, std::list<int>::iterator>, vvv.begin(), vvv.end(), vvv.begin());

    std::cout << "parallel partial_sum time: " << t1 << std::endl;
    std::cout << "parallel partial_sum_ time: " << t2 << std::endl;
    std::cout << "std partial_sum time: " << t3 << std::endl;
    std::cout << std:: endl << (v == vvv) <<std::endl;

   
  /*
    for (int i : v) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    for (int i : vv) {
        std::cout << i << ' ';
    }
    */
    std::cout << std::endl;

    return 0;
}
