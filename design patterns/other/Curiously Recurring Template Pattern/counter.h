template <typename T>
struct counter
{
	static int objects_created;
	static int objects_alive;

	counter()
	{
		++objects_created;
		++objects_alive;
	}
	counter(const counter&)
	{
		++objects_created;
		++objects_alive;
	}

	~counter()
	{
		--objects_alive;
	}
};

template <typename T>
int counter<T>::objects_created = 0;

template <typename T>
int counter<T>::objects_alive = 0;


class A : public counter<A>
{
	int a;
public:
	A() = default;
	~A() = default;
};

class B : public counter<B>
{
	double b;
public:
	B() = default;
	~B() = default;
};

struct counter2
{
	static int objects_created;
	static int objects_alive;

	counter2()
	{
		++objects_created;
		++objects_alive;
	}
	counter2(const counter2&)
	{
		++objects_created;
		++objects_alive;
	}

	~counter2()
	{
		--objects_alive;
	}
};
int counter2::objects_created = 0;
int counter2::objects_alive = 0;
/*
class A : public counter2
{
	int a;
public:
	A() = default;
	~A() = default;
};

class B : public counter2
{
	double b;
public:
	B() = default;
	~B() = default;
};
*/