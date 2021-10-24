#include <iostream>
#include "bridge_example.h"

int main() {
	raster_renderer rr;
	
	circle raster_circle(rr, 5, 5, 5);
	raster_circle.draw();
	raster_circle.resize(2);
	raster_circle.draw();

	return 0;
}