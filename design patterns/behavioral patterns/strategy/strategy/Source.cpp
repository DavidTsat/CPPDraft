#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include "strategy.h"

using namespace std;

enum OutputFormat
{
	html, markdown
};

struct ListStrategy
{
	virtual void start(ostringstream& oss) {}
	virtual void add_list_item(ostringstream& oss, const string& item) {}
	virtual void end(ostringstream& oss) {}
};

struct HtmlListStrategy : ListStrategy
{
	void start(ostringstream& oss) override
	{
		oss << "<ul>\n";
	}

	void end(ostringstream& oss) override
	{
		oss << "</ul>\n";
	}

	void add_list_item(ostringstream& oss, const string& item) override
	{
		oss << "<li>" << item << "</li>\n";
	}
};

struct MarkdownListStrategy : ListStrategy
{
	void add_list_item(ostringstream& oss, const string& item) override
	{
		oss << " * " << item << endl;
	}
};

class TextProcessor
{
	ostringstream oss;
	unique_ptr<ListStrategy> list_strategy;
public:
	void set_output_format(OutputFormat of)
	{
		switch (of)
		{
		case OutputFormat::markdown:
			list_strategy = make_unique<MarkdownListStrategy>();
			break;
		case OutputFormat::html:
			list_strategy = make_unique<HtmlListStrategy>();
			break;
		}
	}
	
	void append_list(const vector<string>& v)
	{
		list_strategy->start(oss);
		for (const auto& item : v)
		{
			list_strategy->add_list_item(oss, item);
		}
		list_strategy->end(oss);
	}

	string str() const
	{
		return oss.str();
	}
	
	void clear()
	{
		oss.str("");
		oss.clear();
	}
};

int main()
{
	vector<string> v({ "a", "e", "c", "b", "d" });

	context c(strategy_type::A);
	c.do_some_business_logic(v);
	c.set_strategy(strategy_type::B);
	c.do_some_business_logic(v);

	/*
	TextProcessor tp;
	tp.set_output_format(OutputFormat::markdown);
	tp.append_list({ "foo", "bar", "baz" });
	
	cout << tp.str() << endl;

	tp.clear();
	tp.set_output_format(OutputFormat::html);
	tp.append_list({ "foo", "bar", "baz" });
	cout << tp.str() << endl;
	*/



	return 0;
}