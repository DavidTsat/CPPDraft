#include <iostream>
#include <future>
#include <chrono>

using namespace std;

int find_the_answer_to_ltuae()
{
	cout << "find_the_answer_to_ltuae\n";
	return 7;
}

void do_other_stuff()
{
	cout << "other stuff\n";
}

struct X
{
	void foo(int, const string&)
	{

	}
	string bar(const string&)
	{
		return "";
	}
};

struct Y
{
	double operator()(double d)
	{
		cout << "Y::operator() " << d << endl;
		return d;
	}
};

X baz(X& x)
{
	return x;
}

class move_only
{
public:
	move_only() = default;
	move_only(move_only&&) = default;
	move_only& operator=(move_only&&) = default;

	move_only(const move_only&) = delete;
	move_only& operator=(const move_only&) = delete;
	void operator() ()
	{

	}
};
int main()
{
	future<int> the_answer = async(find_the_answer_to_ltuae);
	//this_thread::sleep_for(chrono::milliseconds(100));

	do_other_stuff();
	cout << "the answer is: " << the_answer.get() << endl;

	X x;
	Y y;

	auto f1 = async(&X::foo, &x, 42, "hello");
	auto f2 = async(&X::bar, x, "goodbye");

	auto f3 = async(launch::async, Y(), 3.141);
	auto f4 = async(std::ref(y), 2.718);
	async(baz, std::ref(x));
	auto f5 = async(move_only());
	return 0;
}