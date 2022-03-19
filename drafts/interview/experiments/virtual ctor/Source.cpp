#include <iostream>
#include <string>
using namespace std;


class shape
{
protected:
	string name;
public:
	virtual void draw() const = 0;
	virtual void resize(int factor) = 0;
	virtual shape* clone() = 0;
	virtual shape* create() = 0;
	virtual ~shape() {}
	string get_name() const { return name; }
};

class circle : public shape
{
	char c = 'k';
	string ss = "circle";

	circle(const circle& cc) { *this = cc; };
public:
	circle(string n) { shape::name = n; }
	
	circle* clone() override
	{
		return new circle(*this);
	}

	circle* create() override
	{
		return new circle("c");
	}

	void draw() const override
	{

	}
	void resize(int factor) override
	{

	}
};

class square : public shape
{
	int x;
	const char* cp = "CCPCPPCPC";
	square(const square& cc) { *this = cc; };
public:
	square(string n) { shape::name = n; }
	square* clone() override
	{
		return new square(*this);
	}
	square* create() override
	{
		return new square("s");
	}
	void draw() const override
	{

	}
	void resize(int factor) override
	{

	}
	void rotate(int angle)
	{
		x = angle+5;
		cout << "rotate: " << cp << x <<endl;
	}
};

void f(shape* s)
{

	shape* s1 = s->clone();

	dynamic_cast<square*>(s1)->rotate(5);
	cout << s->get_name() << endl;
}

int main()
{
	shape* s1 = new circle("circle 1");
	shape* s2 = new square("square 1");
	//f(s1);
	f(s2);

	//circle cc(circle("bg"));
	return 0;
}
