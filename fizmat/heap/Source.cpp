#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <queue>
#include <limits>

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

template <typename Q, typename Comp = greater<Q>>
class priority_queue_;

template <typename T, typename Comp = greater<T>>
class heap
{
//	template <typename T, typename Comp = greater<Q>>
	friend	class priority_queue_<T, Comp>;

	size_t left(size_t i) const { return i << 1; }
	size_t right(size_t i) const { return (i << 1) | 1; }
	size_t parent(size_t i) const { return i / 2; }

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
		
		if ((l <= heap_size) && cmp(v[l], v[max_]))
		{
			max_ = l;
		}
		if ((r <= heap_size) && cmp(v[r], v[max_]))
		{
			max_ = r;
		}
		if (max_ == i)
		{
			return;
		}
		swap(v[max_], v[i]);
		heapify(max_);
	}

	void build_heap()
	{
		heap_size = v.size() - 1;
		for (size_t i = heap_size / 2; i >= 1; --i)
		{
			heapify(i);
		}
	}

	void heap_increase_val(size_t i, const T& new_val)
	{
		if (!cmp(new_val, v[i]))
			return;
		v[i] = new_val;

		while (i > 1 && cmp(v[i], v[parent(i)]))
		{
			swap(v[i], v[parent(i)]);
			i = parent(i);
		}
	}

public:
	using value_type = T;
private:
	vector<value_type> v;
	Comp cmp;
	size_t heap_size;
public:

	heap() : v(vector<value_type>(1, value_type())), cmp(Comp()), heap_size(0) {}
	
	template <typename It>
	heap(It begin, It end) : heap()
	{
		while (begin != end)
		{
			v.push_back(*begin);
			++begin;
		}
		build_heap();
	}

	heap(const vector<value_type>& v) : heap(v.cbegin(), v.cend()) {}

	template <typename Q, typename C = greater<Q>>
	friend void swap_(heap<Q, C>&, heap<Q, C>&);

	heap(const heap<value_type, Comp>& m) : heap(next(m.v.cbegin()), m.v.cend()) { cmp = m.cmp; }
	const size_t size() const { return heap_size; }

	const value_type& operator[](size_t i) const { return v[i + 1]; }

	template <typename Q, typename C = greater<Q>>
	friend ostream& operator<<(ostream&, const heap<Q, C>&);

	void heap_sort()
	{
		for (size_t i = heap_size; i >= 2; --i)
		{
			swap(v[i], v[1]);
			--heap_size;
			heapify(1);
		}
	}
};

template <typename Q, typename C>
void swap_(heap<Q, C>& m1, heap<Q, C>& m2)
{
	swap(m1.cmp, m2.cmp);
	swap(m1.v, m2.v);
}

template <typename Q, typename C>
ostream& operator<<(ostream& os, const heap<Q, C>& h)
{
	copy(next(h.v.cbegin()), next(h.v.cbegin(), h.heap_size), ostream_iterator<Q>(os, " "));
	return os;
}

