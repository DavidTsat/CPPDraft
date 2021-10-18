#include <iostream>

class S {
	/*
	*private members
	*/
	
	S() {
		// to implement
	}

	/*
	* other functions
	*/

public:
	S(const S&) = delete;
	S& operator=(const S&) = delete;

	static S& get_instance() {
		static S s;
		return s;
	}
};

int main() {


	return 0;
}