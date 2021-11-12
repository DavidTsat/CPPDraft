#include "conceptual_flyweight.h"

int main() {
	flyweight_factory* factory = new flyweight_factory({ shared_state({"Chevrolet", "Camaro2018", "pink"}), shared_state({"Mercedes Benz", "C300", "black"}),
		shared_state({"Mercedes Benz", "C500", "red"}), shared_state({"BMW", "M5", "red"}), shared_state({"BMW", "X6", "white"}) });

	factory->list_flyweights();

	add_car_to_police_database(*factory, {{ "James Doe", "CL234IR" }, { "BMW", "M5", "red" }});

    add_car_to_police_database(*factory, {{ "James Doe", "CL234IR" }, { "BMW", "X1", "red" }});

    factory->list_flyweights();

	delete factory;
	return 0;
}