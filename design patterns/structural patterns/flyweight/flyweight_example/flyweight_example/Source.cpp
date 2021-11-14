#include <iostream>
#include "user.h"
#include "string_range.h"

int main() {
	FormattedText f("This is a brave new world");

	std::cout << f << std::endl;
	f.get_range(10, 15).capitalize = true;
	std::cout << f << std::endl;

	user u1("David", "Ts");
	user u2("Daria", "Ts");
	user u3("Julia", "Gr");

	std::cout << &u1.get_first_name() << ' ' << &u2.get_first_name() << ' ' << &u3.get_first_name() << std::endl;
	std::cout << &u1.get_last_name() << ' ' << &u2.get_last_name() << ' ' << &u3.get_last_name() << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;

	user2 uu1("David", "Ts");
	user2 uu2("Daria", "Ts");
	user2 uu3("Julia", "Gr");

	std::cout << &uu1.get_first_name() << ' ' << &uu2.get_first_name() << ' ' << &uu3.get_first_name() << std::endl;
	std::cout << &uu1.get_last_name() << ' ' << &uu2.get_last_name() << ' ' << &uu3.get_last_name() << std::endl;

	std::cout << std::endl;
	uu2.last_name = "GGG";
	std::cout << &uu1.get_first_name() << ' ' << &uu2.get_first_name() << ' ' << &uu3.get_first_name() << std::endl;
	std::cout << &uu1.get_last_name() << ' ' << &uu2.get_last_name() << ' ' << &uu3.get_last_name() << std::endl;
	
	return 0;
}