#pragma once
#include "btree_map.h"
#include <string>
#include <assert.h>

using namespace std;

btree_map<int, string> get_btree_example()
{
	btree_map<int, string> m;
	m[5] = "David";
	m[5] = "abc";

	m[12] = "abc12";
	m[18] = "abc132";
	m[2] = "abc15156";
	m[9] = "abc15";
	m[19] = "abc58181";
	m[17] = "abc5151";
	m[13] = "abc4949";

	return m;
}

void test1()
{
	btree_map<int, string> m;
	m[5] = "David";
	m[5] = "abc";

	m[12] = "abc12";
	m[18] = "abc132";
	m[2] = "abc15156";
	m[9] = "abc15";
	m[19] = "abc58181";
	m[17] = "abc5151";
	m[13] = "abc4949";

	m.print_inorder();	
}

void test2()
{
	btree_map<int, string> m;
	m[5] = "David";
	m[5] = "abc";

	m[12] = "abc12";
	m[18] = "abc132";
	m[2] = "abc15156";
	m[9] = "abc15";
	m[19] = "abc58181";
	m[17] = "abc5151";
	m[13] = "abc4949";
	m[3] = "sdfsabc12";
	m[1] = "ssdfsabc12";

//	m.print_postorder();

	for (btree_map<int, string>::iterator it = m.begin(); it != m.end(); ++it)
	{
		cout << (*it).first << " : " << (*it).second << endl;
	}	
}

struct A
{
	int c;
	static int copy_counter;
	static int delete_counter;

	A(int cc) : c(cc) {}
	A(const A& a) : c(a.c) 
	{
		++copy_counter;
	}
	A(A&& a) : c(a.c)
	{
		++copy_counter;
	}
	~A()
	{
		++delete_counter;
	}
	 operator int() const { return c; }
};

int A::copy_counter = 0;
int A::delete_counter = 0;

void test3()
{
	cout << A::copy_counter << " : " << A::delete_counter << endl;
	{
		btree_map<A, string, std::function<bool(const A&, const A&)>> m([](const A& a, const A& b) {return a.c < b.c; });

		m[5] = "David";
		m[5] = "abc";

		m[12] = "abc12";
		m[18] = "abc132";
		m[2] = "abc15156";
		m[9] = "abc15";
		m[19] = "abc58181";
		m[17] = "abc5151";
		m[13] = "abc4949";
		m[3] = "sdfsabc12";
		m[1] = "ssdfsabc12";

	//	for (auto it = m.begin(); it != m.end(); ++it)
		{
		//	cout << (*it).first << " : " << (*it).second << endl;
		}
	}
	cout << A::copy_counter << " : " << A::delete_counter << endl;
}

void test4()
{
	btree_map<string, int> m1;
	btree_map<string, int> m2;

	m1["abc"] = 4;
	m1["afafas"] = 5;
	m1["spdfpsd"] = 8;
	m1["pasdpasd"] = 9;

	m2["abc"] = 4545;
	m2["qqfq"] = 859;
 
	for (btree_map<string, int>::iterator it = m1.begin(); it != m1.end(); ++it)
	{
		cout << (*it).first << " : " << (*it).second << endl;
	}
	cout << endl;
	for (btree_map<string, int>::iterator it = m2.begin(); it != m2.end(); ++it)
	{
		cout << (*it).first << " : " << (*it).second << endl;
	}

	m1.swap(m2);

	cout << "--------------------------------------------" << endl;

	for (btree_map<string, int>::iterator it = m1.begin(); it != m1.end(); ++it)
	{
		cout << (*it).first << " : " << (*it).second << endl;
	}
	cout << endl;
	for (btree_map<string, int>::iterator it = m2.begin(); it != m2.end(); ++it)
	{
		cout << (*it).first << " : " << (*it).second << endl;
	}
}

void test5()
{
	btree_map<int, string> m;
	m[5] = "David";
	m[5] = "abc";

	m[12] = "abc12";
	m[18] = "abc132";
	m[2] = "abc15156";
	m[9] = "abc15";
	m[19] = "abc58181";
	m[17] = "abc5151";
	m[13] = "abc4949";
	m[3] = "sdfsabc12";
	m[1] = "ssdfsabc12";

	m.print_levelorder();
}

void test6()
{
	btree_map<A, string> m;
	m[5] = "David";
	m[5] = "abc";

	m[12] = "abc12";
	m[18] = "abc132";
	m[2] = "abc15156";
	m[9] = "abc15";
	m[19] = "abc58181";
	m[17] = "abc5151";
	m[13] = "abc4949";
	m[3] = "sdfsabc12";
	m[1] = "ssdfsabc12";

	A::copy_counter = 0;
	A::delete_counter = 0;

	cout << A::copy_counter << endl;
	btree_map<A, string> m2(m);
	cout << A::copy_counter << endl <<endl;
	for (btree_map<A, string>::iterator it = m2.begin(); it != m2.end(); ++it)
	{
		cout << (*it).first << " : " << (*it).second << endl;
	}
}

