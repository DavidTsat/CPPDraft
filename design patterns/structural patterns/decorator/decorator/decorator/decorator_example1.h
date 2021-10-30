#pragma once
#include <string>

struct shape {
	virtual std::string str() const = 0;
};

struct shape_decorator : shape {
	shape* s;
	shape_decorator(shape* s_) : s(s_) {}
	
	std::string str() const override {
		return s->str();
	}
};

struct circle : shape {
	float radius;

	explicit circle(const float r) : radius(r) {}
	void resize(float f) { radius *= f; }

	std::string str() const override {
		return "A circle of radius " + std::to_string(radius);
	}
};

struct square : shape {
	float length;

	explicit square(const float l) : length(l) {}
	void resize(float f) { length *= f; }

	std::string str() const override {
		return "A square of length " + std::to_string(length);
	}
};

struct colored_shape : shape_decorator {
	std::string color;

	colored_shape(shape* s_, const std::string& c) : shape_decorator(s_), color(c) {}
	std::string str() const override {
		return s->str() + " colored_shape " + "with color" + color;
	}
};

struct transparent_shape : shape_decorator {
	uint8_t t;

	transparent_shape(shape* s_, const uint8_t t_) : shape_decorator(s_), t(t_) {}
	std::string str() const override {
		return s->str() + " transparent_shape " + "with transparensy" + std::to_string(t);
	}
};