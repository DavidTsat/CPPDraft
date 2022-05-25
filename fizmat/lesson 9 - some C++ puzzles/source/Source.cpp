#include <iostream>
#include <vector>
#include <assert.h>
#include <vector>
#include <iterator>
#include <map>

using namespace std;

void question_1_wo()
{
	vector<int> v;
	v.reserve(2);
	assert(v.capacity() == 2);					
	v[0] = 1;									
	v[1] = 2;									
	for (vector<int>::const_iterator i = v.begin(); i < v.end(); i++) { 
		cout << *i << endl; 
	}
	
	cout << v[0];
}

void question_1()
{
	vector<int> v;
	v.reserve(2);
	assert(v.capacity() == 2);					// 1
	v[0] = 1;									// 2
	v[1] = 2;									// 2
	for (vector<int>::const_iterator i = v.begin(); i < v.end(); i++) { // 1. cbegin instead of begin,  2. != instead of <, 3. prefix ++ instead of postfix ++
		cout << *i << endl; // '/n' better than endl, to not flush. Flush after the loop
	}
	// Prefer reusing the standard library's copy and for_each instead of handcrafting your own loops
	cout << v[0];
	//cout << endl;

}

struct A {
	int c;
	//...
	A() {cout << "A default" << endl; }
	A(int cc) : c(cc) { cout << "A(int cc)" << endl; }
	A(const A& aa) { c = aa.c;  cout << "A(const A&)" << endl; }
	A(A&&) noexcept { cout << "A(A&&)" << endl; }
	A& operator=(const A& aa) { c = aa.c; cout << "operator=(const A&)" << endl; return *this; }
	A& operator=(A&&) noexcept { cout << "operator=(A&&)" << endl; return *this; }

	operator int() { return c; }
};

//new (int (*[10])()); // okay: allocates an array of 10 pointers to functions ??? 

template <typename T>
struct vec
{
	T* v;
	size_t c;
	size_t s;

	vec() : v((T*) operator new [](100 * sizeof(T))), c(100), s(0) {}
	vec(size_t s_) : v(new T[s_]), c(s_), s(s_) {}
	T& operator[](size_t i) { return v[i]; }
};

// question 2 new, operator new, placement new

void question_2()
{
	//vec<A> v(10);
//vector<A> v(10);
	vec<A> v;
	//	v.reserve(10);
	v[45] = A(7); // ERROR
//	new (v.v + 45) A(7); // OKAY
	cout << v[45] << endl;
}

/*
{
	Object* p = new Object(value);
	// EQUIVALENT TO
	Object* p = reinterpret_cast<Object*>(operator new(sizeof(Object))); //no contruction here
	new(p) Object(value); //calls operator new(size_t, void*) via keyword
}
*/

// question 3 copy vs unitiliazed copy
template<class InputIt, class OutputIt>
OutputIt copy_(InputIt first, InputIt last, OutputIt d_first)
{
	for (; first != last; (void)++first, (void)++d_first) 
	{
		*d_first = *first;
	}
	return d_first;
}


template<class InputIt, class OutputIt>
OutputIt uninitialized_copy_(InputIt first, InputIt last, OutputIt d_first)
{
	using T = typename iterator_traits<InputIt>::value_type;
	OutputIt d = d_first;
	try
	{
		for (; first != last; (void)++first, (void)++d_first)
		{
			::new (addressof(*d_first)) T(*first);
		}
		return d_first;
	}
	catch (...)
	{
		for (; d != d_first; ++d)
		{
			d->~T();
			throw;
		}
	}
}

void question_3()
{
	vector<int> vv{ 1,4,5,7,8 };

	int* p = (int*) operator new[](10*sizeof(int));
	uninitialized_copy_(vv.cbegin(), vv.cend(), p);

	copy(p, p + vv.size(), ostream_iterator<int>(cout, " "));
	operator delete[] (p);
}

// Question: Write a construct template to call placement new
template <typename T1, typename T2>
inline void construct_(T1* p, const T2& v)
{
	new(p) T1(v);
}

template <typename T>
void destroy(T* p) 
// QUESTION: USE destroy(T p) instead ??? 
{
	p->~T();

	//using TT = typename iterator_traits<T>::value_type;
	//p->~TT();
}
//Remember that pointers (into an array) are always iterators, but iterators are not always pointers.
template <typename It>
void destroy(It begin, It end)
{
	while (begin != end)
	{
		destroy(begin);
		//destroy(&*begin);
		++begin;
	}
}

template<class InputIt, class OutputIt>
OutputIt uninitialized_copy2_(InputIt first, InputIt last, OutputIt d_first)
{
	using T = typename iterator_traits<InputIt>::value_type;
	OutputIt d = d_first;
	try
	{
		for (; first != last; (void)++first, (void)++d_first)
		{
			::new (addressof(*d_first)) T(*first);
		}
		return d_first;
	}
	catch (...)
	{
		destroy(d, d_first);
		throw;
	}
}

void question_4()
{
	vector<int> vv{ 1,4,5,7,8 };

	int* p = (int*) operator new[](10 * sizeof(int));
	uninitialized_copy2_(vv.cbegin(), vv.cend(), p);

	copy(p, p + vv.size(), ostream_iterator<int>(cout, " "));
	operator delete[](p);
}

/*
What are the semantics of the following function, including the requirements on T ? Is it possible
to remove any of those requirements ? If so, demonstrate how, and argue whether doing so is a
good idea or a bad idea.
// Example 6-2(a): swap.
//
template <class T>
void swap(T & a, T & b) {
	T temp(a); a = b; b = temp;
}
*/

