#include <iostream>
#include "user.h"

int main() {
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