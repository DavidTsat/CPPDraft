#pragma once

template <typename derived_class>
class singleton
{
protected:
	static derived_class* p;

	singleton() = default;
	singleton(const singleton&) = default;
	singleton& operator=(const singleton&) = default;
public:

	/*
	singleton() = delete;
	singleton(const singleton&) = delete;
	singleton& operator=(const singleton&) = delete;
	*/
	static derived_class* get_instance()
	{
		if (p == nullptr)
		{
			p = new derived_class;
		}
		return p;
	}
};

template <typename derived_class>
derived_class* singleton<derived_class>::p = nullptr;

class test_singl : public singleton<test_singl>
{
	string s;

	friend class singleton;
	test_singl() = default;
public:
	

	void set_s(string s_)
	{
		s = s_;
	}

	string& get_s()
	{
		return s;
	}
};