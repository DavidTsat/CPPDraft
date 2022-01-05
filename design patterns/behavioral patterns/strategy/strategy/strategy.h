#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class strategy
{
public:
	virtual ~strategy() {}
	virtual string do_algorithm(const vector<string>& data) const = 0;
};

enum class strategy_type
{
	A, B
};

class concrete_strategy_A : public strategy
{
	string do_algorithm(const vector<string>& data) const override
	{
		string result;
		for_each(data.cbegin(), data.cend(), [&result](const string& d) { result += d; });
		sort(result.begin(), result.end());
		return result;
	}
};
 
class concrete_strategy_B : public strategy
{
	string do_algorithm(const vector<string>& data) const override
	{
		string result;
		for_each(data.cbegin(), data.cend(), [&result](const string& d) { result += d; });
		sort(result.begin(), result.end());
		for (int i = 0; i < result.size() / 2; i++)
		{
			swap(result[i], result[result.size() - i - 1]);
		}

		return result;
	}
};

class context
{
	strategy* s;
	void _set_strategy_(strategy_type s_)
	{
		switch (s_)
		{
		case strategy_type::A:
			s = new concrete_strategy_A();
			break;
		case strategy_type::B:
		{
			s = new concrete_strategy_B();
			break;
		}
		}
	}
public:
	context(strategy_type s_) 
	{
		_set_strategy_(s_);
	}

	~context()
	{
		delete s;
	}

	void set_strategy(strategy_type s_)
	{
		delete s;
		_set_strategy_(s_);
	}
	void do_some_business_logic(const vector<string>& v) const
	{
		cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
		string res = s->do_algorithm(v);
		cout << res << "\n";
	}
};

