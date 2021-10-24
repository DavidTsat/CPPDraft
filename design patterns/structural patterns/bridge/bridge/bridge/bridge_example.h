#pragma once
#include <iostream>

struct renderer {
	virtual void render_circle(float x, float y, float radius) = 0;
};

struct vector_renderer : renderer {
	void render_circle(float x, float y, float radius) override {
		std::cout << "vector renderer of radius " << radius << std::endl;
	}
};

struct raster_renderer : renderer {
	void render_circle(float x, float y, float radius) override {
		std::cout << "raster renderer of radius " << radius << std::endl;
	}
};

struct shape {
protected:
	renderer& renderer_;
	shape(renderer& renderer__) : renderer_(renderer__) {}
public:
	virtual void draw() = 0;
	virtual void resize(float factor) = 0;
};

struct circle : shape {
	float x, y, radius;

	circle(renderer& renderer__, float x_, float y_, float radius_) :
		shape(renderer__), x(x_), y(y_), radius(radius_) {}

	void draw() override {
		renderer_.render_circle(x, y, radius);
	}

	void resize(float factor) override {
		radius *= factor;
	}
};