template <typename Q, typename C = greater<Q>>
bool operator==(const heap<Q, C>& h, const vector<Q>& v)
{
	if (h.size() != v.size())
		return false;

	for (int i = 0; i < h.size(); ++i)
	{
		if (h[i+1] != v[i])
			return false;
	}

	return true;
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

void heap_tests()
{
	vector<int> v1 = { 16,14,10,8,7,9,3,2,4,1 };
	vector<int> v2 = { 16,4,10,14,7,9,3,2,8,1 };
	vector<int> v3 = { 4,1,3,2,16,9,10,14,8,7 };

	vector<vector<int>> input_vecs = { v1, v2, v3 };
	
	bool b = false;
	
	for (int i = 0; i < 3; ++i)
	{
		heap<int> h1(input_vecs[i]);
		heap<int> h2(input_vecs[i].cbegin(), input_vecs[i].cend());
 		heap<int> h3(h2);

	//	cout << h1 << endl;
	//	vector<int> h_std(input_vecs[i]);
	//	make_heap(h_std.begin(), h_std.end());
		
		if (!is_heap(&h1[1], &h1[1] + h1.size()))
		{
			cout << boolalpha << false << " h1 " << i << endl;
			b = true;
		}
		if (!is_heap(&h2[1], &h2[1] + h2.size()))
		{
			cout << boolalpha << false << " h2 " << i << endl;
			b = true;
		}
		if (!is_heap(&h3[1], &h3[1] + h3.size()))
		{
			cout << boolalpha << false << " h3 " << i << endl;
			b = true;
		}
	}
	
	if (!b)
		cout << boolalpha << true << endl;
	
	b = false;

	for (int i = 0; i < 100; ++i)
	{
		vector<int> random_vec = generate_random_vector(1000);

		heap<int> h1(random_vec);
		heap<int> h2(random_vec.cbegin(), random_vec.cend());
		heap<int> h3(h2);

		if (!is_heap(&h1[0], &h1[0] + h1.size()))
		{
			cout << boolalpha << false << " h1 " << i << endl;
			b = true;
		}
		if (!is_heap(&h2[0], &h2[0] + h2.size()))
		{
			cout << boolalpha << false << " h2 " << i << endl;
			b = true;
		}
		if (!is_heap(&h3[0], &h3[0] + h3.size()))
		{
			cout << boolalpha << false << " h3 " << i << endl;
			b = true;
		}
	}
	if (!b)
		cout << boolalpha << true << endl;
}

void heap_sort_tests()
{
	vector<int> v1 = { 16,14,10,8,7,9,3,2,4,1 };
	vector<int> v2 = { 16,4,10,14,7,9,3,2,8,1 };
	vector<int> v3 = { 4,1,3,2,16,9,10,14,8,7 };

	vector<vector<int>> input_vecs = { v1, v2, v3 };

	bool b = false;

	for (int i = 0; i < 3; ++i)
	{
		heap<int> h1(input_vecs[i]);
		heap<int> h2(input_vecs[i].cbegin(), input_vecs[i].cend());
		heap<int> h3(h2);

		h1.heap_sort();
		h2.heap_sort();
		h3.heap_sort();

		if (!is_sorted(&h1[1], &h1[1] + h1.size()))
		{
			cout << boolalpha << false << " h1 " << i << endl;
			b = true;
		}
		if (!is_sorted(&h2[1], &h2[1] + h2.size()))
		{
			cout << boolalpha << false << " h2 " << i << endl;
			b = true;
		}
		if (!is_sorted(&h3[1], &h3[1] + h3.size()))
		{
			cout << boolalpha << false << " h3 " << i << endl;
			b = true;
		}
	}

	if (!b)
		cout << boolalpha << true << endl;

	b = false;

	for (int i = 0; i < 100; ++i)
	{
		vector<int> random_vec = generate_random_vector(10);

		heap<int> h1(random_vec);
		heap<int> h2(random_vec.cbegin(), random_vec.cend());
		heap<int> h3(h2);

		h1.heap_sort();
		h2.heap_sort();
		h3.heap_sort();

		if (!is_sorted(&h1[0], &h1[0] + h1.size()))
		{
			cout << boolalpha << false << " h1 " << i << endl;
			b = true;
		}
		if (!is_sorted(&h2[0], &h2[0] + h2.size()))
		{
			cout << boolalpha << false << " h2 " << i << endl;
			b = true;
		}
		if (!is_sorted(&h3[0], &h3[0] + h3.size()))
		{
			cout << boolalpha << false << " h3 " << i << endl;
			b = true;
		}
	}
	if (!b)
		cout << boolalpha << true << endl;
}

template <typename Q, typename Comp>
class priority_queue_
{
	heap<Q, Comp> h;

public:
	using value_type = Q;

	priority_queue_() : h() {}
	
	template <typename It>
	priority_queue_(It begin, It end) : h(begin, end) {}
	
	priority_queue_(const vector<value_type>& v) : h(v) {}
	priority_queue_(const priority_queue_<Q, Comp>& q2) : h(q2.h) {}

	const value_type& top() const
	{
		return h[0];
	}

	void push(const value_type& value)
	{
		++h.heap_size;
		h.v.push_back(numeric_limits<value_type>::min());
		h.heap_increase_val(h.heap_size, value);
	}
	
	void pop()
	{
		h.v[1] = h.v[h.heap_size];
		--h.heap_size;
		h.heapify(1);
	}


	bool empty() const { return h.heap_size == 0; }
};

// QUESTION
template <typename FirstArg, typename SecondArg>
bool all_equal(FirstArg first_arg, SecondArg second_arg)
{
	return first_arg == second_arg;
}

template <typename FirstArg, typename SecondArg, typename... Args>
bool all_equal(FirstArg first_arg, SecondArg second_arg, Args... args)
{
	return (first_arg == second_arg) && all_equal(second_arg, args...);
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
//	heap_tests();
//	heap_sort_tests();
	priority_queue_tests();
	return 0;
}