#include "tests.h"
#include <unordered_map>

using namespace std;

void std_umap_test1()
{
	unordered_map<int, string> um;
	//	um[1] = "sfsdfs";
	cout << um.bucket_count() << endl;
	cout << um.load_factor() << endl;
	cout << um.max_bucket_count() << endl;
	um.max_load_factor(14);
	cout << um.max_load_factor() << endl;
}

int main()
{
	/*
	test1();
	test2();
	test3();
	test4();
	*/
	//test5();
	//test6();
	//test7();
	//test8();
	//test9();
	test10();

	// unordered_set vs vector, and comparison of all containers
	return 0;
}