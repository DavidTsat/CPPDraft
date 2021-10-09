#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>
#include <functional>

template <typename ForIt, typename F>
F dfor_each(ForIt begin, ForIt end, F f) {

	for (; begin != end; ++begin) {
		f(*begin);
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
auto measure_performance(F f, Fargs... fargs) {
    auto start_time = std::chrono::high_resolution_clock::now();
    f(std::forward<Fargs>(fargs)...);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;

    return time / std::chrono::milliseconds(1);
}


struct Foo {
    void display_greeting() {
        std::cout << "Hello, world.\n";
    }
    void display_number(int i) {
        std::cout << "number: " << i << '\n';
    }
    int add_xy(int x, int y) {
        return data + x + y;
    }


    int data = 7;
};

int main() {

    

    std::vector<int> v(10);

    random_fill(v.begin(), v.end());
    
    Foo ff;
    ff.display_greeting();
    auto dd = std::mem_fn(&Foo::display_greeting);
    dd(ff);

    for (int i : v) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    auto d = dfor_each<std::vector<int>::iterator, std::function<void(int&)>>;
    d(v.begin(), v.end(), [](int& i) {++i; });


    for (int i : v) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

}
