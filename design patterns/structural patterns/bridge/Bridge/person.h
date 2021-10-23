#pragma once
#include <memory>
#include <string>
#include <iostream>

class person {
	class person_impl;
	std::unique_ptr<person_impl> impl;

	person(std::string, unsigned);

public:

//	person(std::string, unsigned);
	person(const person&);
	~person();
	
	void greet();


	struct person_factory {
		//		std::unique_ptr<person_impl> impl;

		/*static std::unique_ptr<person> create_person_pointer(std::string name_, unsigned age_) {
			return std::make_unique<person>(name_, age_);
		}*/
		static person create_person(std::string name_, unsigned age_) {
			return person(name_, age_);
		}
	};
	static person_factory factory;
};