template <class T>
void swap_(T& a, T& b) 
{
	// exception safety discussion

	T temp(a); 
	a = b; 
	b = temp;
}

template <class T>
void swap2_(T& a, T& b) // without assignment operators
{
	if (&a != &b)
	{
		T temp(a);

		a.~T();
		new (addressof(a)) T(b);

		b.~T();
		new (addressof(b)) T(temp);
	}
	/*
	destroy(&a);
	construct_(&a, b);

	destroy(&b);
	construct_(&b, temp);
	*/
}
//First, this is never appropriate if T copy assignment can throw, because then you get all the exception safety problems of the original version, only in spades
void question_5()
{
	A a(7);
	A b(8);

	cout << a << endl;
	cout << b << endl;

	//swap_(a, b);
	swap2_(a, b);

	cout << a << endl;
	cout << b << endl;
}
// EMPLACE examples

//2. In the following code, which version of f will be invoked by the last line ? Why ?
template<class T>
void f(T)
{
	cout << "void f(T)\n";
}

template<>
void f<int*>(int*)
{
	cout << "void f<int*>(int*)\n";
}

template<class T>
void f(T*)
{
	cout << "void f(T*)\n";
}

/*
template<>
void f<int>(int*)
{
	cout << "void f<int*>(int*)\n";
}
*/
/*
Remember that function template specializations don't participate in overload resolution. A
specialization will be used only when its primary template is chosen, and the choice of
primary template isn't affected by whether it happens to have specializations or not

If you do provide overloads of a function template, avoid also providing
specializations
*/
void question_6()
{
	int* p = new int(7);
	f(p);
	delete p;

	bool b = true;
	int i = 77;
	double d = 41;

	f(b); // calls (b) with T = bool
	f(&i); // calls (d) with T = int
	f(i); // calls (e)
	f(d);
}

void update_count(map<std::string, int>& storage, string str)
{
	if (storage.count(str))
		++storage[str];
	else
		storage[str] = 1;
}


void split_(vector<string>& v, const string& s, char c)
{
	auto p = s.cbegin();

	while (p != s.cend())
	{
		auto p2 = find(p, s.cend(), c);
		v.push_back(string(p, p2));
		p = p2 == s.cend() ? p2 : ++p2;
	}
}


template <typename Cont, typename It, typename Delim>
void split_(Cont& v, It begin, It end, const Delim& c)
{
	auto b = back_inserter(v);
	while (begin != end)
	{
		auto p2 = find(begin, end, c);
		*b++ = { begin, p2 };
		begin = p2 == end ? p2 : ++p2;
	}
}


void question_7()
{
	std::map<std::string, int> wordsCount;
	std::vector<std::string> words;
	std::string text("some very long long text");
	//boost::split(words, text, boost::is_any_of(" "));
	//split_(words, text, ' ');
	split_(words, text.cbegin(), text.cend(), ' ');
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

// TOPTAL QUESTIONS
void question_8()
{
	std::cout << 25u - 50 << endl;
}

struct my_struct
{
	//...
};

void question_9()
{
	my_struct* bar;
	/* ... do stuff, including setting bar to point to a defined my_struct_t object ... */
	//memset(bar, 0, sizeof(bar));
}

template <typename A, typename B>
struct is_same_
{
	static const bool val = false;
};

template <typename A>
struct is_same_<A, A>
{
	static const bool val = true;
};

// postfix prefix ++
template <typename A, typename B>
bool is_same_class()
{
	
	return is_same_<A, B>::val;
}

void question_10()
{
	cout << boolalpha << is_same_class<int, double>() << endl;
	cout << is_same_class<int, int>() << endl;
	cout << is_same_class<string, vector<string>>() << endl;
	cout << is_same_class<string, string>() << endl;
}

class AA {
public:
	AA() {}
	~AA() {
		throw 42;
	}
};

void question_11() 
{
	try {
		A a;
		throw 32;
	}
	catch (int a) {
		std::cout << a;
	}
}

class S {
public:
	S() {
		topSecretValue = 42;
	}
	bool b;
	int i;
	string s;
private:
	int topSecretValue;
};


void question_12()
{
	S* s = new S;

	class S_ {
	public:
		int getTopSecretValue() { return topSecretValue; }
		bool b;
		int i;
		string s;
	private:
		int topSecretValue;
	};

	S_* s_ = reinterpret_cast<S_*>(s);
	cout << s_->getTopSecretValue() << endl;

	delete s;
}

void question_13()
{
	unsigned char half_limit = 150;

	for (unsigned char i = 0; i < 2 * half_limit; ++i)
	{
		// do something;
	}
}

/*
How can you make sure a C++ function can be called as e.g. void foo(int, int) but not as any other type like void foo(long, long)?
*/
void foo(int a, int b) {
	// whatever
	cout << a << " : " << b << endl;
}

template <typename T1, typename T2> 
void foo(T1 a, T2 b) = delete;

void question_14()
{
	foo(14, 7);
}

//volatile mutable expplicit extern

void question_15()
{
	const size_t m = 4;
	volatile size_t c = 0;
	//...
	if (c > m)
	{
		// Выдаем предупреждение
	}
	// Значение переменной countPeople к примеру будет менять с другого потока
}

int main()
{
//	question_1();
//	question_2();
//	question_3();
//	question_4();
//	question_5();
//	question_6();
//	question_7();
//	question_10();
//	question_12();
	question_14();
	return 0;
}