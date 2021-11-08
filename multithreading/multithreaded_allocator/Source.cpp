#include <iostream>
#include <type_traits>
#include <vector>
#include <memory>
#include <algorithm>
#include <thread>
#include <future>
#include <list>
#include <mutex>

template <typename T>
class my_simple_allocator {
	constexpr static std::size_t MAX_AVAILABLE_MEMORY = 100 * sizeof(T);
	static std::size_t memory_left;
	static std::mutex memory_guard;
	static std::condition_variable memory_guard_condition;
public:
	using value_type = T;
	using is_always_equal = std::true_type;
	using propogate_on_container_move_assignment = std::true_type;
	using size_type = std::size_t;

	my_simple_allocator() {}

	template <typename Q>
	my_simple_allocator(const my_simple_allocator<Q>&) noexcept { }

	T* allocate(size_type n) {
		std::unique_lock<std::mutex> l(memory_guard);
		memory_guard_condition.wait(l, [this, n]() {return memory_left >= n * sizeof(T); });
		auto p = static_cast<T*>(::operator new(n * sizeof(T)));
		memory_left -= n * sizeof(T);
		l.unlock();
		std::cout << "allocated " << n * sizeof(T) << " bytes\n";
		return p;
	}

	void deallocate(T* p, size_type n) {
		{
			std::lock_guard<std::mutex> l(memory_guard);
			::operator delete(p);
			memory_left += n * sizeof(T);
			memory_guard_condition.notify_all();
		}
		std::cout << "deallocated " << n * sizeof(T) << " bytes \n";
	}

	static size_type get_memory_left() {
		return memory_left;
	}

	constexpr size_type max_size() const { 
		return MAX_AVAILABLE_MEMORY;
	}

	template<typename Q>
	struct rebind_alloc {
		typedef my_simple_allocator<Q> other;
	};
};

template <typename T>
std::size_t my_simple_allocator<T>::memory_left = my_simple_allocator::MAX_AVAILABLE_MEMORY;

template <typename T>
std::mutex my_simple_allocator<T>::memory_guard;

template <typename T>
std::condition_variable my_simple_allocator<T>::memory_guard_condition;

template <typename T> 
bool operator==(const my_simple_allocator<T>& l, const my_simple_allocator<T>& r) {
	return true;
}	

template <typename T>
bool operator!=(const my_simple_allocator<T>& l, const my_simple_allocator<T>& r) {
	return false;
}

void test() {
	std::vector<int, my_simple_allocator<int>> v; // 
	v.reserve(90);  // memory_left == 10*sizeof(int)

	for (int i = 0; i < 10; ++i) {
		v.push_back(i);
	}

	std::thread t1([]() {
		std::vector<int, my_simple_allocator<int>> v1;
		v1.reserve(95); // заблокируется так как memory_left == 10*sizeof(int)
		//...
		std::cout << "thread 1 finished\n";
		});

	std::thread t2([]() {
		std::vector<int, my_simple_allocator<int>> v2;
		v2.reserve(20); // заблокируется так как memory_left == 10*sizeof(int)
		//...
		std::cout << "thread 2 finished\n";
		});
	std::this_thread::sleep_for(std::chrono::microseconds(1000));

	v.shrink_to_fit(); // сначала вызовет allocate(10), после чего deallocate(90) и сигнализирует потоку 2. memory_left == 90

	t2.join();
	v.clear();
	v.shrink_to_fit(); // освободит всю память 100 и сигнализирует потоку 1
	t1.join();
}
int main() {

	test();
	return 0;
}