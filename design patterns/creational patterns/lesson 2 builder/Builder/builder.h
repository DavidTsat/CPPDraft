#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <memory>

class PersonBuilder;
class PersonAddressBuilder;
class PersonJobBuilder;

class Person {
	friend class PersonAddressBuilder;
	friend class PersonJobBuilder;
	// address
	std::string street_address, post_code, city;

	// employment
	std::string company_name, position;
	int annual_income = 0;
public:
	Person() {}

	static PersonBuilder create();
	
	void pretty_print() {
		std::cout << "street_address: " << street_address << ", post_code: " << post_code << ", city: " << city << std::endl;
		std::cout << "company_name: " << company_name << ", position: " << position << ", earning: " << annual_income << std::endl;
	}
};

class PersonBuilderBase {
protected:
	Person& person;
	explicit PersonBuilderBase(Person& person_) : person(person_) {

	}
public:
	operator Person() {
		return std::move(person);
	}

	//builder facets
	PersonAddressBuilder lives() const;
	PersonJobBuilder works() const;
};

class PersonBuilder : public PersonBuilderBase {
	Person p;
public:
	PersonBuilder() : PersonBuilderBase(p) {}

};


PersonBuilder Person::create() {
	return PersonBuilder();
}

class PersonAddressBuilder : public PersonBuilderBase {
public:
	explicit PersonAddressBuilder(Person& person) : PersonBuilderBase(person) {}
	
	PersonAddressBuilder& at(const std::string& street_address_) {
		person.street_address = street_address_;
		return *this;
	}

	PersonAddressBuilder& with_postcode(const std::string& post_code_) {
		person.post_code = post_code_;
		return *this;
	}

	PersonAddressBuilder& in(const std::string& city_) {
		person.city = city_;
		return *this;
	}
};

class PersonJobBuilder : public PersonBuilderBase {
public:
	explicit PersonJobBuilder(Person& person) : PersonBuilderBase(person) {}

	PersonJobBuilder& at(const std::string& company_name_) {
		person.company_name = company_name_;
		return *this;
	}

	PersonJobBuilder& as_a(const std::string& position_) {
		person.position = position_;
		return *this;
	}

	PersonJobBuilder& earning(int annual_income_) {
		person.annual_income = annual_income_;
		return *this;
	}
};

PersonAddressBuilder PersonBuilderBase::lives() const {
	return PersonAddressBuilder(person);
}

PersonJobBuilder PersonBuilderBase::works() const {
	return PersonJobBuilder(person);
}
