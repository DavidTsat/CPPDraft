#pragma once
#include <string> 
#include <iostream>

using namespace std;

struct image
{
	virtual void draw() = 0;
};

struct bitmap : image
{
	string fn;

	bitmap(const string& filename) : fn(filename)
	{
		cout << "loading image: " << filename << endl;
	}
	void draw() override
	{
		cout << "Drawing image " << fn << endl;
	}
};

// virtual proxy
struct lazy_bitmap : image
{
	string fn;
	bitmap* bmp{ nullptr };

	lazy_bitmap(const string& filename)
		: fn(filename) {}
	~lazy_bitmap() { delete bmp; }
	void draw() override
	{
		if (!bmp)
			bmp = new bitmap(fn);
		bmp->draw();
	}
};