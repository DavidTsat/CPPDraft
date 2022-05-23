#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <limits>
#include <queue>

using namespace std;

/*
16 14 10 8 7 9 3 2 4 1

			16
		  /    \
		14      10
	   /  \    /  \
	  8    7  9    3
	/   \ /
   2    4 1

   left(i)   = 2*i       (i << 1)
   right(i)  = 2*i + 1   ((i << 1) |1)
   parent(i) = i/2       (i >> 1)
*/

// About the height of the tree
/*
n = 2^0 + 2^1 + 2^2 + ... + 2^h

l_k = 2^k - 1 = 2*l_k-1
height: 2^h = n + 1     h = log(n+1)
number of leaves:		l_h = (n+1)/2
leaves indices: n/2 + 1, n/2 + 2, ... , n

mean-heap vs max-heap
*/

#define DEBUG

template <typename T, typename Cmp = std::greater<T>>
class priority_queue_;

template <typename T, typename Cmp = greater<T>>
class heap
{
	friend class priority_queue_<T, Cmp>;

	vector<T> data;
	Cmp cmp;
	size_t heap_size;

	static size_t left(size_t i)
	{
		return i << 1;
	}

	static size_t right(size_t i)
	{
		return (i << 1) | 1;
	}

	static size_t parent(size_t i)
	{
		return i >> 1;
	}

	void heapify(size_t i)
	{
/*
			4
		  /   \
		 8     7
		/ \   /
	   2   4 1
*/
		// max-heap
		size_t l = left(i);
		size_t r = right(i);
		size_t max_ = i;

		if (l <= heap_size && cmp(data[l], data[max_]))
		{
			max_ = l;
		}
		if (r <= heap_size && cmp(data[r], data[max_]))
		{
			max_ = r;
		}
		if (max_ == i) return;

		swap(data[max_], data[i]);
		heapify(max_);
	}

	void build_heap()
	{
		heap_size = data.size()-1;
		for (size_t i = heap_size / 2; i >= 1; --i)
		{
			heapify(i);
		}
	}
public:
	using value_type = T;

	heap() : data(vector<T>(1, T())), cmp(Cmp()), heap_size(0) {}
	
	heap(const Cmp& c) : data(vector<T>(1, T())), cmp(c), heap_size(0) {}

	template <typename It>
	heap(It begin, It end) : heap()
	{
		copy(begin, end, back_inserter(data));
		heap_size = data.size() - 1;
		build_heap();
	}

	heap(const vector<value_type>& v) : heap(v.cbegin(), v.cend()) {}
	
	heap(const heap<T, Cmp>& h2) : heap(next(h2.data.cbegin()), h2.data.cend())
	{
		cmp = h2.cmp;
	}

	const value_type& operator[](size_t i) const
	{
		return data[i + 1];
	}

	const size_t size() const
	{
		return heap_size;
	}

	void heap_sort()
	{
		// max-heap
		for (size_t i = heap_size; i > 1; --i)
		{
			swap(data[i], data[1]);
			--heap_size;
			heapify(1);
		}
	}
};

template <typename T, typename Cmp = greater<T>>
ostream& operator<<(ostream& os, const heap<T, Cmp>& h)
{
	if (!h.size()) return os;

	copy(&h[0], next(&h[1], h.size() - 1), ostream_iterator<T>(os, " "));
	return os;
}

template <typename T, typename Cmp = greater<T>>
bool operator==(const heap<T, Cmp>& h1, const heap<T, Cmp>& h2)
{
	if (h1.size() != h2.size()) return false;

	for (size_t i = 1; i < h1.size(); ++i)
	{
		if (h1[i] != h2[i]) return false;
	}
	return true;
}

template <typename FirstArgType, typename SecondArgType, typename... OtherArgTypes>
bool all_equal(const FirstArgType& f, const SecondArgType& s)
{
	return f == s;
}

template <typename FirstArgType, typename SecondArgType, typename... OtherArgTypes>
bool all_equal(const FirstArgType& f, const SecondArgType& s, const OtherArgTypes&... o)
{
	return (f == s) && all_equal(s, o...);
}

std::vector<int> generate_random_vector(size_t size, int left = -1000, int right = 1000)
{
	using value_type = int;

	static std::uniform_int_distribution<value_type> distribution(
		left, right
	);
	static std::default_random_engine generator;

	std::vector<value_type> data(size);
	std::generate(data.begin(), data.end(), []() { return distribution(generator); });
	return data;
}

void heap_sort_construction_tests()
{
	vector<int> v1 = { 16,14,10,8,7,9,3,2,4,1 };
	vector<int> v2 = { 16,4,10,14,7,9,3,2,8,1 };
	vector<int> v3 = { 4,1,3,2,16,9,10,14,8,7 };

	vector<vector<int>> input_vecs = { v1, v2, v3, generate_random_vector(1000) };

	for (int i = 0; i < 4; ++i)
	{
		heap<int> h1(input_vecs[i]);
		heap<int> h2(input_vecs[i].cbegin(), input_vecs[i].cend());
		heap<int> h3(h2);
		cout << boolalpha << all_equal(h1, h2, h3) << endl;
	}
}

void heap_print_tests()
{
	vector<int> v1 = { 16,14,10,8,7,9,3,2,4,1 };
	vector<int> v2 = { 16,4,10,14,7,9,3,2,8,1 };
	vector<int> v3 = { 4,1,3,2,16,9,10,14,8,7 };

	vector<vector<int>> input_vecs = { v1, v2, v3 };

	for (int i = 0; i < 3; ++i)
	{
		heap<int> h(input_vecs[i]);
		cout << h << endl;
	}
}


