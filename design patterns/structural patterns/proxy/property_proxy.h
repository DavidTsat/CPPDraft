#pragma once

template <typename T>
struct property
{
	T value;

	property(const T initial_value)
	{
		*this = initial_value;
	}
	operator T()
	{
		// perform some getter action
		return value;
	}
	T operator=(const T new_value)
	{
		// perform some setter action
		return value = new_value;
	}
};