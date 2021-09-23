#pragma once
#include <cmath>
#include <memory>
#include <algorithm>
#include <map>
#include <functional>

/*
1. 
struct Point {
	float x, y;
protected:
	Point (const float x_, const float y_) : x(x_), y(y_) {}
public:
	static Point NewCartesian(float x, float y) {
		return Point(x, y);
	}
	static Point NewPolar(float r, float theta) {
		return Point(r* std::cos(theta), r* std::sin(theta));
	}
};
*/

/*
3.
struct Point {
	float x, y;
	friend class PointFactory;
	Point(const float x_, const float y_) : x(x_), y(y_) {}
public:
	static Point NewCartesian(float x, float y) {
		return Point(x, y);
	}
	static Point NewPolar(float r, float theta) {
		return Point(r * std::cos(theta), r * std::sin(theta));
	}
};

struct PointFactory {
	static Point NewCartesian(float x, float y) {
		return Point(x, y);
	}
	static Point NewPolar(float r, float theta) {
		return Point(r * std::cos(theta), r * std::sin(theta));
	}
};
*/

struct Point {
	float x, y;
private:
	Point(float x_, float y_) : x(x_), y(y_) {}

	struct PointFactory {
	private:
		PointFactory() {}
	public:
		static Point NewCartesian(float x, float y) {
			return Point(x, y);
		}
		static Point NewPolar(float r, float theta) {
			return Point(r * std::cos(theta), r * std::sin(theta));
		}
	};
public:
	static PointFactory Factory;
};

struct HotDrink {
	virtual void prepare(int volume) = 0;
	virtual void c() = 0;
};

struct Tea : HotDrink {
	void prepare(int volume) override {
		std::cout << "HotDrink::Tea" << volume << std::endl;
	}
	void c() override {
		std::cout << "CT" << std::endl;
	}
};

struct Coffee : HotDrink {
	void prepare(int volume) override {
		std::cout << "HotDrink::Coffee" << volume << std::endl;
	}
	void c() override {
		std::cout << "CC" << std::endl;
	}
};

struct HotDrinkFactory {
	virtual std::unique_ptr<HotDrink> make() const = 0;
};

struct CoffeeFactory : HotDrinkFactory {
	std::unique_ptr<HotDrink> make() const override {
		return std::make_unique<Coffee>();
	}
};

struct TeaFactory : HotDrinkFactory {
	std::unique_ptr<HotDrink> make() const override {
		return std::make_unique<Tea>();
	}
};

class DrinkFactory {
	std::map<std::string, std::unique_ptr<HotDrinkFactory>> hot_factories;
public:
	DrinkFactory() {
		hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
		hot_factories["tea"] = std::make_unique<TeaFactory>();
	}

	std::unique_ptr<HotDrink> make_drink(const std::string& name) {
		std::unique_ptr<HotDrink> drink = hot_factories[name]->make();
		drink->prepare(200);
		return drink;
	}
};

class DrinkWithVolumeFactory {
	std::map<std::string, std::function<std::unique_ptr<HotDrink>()>> factories;
public:
	DrinkWithVolumeFactory() {
		factories["tea"] = [] {
			std::unique_ptr<Tea> tea = std::make_unique<Tea>();
			tea->prepare(200);
			return tea;
		};

		factories["coffee"] = [] {
			std::unique_ptr<Coffee> coffee = std::make_unique<Coffee>();
			coffee->prepare(200);
			return coffee;
		};
	}

	std::unique_ptr<HotDrink> make_drink(const std::string& name) {
		return factories[name]();
	}

};