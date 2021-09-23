#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


struct Address {
	std::string street, city;
	int suite;
	Address(std::string street_, std::string city_, int suite_) : street(street_), city(city_), suite(suite_) {}
	Address() = default;
private:
	friend class boost::serialization::access;
	template<typename Ar>
	void serialize(Ar& ar, const unsigned int version) {
		ar & street;
		ar & city;
		ar & suite;
	}
};

struct Contact {
	std::string name;
	Address* address = nullptr;

	Contact(std::string name_, Address* address_) : name(name_), address(address_) {}
	Contact() = default;
	Contact(const Contact& r) = delete;
	Contact(Contact&& r) = default;
	/*
	Contact(const Contact& r) {
		name = r.name;
		address = new Address(*r.address);
	}
	*/
	//~Contact() { delete address; }
private:
	friend class boost::serialization::access;
	template <typename Ar>
	void serialize(Ar& ar, const unsigned int version) {
		ar & name;
		ar & address;
	}
};

Address a = Address("123 East Dr", "London", 0);
Contact worker("", &a);

/*
auto clone = [](const Contact& c) {
	// 1. serialize the contact
	std::ostringstream oss;
	boost::archive::text_oarchive oa(oss);
	oa << c;
	std::string s = oss.str();
	// 2. deserialize the contact
	std::istringstream iss(oss.str());
	boost::archive::text_iarchive ia(iss);
	Contact result;
	ia >> result;
	return result;
};
*/
auto clone = [](const Contact& c) {
	// 1. serialize the contact
	std::ostringstream oss;
	boost::archive::text_oarchive oa(oss);
	oa << c;
	std::string s = oss.str();
	// 2. deserialize the contact
	std::istringstream iss(oss.str());
	boost::archive::text_iarchive ia(iss);
	std::unique_ptr<Contact> result = std::make_unique<Contact>();
	ia >> *result;
	return result;
};


struct EmployeeFactory {
	static Contact main_;
	static Contact aux_;
	
	static std::unique_ptr<Contact> NewMainOfficeEmployee(std::string name, int suite) {
		return NewEmployee(name, suite, EmployeeFactory::main_);
	}
	static std::unique_ptr<Contact> NewAuxOfficeEmployee(std::string name, int suite) {
		return NewEmployee(name, suite, EmployeeFactory::aux_);
	}
private:
	static Address a;
	static Address b;

	static std::unique_ptr<Contact> NewEmployee(std::string name, int suite, Contact& proto) {
		auto result = clone(proto);
		result->name = name;
		result->address->suite = suite;
		return result;
	}
};

Address EmployeeFactory::a("123 East Dr", "London", 0);
Address EmployeeFactory::b("123 East Dr B", "London", 0);

Contact EmployeeFactory::main_("", &a);
Contact EmployeeFactory::aux_("", &b);

int main() {

	std::unique_ptr<Contact> john1 = EmployeeFactory::NewAuxOfficeEmployee("JohnDoe", 123);
	std::unique_ptr<Contact> jane1 = EmployeeFactory::NewMainOfficeEmployee("JaneDoe", 125);


	std::unique_ptr<Contact> john = clone(worker);
	std::unique_ptr<Contact> jane = clone(worker);

	john->name = "John Doe";
	john->address->suite = 10;
	jane->name = "Jane Doe";
	jane->address->suite = 11;

	std::cout << "john: " << john->name << ", " << john->address->city <<
		", " << john->address->street << ", " << john->address->suite << std::endl;
	std::cout << "jane: " << jane->name << ", " << jane->address->city <<
		", " << jane->address->street << ", " << jane->address->suite << std::endl;

	std::cout << "ASAAA\n";
	
	std::cout << "john: " << john1->name << ", " << john1->address->city <<
		", " << john1->address->street << ", " << john1->address->suite << std::endl;
	std::cout << "jane: " << jane1->name << ", " << jane1->address->city <<
		", " << jane1->address->street << ", " << jane1->address->suite << std::endl;


	return 0;
}