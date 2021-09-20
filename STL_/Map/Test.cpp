#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include <boost/random.hpp>
#include <map>
#include <vector>
#include <algorithm>
#include "btree.h"
#include "rbtree.h"

std::vector<std::pair<int, int>> get_random_pairs(int sz = 1000) {
	std::vector<std::pair<int, int>> random_pairs;

	boost::random::mt19937 rng;
	boost::random::uniform_int_distribution<> rand_dist(1, 100000);

	for (int i = 0; i < sz; ++i) {
		int rk = rand_dist(rng);
		int rv = rand_dist(rng);
		if (std::find_if(random_pairs.begin(), random_pairs.end(), [rk](const std::pair<int, int>& p) {return p.first == rk; }) == random_pairs.end()) {
			random_pairs.push_back(std::make_pair(rk, rv));
		}
	}
	return random_pairs;
}



// throw exception if same key is given twice
BOOST_AUTO_TEST_CASE(myTestCase1)
{
	try {
		DSTL::btree<std::string, int> b({ {"David", 7}, {"Armen", 0}, {"Yuri", 4}, {"Narek", 5}, {"Arman", 9}, {"Hayk", 14}, {"Sergey", 8},  { "Arman", 99 } });
		BOOST_CHECK(false);
	}
	catch (const DSTL::repeated_key_exception& e) {
		e.what();
		BOOST_CHECK(true);
	}
}

// checking key_not_found_exception exception
BOOST_AUTO_TEST_CASE(myTestCase2)
{
	DSTL::btree<int, int> b;
	try {
		b.insert(4);
		b.insert(7);
		auto c = b[5];
		BOOST_CHECK(false);
	}
	catch (const DSTL::key_not_found_exception& e) {
		e.what();
		BOOST_CHECK(true);
	}
}

// checking subscript operator
BOOST_AUTO_TEST_CASE(myTestCase3)
{
	try {
		DSTL::btree<std::string, int> b({ {"David", 7}, {"Armen", 0}, {"Yuri", 4}, {"Narek", 5}, {"Arman", 9}, {"Hayk", 14}, {"Sergey", 8}});
		std::pair<std::string, int> p = b["David"];
		BOOST_CHECK(p.second == 7);
	}
	catch (const DSTL::repeated_key_exception& e) {
		e.what();
		BOOST_CHECK(false);
	}
}

// test forward iterator
BOOST_AUTO_TEST_CASE(myTestCase4)
{
	DSTL::btree<int, int> bdstl;
	std::map<int, int> bstd;
	std::vector<std::pair<int, int>> random_pairs = get_random_pairs();

	for (const std::pair<int, int>& p : random_pairs) {
		bdstl.insert(p);
		bstd.insert(p);
	}

	DSTL::btree<int, int>::const_iterator itb = bdstl.begin();
	for (std::map<int, int>::const_iterator its = bstd.begin(); its != bstd.end() && itb != bdstl.end(); ++its, ++itb) {
		BOOST_CHECK(itb->first == its->first);
		BOOST_CHECK(itb->second == its->second);
		//	std::cout << itb->first << ' ' << itb->first << ' ' << its->second << ' ' << itb->second;
		//	std::cout << std::endl;
	}
}

// test changing value with iterator
BOOST_AUTO_TEST_CASE(myTestCase5)
{
	int i = 0;
	DSTL::btree<int, int> bdstl;
	std::map<int, int> bstd;
	boost::random::mt19937 rng;

	const std::vector<std::pair<int, int>> random_pairs = get_random_pairs();
	boost::random::uniform_int_distribution<> rand_dist(1, 1000);

	for (const std::pair<int, int>& p : random_pairs) {
		bdstl.insert(p);
		bstd.insert(p);
	}

	std::cout << "btree.size: " << bdstl.get_size() << " btree.height: " << bdstl.get_height();
	std::cout << "std::map.size: " << bstd.size();
	std::cout << std::endl;

	DSTL::btree<int, int>::iterator itb = bdstl.begin();
	for (std::map<int, int>::iterator its = bstd.begin(); ++i != 100; ++its, ++itb) {
		int rv = rand_dist(rng);

		itb->second = rv;
		its->second = rv;
	}
	
	DSTL::btree<int, int>::const_iterator itbb = bdstl.begin();
	for (std::map<int, int>::const_iterator its = bstd.begin(); its != bstd.end() && itbb != bdstl.end(); ++its, ++itbb) {
		BOOST_CHECK(itbb->first == its->first);
		BOOST_CHECK(itbb->second == its->second);
	}
}

