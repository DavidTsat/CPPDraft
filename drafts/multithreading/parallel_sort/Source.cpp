#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cassert>
#include <list>

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


int main() {
    std::list<int> l(100);
    random_fill(l.begin(), l.end());
    std::list<int> ll(l);

    for (int i = 0; i < 10; ++i) {
        std::vector<int> v(2000);
        std::vector<int> vv(v);

        DSTL::quick_sort(v.begin(), v.end());
        std::sort(vv.begin(), vv.end());
        assert(v == vv);
        std::cout << i << std::endl;
    }

    l = DSTL::sequential_quick_sort(l);
    ll.sort();
    assert(l == ll);

    for (int i : l) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

  /*
    for (int i : vv) {
        std::cout << i << ' ';
    }
    */

    
    std::cout << std::endl;
	return 0;
}