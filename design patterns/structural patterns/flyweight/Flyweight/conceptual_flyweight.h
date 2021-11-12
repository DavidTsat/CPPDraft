#pragma once
#include <iostream>
#include <string>
#include <ostream>
#include <unordered_map>

struct car {
	//std::array<std::string, 2> unique_data; // owner, plates;
	//std::array<std::string, 3> shared_data; // brand, model, color, owner, plates;
	struct unique_data {
		std::string owner, plates;
	};
	struct shared_data {
		std::string brand, model, color;
	};

	unique_data u;
	shared_data s;

	car(const unique_data& u_, const shared_data& s_) : u(u_), s(s_) {}
};

struct shared_state {
	car::shared_data s;
	
	shared_state(const car::shared_data& s_) : s(s_) {}
	friend std::ostream& operator<<(std::ostream& os, const shared_state& ss) {
		return os << "[ " << ss.s.brand << " , " << ss.s.model << " , " << ss.s.color << " ]";
	}
};

struct unique_state {
	car::unique_data u;

	unique_state(const car::unique_data& u_) : u(u_) {}
	friend std::ostream& operator<<(std::ostream& os, const unique_state& us) {
		return os << "[ " << us.u.owner << " , " << us.u.plates << " ]";
	}
};

// flyweight keeps a reference on the shared data
class flyweight {
	shared_state* s;
public:
	flyweight(const shared_state* s_) : s(new shared_state(*s_)) {}
	flyweight(const flyweight& r) : s(new shared_state(*r.s)) {}
	~flyweight() {
		delete s;
	}
	void operation(const unique_state& unique_part) const {
		std::cout << "Flyweight: Displaying shared (" << *s << ") and unique (" << unique_part << ") state.\n";
	}
};

class flyweight_factory {
	std::unordered_map<std::string, flyweight> flyweights_;

	std::string get_key(const shared_state& ss) const {
		return ss.s.brand + '_' + ss.s.model + '_' + ss.s.color;
	}
public:
	flyweight_factory(std::initializer_list<shared_state> shared_states) {
		for (const shared_state& ss : shared_states) {
			flyweights_.insert(std::make_pair<std::string, flyweight>(get_key(ss), flyweight(&ss)));
		}
	}

	flyweight get_flyweight(const shared_state& s) {
		std::string key = get_key(s);
		if (flyweights_.find(key) == flyweights_.end()) {
			std::cout << "FlyweightFactory: Can't find a flyweight, creating new one \n";
			flyweights_.insert(std::make_pair(key, flyweight(&s)));
		}
		else {
			std::cout << "FlyweightFactory: Reusing existing flyweight.\n";
		}
		return flyweights_.at(key);
	}

	void list_flyweights() const {
		size_t count = this->flyweights_.size();
		std::cout << "\nFlyweightFactory: I have " << count << " flyweights:\n";
		for (const std::pair<std::string, flyweight>& pair : flyweights_) {
			std::cout << pair.first << "\n";
		}
	}
};

void add_car_to_police_database(flyweight_factory& ff, const car& c) {
	std::cout << "\nClient: Adding a car to database.\n";
	const flyweight& f = ff.get_flyweight(c.s);

	f.operation(c.u);
}