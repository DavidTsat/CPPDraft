#include <iostream>
#include <atomic>
#include <cassert>
#include <chrono>
#include <mutex>
#include <future>
#include <vector>
#include <random>
#include <string>
#include <list>

class A
{
public:
	A() : m_i(0) { }

	int m_i;
};

class B
{
public:
	B() : m_d(0.0) { }

	double m_d;
};

class C
	: public A
	, public B
{
public:
	C() : m_c('a') { }

private:
	char m_c;
};

int main()
{
	C c;
	A* pa = &c;
	B* pb = &c;

	

	const int x = (pa == &c) ? 1 : 2;
	const int y = (pb == &c) ? 3 : 4;
	const int z = (reinterpret_cast<char*>(pa) == reinterpret_cast<char*>(pb)) ? 5 : 6;

	std::cout << x << y << z << std::endl;

	return 0;
}



/*
template <typename T>
class Sync_queue {
public:
	void put(const T& val) {
		std::unique_lock<std::mutex> lck(mtx);
		cond.wait(lck, [this] {return q.size() < 1; });
		q.push_back(val);
		std::cout << "producer message: " << val << " AAAAAAAAAAAAAAAAAAA    " <<q.size() << std::endl;
		cond.notify_one();
	}
	//void put(T&& val);
	void get(T& val) {
		std::unique_lock<std::mutex> lck(mtx);
		cond.wait(lck, [this] {return !q.empty(); });
		val = q.front();
		q.pop_front();
		std::cout << "consumer message: " << val << std::endl;
		cond.notify_one();
	}

private:
	std::mutex mtx;
	std::condition_variable cond;
	std::list<T> q;
};

Sync_queue<std::string> mq;

void producer() {
	int i = 0;
	while (true) {
		std::string message(std::to_string(i++));
		mq.put("message from producer: " + message);
	}
}

void consumer() {
	int i = 0;
	while (true) {
		std::string message;
		mq.get(message);
	}
}

int main() {
	std::thread t1(producer);
	std::thread t2(consumer);

	t1.join();
	t2.join();

	return 0;
}
*/