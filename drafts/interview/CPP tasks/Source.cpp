#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <map>

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
	/*
	C(const C& c)
	{
		a_ = new A(*c.a_);
		b_ = new B(*c.b_);
	}
	*/
	void f()
	{
		std::cout << "c::f()" << std::endl;
	}
};
int main()
{
	C c();
	//c.f();
	{
		C c2(c);
	}
	return 0;
}