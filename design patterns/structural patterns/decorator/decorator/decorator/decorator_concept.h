#pragma once
#include <string>
#include <memory>

class component {
public:
	~component() {}
	virtual std::string operation() const = 0;
};

class concrete_component : public component {
public:
	std::string operation() const override {
		return "concrete_component";
	}
};

class decorator : public component {
protected:
	component* component_;
public:
	decorator(component* component__) : component_(component__) {}
	std::string operation() const override {
		return component_->operation();
	}
};

class concrete_decorator_a : public decorator {
public:
	concrete_decorator_a(component* component__) : decorator(component__) {}
	std::string operation() const override {
		return "concrete_decorator_a(" + decorator::operation() + ')';
	}
};

class concrete_decorator_b : public decorator {
public:
	concrete_decorator_b(component* component__) : decorator(component__) {}
	std::string operation() const override {
		return "concrete_decorator_b(" + decorator::operation() + ')';
	}
};