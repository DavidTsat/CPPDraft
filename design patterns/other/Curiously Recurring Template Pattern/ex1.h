#pragma once
#include <iostream>

using namespace std;

template <typename T>
struct base
{
	void foo()
	{
		(static_cast<T*>(this))->foo();
	}
};

struct derived1 : public base<derived1>
{
	void foo()
	{
		cout << "derived1 foo" << endl;
	}
};

struct derived2 : public base<derived2>
{
	void foo()
	{
		cout << "derived2 foo" << endl;
	}
};