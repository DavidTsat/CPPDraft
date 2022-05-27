#pragma once

#include <new>
#include <vector>

using namespace std;

#define INITIAL_SIZE 10

template <typename T>
class vec
{
public:
	using value_type		= T;
	using size_type			= size_t;
	using reference			= value_type&;
	using const_reference	= const value_type&;

	vec() : data(static_cast<value_type*> (operator new(sizeof(value_type)*default_init_capacity))), capacity_(default_init_capacity), size_used(0) { }
	
	explicit vec(size_type sz) : data(static_cast<value_type*> (operator new(sizeof(value_type) * sz * 2))), capacity_(sz * 2), size_used(sz) 
	{
		for (size_t i = 0; i < size_used; ++i)
		{
			new (data + i) value_type(value_type());
		}
	}

	vec(size_type sz, const value_type& def_val) : data(static_cast<value_type*> (operator new(sizeof(value_type)* sz * 2))), capacity_(sz * 2), size_used(sz)
	{
		// fill [0, sz)
		for (size_t i = 0; i < sz; ++i)
		{
			new (data + i) value_type(def_val);
		}
	}

	vec(const vec& v2) : data(static_cast<value_type*> (operator new(sizeof(value_type)* v2.capacity_))), capacity_(v2.capacity_), size_used(v2.size_used)
	{
		for (size_t i = 0; i < size_used; ++i)
		{
			new (data + i) value_type(v2.data[i]);
		}
	}

	vec(vec&& v2) noexcept : data(v2.data), capacity_(v2.capacity_), size_used(v2.size_used)
	{
		v2.data = nullptr;
	}

	vec(const std::vector<T>& v) : data(static_cast<value_type*> (operator new(sizeof(value_type)* v.capacity()))), capacity_(v.capacity()), size_used(v.size())
	{
		for (size_t i = 0; i < size_used; ++i)
		{
			new (data + i) value_type(v[i]);
		}
	}

	explicit operator std::vector<T>() const
	{
		vector<T> v;
		v.reserve(size_used);

		for (size_t i = 0; i < size_used; ++i)
		{
			v.push_back(data[i]);
		}
		return v;
	}

	~vec() noexcept
	{
		for (size_t i = 0; i < size_used; ++i)
		{
			data[i].~value_type();
		}

		operator delete(data);
	}

	vec& operator=(const vec& v2)
	{
		this->~vec();
		data = nullptr;
		size_used = 0;
		vec temp(v2);
		swap_(*this, temp);
		return *this;
	}

	vec& operator=(vec&& v2) noexcept
	{
		swap_(*this, v2);
		return *this;
	}

	template <typename Q>
	friend void swap_(vec<Q>&, vec<Q>&);

	void resize(size_t new_size)
	{
		value_type* d2 = static_cast<value_type*> (operator new(sizeof(value_type) * new_size));
		
		for (size_t i = 0; i < new_size; ++i)
		{
			new (d2 + i) value_type(data[i]);
		}

		~vec();

		data = d2;
		size_used = new_size;
		
		if (capacity_ > size_used)
		{
			for (size_t i = size_used; i < capacity_; ++i)
			{
				new (data + i) value_type(value_type{});
			}
		}
	}

	void reserve(size_t new_capacity)
	{
		if (new_capacity <= capacity_)
		{
			return;
		}

		value_type* d2 = static_cast<value_type*> (operator new(sizeof(value_type) * size_used));

		for (size_t i = 0; i < size_used; ++i)
		{
			new (d2 + i) value_type(data[i]);
		}

		this->~vec();

		data = d2;
		capacity_ = new_capacity;
	}

	size_type size() const
	{
		return size_used;
	}

	size_type capacity() const
	{
		return capacity_;
	}

	void push_back(const value_type& new_val)
	{
		if (size_used < capacity_)
		{
			new (data + size_used) value_type(new_val);
			++size_used;
		}
		else
		{
			capacity_ *= 2;
			value_type* d2 = static_cast<value_type*> (operator new(sizeof(value_type) * capacity_));
			for (size_t i = 0; i < size_used; ++i)
			{
				new (d2 + i) value_type(data[i]);
			}
			new (d2 + size_used) value_type(new_val);
			
			this->~vec();

			data = d2;
			++size_used;
		}
	}

	void pop_back()
	{
		if (size_used == 0) return;
		
		data[size_used - 1].~value_type();
		--size_used;
	}

	reference operator[](size_t i)
	{
		return data[i];
	}

	const_reference operator[](size_t i) const
	{
		return data[i];
	}

	value_type* cbegin()
	{
		return data;
	}

	value_type* cend()
	{
		return data + size_used;
	}

	// emplace, etc.
private:
	value_type* data;
	size_t capacity_;
	size_t size_used;

	static const size_type default_init_capacity = INITIAL_SIZE;
};

template <typename Q>
void swap_(vec<Q>& v1, vec<Q>& v2)
{
	std::swap(v1.data, v2.data);
	std::swap(v1.capacity_, v2.capacity_);
	std::swap(v1.size_used, v2.size_used);
}

template <typename T>
bool operator==(vec<T>& v1, vec<T>& v2)
{
	return v1.size() == v2.size() && v1.capacity() == v2.capacity() && equal(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend());
}
