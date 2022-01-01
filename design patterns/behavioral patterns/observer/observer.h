#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
struct Observer;

template <typename T>
class Observable
{
	vector<Observer<T>*> observers;
public:
	void notify(T& source, const string& name)
	{
		for (auto obs : observers)
		{
			obs->field_changed(source, name);
		}
	}
	virtual void subscribe(Observer<T>* f)
	{
		observers.push_back(f);
	}
	virtual void unsubscribe(Observer<T>* f)
	{

	}
};

class Person : public Observable<Person>
{
	int age;
public:
	Person(int a) : age(a) {}
	int get_age() const
	{
		return age;
	}
	void set_age(const int value)
	{
		if (age == value) return;
		age = value;
		notify(*this, "age");
	}
};

struct PersonListener
{
	virtual void person_changed(Person& p, const string& property_name, const int new_value) = 0;
};

template <typename T>
struct Observer
{
	virtual void field_changed(T& source, const string& field_name) = 0;
};


struct ConsolePersonObserver : Observer<Person>
{
	void field_changed(Person& source, const string& field_name) override
	{
		cout << "Person's " << field_name << " has changed to " << source.get_age() << endl;
	}
};
