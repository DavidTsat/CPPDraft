#include "property_proxy.h"
#include "virtual_proxy.h"

#include <iostream>

using namespace std;

struct creature
{
	property<int> strength {5};
	property<int> agility  {7};
};

void draw_image(image& img)
{
	cout << "About to draw the image" << endl;
	img.draw();
	cout << "Done drawing the image" << endl;
}

int main()
{
	/*
	creature c;
	c.agility = 10;
	//int x = c.strength;
	//cout << x << endl;
	*/
	
	//bitmap img("pokemon.png");
	lazy_bitmap img("pokemon.png");
	draw_image(img);
	return 0;
}