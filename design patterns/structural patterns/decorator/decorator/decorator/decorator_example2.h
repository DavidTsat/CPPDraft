#pragma once
#include <string>
#include <iostream>

class VisualComponent {
protected:
	int length;
public:
	VisualComponent(int l) : length(l) { }
	virtual void draw() = 0;
	virtual void resize(int) = 0;
};

class TextView : public VisualComponent {
	std::string color;
public:
	TextView(int l, std::string c) : VisualComponent(l), color(c) {}
	void draw() override {
		std::cout << "TextView " << "draw\n";
	}
	void resize(int c) override {
		length *= c;
	}
};

class button : public VisualComponent {
public:
	enum shape {circle, rectangle};

	button(int r, shape s_, std::string c) : VisualComponent(r), s(s_), color(c) {}
	void draw() override {
		std::cout << "button " << (s == circle ? "circle" : "rectangle") << "draw\n";
	}
	void resize(int c) override {
		resize(c);
	}
private:
	shape s;
	std::string color;
};

class Decorator : public VisualComponent {
	VisualComponent* v;
public:
	Decorator(int l, VisualComponent* v_) : VisualComponent(l), v(v_) {}
	void draw() override{
		v->draw();
	}
	void resize(int c) override {
		v->resize(c);
	}
};

class BorderDecorator : public Decorator {
	void drawBorder() {
		std::cout << "BorderDecorator: drawBorder\n";
	}
public:
	BorderDecorator(int b, VisualComponent* v_) : Decorator(b, v_) {}
	void draw() override {
		Decorator::draw();
		drawBorder();
	}
	void resize(int c) override {
		//..
		Decorator::resize(c);
	}
};

class ScrollDecorator : public Decorator {
	void drawscroll() {
		std::cout << "ScrollDecorator: drawscroll\n";
	}
public:
	ScrollDecorator(int l, VisualComponent* v_) : Decorator(l, v_) {}
	void draw() override {
		Decorator::draw();
		drawscroll();
	}
	void resize(int c) override{
		//..
		Decorator::resize(c);
	}
};

class DropShadowDecorator : public Decorator {
	char c;
	void drawShadow() {
		std::cout << "DropShadowDecorator: drawShadow\n";
	}
public:
	DropShadowDecorator(int l, VisualComponent* v_, char c_) : Decorator(l, v_), c(c_) {}
	void draw() override {
		Decorator::draw();
		drawShadow();
	}
	void resize(int c) override {
		//..
		Decorator::resize(c);
	}
};