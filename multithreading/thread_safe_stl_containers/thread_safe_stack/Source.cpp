#include "thread_safe_stack.h"
#include <iostream>
#include <stack>



int main() {

	thread_safe_stack<std::string> t;

	t.push("David");
	t.push("Juliana");
	t.push("Daria");
	
	try {
		std::string s;
		t.pop(s);
		std::cout << s << *t.pop() << *t.pop() << std::endl;
	}
	catch (empty_stack& e) {
		std::cout << e.what();
	}
	return 0;
}