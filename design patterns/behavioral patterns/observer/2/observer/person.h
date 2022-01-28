#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class observer
{
public:
	using observable_object = T;
	virtual void field_changed(observable_object& o, std::string field_name) = 0;
};

template <typename T>
class observable
{
	vector<observer<T>*> v;
protected:
	void notify_observers(T& t, const string& n)
	{
		for (const auto& o : v)
		{
			o->field_changed(t, n);
		}
	}
public:
	void subscribe_observer(unique_ptr<observer<T>> o)
	{
		v.push_back(o);
	}
	void unsubscribe_observer(unique_ptr<observer<T>> o)
	{
		//todo
	}
};

class person : public observable<person>
{
	string name;
	int age;
public:
	string get_name() const { return name; }
	void set_name(const string& n)
	{
		name = n;
		notify_observers(*this, "name");
	}

	int get_age() const { return age; }
	void set_age(int a)
	{
		age = a;
		notify_observers(*this, "age");
	}
};

class console_printer_observer : public observer<person>
{
public:
	void field_changed(observable_object& o, std::string field_name) override
	{
		if (field_name == "age")
		{
			cout << "age is changed, new value is: " << o.get_age() << endl;
		}
		else if (field_name == "name")
		{
			cout << "name is changed, new value is: " << o.get_name() << endl;
		}
	}

};
