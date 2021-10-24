#include "person.h"

person::person_factory person::factory;

class person::person_impl {
	std::string name;
	unsigned age;
	//...
public: 
	~person_impl();
	person_impl(std::string, unsigned);
	person_impl(const person_impl&);

	void greet();
};

person::person(std::string name, unsigned age) : impl(std::make_unique<person_impl>(name, age)) {}

void person::greet() {
	impl->greet();
}

person::~person() { }


//###########################################################################################


person::person_impl::person_impl(std::string name_, unsigned age_) : name(name_), age(age_) {}

person::person_impl::person_impl(const person_impl& p) : name(p.name), age(p.age) {}

void person::person_impl::greet() {
	std::cout << "hello " << name << std::endl;
}

person::person_impl::~person_impl() {}
