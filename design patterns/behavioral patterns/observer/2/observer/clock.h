#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <variant>

using namespace std;

/*
class observable;

struct observer
{
	virtual void state_changed(observable*) = 0;
	virtual ~observer() {}
};


class observable
{
	vector<observer*> observers;
protected:
	void notify_observers(observable* changed_obj)
	{
		for (observer* o : observers)
		{
			o->state_changed(changed_obj);
		}
	}
public:
	void subscribe_observer(observer* o)
	{
		observers.push_back(o);
	}
	void unsubscribe_observer(observer* o)
	{

	}
};

class clock_ : public observable
{
	string date;
public:
	void set_date(const string& new_date) { date = new_date; notify_observers(this); }
	string get_date() const { return date; }
};

class clock_drawer : public observer
{
public:
	void state_changed(observable* c) override
	{
		cout << "clock_drawer notified, new date is " << c->get_date() << endl;
	}
	~clock_drawer() {}
};
*/


template <typename T>
struct observer
{
	virtual void state_changed(T*, variant<string, int, bool>) = 0;
	virtual ~observer() {}
};

template <typename T>
class observable
{
	vector<unique_ptr<observer<T>>> observers;
protected:
	void notify_observers(T* changed_obj, variant<string, int, bool> changed_state)
	{
		for (unique_ptr<observer<T>>& o : observers)
		{
			o->state_changed(changed_obj, changed_state);
		}
	}
public:
	void subscribe_observer(unique_ptr<observer<T>> o)
	{
		observers.push_back(move(o));
	}
	void unsubscribe_observer(unique_ptr<observer<T>> o)
	{

	}
};

class date : public observable<date>
{
	string date_;
	int code;
	bool is_bank_holiday;

public:
	void set_date_properties(int code_ = 0, bool is_bank_holiday_ = false)
	{
		code = code_;
		is_bank_holiday = is_bank_holiday_;
		//...
		notify_observers(this, code);
		notify_observers(this, is_bank_holiday);
	}

	void set_date(const string& new_date, int code_ = 0, bool is_bank_holiday_ = false) 
	{ 
		date_ = new_date; 
		//...
		notify_observers(this, new_date);
	}
	string get_date() const { return date_; }
};

class date_drawer : public observer<date>
{
public:
	void state_changed(date* c, variant<string, int, bool> state) override
	{
		visit([c](const auto& x) {cout << "date_drawer notified, new state is " << x << ", new date is " << c->get_date() << endl; }, state);
	}
};
