#pragma once
#include <functional>
#include <iterator>
#include <algorithm>

#define DEFAULT_CAPACITY 17

using namespace std;
template <typename Key, typename T, typename Hash = hash<Key>, typename KeyEqual = equal_to<Key>>
class _unordered_map
{
public:
	using key_type			= Key;
	using mapped_type		= T;
	using value_type		= pair<const Key, T>;
	using size_type			= size_t;
	using key_equal			= KeyEqual;
	using reference			= value_type&;
	using const_reference	= const value_type&;
	using diff_type			= ptrdiff_t;

private:
	struct node
	{
		value_type val;
		node* prev;
		node* next;

		node(const value_type& v, node* prev_ = nullptr, node* next_ = nullptr) : val(v), prev(prev_), next(next_) {}
	};

	size_type sz;
	size_type bucket_num;
	Hash h;
	KeyEqual eq;
	node** data;
	float max_load = 2;
public:
	class iterator : public  std::iterator<std::bidirectional_iterator_tag, value_type>
	{
		node** a;
		node* p;
		bool b; // bucket_begin

		bool get_b()
		{
			if (p && p->prev == nullptr)
				b = true;
			return b;
		}
	public:
		//...
		friend class _unordered_map;

		iterator(node** a_, node* p_, bool b_) : a(a_), p(p_), b(b_) {}

		iterator& operator++()
		{
			if (p && p->next)
			{
				p = p->next;
				b = false;
			}
			else
			{
				++a;
				p = *a;

				while (p == nullptr)
				{
					++a;
					p = *a;
				}
				b = true;
			}

			return *this;
		}

		iterator& operator--()
		{
			if (b || p == nullptr || p->prev == nullptr)
			{
				--a;
				p = *a;

				while (p == nullptr)
				{
					--a;
					p = *a;
				}
			}

			//if (p && p->prev)
			else
			{
				p = p->prev;
				if (!p->prev)
					b = true;
				else
					b = false;
			}

			return *this;
		}
		/*
		diff_type operator-(iterator it2) const
		{
			diff_type c = 0;
			if (a < it2.a)
			{
				while (it2 != *this)
				{
					++c;
					--it2;
				}
			}
			else
			{
				while (it2 != *this)
				{
					--c;
					++it2;
				}
			}
			return c;
		}
		*/

		value_type& operator*()
		{
			return p->val;
		}
		
		value_type* operator->()
		{
			return &(p->val);
		}

		bool operator==(const iterator& it) const
		{
			return a == it.a && p == it.p;
		}

		bool operator!=(const iterator& it) const
		{
			return a != it.a || p != it.p;
		}
	};

	class const_iterator : public  std::iterator<std::bidirectional_iterator_tag, value_type>
	{
		node** a;
		node* p;
		bool b; // bucket_begin

		bool get_b() 
		{
			if (p && p->prev == nullptr)
				b = true;
			return b;
		}
	public:
		//...
		friend class _unordered_map;

		const_iterator(node** a_, node* p_, bool b_) : a(a_), p(p_), b(b_) {}

		const_iterator& operator++()
		{
			if (p && p->next)
			{
				p = p->next;
				b = false;
			}
			else
			{
				++a;
				p = *a;

				while (p == nullptr)
				{
					++a;
					p = *a;
				}
				b = true;
			}

			return *this;
		}

		const_iterator& operator--()
		{
			if (b || p == nullptr || p->prev == nullptr)
			{
				--a;
				p = *a;

				while (p == nullptr)
				{
					--a;
					p = *a;
				}
			}

			//if (p && p->prev)
			else
			{
				p = p->prev;
				if (!p->prev)
					b = true;
				else
					b = false;
			}

			return *this;
		}

		const value_type& operator*() const
		{
			return p->val;
		}

		const value_type* operator->() const
		{
			return &(p->val);
		}

		bool operator==(const const_iterator& it) const
		{
			return a == it.a && p == it.p;
		}

		bool operator!=(const const_iterator& it) const
		{
			return a != it.a || p != it.p;
		}
	};

	~_unordered_map() noexcept
	{
		for (iterator p = begin(); p != end(); )
		{
			auto p2 = next(p);
			delete p.p;
			p = p2;
		}
		delete data;
	}

