#include "factory.h"
#include "abstract_factory.h"

#include <memory>
using namespace std;

int main()
{
	//point p = point_factory::newDecartPoint(7.4, 5.2);

//	unique_ptr<point> p = point::pf.newDecartPoint(7.4, 5.2);

	drink_factory d = drink_factory::get_instance();

	shared_ptr<hot_drink> c = d.make_drink("coffee");

	c->prepare(245);
	return 0;
}