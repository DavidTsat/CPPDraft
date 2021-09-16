#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "btree.h"

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