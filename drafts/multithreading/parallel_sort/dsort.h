#pragma once
#include <iterator>
#include <algorithm>
#include <vector>
#include <list>
#include <thread>
#include <future>
#include <chrono>

namespace DSTL {
	/*
	template <typename T>
	int partition(std::vector<T>& A, int p, int r) {
		T x = A[r];
		bool changed = false;
		int i = p - 1;
		for (int j = p; j <= r - 1; ++j) {
			if (A[j] <= x) {

				++i;
				std::swap(A[i], A[j]);
			}
		}
		std::swap(A[i + 1], A[r]);
		return i + 1;
	}

	template <typename T>
	void _quick_sort_(std::vector<T>& A, int p, int r) {
		//if (std::distance(p, r) > 0) {
		if (p < r) {
			int q = partition(A, p, r);
			_quick_sort_(A, p, q - 1);
			_quick_sort_(A, q + 1, r);
		}
	}

	template <typename T>
	void quick_sort(std::vector<T>& A) {
		_quick_sort_(A, 0, A.size()-1);
	}
	*/

	template <typename RandIt>
	RandIt partition(RandIt p, RandIt r) {
		typedef typename std::iterator_traits<RandIt>::value_type value_type;
		const RandIt start = p;
		value_type x = *r;
		bool i_changed = false;

		RandIt i{};
		for (RandIt j = p; j <= r - 1; ++j) {
			if (*j <= x) {
				if (!i_changed) {
					i_changed = true;
					i = start;
					std::swap(*i, *j);
					continue;
				}
				++i;
				std::swap(*i, *j);
			}
		}

		if (!i_changed) {
			i = start;
			std::swap(*i, *r);
			return i;
		}
		else {
			std::swap(*(i + 1), *r);
		}
		return i + 1;
	}


	template <typename RandIt>
	void _quick_sort_p_(RandIt p, RandIt r) {
		if (std::distance(p, r) > 0) {

			std::thread t_left;

			RandIt q = partition(p, r);
			if (q != p) {
				t_left = std::thread(_quick_sort_p_<RandIt>, p, q - 1);
			}
			_quick_sort_p_(q + 1, r);
			if (t_left.joinable()) {
				t_left.join();
			}
		}
	}

	template <typename RandIt>
	void _quick_sort_(RandIt p, RandIt r) {
		if (std::distance(p, r) > 0) {
			RandIt q = partition(p, r);
			if (q != p) {
				_quick_sort_(p, q - 1);
			}
			_quick_sort_(q + 1, r);
		}
	}

	enum run_policy { sequential, parallel };

	template <typename RandIt>
	void quick_sort(RandIt p, RandIt r, run_policy policy) {
		if (policy == run_policy::parallel) {
			_quick_sort_p_(p, --r);
		}
		else {
			_quick_sort_(p, --r);
		}
	}

	template <typename T>
	std::list<T> sequential_quick_sort(std::list<T> input) {
		if (input.empty()) {
			return input;
		}
		std::list<T> result;
		result.splice(result.begin(), input, input.begin());
		T const& pivot = *result.begin();
		auto divide_point = std::partition(input.begin(), input.end(), [&](T const& t) {return t < pivot; });
		std::list<T> lower_part;
		lower_part.splice(lower_part.end(), input, input.begin(), divide_point);
		auto new_lower(sequential_quick_sort(std::move(lower_part)));
		auto new_higher(sequential_quick_sort(std::move(input)));
		result.splice(result.end(), new_higher);
		result.splice(result.begin(), new_lower);
		return result;
	}

}