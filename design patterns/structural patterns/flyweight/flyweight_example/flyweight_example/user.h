#pragma once
#include <vector>
#include <string>
#include <ostream>
#include <boost/flyweight.hpp>

class user {
	using key = std::size_t;

	key first_name, last_name;
	static std::vector<std::string> names;

	static key add(const std::string& s) {
		for (key i = 0; i < names.size(); ++i) {
			if (names[i] == s) {
				return i;
			}
		}
		names.push_back(s);
		return names.size()-1;
	}
public:
	user(const std::string& f, const std::string& l) : first_name(add(f)), last_name(add(l)) {}

	const std::string& get_first_name() const {
		return names[first_name];
	}
	const std::string& get_last_name() const {
		return names[last_name];
	}
	friend std::ostream& operator<<(std::ostream& os, const user& obj) {
		return os << "first name: " << obj.get_first_name() << "last name: " << obj.get_last_name();
	}
};

std::vector<std::string> user::names;

class user2 {
public:
	boost::flyweight<std::string> first_name, last_name;
//public:
	user2(const std::string& f, const std::string& l) : first_name(f), last_name(l)  {}

	const std::string& get_first_name() const {
		return first_name;
	}
	const std::string& get_last_name() const {
		return last_name;
	}
	friend std::ostream& operator<<(std::ostream& os, const user2& obj) {
		return os << "first name: " << obj.get_first_name() << "last name: " << obj.get_last_name();
	}
};