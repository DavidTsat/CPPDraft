#pragma once
#include <iostream>
#include <list>

using namespace std;

struct graphic_object
{
	virtual void draw() = 0;
};

struct circle : graphic_object
{
	void draw() override
	{
		cout << "circle" << endl;
	}
};

struct group : graphic_object
{
	string name;

	explicit group(const string& name_) : name(name_) {}

	void draw() override
	{
		cout << "group " << name << " contains:" << endl;
		for (const auto& o : objects)
		{
			o->draw();
		}
	}
	void add(graphic_object* g)
	{
		objects.push_back(g);
	}

private:
	list<graphic_object*> objects;
};