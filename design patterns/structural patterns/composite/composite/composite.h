#pragma once
#include <vector>
#include <string>
#include <iostream>

struct graphic_object {
	virtual void draw() = 0;
};

struct circle : graphic_object {
	void draw() override {
		std::cout << "circle" << std::endl;
	}
};

struct group : graphic_object {
	std::string name;
	std::vector<graphic_object*> objects;

	explicit group(const std::string& name_) : name(name_) {}

	void draw() override {
		std::cout << "group" << name << " contains:" << std::endl;
		for (auto o : objects) {
			o->draw();
		}
	}

	group& add_object(graphic_object* o) {
		objects.push_back(o);
		return *this;
	}
};