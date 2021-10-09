#include <chrono>
#include <iostream>
#include "find.h"

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
auto measure_performance(F&& f, Fargs&&... fargs) {
    auto start_time = std::chrono::high_resolution_clock::now();
    f(std::forward<Fargs>(fargs)...);
   
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;

    return time / std::chrono::milliseconds(1);
}


int main() {
    int r = 0;
    unsigned int block_size = 10000;
    unsigned int vec_size = std::thread::hardware_concurrency() * block_size;
 
    std::vector<int> v(vec_size);

    random_fill(v.begin(), v.end(), -10*(int)block_size, 10*(int)block_size);


    int find_val = 50;

    
    auto t1 = measure_performance(pdfind<std::vector<int>::const_iterator, int>, v.cbegin(), v.cend(), find_val);
   
    std::cout << "\ntime with parallel pdfind: " << t1 << std::endl;
   

 
    auto t2 = measure_performance(std::find<std::vector<int>::const_iterator, int>, v.cbegin(), v.cend(), find_val);

    std::cout << "\ntime with sequential std find: " << t2 << std::endl;

    

    auto t3 = measure_performance(pfind<std::function<bool(int)>, int>, v, [&find_val](int v) {return v == find_val; });
  
    std::cout << "\ntime with parallel pfind: " << t3 << std::endl;
 
   
	return 0;
}
