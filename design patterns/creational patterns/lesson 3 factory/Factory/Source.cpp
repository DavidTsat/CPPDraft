#include <iostream>
#include "factory.h"

int main() {
	/*
	auto p = Point::NewPolar(5, 60);
	auto my_point = PointFactory::NewCartesian(3, 4);
	*/
	Point pp = Point::Factory.NewCartesian(2, 3);

	DrinkFactory d;
	std::unique_ptr<HotDrink> c = d.make_drink("coffee");
	
	c->c();


	DrinkWithVolumeFactory dd;

	auto dc = dd.make_drink("tea");

	dc->c();
	return 0;
}