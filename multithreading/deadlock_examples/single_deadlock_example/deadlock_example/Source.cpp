#include <iostream>
#include <thread>
#include <future>

std::recursive_mutex m;

void print_args() {
	std::cout << "Не будет вызываться, но мы должны были определить эту функцию" << ' ';
}

template <typename FirstArg, typename ...RestArgs>
void print_args(FirstArg t, RestArgs&&... args) {
	m.lock();
	constexpr std::size_t num_args = sizeof...(args);
	if (num_args == 0) {
		std::cout << t << ' ';
		m.unlock();
		return;
	}

	std::cout << t << ' ';
	print_args(std::forward<RestArgs>(args)...);

	m.unlock();
}


int main() {

	
	print_args("David", 26, 'M', "Daria", 23);

	return 0;
}
