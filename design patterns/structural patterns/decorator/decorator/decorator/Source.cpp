#include "decorator_concept.h"
#include "decorator_example1.h"
#include "decorator_example2.h"

#include <iostream>

void client_code(component* component_) {
	//...
	std::cout << "RESULT: " << component_->operation();
	//..
}


int main() {
	/*
	* 1.
	* 
	component* simple = new concrete_component;
	client_code(simple);
	std::cout << std::endl << std::endl;
	component* decorator1 = new concrete_decorator_a(simple);
	component* decorator2 = new concrete_decorator_b(decorator1);
	client_code(decorator1);
	std::cout << std::endl << std::endl;
	client_code(decorator2);
	std::cout << std::endl << std::endl;
	*/

	/*
	* 2.
	square s(4);
	circle c(10);

	std::cout << s.str() << std::endl;
	std::cout << c.str() << std::endl;

	colored_shape cs(&s, "red");
	colored_shape cc(&c, "green");

	std::cout << cs.str() << std::endl;
	std::cout << cc.str() << std::endl;

	transparent_shape ts(&s, 7);
	transparent_shape tc(&c, 9);

	std::cout << ts.str() << std::endl;
	std::cout << tc.str() << std::endl;

	transparent_shape tcs(&cs, 85);
	colored_shape ctc(&tc, "grey");

	std::cout << tcs.str() << std::endl;
	std::cout << ctc.str() << std::endl;

	std::cout << std::endl;
	// all on a single line
	// but we need to delete the pointers
	/*
	colored_shape colored_transparent_square (new transparent_shape(new square(77), 78), "beryuzovi");
	std::cout << colored_transparent_square.str() << std::endl;
	*/
	TextView tv(4, "red");
	
	BorderDecorator b(2, &tv);
	b.draw();
	ScrollDecorator s(4, &b);
	DropShadowDecorator d(5, &s, 'D');

	d.draw();

	return 0;
}