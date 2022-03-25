#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

enum policy { sequential, parallel };



template <typename It, typename F>
inline void seq_for_each(It b, It e, F f)
{
	/*
	while (b != e)
		f(*b++);
	*/
	for (; b != e; ++b) {
		f(*b);
	}

};

template <typename It, typename F>
void for_each_(policy p, It begin, It end, F f)
{
	/*
	auto seq_for_each = [&f](It b, It e)
	{
		while (b != e)
			f(*b++);
	};
	*/
	if (p == policy::sequential)
	{
		//	seq_for_each(begin, end, f);
		std::for_each(begin, end, f);
	}
	else
	{
		size_t thread_count = thread::hardware_concurrency();
		//	size_t thread_count = 8;
		size_t seq_len = distance(begin, end);

		if (seq_len < thread_count) {
			//seq_for_each(begin, end, f);
			std::for_each(begin, end, f);
			return;
		}

		size_t chunk_size = seq_len / thread_count;
		size_t last_chunk_size = seq_len - ((thread_count - 1) * chunk_size);
		vector<thread> vt;
		vt.reserve(thread_count);
		for (size_t i = 0; i < thread_count; ++i) {

			if (i == thread_count - 1)
			{
				//vt.push_back(thread([f](It b, It e) {std::for_each(b, e, f); }, begin, next(begin, last_chunk_size)));
				//vt.push_back(thread([&f](It b, It e) {seq_for_each(b, e, f); }, begin, next(begin, last_chunk_size)));

				vt.push_back(thread(std::for_each<It, F>, begin, next(begin, last_chunk_size), f));
				//vt.push_back(thread(seq_for_each<It, F>, begin, next(begin, last_chunk_size), f));
			}
			else
			{
				//vt.push_back(thread([&f](It b, It e) {seq_for_each(b, e, f); }, begin, next(begin, chunk_size)));
				vt.push_back(thread(std::for_each<It, F>, begin, next(begin, chunk_size), f));
				//vt.push_back(thread(seq_for_each<It,F>, begin, next(begin, chunk_size), f));
				advance(begin, chunk_size);
			}
		}

		for (thread& t : vt)
		{
			if (t.joinable()) {
				t.join();
			}
		}
	}

}

template <typename It, typename F>
F d_parallel_for_each(It begin, It end, F f) {
	std::vector<std::thread> threads;


	auto range_length = std::distance(begin, end);
	auto thread_max_count = std::thread::hardware_concurrency() - 1;

	unsigned chunk_length = unsigned(range_length / thread_max_count);

	threads.reserve(thread_max_count);

	It& chunk_begin = begin;
	for (unsigned i = 0; i < thread_max_count; ++i) {
		It chunk_end = chunk_begin;
		std::advance(chunk_end, chunk_length);

		threads.push_back(std::thread(std::for_each<It, F>, chunk_begin, chunk_end, f));
		chunk_begin = chunk_end;
	}

	seq_for_each(chunk_begin, end, f);
	for (thread& t : threads)
	{
		if (t.joinable()) {
			t.join();
		}
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

/*
int main() {
	vector<int> v1({ -2,-1,0,1,2,3 });

	auto print_v = [](const vector<int>& v) { for (int a : v) cout << a << ' '; cout << endl; };

	print_v(v1);
	for_each_(policy::parallel, v1.begin(), v1.end(), [](int& a) {++a; });
	print_v(v1);

	std::vector<int> v2(120000007);

	random_fill(v2.begin(), v2.end());
	auto v2_copy(v2);

	auto start_time1 = std::chrono::high_resolution_clock::now();
	std::for_each(v2.begin(), v2.end(), [](int& a) {++a; });
	auto end_time1 = std::chrono::high_resolution_clock::now();

	auto time1 = end_time1 - start_time1;

	cout << "sequential std::for_each took time: " << time1 / std::chrono::milliseconds(1) << endl;

	auto start_time2 = std::chrono::high_resolution_clock::now();
	for_each_(policy::parallel, v2_copy.begin(), v2_copy.end(), [](int& a) {++a; });
	//	d_parallel_for_each(v2_copy.begin(), v2_copy.end(), [](int& a) {++a; });
	auto end_time2 = std::chrono::high_resolution_clock::now();

	auto time2 = end_time2 - start_time2;

	cout << "parallel custom for_each_ took time: " << time2 / std::chrono::milliseconds(1) << endl;


	cout << (v2 == v2_copy) << endl;
	return 0;
}
*/