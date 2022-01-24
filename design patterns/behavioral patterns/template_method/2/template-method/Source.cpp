#include <iostream>
using namespace std;


template <typename T>
class abstract_base // e.g. game, viewer, etc.
{
protected:
	using result_type = T;

	virtual void do_prepare() { cout << "abstract_base prepare\n"; }
	virtual result_type do_get_initial_result() = 0;
	virtual void do_preprocess_initial_result(result_type&) = 0;
	virtual bool do_get_final_result(result_type&) = 0;
	virtual void do_clean_up() { cout << "abstract_base clean-up\n"; }
public:
	result_type an_algorithm()
	{
		do_prepare();
		result_type r = do_get_initial_result();
		do_preprocess_initial_result(r);
		bool b = do_get_final_result(r);
		do_clean_up();

		if (!b)
		{
			throw std::runtime_error("error!...");
		}
		
		return r;
	}
};

template <typename T>
class concrete_class : public abstract_base<T>
{
	using result_type = T;

	bool check_result(const result_type& r)
	{
		// some logic
		return true;
	}

	result_type do_get_initial_result() override
	{
		// some logic
		cout << "concrete_class::get_initial_result\n";
		return result_type();
	}
	void do_preprocess_initial_result(result_type& r)
	{
		// some logic
		cout << "concrete_class::preprocess_initial_result\n";
	}
	bool do_get_final_result(result_type& r)
	{
		// some logic
		cout << "concrete_class::get_final_result\n";
		return check_result(r);
	}
	void do_clean_up() override
	{
		// some logic
		cout << "concrete_class::clean_up\n";
	}
};

int main()
{
	concrete_class<int> c;
	c.an_algorithm();

	return 0;
}