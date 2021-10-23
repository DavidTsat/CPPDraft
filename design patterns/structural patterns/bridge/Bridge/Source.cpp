#include <iostream>
#include "person.h"

int main() {
	person p = person::factory.create_person("David", 26);
	p.greet();
	return 0;
}
