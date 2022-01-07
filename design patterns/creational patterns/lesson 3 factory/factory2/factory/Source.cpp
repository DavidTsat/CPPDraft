#include "factory.h"
#include <memory>
using namespace std;

int main()
{
	//point p = point_factory::newDecartPoint(7.4, 5.2);

	unique_ptr<point> p = point::pf.newDecartPoint(7.4, 5.2);
	return 0;
}