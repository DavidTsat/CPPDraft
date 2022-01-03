#pragma once
#include <ostream>
#include <sstream>
//(1.0 + (2.0 + 3.0))

using namespace std;

/*
struct expression
{
	virtual void print(ostringstream& oss) = 0;
};

struct double_expression : expression
{
	double value;
	explicit double_expression(const double v) : value(v) {}
	void print(ostringstream& oss) override
	{
		oss << value;
	}
};

struct addition_expression : expression
{
	expression* left, * right;

	addition_expression(expression* l, expression* r) : left(l), right(r) {}
	~addition_expression()
	{
		//delete left; 
		//delete right;
	}
	void print(ostringstream& oss) override
	{
		oss << "("; 
		left->print(oss);
		oss << "+";
		right->print(oss);
		oss << ")";
	}
};
*/

/*
struct expression
{
	virtual ~expression() = default;
};

struct double_expression : expression
{
	double value;
	explicit double_expression(const double v) : value(v) {}
};

struct addition_expression : expression
{
	expression* left, * right;

	addition_expression(expression* l, expression* r) : left(l), right(r) {}
	~addition_expression()
	{
		//delete left; 
		//delete right;
	}
};

struct expression_printer
{
	void print(expression* e, ostringstream& oss)
	{
		if (auto d = dynamic_cast<double_expression*>(e))
			oss << d->value;
		else if (auto d = dynamic_cast<addition_expression*>(e))
		{
			oss << "(";
			print(d->left, oss);
			oss << "+";
			print(d->right, oss);
			oss << ")";
		}
	}
};
*/

struct expression;
struct double_expression;
struct addition_expression;

struct expression_visitor;
struct expression_printer;


struct expression_visitor
{
	virtual void visit(double_expression* e) = 0;
	virtual void visit(addition_expression* e) = 0;
};

struct expression
{
	virtual ~expression() = default;

	virtual void accept(expression_visitor* visitor) = 0;
};


struct double_expression : expression
{
	double value;
	explicit double_expression(const double v) : value(v) {}

	void accept(expression_visitor* visitor) override
	{
		visitor->visit(this);
	}
};

struct addition_expression : expression
{
	expression* left, * right;

	addition_expression(expression* l, expression* r) : left(l), right(r) {}
	~addition_expression()
	{
		//delete left; 
		//delete right;
	}

	void accept(expression_visitor* visitor) override
	{
		visitor->visit(this);
	}
};


struct expression_printer : expression_visitor
{
	ostringstream oss;
	void visit(double_expression* e) override
	{
		oss << e->value;
	}

	void visit(addition_expression* e) override
	{
		oss << "(";
		e->left->accept(this);
		oss << "+";
		e->right->accept(this);
		oss << ")";
	}

	string str() const 
	{
		return oss.str();
	}
};

struct expression_evaluator : expression_visitor
{
	double r = 0;

	void visit(double_expression* e) override
	{
		r = e->value;
	}

	void visit(addition_expression* e) override
	{
		double d = 0;
		e->left->accept(this);
		d += r;

		e->right->accept(this);
		d += r;
		r = d;
	}
};
