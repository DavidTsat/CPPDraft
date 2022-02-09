#pragma once
#include <string>
#include <sstream>
#include <type_traits>

using namespace std;

struct shape
{
	virtual string str() const = 0;
};

struct circle : shape
{
	float radius;
	explicit circle(const float radius_) : radius(radius_) {}
	void resize(float factor) { radius *= factor; }
	string str() const override
	{
		ostringstream oss;
		oss << "A circle of radius " << radius;
		return oss.str();
	}
};

struct square : shape
{
	float size;
	explicit square(const float size_) : size(size_) {}
	void resize(float factor) { size *= factor; }
	void square_func() { cout << "square_func\n"; }
	string str() const override
	{
		ostringstream oss;
		oss << "A square of radius " << size;
		return oss.str();
	}
};

struct colored_shape : shape
{
	shape& s;
	string color;

	colored_shape(shape& s_, const string& c_) : s(s_), color(c_) {}

	string str() const override
	{
		ostringstream oss;
		oss << s.str() << " with color " << color ;
		return oss.str();
	}
};

struct transparent_shape : shape
{
	shape& s;
	uint8_t t;

	transparent_shape(shape& s_, const uint8_t t_) :
		s(s_), t(t_) {}

	string str() const override
	{
		ostringstream oss;
		oss << s.str() << " with transparrency " << t / 255.f * 100.f;
		return oss.str();
	}
};

template <typename T>
struct colored_shape_ : T
{
	string color;

	template <typename... Args>
	colored_shape_(const string& c, Args&& ... args) : color(c), T(std::forward<Args>(args)...)
	{
		static_assert(is_base_of<shape, T>::value, "Template argument must be a Shape");
	}

	string str() const override
	{
		ostringstream oss;
		oss << T::str() << " with color " << color;
		return oss.str();
	}
};

template <typename T>
struct transparent_shape_ : T
{
	uint8_t t;
	
	template <typename... Args>
	transparent_shape_(const uint8_t t_, Args&& ... args) : t(t_), T(std::forward<Args>(args)...)
	{
		static_assert(is_base_of<shape, T>::value, "Template argument must be a Shape");
	}

	string str() const override
	{
		ostringstream oss;
		oss << T::str() << " with transparrency " << t / 255.f * 100.f;
		return oss.str();
	}
};