#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <chrono>

// task 1
void update_count(std::map<std::string, int> storage, std::string str)
{
	if (storage.count(str))
		++storage[str];
	else
		storage[str] = 1;
}

void test_task1()
{
	std::map<std::string, int> wordsCount;
	std::vector<std::string> words;
	std::string text("some very long long text");
	boost::split(words, text, boost::is_any_of(" "));

	for (const std::string& word : words)
	{
		update_count(wordsCount, word);
	}
	for (const auto& word : wordsCount)
	{
		std::cout << word.first << " : " << word.second << std::endl;
	}

	std::cout << "finished!" << std::endl;
}

// task 2
/*
class Base
{
	void print() {
		std::cout << "from base" << std::endl;
	}
public:
	Base() { print(); }
	~Base() { print(); }
	void basePrint() { print(); }
};

class Derived : public Base
{
	virtual void print()
	{
		std::cout << "from Derived" << std::endl;
	}
public:
	Derived() { print(); }
	~Derived() { print(); }
};
*/
class Base
{
	virtual void print() {
		std::cout << "from base" << std::endl;
	}
public:
	Base() { print(); }
	virtual ~Base() { print(); }
	void basePrint() { print(); }
};

class Derived : public Base
{
	virtual void print()
	{
		std::cout << "from Derived" << std::endl;
	}
public:
	Derived() { print(); }
	~Derived() { print(); }
};

/*
from base
from derived
from base
from base
*/

/*
* 
from base
from derived
from derived
from derived 
from base
*/

void test_task2()
{
	Base* base = new Derived;
	base->basePrint();
	delete base;
}

// task 3
class A
{

};
class B
{

};

class C
{
	A* a_;
	B* b_;
public:
	C()
	{
		a_ = new A();
		b_ = new B();
	}
	~C()
	{
		delete a_;
		delete b_;
	}

};

void test_task3()
{
	C c();
	{
		C c2(c);
	}
}

// task 4. compute pow(x, a)

int cc = 0;
double p_1(double x, double a)
{
	if (a == 0) return 1;
	if (a == 1) return x;
	++cc;

	if (a < 0)
		return 1 / (x * p_1(x, abs(a) - 1));

	return x * p_1(x, abs(a) - 1);
}

double p_2(double x, double a)
{
	if (a == 0) return 1;
	if (a == 1) return x;
	++cc;

	double pow_ = p_2(x, abs(a / 2));

	if ((int)a % 2 == 0)
		pow_ = pow_ * pow_;
	else
		pow_ = pow_ * pow_ * x;

	return a < 0 ? 1 / pow_ : pow_;
}

void test_task4(double (*f_)(double, double))
{
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	std::cout << f_(2, -2) << std::endl;
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " ms" << std::endl;
	//std::cout << "CCCCC: " << cc << std::endl;
}

// task 5
struct A {

	~A() {
		throw 1;
	}
};

void test_task5()
{
	try
	{
		A a;
		throw "abc";
	}
	catch (int a)
	{
		std::cout << a << std::endl;
	}
	catch (const char* a)
	{
		std::cout << a << std::endl;
	}


	std::cout << "Hello World";

}

int main()
{
	test_task4(p_1);
	return 0;
}