void test7()
{
	btree_map<A, string> m;
	m[5] = "David";
	m[5] = "abc";

	m[12] = "abc12";
	m[18] = "abc132";
	m[2] = "abc15156";
	m[9] = "abc15";
	m[19] = "abc58181";
	m[17] = "abc5151";
	m[13] = "abc4949";
	m[3] = "sdfsabc12";
	m[1] = "ssdfsabc12";

	A::copy_counter = 0;
	A::delete_counter = 0;

	cout << A::copy_counter << endl;
	cout << A::delete_counter << endl;

	btree_map<A, string> m2(move(m));

	cout << A::copy_counter << endl;
	cout << A::delete_counter << endl;

	cout << endl;
	for (btree_map<A, string>::iterator it = m2.begin(); it != m2.end(); ++it)
	{
		cout << (*it).first << " : " << (*it).second << endl;
	}
}

void test8()
{
	btree_map<A, string> m, m2;
	m[5] = "David";
	m[5] = "abc";

	m[12] = "abc12";
	m[18] = "abc132";
	m[2] = "abc15156";
	m[9] = "abc15";
	m[19] = "abc58181";
	m[17] = "abc5151";
	m[13] = "abc4949";
	m[3] = "sdfsabc12";
	m[1] = "ssdfsabc12";

	m2[551] = "sdfsdf";
	m2[84] = "pqoqqw";
	m2[999] = "fsdfs";

	A::copy_counter = 0;
	A::delete_counter = 0;

	m2 = m;

	cout << A::copy_counter << endl;
	cout << A::delete_counter << endl;

	cout << endl;
	for (btree_map<A, string>::iterator it = m2.begin(); it != m2.end(); ++it)
	{
		cout << (*it).first << " : " << (*it).second << endl;
	}
}

void test9()
{
	btree_map<A, string> m, m2;
	m[5] = "David";
	m[5] = "abc";

	m[12] = "abc12";
	m[18] = "abc132";
	m[2] = "abc15156";
	m[9] = "abc15";
	m[19] = "abc58181";
	m[17] = "abc5151";
	m[13] = "abc4949";
	m[3] = "sdfsabc12";
	m[1] = "ssdfsabc12";

	m2[551] = "sdfsdf";
	m2[84] = "pqoqqw";
	m2[999] = "fsdfs";

	A::copy_counter = 0;
	A::delete_counter = 0;

	m2 = move(m);

	cout << A::copy_counter << endl;
	cout << A::delete_counter << endl;

	cout << endl;
	for (btree_map<A, string>::iterator it = m2.begin(); it != m2.end(); ++it)
	{
		cout << (*it).first << " : " << (*it).second << endl;
	}
}

void test10()
{
	btree_map<A, string> m;
	m[5] = "David";
	m[5] = "abc";

	m[12] = "abc12";
	m[18] = "abc132";
	m[2] = "abc15156";
	m[9] = "abc15";
	m[19] = "abc58181";
	m[17] = "abc5151";
	m[13] = "abc4949";
	m[3] = "sdfsabc12";
	m[1] = "ssdfsabc12";

	vector<int> k = { 5, 12, 9, 1, 15, 0 };
	vector<string> v = { "abc", "abc12", "abc15", "ssdfsabc12"};

	for (int i = 0; i < v.size(); ++i)
	{
		btree_map<A, string>::iterator a = m.find(k[i]);
		if (i < v.size())
		{
			assert(k[i] == a->first);
			assert(v[i] == a->second);
		}
		else
		{
			a == m.end();
		}
	}
}

void test11()
{
	btree_map<A, string> m;
	m[5] = "David";
	m[5] = "abc";

	m[12] = "abc12";
	m[18] = "abc132";
	m[2] = "abc15156";
	m[9] = "abc15";
	m[19] = "abc58181";
	m[17] = "abc5151";
	m[13] = "abc4949";
	m[3] = "sdfsabc12";
	m[1] = "ssdfsabc12";

	A::copy_counter = 0;
	A::delete_counter = 0;

	vector<int> k = { 5, 12, 9, 1, 15, 0 };
	vector<string> v = { "abc", "abc12", "abc15", "ssdfsabc12" };

	for (int i = 0; i < v.size(); ++i)
	{
		btree_map<A, string>::iterator a = m.find(k[i]);
		m.erase(a);
		
		//check bst property 
		// TODO QUESTION
	//	assert(m.is_valid_bst());

	//	cout << A::delete_counter << endl;

		m.print_levelorder();
		cout << endl;
	}
}

void test12()
{
	btree_map<int, string> m;
	m[5] = "David";
	m[5] = "abc";

	m[12] = "abc12";
	m[18] = "abc132";
	m[2] = "abc15156";
	m[9] = "abc15";
	m[19] = "abc58181";
	m[17] = "abc5151";
	m[13] = "abc4949";
	m[3] = "sdfsabc12";
	m[1] = "ssdfsabc12";

	vector<int> k = { 5, 12, 9, 1, 15, 0 };
	vector<string> v = { "abc", "abc12", "abc15", "ssdfsabc12" };

	for (int i = 0; i < v.size(); ++i)
	{
		btree_map<int, string>::iterator a = m.find(k[i]);
	//	m.erase(a);

		//check bst property 
		// TODO QUESTION
		assert(m.is_valid_bst());

		//	cout << A::delete_counter << endl;

		m.print_levelorder();
		cout << endl;
	}
}

void test13()
{
	btree_map<int, int> m;
	m.check_is_valid_bst();
}