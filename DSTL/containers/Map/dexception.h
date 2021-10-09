#pragma once
#include <string>
#include <stdexcept>
#include <iostream>

namespace DSTL {

	class key_not_found_exception : public std::exception {
		const std::string message;
	public:
		key_not_found_exception(const std::string& message_ = "Given key is not present in the tree!") : message(message_) {}

		virtual const char* what() const override {
			std::cout << message << std::endl;
			return message.c_str();
		}
	};

	class repeated_key_exception : public std::exception {
	const std::string message;
	public:
		repeated_key_exception(const std::string& message_ = "Given key already exist in tree!") : message(message_) {}

		virtual const char* what() const override {
			std::cout << message << std::endl;
			return message.c_str();
		}
	};
}