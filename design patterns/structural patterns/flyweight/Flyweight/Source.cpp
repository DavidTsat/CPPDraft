#include "conceptual_flyweight.h"
#include <map>
#include <functional>
#include <memory>

class police_database {
	std::unique_ptr<flyweight_factory> factory;

	std::function<bool(const car::unique_data&, const car::unique_data&)> key_comp = [](const car::unique_data& l, const car::unique_data& r) { return l.owner + l.plates < r.owner + r.plates; }; // here we could optimise a bit more by excluding + operation
	std::map<const car::unique_data, std::shared_ptr<flyweight>, decltype(key_comp)> cars;
public:
	police_database(std::initializer_list<car> cars_) : factory(std::make_unique<flyweight_factory>()), cars(key_comp)  {
		for (const car& c : cars_) {
			cars[c.u] = factory->add_flyweight(c.s);
		}
	}
	void add_car_to_police_database(const car& c) {
		cars[c.u] = factory->add_flyweight(c.s);
	}
	void operation() const {
		for (const auto& car_data : cars) {
			car_data.second->operation(car_data.first);
		}
	}
	void list_flyweight() const {
		factory->list_flyweights();
	}
};

int main() {
	police_database p({
		car{ "James Doe",			"CL234IR",	"Chevrolet",	  "Camaro2018", "pink"  },
		car{ "Megan Russel",		"CK148PQ",	"Mercedes Benz",  "C300",		"black" },
		car{ "Cynthia Fritz",		"QR008UQ",	"Mercedes Benz",  "C500",		"red"   },
		car{ "Kristin Fitzgerald",  "RT789IU",	"Mercedes Benz",  "C400",		"red"   },
		car{ "Robert Jarvis",		"OP788YU",	"BMW",			  "M5",			"red"   }, // same
		car{ "Kelly Barber",		"TR045ER",	"BMW",			  "X6",			"white" },
		car{ "Erin Moore",			"ET778TR",	"BMW",			  "M5",			"red"   }, // same
		car{ "Grant Barnes",		"TT785TE",	"BMW",			  "X1",			"red"   }
		});

	p.list_flyweight();
	p.add_car_to_police_database({ "Kristin Molina",  "DY458UJ",  "BMW", "M5", "red"   }); // same
	p.add_car_to_police_database({ "Alicia Stafford", "CU785YT",  "BMW", "X1", "black" }); 
	p.list_flyweight();
	std::cout << std::endl;
	p.operation();

	return 0;
}