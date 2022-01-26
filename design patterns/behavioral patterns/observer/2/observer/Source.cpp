#include <iostream>
#include <vector>
#include "person.h"

using namespace std;


int main()
{
	person p;
	//console_printer_observer c;

	p.set_age(6);
	p.set_name("Davi");

	p.subscribe_observer(new console_printer_observer);

	p.set_age(7);
	p.set_name("David");
	return 0;
}
