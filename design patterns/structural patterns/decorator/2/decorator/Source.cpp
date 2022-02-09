#include <iostream>
#include "decorator_ex.h"

int main()
{
	circle c(0.5f);
	colored_shape red_circle(c, "red");

	//cout << red_circle.str() << endl;

	square s(3);
	transparent_shape demi_square(s, 85);
//	cout << demi_square.str();

	transparent_shape transparent_colored_square(*(new colored_shape(*(new square(4)), "blue")), 85);

	cout << transparent_colored_square.str() << endl;
	
	colored_shape_<transparent_shape_<square>> sq{ "blue", 8.4f, 5 };

	cout << sq.str() << endl;
	return 0;
}