#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>
#include <thread>
#include <future>
#include <cassert>


template <typename It, typename T>
It dfind(It begin, It end, T t) {

    while (begin != end) {
        if (*begin++ == t) {
            return --begin;
        }
    }
    return end;
}

template <typename It, typename T>
It pdfind(It begin, It end, T t, unsigned int n = std::thread::hardware_concurrency()) {

    std::vector<std::future<It>> r;

    for (; begin < end; begin += n) {
        r.push_back(std::async(dfind<It, T>, begin, begin + n, t));
    }

    for (std::future<It>& f : r) {
        auto p = f.get();
        if (p != end && *p == t) {
            return p;
        }
    }
    return end;
}

template <typename Pred, typename Record>
Record* find_rec(std::vector<Record>& vr, int first, int last, Pred pr) {
	typename std::vector<Record>::iterator p = std::find_if(vr.begin() + first, vr.begin() + last, pr);
	if (p == vr.begin() + last) {
		return nullptr;
	}
	return &*p;
}

template <typename Pred, typename Record>
Record* pfind(std::vector<Record>& vr, Pred pr, unsigned int grain = std::thread::hardware_concurrency()) {
	assert(vr.size() % grain == 0);
	std::vector<std::future<Record*>> res;

	for (int i = 0; i != vr.size(); i += grain) {
		res.push_back(std::async(find_rec<Pred, Record>, std::ref(vr), i, i + grain, pr));
	}

	for (int i = 0; i != res.size(); ++i) {
		if (auto p = res[i].get()) {
			return p;
		}
	}
    return nullptr;
}


