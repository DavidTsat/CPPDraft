#include <iostream>

using namespace std;

class base
{
	virtual void print() { cout << "from base" << endl; }
public:
	virtual void f() { cout << "ABCD base\n"; }
	base() { print(); }
	virtual ~base() { print(); }
	void base_print() { print(); }
};

class derived : public base
{
	virtual void f() { cout << "ABCD derived\n"; }
	virtual void print() { cout << "from derived" << endl; }
public:
	
	derived() { print();  }
	~derived() { print(); }
};

class A
{
	int a;
	char c;

	virtual void g() { cout << "from A\n"; }
protected:
	void _set_a(int aa) { a = aa; };
	int& _get_a() { return a; }
public:
	void gg() { g(); }
};

class B :public A
{
	void g() override { cout << "from B\n"; }
public:
	void f(int a)
	{
		_set_a(a);
	}
	int& get_a() 
	{
		return _get_a();
	}
	//void gg() { g(); }
};

int main()
{
	A a;
	B b;
	
	A* aa = &b;
	aa->gg();
	
	/*
	b.f(77);
	
	cout << b.get_a() << endl;
	b.get_a() = 85;
	cout << b.get_a() << endl;

	cout << sizeof(a) << ',' << sizeof(b) << endl;
	*/


	/*
	base* b = new derived;
//	b->base_print();
	derived d;
	cout << "AAAAAAAAAAA\n";
	d.base_print();
	cout << "BBBBBBBBBBB\n";
//	b->f();
	delete b;
	*/
	return 0;
}

/*
from base
from derived
from derived
from derived
from base
*/