#include "composite.h"
#include "creature.h"
#include <iostream>

int main() {
	group root("root");
	circle c1, c2;
	root.add_object(&c1);

	group subgroup("sub");
	subgroup.add_object(&c2);

	root.add_object(&subgroup);
	
	c1.draw();
	std::cout << std::endl; 
	root.draw();
	//subgroup.draw();
	return 0;
}