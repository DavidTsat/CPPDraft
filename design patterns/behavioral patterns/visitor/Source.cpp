#include <iostream>
#include "visitor.h"

struct A;
struct B;
struct C;

void f(B* b);
void f(C* c);

struct A
{
	int a;
	A(int a_) : a(a_) {}

	virtual void f() = 0;
};

struct B : A
{
	B(int a_) : A(a_) {}

	void f() override
	{
		::f(this);
	}
};

struct C : A
{
	C(int a_) : A(a_) {}

	void f() override
	{
		::f(this);
	}
};

void f(B* b)
{
	cout << b->a << endl;
}

void f(C* c)
{
	cout << c->a << endl;
}

int main()
{
	B* b = new B(7);
	C* c = new C(8);

	f(b);
	
	A* a = new B(9);
	a->f();

	
	addition_expression* e = new addition_expression(new double_expression(1),
		new addition_expression(new double_expression(2), new double_expression(3)));
	
	
	ostringstream oss;
//	e->print(oss);
	/*
	expression_printer ee;
	ee.print(e, oss);
	cout << oss.str() << endl;
	*/
	expression_printer ep;
	ep.visit(e);

	cout << ep.str() << endl;

	expression_evaluator ev;
	ev.visit(e);
	cout << ev.r << endl;
	return 0;
}
