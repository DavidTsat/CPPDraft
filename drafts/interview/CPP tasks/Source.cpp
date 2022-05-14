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
	void print()
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
		C c2;//(c);
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
struct AA {

	~AA() {
		throw 1;
	}
};

void test_task5()
{
	try
	{
		AA a;
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

// task 6

/*
Есть ли тут проблема ?
Вопросы.
1. Скомпилируется ? - Да, 5 строка легальна
2. Что будет, если запустить ? - крашится
3. Почему ? Где проблема ? - проблема на 3 строке, арифметика указателей. 
4. Можешь переписать 3 строку без индексации (без квадратных скобок, а с помощью арифметики указателей) ? - arrayOfBase[1] == arrayOfBase + sizeof(Base)
5. Видишь где проблема ? - arrayOfBase[1] == arrayOfBase + sizeof(Base) ссылается не на начало какого-либо объекта, а в середину какого-то объекта, ибо массив у нас из объектов Derived_, а sizeof(Derived) > sizeof(Base)
6. (Этот вопрос можно задавать и в начале). Что будет, если закомментируем 2 строку (int i_; ) - напечатает Derived_::f
*/

class Base_ {
public:
	virtual void f()             // 1
	{
		std::cout << "Base_::f" << std::endl;
	}
};

class Derived_ : public Base_ {
public:
	// ...
private:
	int i_;                       

	void f() override
	{
		std::cout << "Derived_::f" << std::endl;
	}
};

void userCode(Base_* arrayOfBase)
{
	arrayOfBase[1].f();          
}

void test_task6()
{
	Derived_ arrayOfDerived[10];   
	userCode(arrayOfDerived);     
	// ...
}

// Task 7.
/*
Объявить указатель на массив const char[3] = {'a', b', 'c'};
*/

void test_task7()
{
	const char a[3] = { 'a', 'b', 'c' };
	const char(*p)[3] = &a;
	std::cout << (*p)[0] << std::endl;
}

// Task 8.
/*
Объявить массив указателей на функции.
Даны функции f и g, требуется записать их в массив и вызвать
*/
void f_(int, const char*) { std::cout << "f_\n"; }
void g_(int, const char*) { std::cout << "g_\n"; }

void test_task8()
{
	void (*m[2]) (int, const char*) = { f_, g_ };
	m[0](7, nullptr);
	m[1](8, nullptr);
}


#define show(x) cout <<  #x " = " << x << endl;
// Test three
struct Employee
{
	string email_;
	string firstName_;
	string lastName_;

	// В чем проблема и как можно исправить ?
	Employee(const char* firstName, const char* lastName)
		: firstName_(firstName), lastName_(lastName), email_(firstName_ + "." + lastName_ + "@gmail.com") {}
};

void test_task9()
{
	Employee e("David", "Tsaturyan");

	show(e.email_)
	show(e.firstName_)
	show(e.lastName_)
}

int main()
{
	test_task8();
	//test_task6();
	//test_task4(p_1);
	return 0;
}