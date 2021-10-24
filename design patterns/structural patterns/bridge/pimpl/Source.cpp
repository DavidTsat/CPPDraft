#include <iostream>
#include "person.h"

int main() {
	person p = person::factory.create_person("David", 26);
	p.greet();

	auto pp = person::factory.create_person_pointer("Juliana", 23);
	pp->greet();
	return 0;
}
