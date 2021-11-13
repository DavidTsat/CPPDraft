#pragma once
#include <iostream>
#include <string>
#include <ostream>
#include <set>
#include <memory>

class car {
	struct unique_data {
		std::string owner, plates;
	};
	struct shared_data { // flyweight will work on shared data
		std::string brand, model, color;
	};

	unique_data u;
	shared_data s;

	friend class flyweight;
	friend class flyweight_factory;
	friend class police_database;
public:
	car(std::string&& owner, std::string&& plates, std::string&& brand, std::string&& model, std::string&& color) {
		u.owner  = std::move(owner);
		u.plates = std::move(plates);
		s.brand  = std::move(brand);
		s.model  = std::move(model);
		s.color  = std::move(color);
	}

	friend std::ostream& operator<<(std::ostream& os, const unique_data& us) {
		return os << "[ " << us.owner << " , " << us.plates << " ]";
	}
	friend std::ostream& operator<<(std::ostream& os, const shared_data& ss) {
		return os << "[ " << ss.brand << " , " << ss.model << " , " << ss.color << " ]";
	}
	friend bool operator==(const shared_data& l, const shared_data& r) {
		return l.brand == r.brand && l.color == r.color && l.model == r.model;
	}
	// other methods
};

class flyweight {
	std::shared_ptr<car::shared_data> s; // flyweight keeps a reference on the shared data
	friend class flyweight_factory;
public:
	flyweight() = default;
	flyweight(const car::shared_data* s_) : s(std::make_shared<car::shared_data>(*s_)) {}
	//flyweight(const flyweight& r) : s(std::make_shared<car::shared_data>(*r.s)) {}
	flyweight(const flyweight& r) = delete;

	void operation(const car::unique_data& unique_part) const {
		std::cout << "Flyweight: Displaying shared (" << *s << ") and unique (" << unique_part << ") state.\n";
	}
};

class flyweight_factory {
	std::set<std::shared_ptr<flyweight>> flyweights_;

	std::shared_ptr<flyweight> add_flyweight_element(const car::shared_data& new_elem) {
		for (const std::shared_ptr<flyweight>& existing_elem : flyweights_) {
			if (*(existing_elem->s) == new_elem) {
				return existing_elem;
			}
		}
		return *flyweights_.insert(std::make_shared<flyweight>(&new_elem)).first;
	}
public:
	flyweight_factory() = default;

	flyweight_factory(std::initializer_list<car::shared_data> shared_states) {
		for (const car::shared_data& ss : shared_states) {
			add_flyweight_element(ss);
		}
	}
	std::shared_ptr<flyweight> add_flyweight(const car::shared_data& new_elem) { // the same as get_flyweight
		return add_flyweight_element(new_elem);
	}
	void list_flyweights() const {
		size_t count = this->flyweights_.size();
		std::cout << "\nFlyweightFactory: I have " << count << " flyweights:\n";
		for (const std::shared_ptr<flyweight>& f : flyweights_) {
			std::cout << *f->s << "\n";
		}
	}
};