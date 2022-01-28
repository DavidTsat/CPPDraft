#include <iostream>
#include <vector>
#include <any>
//#include "person.h"
#include "clock.h"

using namespace std;

struct A
{
	virtual ~A() = 0;
};
A::~A() {}

struct B : public A
{
	B() { int a = 7; }
	B(const B& b) { int a = 7; }

	//string ssk;

	void foo() { cout << "FFF\n"; }
};

struct C
{
	int j;
	string ss;
	void goo() { cout << "GGGG\n"; }
};
int main()
{
	date c;
	//clock_drawer cc;
	//observer<clock_>* oo = new clock_drawer;
	c.subscribe_observer(make_unique<date_drawer>());
	c.set_date("27.01.2022");
	c.set_date_properties(7, true);

	/*
	//any a =7;
	//a = "AAAD";
	B b;
	void* p = &b;
	//(static_cast<B*>(p))->foo();
	(static_cast<C*>(p))->ss = "POOOOP";
	(static_cast<C*>(p))->goo();
	*/
	/*
	date c;
	//clock_drawer cc;
	//observer<clock_>* oo = new clock_drawer;
	c.subscribe_observer(make_unique<date_drawer>());
	c.set_date("27.01.2022");
	*/

	/*
	A a;
	
	person p;
	//console_printer_observer c;

	p.set_age(6);
	p.set_name("Davi");

	p.subscribe_observer(new console_printer_observer);

	p.set_age(7);
	p.set_name("David");
	*/
	return 0;
}
