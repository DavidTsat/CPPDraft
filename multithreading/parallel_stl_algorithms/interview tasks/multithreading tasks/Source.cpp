#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;


/*
template <typename It, typename F>
void for_each_(policy p, It begin, It end, F f)
{
	auto seq_for_each = [](It b, It e, F f)
	{
		while (b != e)
			f(*b++);
	};
	
	if (p == policy::sequential) 
	{
		seq_for_each(begin, end, f);
	}
	else
	{
	//	size_t thread_count = thread::hardware_concurrency();
		size_t thread_count = 8;
		size_t seq_len = distance(begin, end);
		
		if (seq_len < thread_count) {
			seq_for_each(begin, end, f);
			return;
		}

		size_t chunk_size = seq_len / thread_count;
		size_t last_chunk_size = seq_len - ((thread_count - 1) * chunk_size);
		vector<thread> vt;
		vt.reserve(thread_count);
		for (size_t i = 0; i < thread_count; ++i) {
			
			if (i == thread_count - 1) 
			{
				vt.push_back(thread(seq_for_each, begin, next(begin, last_chunk_size), f));
			} 
			else
			{
				vt.push_back(thread(seq_for_each, begin, next(begin, chunk_size), f));
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
*/

/*
Реализовать многопоточный вариант std::for_each
*/
enum policy { sequential, parallel };

template </*TODO*/>
void for_each_(policy p, /*TODO*/)
{
	auto seq_for_each = /*TODO*/ // лямбда-функция, реализующая обычный последовательный вариант std::for_each

	if (p == policy::sequential)
	{
		seq_for_each(/*TODO*/);
	}
	else
	{
		size_t thread_count = 8;
		/*TODO*/
		/*
		* Реализация многопоточного варианта std::for_each
		*/
	}

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

int main() {
	vector<int> v1({ -2,-1,0,1,2,3 });
	vector<int> v1_copy(v1);

//	auto print_v = [](const vector<int>& v) { for (int a : v) cout << a << ' '; cout << endl; };

//	print_v(v1);
//	for_each_(policy::sequential, v1.begin(), v1.end(), [](int& a) {--a; });
//	print_v(v1);


	std::vector<int> v2(120007);
	std::vector<int> v3(8000);

	random_fill(v2.begin(), v2.end());
	random_fill(v3.begin(), v3.end());

	std::vector<int> v2_copy(v2);
	std::vector<int> v3_copy(v3);

	// TEST 1
	std::for_each(v1.begin(), v1.end(), [](int& a) {--a; });
	for_each_(policy::sequential, v1_copy.begin(), v1_copy.end(), [](int& a) {--a; });

	cout << "Test 1 result: " << std::boolalpha << (v1 == v1_copy) << endl;

	// TEST 2
	std::for_each(v2.begin(), v2.end(), [](int& a) {++a; });
	for_each_(policy::parallel, v2_copy.begin(), v2_copy.end(), [](int& a) {++a; });

	cout << "Test 2 result: " << std::boolalpha << (v2 == v2_copy) << endl;

	// TEST 3
	std::for_each(v3.begin(), v3.end(), [](int& a) {a*a; });
	for_each_(policy::parallel, v3_copy.begin(), v3_copy.end(), [](int& a) {a*a; });
	
	cout << "Test 3 result: " << std::boolalpha << (v2 == v2_copy) << endl;


	return 0;
}
