#pragma once
#include <string>
#include <stdexcept>
#include <iostream>

namespace DSTL {

	class empty_btree_exception : public std::exception {
		const std::string message;
	public:
		empty_btree_exception(const std::string& message_ = "The btree object is empty!") : message(message_) {}

		virtual const char* what() const override {
			std::cout << message << std::endl;
			return message.c_str();
		}
	};

	class repeated_key_exception : public std::exception {
	const std::string message;
	public:
		repeated_key_exception(const std::string& message_ = "Given key already exist in btree!") : message(message_) {}

		virtual const char* what() const override {
			std::cout << message << std::endl;
			return message.c_str();
		}
	};
}