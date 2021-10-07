#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cassert>
#include <list>
#include <functional>
#include <type_traits>

#include "dsort.h"

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
auto measure_performance(F f, Fargs... fargs) {
    auto start_time = std::chrono::high_resolution_clock::now();
    f(std::forward<Fargs>(fargs)...);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;

    return time / std::chrono::milliseconds(1);
}


int main() {
    constexpr int sz = 500;
    std::vector<int> v(sz);
    std::vector<int> v2(sz);
    std::vector<int> v3(sz);

    random_fill(v.begin(), v.end());
    random_fill(v2.begin(), v2.end());
    random_fill(v3.begin(), v3.end());

    auto t = measure_performance (DSTL::quick_sort<std::vector<int>::iterator>, v.begin(), v.end(), DSTL::run_policy::sequential);

    auto t2 = measure_performance(DSTL::quick_sort<std::vector<int>::iterator>, v2.begin(), v2.end(), DSTL::run_policy::parallel);
    

    auto vvd(v3);

    auto t3 = measure_performance(DSTL::parallel_quick_sort_<std::vector<int>::iterator>, v3.begin(), v3.end());

    

    std::sort(vvd.begin(), vvd.end());
    std::cout << (vvd == v3);

    std::cout << "sequential qsort: " << t << "ms to run.\n";
    std::cout << "parallel qsort recursive threads: " << t2 << "ms to run.\n";
    std::cout << "parallel qsort optimal threads: " << t3 << "ms to run.\n";
    

    /*
    std::list<int> l(sz);
    random_fill(l.begin(), l.end());
    std::list<int> l2(sz);
    
    random_fill(l.begin(), l.end());
    random_fill(l2.begin(), l2.end());

    auto tl = measure_performance(DSTL::sequential_quick_sort<int>, l);

    auto tl2 = measure_performance(DSTL::parallel_quick_sort<int>, l2);


    std::cout << std::endl;

    std::cout << "sequential qsort: " << tl << "ms to run.\n";
    std::cout << "parallel qsort: " << tl2 << "ms to run.\n";

    */

  /*
  * std::list<int> l3(l);
  *  l3.sort();
    assert(l == l2);
    assert(l == l3);
  * for (int i = 0; i < 10; ++i) {
        std::vector<int> v(2000);
        random_fill(v.begin(), v.end());
        std::vector<int> vv(v);

        DSTL::quick_sort(v.begin(), v.end(), DSTL::run_policy::parallel);
        std::sort(vv.begin(), vv.end());
        assert(v == vv);
        std::cout << i << std::endl;
    }

    for (int i : vv) {
        std::cout << i << ' ';
    }
    */

    
    std::cout << std::endl;
	return 0;
}