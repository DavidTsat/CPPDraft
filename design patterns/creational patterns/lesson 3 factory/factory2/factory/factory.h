#pragma once
#include <math.h>
#include <memory>

using namespace std;

class point
{
	float x, y;
	point(float x_, float y_) : x(x_), y(y_) {}
//	friend class unique_ptr<point>;
	struct point_factory
	{
		static unique_ptr<point> newDecartPoint(float x_, float y_)
		{
		//	return make_unique<point>(x_, y_);
			return unique_ptr<point>(new point(x_, y_));
		}

		static unique_ptr<point> newPolarPoint(float r, float theta)
		{
			return unique_ptr<point>(new point(r * (float)cos(theta), r * (float)sin(theta)));
		}
	};
public:
	static point_factory pf;
	
};

/*
class point
{
	float x, y;
	point(float x_, float y_) : x(x_), y(y_) {}
	friend class point_factory;
public:
	/*
	static point newDecartPoint(float x_, float y_)
	{
		return { x_, y_ };
	}

	static point newPolarPoint(float r, float theta)
	{
		return { r * (float)cos(theta), r * (float)sin(theta) };
	}
	*/
/*
};

struct point_factory
{
	static point newDecartPoint(float x_, float y_)
	{
		return { x_, y_ };
	}

	static point newPolarPoint(float r, float theta)
	{
		return { r * (float)cos(theta), r * (float)sin(theta) };
	}
};
*/