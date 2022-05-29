#pragma once
#include <new>
#include <assert.h>

using namespace std;

template <typename T>
class _deque
{
public:
	using value_type		= T;
	using reference			= value_type&;
	using const_reference	= const reference;
	using size_type			= size_t;
	using diff_type			= ptrdiff_t;

	class _deque_iterator // random access iterator
	{
		value_type** map_ptr;	// offset from the map begin
		value_type* first;		// last elem of the chunk
		value_type* current;	// current elem of the chunk
		value_type* last;		// last elem of the chunk

		friend class _deque;

		void advance(diff_type offset)
		{
			if (offset == 0) return;

			diff_type chunk_size = last - first;
			offset += current - first;

			current = first;

			if (offset >= 0 && offset < chunk_size)
			{
				// same chunk
				current += offset;
			}
			else
			{
				diff_type map_offset;

				if (offset > 0) {
					map_offset = offset / chunk_size;
				}
				else {
					map_offset = -((-offset - 1) / chunk_size) - 1;
				}
				diff_type chunk_offset = offset - map_offset * chunk_size;

				map_ptr += map_offset;
				first	= *map_ptr;
				current = first + chunk_offset;
				last	= first + chunk_size;
			}
		}
	public:
		reference operator*()
		{
			return *current;
		}
		_deque_iterator& operator++()
		{
			advance(1);
			return *this;
		}
		_deque_iterator& operator--()
		{
			advance(-1);
			return *this;
		}
		_deque_iterator operator+(size_type n)
		{
			_deque_iterator t(*this);
			t.advance(n);
			return t;
		}
		_deque_iterator operator-(size_type n)
		{
			_deque_iterator t(*this);
			t.advance(n);
			return t;
		}
		diff_type operator-(const _deque_iterator& d)
		{
			if (map_ptr == d.map_ptr)
				return current - d.current;

			size_type chunk_size = last - first;
			//auto d1 = (map_ptr - d.map_ptr - 1);
			//auto d2 = (map_ptr - d.map_ptr - 1) * chunk_size;
			//auto d3 = (map_ptr - d.map_ptr - 1) * chunk_size + (current - first) + (d.last - d.current);
			return (map_ptr - d.map_ptr - 1) * chunk_size + (current - first) + (d.last - d.current);
		}
		bool operator==(const _deque_iterator& d)
		{
			return current == d.current;
		}
		bool operator!=(const _deque_iterator& d)
		{
			return current != d.current;
		}
	};

	_deque(size_type elems_num = 0, const value_type& v = value_type()) : map_size(min_map_size), chunk_size(elems_num / map_size + 1), map_head(allocate_map())
	{
		allocate_chunks();
		set_begin(elems_num);
		set_end(elems_num);

		assert(_end - _begin == elems_num);
		initialize_data(_begin, _end, v);
	}

	~_deque()
	{
		while (_begin != _end)
		{
			(*_begin).~value_type();
			++_begin;
		}
		operator delete (map_head);
	}

	void push_back(const value_type& v)
	{

	}
	void pop_back()
	{

	}

	void push_front(const value_type& v)
	{
		if (_begin.current > _begin.first || _begin.map_ptr > map_head)
		{
			--_begin;
			construct_elem(&*_begin, v);
		}
		else
		{
			//cout << "OOOOO";
			value_type* new_chunk = allocate_chunk(chunk_size);
			++map_size;
			value_type** new_map_head = allocate_map();

			new_map_head[0] = new_chunk;
			for (size_type i = 1; i < map_size; ++i)
			{
				new_map_head[i] = map_head[i - 1];
			}
			operator delete(map_head);
			map_head = new_map_head;
			
			set_to_begin(_begin);
			_begin.advance(chunk_size);

			push_front(v);
		}
	}
	void pop_front()
	{

	}

	_deque_iterator begin() const
	{
		return _begin;
	}
	_deque_iterator end() const
	{
		return _end;
	}

private:
	size_type map_size;
	const size_type chunk_size;

	value_type** map_head;

	_deque_iterator _begin;
	_deque_iterator _end;

	const static size_type min_map_size = 8;
private:
	constexpr size_type capacity() const
	{
		return map_size * chunk_size;
	}
	constexpr size_type size() const
	{
		return _end - _begin;
	}

	value_type** allocate_map()
	{
		return new value_type* [map_size];
	}

	value_type* allocate_chunk(size_type n)
	{
		return (value_type*) operator new(n * sizeof(value_type));
	}
	
	void allocate_chunks()
	{
		for (size_type i = 0; i < map_size; ++i)
		{
			map_head[i] = allocate_chunk(chunk_size);
		}
	}
	
	void set_to_begin(_deque_iterator& d)
	{
		d.map_ptr	= map_head;
		d.first		= *d.map_ptr;
		d.current	= d.first;
		d.last		= d.current + chunk_size;
	}
	void set_begin(size_type n)
	{
		set_to_begin(_begin);
		
		size_type offset_from_begin = (capacity() - n) / 2;
		_begin.advance(offset_from_begin);
	}
	
	void set_end(size_type n)
	{
		set_to_begin(_end);

		size_type offset_from_begin = n + (capacity() - n) / 2;
		_end.advance(offset_from_begin);
	} 
	
	void construct_elem(value_type* p, const value_type& v)
	{
		new (&*p) value_type(v);
	}

	void initialize_data(_deque_iterator first, _deque_iterator last, const value_type& v)
	{
		while (first != last)
		{
			construct_elem(&*first, v);
			++first;
		}
	}
};


