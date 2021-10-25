#pragma once
#include <algorithm>
#include <numeric>
#include <array>

/*
class creature {
	int strength, agility, intelligence;
public:
	int get_strength() const {
		return strength;
	}
	void set_strength(int strength_) {
		strength = strength_;
	}

	int get_agility() const {
		return agility;
	}
	void set_agility(int agility_) {
		agility = agility_;
	}

	int get_intelligence() const {
		return intelligence;
	}
	void set_intelligence(int intelligence_) {
		intelligence = intelligence_;
	}

	int sum() const {
		return strength + agility + intelligence;
	}
	double average() const {
		return sum() / 3.0;
	}
	int max() const {
		return std::max(std::max(strength, agility), intelligence);
	}
};
*/

class creature {
	enum Abilities {strength, agility, inteligence, count};
	std::array<int, count> abilities;

	int get_strength() const {
		return abilities[strength];
	}
	int set_strength(int s) {
		abilities[strength] = s;
	}

	int get_agility() const {
		return abilities[agility];
	}
	int set_agility(int a) {
		abilities[agility] = a;
	}

	int get_inteligence() const {
		return abilities[inteligence];
	}
	int set_inteligence(int i) {
		abilities[inteligence] = i;
	}

	int sum() const {
		std::accumulate(abilities.begin(), abilities.end(), 0);
	}
	double average() const {
		return sum() / count;
	}
	int max() const {
		return *std::max_element(abilities.begin(), abilities.end());
	}
};