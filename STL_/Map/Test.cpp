#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include <boost/random.hpp>
#include <map>
#include <vector>
#include <algorithm>
#include "btree.h"
#include "rbtree.h"
#include <chrono>

std::vector<std::pair<int, int>> get_random_pairs(int sz = 1000) {
	std::vector<std::pair<int, int>> random_pairs;

	boost::random::mt19937 rng(static_cast<unsigned int>(std::time(0)));
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


template <typename It, typename Cmp>
bool check_if_bst(It i, const It end, Cmp cmp) {
	while (i != end) {
		const auto& left_child = i->first;
		if (++i != end) {
			const auto& parent = i->first;
			BOOST_CHECK(cmp(left_child, parent));

			if (++i != end) {
				const auto& right_child = i->first;
				BOOST_CHECK(cmp(parent, right_child));
			}
		}
	}
	return true;
}

// checking subscript operator
BOOST_AUTO_TEST_CASE(myTestCase889)
{
	try {
		DSTL::rbtree<std::string, int> b({ {"David", 7}, {"Armen", 0}, {"Yuri", 4}, {"Narek", 5}, {"Arman", 9}, {"Hayk", 14}, {"Sergey", 8} });
		std::pair<std::string, int> p = b["David"];

		check_if_bst<DSTL::rbtree<std::string, int>::iterator>(b.begin(), b.end(), std::less<std::string>());

		BOOST_CHECK(p.second == 7);
	}
	catch (const DSTL::repeated_key_exception& e) {
		e.what();
		BOOST_CHECK(false);
	}
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
		check_if_bst<DSTL::rbtree<int, int>::iterator>(b.begin(), b.end(), std::less<int>());
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

		check_if_bst<DSTL::rbtree<std::string, int>::iterator>(b.begin(), b.end(), std::less<std::string>());

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


/*
Copy and move tests
*/
// copy constructor test 1
BOOST_AUTO_TEST_CASE(myTestCase13)
{
	DSTL::rbtree<std::string, int> b({ {"Karen", 74}, {"Armenak", 14}, {"Arsen", 454}, {"Artak", 85}, {"Narek", 58}, {"Sergey", 94}, {"Rafael", 145}, {"Alex", 85}, {"Vahe", 45}, {"Kostya", 7778}, {"Danil", 495} });

	std::cout << "b size: " << b.get_size() << " b height: " << b.get_height() << std::endl;
	
	auto b2(b);

	std::cout << "b2 size: " << b2.get_size() << " b2 height: " << b2.get_height() << std::endl;
	BOOST_CHECK(b.get_size() == b2.get_size());


	DSTL::rbtree<std::string, int>::const_iterator it2 = b2.begin();
	for (DSTL::rbtree<std::string, int>::const_iterator it = b.begin(); it != b.end(), it2 != b2.end(); ++it, ++it2) {
	//	std::cout << it->first << " " << it->second << " " << it2->first << " " << it2->second;
	//	std::cout << std::endl;
		BOOST_CHECK(it->first == it2->first);
		BOOST_CHECK(it->second == it2->second);
	}
}

// copy constructor test 2
BOOST_AUTO_TEST_CASE(myTestCase14)
{
	DSTL::rbtree<int, int> b;

	const std::vector<std::pair<int, int>> random_pairs = get_random_pairs();
	boost::random::uniform_int_distribution<> rand_dist(1, 1000);

	for (const std::pair<int, int>& p : random_pairs) {
		b.insert(p);
	}

	std::cout << "b size: " << b.get_size() << " b height: " << b.get_height() << std::endl;

	auto b2(b);

	std::cout << "b2 size: " << b2.get_size() << " b2 height: " << b2.get_height() << std::endl;

	BOOST_CHECK(b.get_size() == b2.get_size());


	DSTL::rbtree<int, int>::const_iterator it2 = b2.begin();
	for (DSTL::rbtree<int, int>::const_iterator it = b.begin(); it != b.end(), it2 != b2.end(); ++it, ++it2) {
		//	std::cout << it->first << " " << it->second << " " << it2->first << " " << it2->second;
		//	std::cout << std::endl;
		BOOST_CHECK(it->first == it2->first);
		BOOST_CHECK(it->second == it2->second);
	}
}

// move constructor test 1
BOOST_AUTO_TEST_CASE(myTestCase15)
{
	DSTL::rbtree<std::string, int> b({ {"Karen", 74}, {"Armenak", 14}, {"Arsen", 454}, {"Artak", 85}, {"Narek", 58}, {"Sergey", 94}, {"Rafael", 145}, {"Alex", 85}, {"Vahe", 45}, {"Kostya", 7778}, {"Danil", 495} });

	auto b2(b);

	auto b3(std::move(b));

	/*
	for (DSTL::rbtree<std::string, int>::const_iterator it = b3.begin(); it != b3.end(); ++it) {
		std::cout << it->first << " " << it->second;
		std::cout << std::endl;
	}
	*/
	DSTL::rbtree<std::string, int>::const_iterator it2 = b2.begin();
	for (DSTL::rbtree<std::string, int>::const_iterator it = b3.begin(); it != b3.end(), it2 != b2.end(); ++it, ++it2) {
	//		std::cout << it->first << " " << it->second << " " << it2->first << " " << it2->second;
	//		std::cout << std::endl;
		BOOST_CHECK(it->first == it2->first);
		BOOST_CHECK(it->second == it2->second);
	}
	
}

// move constructor test 2
BOOST_AUTO_TEST_CASE(myTestCase16)
{
	DSTL::rbtree<int, int> b;

	const std::vector<std::pair<int, int>> random_pairs = get_random_pairs();
	boost::random::uniform_int_distribution<> rand_dist(1, 1000);

	for (const std::pair<int, int>& p : random_pairs) {
		b.insert(p);
	}

	std::cout << "b size: " << b.get_size() << " b height: " << b.get_height() << std::endl;

	auto b3(b);

	auto b2(std::move(b));

	std::cout << "b2 size: " << b2.get_size() << " b2 height: " << b2.get_height() << std::endl;

	BOOST_CHECK(b3.get_size() == b2.get_size());


	DSTL::rbtree<int, int>::const_iterator it2 = b2.begin();
	for (DSTL::rbtree<int, int>::const_iterator it = b3.begin(); it != b3.end(), it2 != b2.end(); ++it, ++it2) {
		//	std::cout << it->first << " " << it->second << " " << it2->first << " " << it2->second;
		//	std::cout << std::endl;
		BOOST_CHECK(it->first == it2->first);
		BOOST_CHECK(it->second == it2->second);
	}
}

// a performance test copy vs move
BOOST_AUTO_TEST_CASE(myTestCase17)
{
	DSTL::rbtree<int, int> b;

	const std::vector<std::pair<int, int>> random_pairs = get_random_pairs(10000);

	for (const std::pair<int, int>& p : random_pairs) {
		b.insert(p);
	}

	std::cout << "b size: " << b.get_size() << " b height: " << b.get_height() << std::endl;

	auto start_time_copy = std::chrono::high_resolution_clock::now();
	auto b3(b); // copy
	auto end_time_copy = std::chrono::high_resolution_clock::now();
	auto time_copy = end_time_copy - start_time_copy;

	auto start_time_move = std::chrono::high_resolution_clock::now();
	auto b2(std::move(b));
	auto end_time_move = std::chrono::high_resolution_clock::now();
	auto time_move = start_time_move - end_time_move;

	std::cout << std::endl;
	std::cout << "copy time: " << time_copy / std::chrono::milliseconds(1) << std::endl;
	std::cout << "move time: " << time_move / std::chrono::milliseconds(1) << std::endl;

	BOOST_CHECK(time_move < time_copy);

	// check values
	DSTL::rbtree<int, int>::const_iterator it2 = b2.begin();
	for (DSTL::rbtree<int, int>::const_iterator it = b3.begin(); it != b3.end(), it2 != b2.end(); ++it, ++it2) {
		//	std::cout << it->first << " " << it->second << " " << it2->first << " " << it2->second;
		//	std::cout << std::endl;
		BOOST_CHECK(it->first == it2->first);
		BOOST_CHECK(it->second == it2->second);
	}
}

// copy assignment test
BOOST_AUTO_TEST_CASE(myTestCase18)
{
	DSTL::rbtree<int, int> b1;
	DSTL::rbtree<int, int> b2;

	const std::vector<std::pair<int, int>> random_pairs1 = get_random_pairs(10000);

	for (const std::pair<int, int>& p : random_pairs1) {
		b1.insert(p);
	}

	std::cout << "b1 size: " << b1.get_size() << " b1 height: " << b1.get_height() << std::endl;

	const std::vector<std::pair<int, int>> random_pairs2 = get_random_pairs(10000);

	for (const std::pair<int, int>& p : random_pairs2) {
		b2.insert(p);
	}

	b1 = b2;
	
	DSTL::rbtree<int, int>::const_iterator it2 = b2.begin();
	for (DSTL::rbtree<int, int>::const_iterator it = b1.begin(); it != b1.end(), it2 != b2.end(); ++it, ++it2) {
		//	std::cout << it->first << " " << it->second << " " << it2->first << " " << it2->second;
		//	std::cout << std::endl;
		BOOST_CHECK(it->first == it2->first);
		BOOST_CHECK(it->second == it2->second);
	}
}

// move assignment test
BOOST_AUTO_TEST_CASE(myTestCase19)
{
	DSTL::rbtree<int, int> b1;
	DSTL::rbtree<int, int> b2;

	const std::vector<std::pair<int, int>> random_pairs1 = get_random_pairs(10000);

	for (const std::pair<int, int>& p : random_pairs1) {
		b1.insert(p);
	}

	std::cout << "b1 size: " << b1.get_size() << " b1 height: " << b1.get_height() << std::endl;

	const std::vector<std::pair<int, int>> random_pairs2 = get_random_pairs(10000);

	for (const std::pair<int, int>& p : random_pairs2) {
		b2.insert(p);
	}

	auto b(b2);

	b1 = std::move(b2);

	DSTL::rbtree<int, int>::const_iterator it2 = b.begin();
	for (DSTL::rbtree<int, int>::const_iterator it = b1.begin(); it != b1.end(), it2 != b.end(); ++it, ++it2) {
		//	std::cout << it->first << " " << it->second << " " << it2->first << " " << it2->second;
		//	std::cout << std::endl;
		BOOST_CHECK(it->first == it2->first);
		BOOST_CHECK(it->second == it2->second);
	}
}


// a performance test: copy assignment vs move assignment
BOOST_AUTO_TEST_CASE(myTestCase20)
{
	DSTL::rbtree<int, int> b1;
	DSTL::rbtree<int, int> b2;

	const std::vector<std::pair<int, int>> random_pairs1 = get_random_pairs(10000);

	for (const std::pair<int, int>& p : random_pairs1) {
		b1.insert(p);
	}

	check_if_bst<DSTL::rbtree<int, int>::iterator>(b1.begin(), b1.end(), std::less<int>());

#ifdef DEBUG_MODE
	bool is_rbtree = b1.check_rbtree_properties();
	BOOST_CHECK(is_rbtree);
	std::cout << "is_rbtree: " << is_rbtree << std::endl;
#endif // DEBUG_MODE


	std::cout << "b1 size: " << b1.get_size() << " b1 height: " << b1.get_height() << std::endl;

	const std::vector<std::pair<int, int>> random_pairs2 = get_random_pairs(10000);

	for (const std::pair<int, int>& p : random_pairs2) {
		b2.insert(p);
	}

	check_if_bst<DSTL::rbtree<int, int>::iterator>(b2.begin(), b2.end(), std::less<int>());

	auto b(b2);

	auto start_time_copy = std::chrono::high_resolution_clock::now();
	b1 = b2; // copy
	auto end_time_copy = std::chrono::high_resolution_clock::now();
	auto time_copy = end_time_copy - start_time_copy;

	auto start_time_move = std::chrono::high_resolution_clock::now();
	b1 = std::move(b); // move
	auto end_time_move = std::chrono::high_resolution_clock::now();
	auto time_move = start_time_move - end_time_move;

	std::cout << std::endl;
	std::cout << "copy time: " << time_copy / std::chrono::milliseconds(1) << std::endl;
	std::cout << "move time: " << time_move / std::chrono::milliseconds(1) << std::endl;

	BOOST_CHECK(time_move < time_copy);

	// check values
	DSTL::rbtree<int, int>::const_iterator it2 = b2.begin();
	for (DSTL::rbtree<int, int>::const_iterator it = b1.begin(); it != b1.end(), it2 != b2.end(); ++it, ++it2) {
		//	std::cout << it->first << " " << it->second << " " << it2->first << " " << it2->second;
		//	std::cout << std::endl;
		BOOST_CHECK(it->first == it2->first);
		BOOST_CHECK(it->second == it2->second);
	}
}