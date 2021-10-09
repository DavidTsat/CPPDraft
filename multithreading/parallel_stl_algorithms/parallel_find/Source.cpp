#include "find.h"
#include <chrono>
#include <numeric>
#include <mutex>
#include "thread_pool.h"

template <typename It, typename T>
class accumulate_block_ {
    T acc = T();
public:
    void operator()(It start, It end, T init) {
        for (; start != end; ++start) {
            acc = std::move(init) + *start;
        }
    }

    T get() {
        return acc;
    }
};

std::mutex m;

/*
template<typename Iterator, typename T>
struct accumulate_block {

    T operator()(Iterator first, Iterator last, T & result) {

        T rr{};
        for (; first != last; ++first) {
            rr += *first;
        }

        std::unique_lock<std::mutex> u(m);
        result += rr;
        return result;
    //    std::cout << result << " ::: " << std::this_thread::get_id() << std::endl;
    }
};
*/

template<typename Iterator, typename T>
struct accumulate_block {
    T operator()(Iterator first, Iterator last) {
        return std::accumulate(first, last, T());
    }
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T& init, unsigned int block_size) {
    unsigned long const length = std::distance(first, last);
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
        //pool.submit([&block_start, &block_end, &init] {accumulate_block<Iterator, T>()(block_start, block_end, init); });
        
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
    //std::this_thread::sleep_for(std::chrono::milliseconds(10));
   // std::this_thread::sleep_for(std::chrono::seconds(1));

    /*
    T last_result = accumulate_block<Iterator, T>()(block_start, last);
    T result = init;
    for (unsigned long i = 0; i < (num_blocks - 1); ++i) {
        result += futures[i].get();
    }
    result += last_result;
    return result;
    */
}

int main() {
    int r = 0;
    unsigned int block_size = 1000000;
    unsigned int vec_size = std::thread::hardware_concurrency() * block_size;
 
    std::vector<int> v(vec_size);

    std::random_device rnd_device;
    std::mt19937 mersenne_engine{ rnd_device() };  // Generates random integers
    std::uniform_int_distribution<int> dist{ -50000, 50000 };

    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };

    std::generate(begin(v), end(v), gen);


    auto start_time1 = std::chrono::high_resolution_clock::now();

    int c = parallel_accumulate<std::vector<int>::const_iterator, int>(v.cbegin(), v.cend(), r, block_size);

    auto end_time1 = std::chrono::high_resolution_clock::now();
    auto time1 = end_time1 - start_time1;

    // -----------------------------------------

    auto start_time2 = std::chrono::high_resolution_clock::now();

    int cc = std::accumulate(v.cbegin(), v.cend(), 0);
    auto end_time2 = std::chrono::high_resolution_clock::now();
    auto time2 = end_time2 - start_time2;
    
    std::cout << "mine with thread pool: " << c << " time: " << time1 / std::chrono::milliseconds(1) << std::endl;
    std::cout << "std sequential : " << cc << " time: " << time2 / std::chrono::milliseconds(1) << std::endl;
    return 0;
}

/*
int main() {

    unsigned int vec_size = std::thread::hardware_concurrency() * 20000;

    std::vector<int> v(vec_size);

    std::random_device rnd_device;
    std::mt19937 mersenne_engine{ rnd_device() };  // Generates random integers
    std::uniform_int_distribution<int> dist{ -50000, 50000 };

    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };

    
    std::generate(begin(v), end(v), gen);


    int find_val = 50;


    auto start_time1 = std::chrono::high_resolution_clock::now();
    std::vector<int>::iterator c = pdfind(v.begin(), v.end(), find_val);
    auto end_time1 = std::chrono::high_resolution_clock::now();
    auto time1 = end_time1 - start_time1;

    if (c != v.end()) {
        std::cout << "\nfound: " << *c;
        std::cout << "\ntime: " << time1 / std::chrono::milliseconds(1) << std::endl;
    }

    auto start_time2 = std::chrono::high_resolution_clock::now();
    std::vector<int>::iterator cc = std::find(v.begin(), v.end(), find_val);
    auto end_time2 = std::chrono::high_resolution_clock::now();
    auto time2 = end_time2 - start_time2;

    if (cc != v.end()) {
        std::cout << "\nstd found: " << *c;
        std::cout << "\ntime: " << time2 / std::chrono::milliseconds(1) << std::endl;
    }
    
    auto start_time3 = std::chrono::high_resolution_clock::now();
    int* ccc = pfind(v, [find_val](int c) {return c == find_val; });
    auto end_time3 = std::chrono::high_resolution_clock::now();
    auto time3 = end_time3 - start_time3;
    if (ccc) {
        std::cout << "\nd found: " << *c;
        std::cout << "\ntime: " << time3 / std::chrono::milliseconds(1) << std::endl;
    }


	return 0;
}
*/