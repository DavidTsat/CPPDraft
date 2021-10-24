#pragma once
#include <memory>
#include <string>
#include <iostream>

class person {
	class person_impl;

	std::unique_ptr<person_impl> impl;

	person(std::string, unsigned);
public:

	person(person&&) = default;
	~person();
	
	void greet();

	struct person_factory {
		static std::unique_ptr<person> create_person_pointer(std::string name, unsigned age) {
			return std::unique_ptr<person>(new person(name, age));
		}
		static person create_person(std::string name, unsigned age) {
			return person(name, age);
		}
	};
	static person_factory factory;
};