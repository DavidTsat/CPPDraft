#pragma once
#include <iterator>
#include <algorithm>
#include <vector>

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

	template <typename It>
	It partition(It p, It r) {
		typedef typename std::iterator_traits<It>::value_type value_type;
		const It start = p;
		value_type x = *r;
		bool i_changed = false;

		It i{};
		for (It j = p; j <= r - 1; ++j) {
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

	template <typename It>
	void _quick_sort_(It p, It r) {
		if (std::distance(p, r) > 0) {
			It q = partition(p, r);
			if (q != p) {
				_quick_sort_(p, q - 1);
			}
			_quick_sort_(q + 1, r);
		}
	}

	template <typename It>
	void quick_sort(It p, It r) {
		_quick_sort_(p, --r);
	}
}