void build_heap_tests()
{
	vector<int> v1 = { 16,14,10,8,7,9,3,2,4,1 };
	vector<int> v2 = { 16,4,10,14,7,9,3,2,8,1 };
	vector<int> v3 = { 4,1,3,2,16,9,10,14,8,7 };

	vector<vector<int>> input_vecs = { v1, v2, v3, generate_random_vector(1000), generate_random_vector(1000) };

	for (int i = 0; i < 5; ++i)
	{
		heap<int> h(input_vecs[i]);
		cout << boolalpha << is_heap(&h[0], next(&h[1], h.size() - 1)) << endl;
	}
}

void heap_sort_tests()
{
	vector<int> v1 = { 16,14,10,8,7,9,3,2,4,1 };
	vector<int> v2 = { 16,4,10,14,7,9,3,2,8,1 };
	vector<int> v3 = { 4,1,3,2,16,9,10,14,8,7 };

	vector<vector<int>> input_vecs = { v1, v2, v3, generate_random_vector(1000), generate_random_vector(1000) };
	for (int i = 0; i < 5; ++i)
	{
		heap<int> h(input_vecs[i]);
		h.heap_sort();
		cout << boolalpha << is_sorted(&h[0], next(&h[1], h.size() - 1)) << endl;
	}
}

// priority_queue
template <typename T, typename Cmp>
class priority_queue_
{	
	heap<T, Cmp> h;

	void change_val(size_t i, const T& new_val)
	{
		h.data[i] = new_val;
		while (i > 1)
		{
			if (!h.cmp(h.data[h.parent(i)], h.data[i]))
			{
				swap(h.data[h.parent(i)], h.data[i]);
			}
			i = h.parent(i);
		}
	}
public:
	using value_type = T;

	priority_queue_() : h() {}

	priority_queue_(const Cmp& c) : h(c) {}

	template <typename It>
	priority_queue_(It begin, It end) : h(begin, end) {}

	priority_queue_(const vector<T>& v) : h(v) {}

	priority_queue_(const priority_queue_<T, Cmp>& h2) : h(h2.h) {}

	const value_type& top()
	{
		return h[0]; // O(1)
	}

	void pop()
	{
		swap(h.data[1], h.data[h.heap_size]);
		--h.heap_size;
		h.heapify(1);
	}

	void push(const value_type& v)
	{
		// max-priority_queue
		
		if (h.heap_size < h.data.size() - 1)
		{
			h.data[h.heap_size] = numeric_limits<T>::min();
		}
		else
			h.data.push_back(numeric_limits<T>::min());
		++h.heap_size;

		change_val(h.heap_size, v);
	}

	size_t size() const
	{
		return h.size();
	}

	bool empty() const
	{
		return h.size() == 0;
	}

	template <typename Q, typename Cmp_ = greater<Q>>
	friend bool operator==(const priority_queue_<Q, Cmp_>& pq1, const priority_queue_<Q, Cmp_>& pq2)
	{
		if (pq1.size() != pq2.size()) return false;

		for (size_t i = 1; i < pq1.size(); ++i)
		{
			if (pq1.h[i] != pq2.h[i]) return false;
		}
		return true;
	}

#ifdef DEBUG
	bool is_heap() const
	{
		return std::is_heap(next(h.data.cbegin()), h.data.cend());
	}
#endif
};

void priority_queue_construction_tests()
{
	vector<int> random_vec = generate_random_vector(10);

	priority_queue_<int> pq1(random_vec);
	priority_queue_<int> pq2(random_vec.cbegin(), random_vec.cend());
	priority_queue_<int> pq3(pq2);
	priority_queue_<int> pq4;

	for (int i : random_vec)
	{
		pq4.push(i);
	}
	
	vector<priority_queue_<int>> input_pqs{ pq1, pq2, pq3, pq4 };

	for (const priority_queue_<int>& pq_ : input_pqs)
	{
		cout << boolalpha << pq_.is_heap() <<endl;
	}
}

void priority_queue_tests()
{
	bool b = false;

	vector<int> random_vec = generate_random_vector(1000);

	priority_queue_<int> pq1(random_vec);
	priority_queue_<int> pq2(random_vec.cbegin(), random_vec.cend());
	priority_queue_<int> pq3(pq2);
	priority_queue_<int> pq4;

	for (int i : random_vec)
	{
		pq4.push(i);
	}

	std::priority_queue<int> pq_std(random_vec.cbegin(), random_vec.cend());

	while (!pq_std.empty())
	{

		int c1 = pq1.top();
		int c2 = pq2.top();
		int c3 = pq3.top();
		int c4 = pq4.top();

		int c_std = pq_std.top();

		if (!all_equal(c1, c2, c3, c4, c_std))
		{
			cout << boolalpha << false << " top " << endl;
			b = true;
			break;
		}

		pq1.pop();
		pq2.pop();
		pq3.pop();
		pq4.pop();
		pq_std.pop();
	}

	if (!b)
		cout << boolalpha << true << endl;

	if (!all_equal(true, pq1.empty(), pq2.empty(), pq3.empty(), pq4.empty()))
		cout << boolalpha << false << " empty " << endl;
	else
		cout << boolalpha << true << endl;
}

int main()
{
	heap_sort_construction_tests();
	heap_print_tests();
	build_heap_tests();
	heap_sort_tests();
	priority_queue_construction_tests();
	priority_queue_tests();
	return 0;
}