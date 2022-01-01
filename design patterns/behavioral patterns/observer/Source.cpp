#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
class observer
{
public:
	virtual void field_changed(T* p, string field) = 0;
};

template <typename T>
class observable
{
	vector<observer<T>*> observers;
public:
	virtual void notify(T* p, string field_name)
	{
		for (auto o : observers)
		{
			o->field_changed(p, field_name);
		}
	}
	virtual void subscribe(observer<T>* o)
	{
		observers.push_back(o);
	}
	virtual void unsubscribe(observer<T>* o)
	{
		//
	}
};

class person : public observable<person>
{
	int age;
public:
	person(int a) : age(a) {}
	int get_age() const { return age; }
	void set_age(int a)
	{
		age = a;
		notify(this, "age");
	}
};

class consolePersonObserver : public observer<person>
{
public:
	void field_changed(person* p, string field_name) override
	{
		cout << field_name << ' ' << "has changed " << p->get_age() <<  endl;
	}
};

int main()
{
	person p(20);
	consolePersonObserver cpo;
	p.subscribe(&cpo);

	p.set_age(21);
	p.set_age(22);
	return 0;
}
