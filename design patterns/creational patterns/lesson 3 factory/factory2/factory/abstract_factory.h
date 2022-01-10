#pragma once
#include <map>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

/*
shared_ptr<hot_drink> make_drink(string type)
{
	shared_ptr<hot_drink> drink;
	if (type == "tea")
	{
		drink = make_shared<tea>();
		drink->prepare(200);
	}
	else if (type == "coffee")
	{
		drink = make_shared<coffee>();
		drink->prepare(50);
	}
	return drink;
}
*/

struct hot_drink
{
	virtual void prepare(int volume) = 0;
	virtual ~hot_drink() {};
};

struct tea : hot_drink
{
	void prepare(int volume) override
	{
		cout << "Take tea bag, boil water, pour " << volume << "ml, add some lemon" << endl;
	}
	tea() = default;
	tea(tea&&) = default;
	~tea() = default;
};

struct coffee : hot_drink
{
	void prepare(int volume) override
	{
		cout << "Take coffee bag, boil water, pour " << volume << "ml, add some sugar" << endl;
	}
	coffee() = default;
	coffee(coffee&&) = default;
	~coffee() = default;
};


struct hot_drink_factory
{
	virtual shared_ptr<hot_drink> make() const = 0;
	
};

class coffee_factory : public hot_drink_factory
{
public:
	shared_ptr<hot_drink> make() const override
	{
		return make_shared<coffee>();
	}

};

class tea_factory : public hot_drink_factory
{
public:
	shared_ptr<hot_drink> make() const override
	{
		return make_shared<tea>();
	}

};

class drink_factory
{
	map<string, shared_ptr<hot_drink_factory>> f;
	
public:
	drink_factory()
	{
		f["tea"] = make_shared<tea_factory>();
		f["coffee"] = make_shared<coffee_factory>();
	}

	shared_ptr<hot_drink> make_drink(const string& name)
	{
		return f[name]->make();
	}

	static drink_factory& get_instance()
	{
		static drink_factory instance;
		return instance;
	}
private:
//	static drink_factory instance;
};

//drink_factory drink_factory::instance;
