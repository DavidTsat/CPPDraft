#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cassert>

#include "dsort.h"

std::vector<int> random_vector(std::size_t sz, int left_bound=-99999, int right_bound=99999) {
    std::vector<int> vec(sz);
    std::random_device rnd_device;
    
    std::mt19937 mersenne_engine{ rnd_device() }; 
    std::uniform_int_distribution<int> dist{ left_bound, right_bound };

    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };

    generate(begin(vec), end(vec), gen);

    return vec;
}

int main() {
 //   std::vector<int> v({ 2,1 });
    for (int i = 0; i < 10; ++i) {
        std::vector<int> v = random_vector(20000);
        std::vector<int> vv = v;

        DSTL::quick_sort(v.begin(), v.end());
        std::sort(vv.begin(), vv.end());
        assert(v == vv);
        std::cout << i << std::endl;
    }

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