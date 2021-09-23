#include <boost/di.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "ex1.h"

namespace di = boost::di;

class ctor {
public:
    ctor(int i) : i(i) {}
	int i;
};

struct aggregate {
	double d;
};

class example {
public:
	example(aggregate& a, const ctor& c) {
		assert(87.0 == a.d);
		assert(42 == c.i);
	};
};


int main() {
	/*
	const auto injector = di::make_injector(
	//	di::bind<int>.to(42),
		di::bind<double>.to(87.0)
	);

	injector.create<example>();
	*/
	
	// manual di
	room r = room{};
	std::unique_ptr<speaker> s = std::make_unique<speaker>();
	//attendencees a;
	std::vector<speaker> att_l = { speaker{"David"}, speaker{"Yuri"} };
	attendencees at(att_l);
	


	cppcon_talk_DI talk(14, std::move(r), std::move(s), at);
	

	const auto injector = di::make_injector(
		di::bind<int>.to(15),
		di::bind<attendencees>.to(attendencees({ speaker{ "David" }, speaker{ "Yuri" } }))
	);

	cppcon_talk_DI d = injector.create<cppcon_talk_DI>();

	//auto talkDI = injector.create<A>();
	
	return 0;
}
