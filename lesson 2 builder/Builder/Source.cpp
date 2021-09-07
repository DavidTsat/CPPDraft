#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <memory>

#include "builder.h"

struct HtmlBuilder;

struct HtmlElement {
	std::string name;
	std::string text;
	std::vector<HtmlElement> elements;
	
	friend struct HtmlBuilder;

	std::string str(int indent = 0) const {
		std::string str;

		str.append(name);
		str.append(text);

		for (const HtmlElement& el : elements) {
			str.append(el.name);
			str.append(el.text);
			
			std::string end_token;

			std::string::const_iterator b = std::find(el.name.begin(), el.name.end(), '<');
			end_token.append(el.name.begin(), ++b);
			end_token.append("/");
			end_token.append(b, el.name.end());

			str.append(end_token);
		}

		std::string end_token;

		std::string::const_iterator b = std::find(name.begin(), name.end(), '<');
		end_token.append(++name.begin(), ++b);
		end_token.append("/");
		end_token.append(b, name.end());

		str.append(end_token);
		
		return str;
	}

	static std::unique_ptr<HtmlBuilder> build(const std::string& root_name) {
		return std::make_unique<HtmlBuilder>(root_name);
	}


	static HtmlBuilder build_(const std::string& root_name);
	
private:	
	HtmlElement() {}
	HtmlElement(const std::string& name_, const std::string& text_) : name(name_), text(text_) {}
};

struct HtmlBuilder {
	HtmlElement root;

	HtmlBuilder(const std::string& root_name) { root.name = root_name; }

	void add_child(const std::string& child_name, const std::string& child_text) {
		HtmlElement e(child_name, child_text);
		root.elements.emplace_back(e);
	}
	
	operator HtmlElement() const {
		return root;
	}

	HtmlBuilder* add_child_(const std::string& child_name, const std::string& child_text) {
		HtmlElement e(child_name, child_text);
		root.elements.emplace_back(e);
		return this;
	}

	HtmlBuilder add_child2(const std::string& child_name, const std::string& child_text) {
		HtmlElement e(child_name, child_text);
		root.elements.emplace_back(e);
		return *this;
	}
	std::string str() { return root.str(); }
};


HtmlBuilder HtmlElement::build_(const std::string& root_name) {

	return HtmlBuilder (root_name);
}

int main() {
	Person p = Person::create().lives().at("123 London Road").with_postcode("SW 1GB").in("London").works().at("PragmaSoft").as_a("Consultant").earning(10e6);

	p.pretty_print();

	/*
	// 1
	std::string words[] = { "hello", "world" };
	std::ostringstream oss;
	oss << " <ul> ";
	for (auto w : words) {
		oss << " <li> " << w << " </li> ";
	}
	oss << "</ul>";
	std::cout << " 1 " << oss.str() << std::endl;
	
	/*
	// 2
	HtmlElement list(" <ul> ", "");
	for (auto w : words) {
		list.elements.emplace_back(HtmlElement(" <li> ", w));
	}
	
	std::cout << " 2 " << list.str() << std::endl;
	*/
	/*

	// 3
	HtmlBuilder builder(" <ul> ");
	for (auto w : words) {
		builder.add_child(" <li> ", w);
	}

	std::cout << " 3 " << builder.str() << std::endl;
	
	// 4
	HtmlBuilder builder_(" <ul> ");
	builder_.add_child_(" <li> ", "hello")->
		add_child_(" <li> ", "world");

	std::cout << " 4 " << builder_.str() << std::endl;

	// 5
	std::unique_ptr<HtmlBuilder> b = HtmlElement::build(" <ul> ");
	b->add_child_(" <li> ", "hello")->
		add_child_(" <li> ", "world");

	std::cout << " 5 " << b->str() << std::endl;

	
	// 6
	HtmlElement bb = HtmlElement::build_(" <ul> ").add_child2(" <li> ", "hello").add_child2(" <li> ", "world");

	std::cout << " 6 " << bb.str() << std::endl;
	*/
	return 0;
}