// test checking  delete
BOOST_AUTO_TEST_CASE(myTestCase6)
{
	int i = 0;
	DSTL::btree<int, int> bdstl;
	std::map<int, int> bstd;
	boost::random::mt19937 rng;
	std::vector<int> rand_keys;

	const std::vector<std::pair<int, int>> random_pairs = get_random_pairs();
	boost::random::uniform_int_distribution<> rand_dist(0, random_pairs.size()-1);

	for (const std::pair<int, int>& p : random_pairs) {
		bdstl.insert(p);
		bstd.insert(p);
	}

	for (int i = 0; i < 100; ++i) {
		int rand_idx = rand_dist(rng);
		int rand_key = random_pairs[rand_idx].first;
		if (std::find(rand_keys.begin(), rand_keys.end(), rand_key) == rand_keys.end()) {
			rand_keys.push_back(rand_key);
		}
	}
	for (int rand_key : rand_keys) {
		int c = bstd.erase(rand_key);
		bdstl.delete_entry(rand_key);
	}

	DSTL::btree<int, int>::const_iterator itbb = bdstl.begin();
	for (std::map<int, int>::const_iterator its = bstd.begin(); its != bstd.end() && itbb != bdstl.end(); ++its, ++itbb) {
		BOOST_CHECK(itbb->first == its->first);
		BOOST_CHECK(itbb->second == its->second);
	}
}

/*
rbtree tests
*/

// throw exception if same key is given twice
BOOST_AUTO_TEST_CASE(myTestCase7)
{
	try {
		DSTL::rbtree<std::string, int> b({ {"David", 7}, {"Armen", 0}, {"Yuri", 4}, {"Narek", 5}, {"Arman", 9}, {"Hayk", 14}, {"Sergey", 8},  { "Arman", 99 } });
		BOOST_CHECK(false);
	}
	catch (const DSTL::repeated_key_exception& e) {
		e.what();
		BOOST_CHECK(true);
	}
}


// checking key_not_found_exception exception
BOOST_AUTO_TEST_CASE(myTestCase8)
{
	DSTL::rbtree<int, int> b;
	try {
		b.insert(4);
		b.insert(7);
		auto c = b[5];
		BOOST_CHECK(false);
	}
	catch (const DSTL::key_not_found_exception& e) {
		e.what();
		BOOST_CHECK(true);
	}
}


// checking subscript operator
BOOST_AUTO_TEST_CASE(myTestCase9)
{
	try {
		DSTL::rbtree<std::string, int> b({ {"David", 7}, {"Armen", 0}, {"Yuri", 4}, {"Narek", 5}, {"Arman", 9}, {"Hayk", 14}, {"Sergey", 8} });
		std::pair<std::string, int> p = b["David"];
		BOOST_CHECK(p.second == 7);
	}
	catch (const DSTL::repeated_key_exception& e) {
		e.what();
		BOOST_CHECK(false);
	}
}


// test forward iterator rbtree
BOOST_AUTO_TEST_CASE(myTestCase10)
{
	DSTL::rbtree<int, int> bdstl;
	std::map<int, int> bstd;
	std::vector<std::pair<int, int>> random_pairs = get_random_pairs();

	for (const std::pair<int, int>& p : random_pairs) {
		bdstl.insert(p);
		bstd.insert(p);
	}

	DSTL::rbtree<int, int>::const_iterator itb = bdstl.begin();
	for (std::map<int, int>::const_iterator its = bstd.begin(); its != bstd.end() && itb != bdstl.end(); ++its, ++itb) {
		BOOST_CHECK(itb->first == its->first);
		BOOST_CHECK(itb->second == its->second);
		//	std::cout << itb->first << ' ' << itb->first << ' ' << its->second << ' ' << itb->second;
		//	std::cout << std::endl;
	}
}

// test changing value with iterator
BOOST_AUTO_TEST_CASE(myTestCase11)
{
	int i = 0;
	DSTL::rbtree<int, int> bdstl;
	std::map<int, int> bstd;
	boost::random::mt19937 rng;

	const std::vector<std::pair<int, int>> random_pairs = get_random_pairs();
	boost::random::uniform_int_distribution<> rand_dist(1, 1000);

	for (const std::pair<int, int>& p : random_pairs) {
		bdstl.insert(p);
		bstd.insert(p);
	}

	DSTL::rbtree<int, int>::iterator itb = bdstl.begin();
	for (std::map<int, int>::iterator its = bstd.begin(); ++i != 100; ++its, ++itb) {
		int rv = rand_dist(rng);

		itb->second = rv;
		its->second = rv;
	}

	DSTL::rbtree<int, int>::const_iterator itbb = bdstl.begin();
	for (std::map<int, int>::const_iterator its = bstd.begin(); its != bstd.end() && itbb != bdstl.end(); ++its, ++itbb) {
		BOOST_CHECK(itbb->first == its->first);
		BOOST_CHECK(itbb->second == its->second);
	}
}

// test compare heights of btree and rbtree
BOOST_AUTO_TEST_CASE(myTestCase12)
{
	DSTL::btree<int, int> btree_;
	DSTL::rbtree<int, int> rbtree_;

	const std::vector<std::pair<int, int>> random_pairs = get_random_pairs(10000);

	for (const std::pair<int, int>& p : random_pairs) {
		btree_.insert(p);
		rbtree_.insert(p);
	}

	std::cout << "btree size: " << btree_.get_size() << " btree height: " << btree_.get_height() << std::endl;
	std::cout << "rbtree size: " << rbtree_.get_size() << " rbtree height: " << rbtree_.get_height() << std::endl;

	BOOST_CHECK(btree_.get_size() == rbtree_.get_size());
	BOOST_CHECK(btree_.get_height() >= rbtree_.get_height());
}