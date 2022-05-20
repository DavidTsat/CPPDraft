#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <iostream>
#include <functional>
#include <set>
#include <iterator>
#include <limits>
#include <queue>

using namespace std;

template <typename T, typename Cmp = greater<T>>
class heap;

template <typename T, typename Cont = heap<T>, typename Cmp = greater<T>>
class priority_queue_;

template <typename T, typename Cmp>
class heap
{
	using value_type = T;

	vector<T> v;
	Cmp cmp;
	unsigned heap_size;

	friend class priority_queue_<value_type>;

	constexpr unsigned parent(unsigned i) const
	{
		return i >> 1;
	}

	constexpr unsigned left(unsigned i) const
	{
		return i << 1;
	}

	constexpr unsigned right(unsigned i) const
	{
		return (i << 1) | 1;
	}

	constexpr bool is_leaf(unsigned i) const
	{
		return i >= (heap_size / 2);
	}

	void _heapify_(unsigned i)
	{
		unsigned i_max = i;
		if (left(i) <= heap_size && cmp(v[left(i) - 1], v[i_max - 1]))
		{
			i_max = left(i);
		}
		if (right(i) <= heap_size && cmp(v[right(i) - 1], v[i_max - 1]))
		{
			i_max = right(i);
		}
		if (i_max == i) return;

		swap(v[i_max - 1], v[i - 1]);
		_heapify_(i_max);
	}

	void _build_heap_()
	{
		heap_size = v.size();
		for (int i = heap_size/2; i > 0; --i)
		{
			_heapify_(i);
		}
	}

	void _heap_increase_val_(unsigned i, const T& new_val)
	{
		if (v[i] > new_val)
		{
			//throw
			return;
		}
		v[i] = new_val;
		while (i >= 1 && v[parent(i + 1) - 1] < v[i])
		{
			swap(v[i], v[parent(i + 1) - 1]);
			i = parent(i + 1) - 1;
		}
	}
public:
	heap() : v(), cmp(), heap_size(0) {}

	heap(vector<value_type>& v_) : v(v_), heap_size(v_.size())
	{
		_build_heap_();
	}

	heap(vector<value_type>&& v_) : v(move(v_)), heap_size(v_.size())
	{
		_build_heap_();
	}

	heap(const heap<T>& m2) : cmp(m2.cmp), v(m2.v), heap_size(m2.heap_size) { }

	heap<value_type>& operator=(const heap<value_type>& m2)
	{
		heap<value_type> d(m2);
		swap_(*this, d);
		return *this;
	}

	heap<value_type>& operator=(heap<value_type>&& m2) noexcept
	{
		swap_(*this, m2);
		return *this;
	}

	template <typename Q>
	friend void swap_(heap<Q>& m1, heap<Q>& m2)
	{
		std::swap(m1.cmp, m2.cmp);
		std::swap(m1.v, m2.v);
		std::swap(m1.heap_size, m2.heap_size);
	}

	template <typename Q>
	friend ostream& operator<<(ostream& os, const heap<Q>& m)
	{
		copy(m.v.cbegin(), m.v.cbegin() + m.heap_size, ostream_iterator<Q>(os, " "));
		return os;
	}

	void heap_sort()
	{
	//	_build_heap_();
		int i = heap_size - 1;
		while (i > 0)
		{
			swap(v[i], v[0]);
			--heap_size;
			_heapify_(1);
			--i;
		}
	}

	vector<int>& get_vector()
	{
		return v;
	}
};


template <typename T, typename Cont, typename Cmp>
class priority_queue_
{
	Cont cont;
	Cmp cmp;
public:
	priority_queue_() : cont(), cmp() { }

	template <typename InputIt>
	priority_queue_(InputIt first, InputIt last, const Cmp& compare = Cmp{})
	{
		vector<T> v;
		v.reserve(distance(first, last));

		copy(first, last, back_inserter(v));
		cont = move(v);
	}

	template <typename Q>
	friend ostream& operator<<(ostream& os, const priority_queue_<Q>& m)
	{
		return os << m.cont << endl;
	}

	const T& top() const noexcept
	{
		return cont.v[0];
	}

	void push(const T& value)
	{
		cont.heap_size = cont.heap_size + 1;
		cont.v[cont.heap_size - 1] = numeric_limits<T>::min();
		cont._heap_increase_val_(cont.heap_size - 1, value);
	}

	T pop()
	{
		if (cont.heap_size < 1)
		{
			throw ("empty queue");
		}
		T max_ = cont.v[0];
		cont.v[0] = cont.v[cont.heap_size - 1];
		--cont.heap_size;
		cont._heapify_(1);
		return max_;
	}

	bool empty() const
	{
		return cont.heap_size == 0;
	}
};

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

void heap_sort_tests()
{
	vector<int> v1 = { 16,14,10,8,7,9,3,2,4,1 };
	vector<int> v2 = { 16,4,10,14,7,9,3,2,8,1 };
	vector<int> v3 = { 4,1,3,2,16,9,10,14,8,7 };

	heap<int> m(v3);
	//heap<int> m(v);
	cout << m << endl;
	m.heap_sort();
	cout << m << endl;

	for (int i = 0; i < 10; ++i)
	{
		vector<int> v = generate_random_vector(10000);
		vector<int> v2(v);
		heap<int> m(v);
		sort(v2.begin(), v2.end());
		m.heap_sort();
		v = m.get_vector();
		cout << boolalpha << (v == v2) << endl;
	}
}

void priority_queue_test()
{
	vector<int> v1 = { 4,1,3,2,16,9,10,14,8,7 };
	priority_queue_<int> pq(v1.cbegin(), v1.cend());
//	cout << pq << endl;

	heap<int> m(v1);
	cout << m << endl;

	while (!pq.empty())
	{
		int c = pq.top();
		pq.pop();
		cout << "c = " << c << endl;
//		cout << pq << endl;
	}
}

void priority_queue_tests()
{
	for (int i = 0; i < 10; ++i)
	{
		size_t sz = 10000;
		vector<int> v = generate_random_vector(sz);
		std::priority_queue<int> pq_std(v.cbegin(), v.cend());
		priority_queue_<int> pq_my(v.cbegin(), v.cend());

		while (sz--)
		{
			int c_std = pq_std.top();
			int c_my = pq_my.top();

			if (c_std != c_my)
			{
				cout << boolalpha << false << endl;
				return;
			}
		}
		cout << boolalpha << true << endl;
	}
}

int main()
{
	//heap_sort_tests();
	priority_queue_tests();
	return 0;
}