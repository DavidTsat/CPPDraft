#include <iostream>
#include <string>
#include "number.h"

using namespace std;

class name
{
	string f;
	string l;
public:
	name(string first_name, string last_name) : f(first_name), l(last_name) {}

	void print() const
	{
		cout << l << ", " << f << endl;
	}
};

template <typename printable>
struct repeat_print : printable
{
	explicit repeat_print(const printable& p) : printable(p) {}
	void repeat(unsigned n) const
	{
		while (n--)
		{
			this->print();
		}
	}
};

int main()
{
	re_undoable_number n;
	n.set(42);
	cout << n.get() << endl; // 42
	n.set(84);
	cout << n.get() << endl; // 84
	n.undo();
	cout << n.get() << endl; // 42
	n.redo();
	cout << n.get() << endl; // 84


	/*
	name n("David", "Tsaturyan");
	n.print();

	repeat_print<name> r(n);
	r.repeat(10);
	*/
	return 0;
}