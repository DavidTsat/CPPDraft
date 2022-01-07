#pragma once
#include <iostream>
using namespace std;

struct number
{
	using value_type = int;
	value_type n;
	void set(value_type v) 
	{ 
		n = v; 
	}
	value_type get() const 
	{ 
		return n; 
	}
};

template <typename base, typename T = typename base::value_type>
struct undoable : public base
{
	using value_type = T;
	value_type before;
	void set(value_type v)
	{
		before = base::get();
		base::set(v);
	}
	void undo()
	{
		base::set(before);
	}
};

template <typename base, typename T = typename base::value_type>
struct redoable : public base
{
	using value_type = T;
	value_type after;
	void set(value_type v)
	{
		after = v;
		base::set(v);
	}
	void redo()
	{
		base::set(after);
	}
};

using re_undoable_number = redoable<undoable<number>>;