	_unordered_map() : sz(0), bucket_num(DEFAULT_CAPACITY), h(Hash()), eq(KeyEqual()), data(new node* [bucket_num]()) { }

	_unordered_map(const _unordered_map& m) : sz(0), bucket_num(m.bucket_num), h(m.h), eq(m.eq), data(new node* [bucket_num]())
	{
		for (const_iterator it = m.cbegin(); it != m.cend(); ++it)
		{
			this->operator[](it->first) = it->second; // QUESTION
		}	
	}

	_unordered_map(_unordered_map&& m) noexcept  : _unordered_map()
	{
		swap(m);
	}

	_unordered_map& operator=(const _unordered_map& m)
	{
		_unordered_map m1(m);
		this->swap(m1);
		return *this;
	}

	_unordered_map& operator=(_unordered_map&& m) noexcept
	{
		this->swap(m);
		return *this;
	}

	void swap(_unordered_map& m) noexcept
	{
		std::swap(sz, m.sz);
		std::swap(bucket_num, m.bucket_num);
		std::swap(h, m.h);
		std::swap(eq, m.eq);
		std::swap(max_load, m.max_load);
		std::swap(data, m.data);
	}

	mapped_type& operator[](const key_type& k)
	{
		// TODO
		size_type i_ = h(k);
		size_type i = i_ % bucket_num;
		if (data[i] == nullptr)
		{
			data[i] = new node({ k, mapped_type() }, nullptr, nullptr);
			++sz;
			return data[i]->val.second;
		}
		else
		{
			node* p = data[i]->next;
			while (p)
			{
				if (eq(p->val.first, k))
					return p->val.second;
				p = p->next;
			}
			p = new node({ k, mapped_type() }, nullptr, data[i]);
			data[i]->prev = p;
			data[i] = p;
			++sz;
			return data[i]->val.second;
		}
	}

	iterator find(const key_type& k)
	{
		size_type i = h(k) % bucket_num;

		if (data[i] == nullptr)
			return end();

		node* p = data[i];
		while (p)
		{
			if (p->val.first == k)
				return { data + i, p, p == data[i] };
			p = p->next;
		}
		return end();
	}

	iterator erase(iterator it)
	{
		iterator it2(next(it));

		if (it.get_b())
		{
			//*it.a = it.p->next;
			size_type i = h(it->first)%bucket_num;
			data[i] = it.p->next;
			if (it.p->next)
			{
				(it.p)->next->prev = nullptr;
			}
		}
		else
		{
			(it.p)->prev->next = (it.p)->next;
			if (it.p->next)
				(it.p)->next->prev = (it.p)->prev;
		}
		--sz;
		delete it.p;
		return it2;
	}

	iterator begin()
	{
		for (size_type i = 0; i < bucket_num; ++i)
		{
			if (data[i] != nullptr)
				return { &data[i], data[i], true };
		}
		return end();
	}

	iterator end()
	{
		return { (data + bucket_num), *(data + bucket_num), true };
	}

	const_iterator cbegin() const
	{
		for (size_type i = 0; i < bucket_num; ++i)
		{
			if (data[i] != nullptr)
				return { &data[i], data[i], true };
		}
		return cend();
	}

	const_iterator cend() const
	{
		return { (data + bucket_num), *(data + bucket_num), true };
	}

	size_type size() const
	{
		return sz;
	}

	bool operator==(const _unordered_map& m) const
	{
	//	return true;
		return sz == m.sz && bucket_num == m.bucket_num && equal(m.cbegin(), m.cend(), cbegin()); // TODO
	//	return sz == m.sz && bucket_num == m.bucket_num && equal(m.begin(), m.end(), this->begin(), []( value_type& v1,  value_type& v2) { return v1.first == v2.first && v1.second && v2.second; });
	}
	// buckets
	size_type bucket_count() const
	{
		return bucket_num;
	}

	size_type bucket_size(size_type n) const
	{

	}

	size_type bucket(const key_type& k) const
	{

	}

	// hash
	float load_factor() const
	{
		return (float)sz / bucket_num;
	}

	void rehash(size_type count)
	{

	}

	float max_load_factor() const
	{
		return max_load;
	}

	void max_load_factor(float ml)
	{
		max_load = ml;
	}
};