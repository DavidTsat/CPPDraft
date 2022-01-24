#pragma once
#include <iostream>
#include <list>

using namespace std;

class component
{
	component* parent;
public:
	virtual ~component(){}

	void set_parent(component* p)
	{
		parent = p;
	}
	component* get_parent() const
	{
		return parent;
	}
	virtual void add(component* c) {}
	virtual void remove(component* c) {}
	virtual bool is_composite() const
	{
		return false;
	}

	virtual string operation() const = 0;
};

class leaf : public component
{
public:
	string operation() const override
	{
		return "leaf";
	}
};

class composite : public component
{
protected:
	std::list<component*> children;
public:
	void add(component* c) override
	{
		children.push_back(c);
		//c->set_parent(this);
	}
	void remove(component* c) override
	{
		children.remove(c);
		c->set_parent(nullptr);
	}
	bool is_composite() const override
	{
		return true;
	}
	string operation() const override
	{
		string res;
		for (const component* c : children)
		{
			if (c == children.back())
			{
				res += c->operation();
			}
			else
			{
				res += c->operation() + '+';
			}
		}
		return "branch(" + res + ")";
	}
};

void client_code1(component* c)
{
	cout << "RESULT: " << c->operation();
}

void client_code2(component* c1, component* c2) {
	// ...
	if (c1->is_composite()) 
	{
		c1->add(c2);
	}
	cout << "RESULT: " << c1->operation();
	// ...
}