#pragma once
#include "_unordered_map.h"
#include <iostream>
#include <vector>
#include <assert.h>
#include <iterator>
#include <string>

using namespace std;


void test1()
{
	_unordered_map<int, string> m1;
	_unordered_map<string, int> m2;
	
	vector<pair<int, string>> v = { {14, "dsdfsd"}, {25, "asasdda"}, {0, "fsdfs"}, {-4, "wepfwelp"}, {845, "qffqf"}, {741, "sffasff"}, {510, "sdfsdf"} };

	size_t i = 1;
	for (const auto& p : v)
	{
		m1[p.first] = p.second;
		m2[p.second] = p.first;

		assert(distance(m1.begin(), m1.end()) == i);
		assert(distance(m2.begin(), m2.end()) == i);

		++i;
	}

	assert(m1.size() == distance(m1.begin(), m1.end()));
	assert(m1.size() == v.size());

	for (_unordered_map<int, string>::iterator it = m1.begin(); it != m1.end(); ++it)
	{
		cout << it->first << " : " << it->second << endl;
	}
	cout << endl;
	for (_unordered_map<string, int>::iterator it = m2.begin(); it != m2.end(); ++it)
	{
		cout << it->first << " : " << it->second << endl;
	}

	cout << "----------------------------------------------\n";

	for (_unordered_map<string, int>::iterator it = --m2.end(); it != m2.begin(); --it)
	{
		cout << it->first << " : " << it->second << endl;
	}
	cout << endl;
	for (_unordered_map<int, string>::iterator it = --m1.end(); it != m1.begin(); --it)
	{
		cout << it->first << " : " << it->second << endl;
	}
}

void test2()
{
	_unordered_map<int, string> m1;

	cout << distance(m1.begin(), m1.end()) << endl;

	cout << m1.bucket_count() << endl;
	cout << m1.load_factor() << endl;
	cout << m1.max_load_factor() << endl;

	m1.max_load_factor(1);
	cout << m1.max_load_factor() << endl;
}

void test3()
{
	_unordered_map<string, int> m;
	vector<pair<int, string>> v;

	cout << m.size() << endl;
	cout << m.bucket_count() << endl;
	cout << m.load_factor() << endl;
	cout << m.max_load_factor() << endl;
	cout << "---------------------------------------\n";

	for (int i = 0; i < 200; ++i)
	{
		v.push_back({ i, "aaaa" + to_string(i) });
	}

	for (const auto& p : v)
	{
		m[p.second] = p.first;
	}
	/*
	for (_unordered_map<string, int>::iterator it = m.begin(); it != m.end(); ++it)
	{
		cout << it->first << " : " << it->second << ' ';
	}
	cout << endl;
	*/
	cout << m.size() << endl;
	cout << m.bucket_count() << endl;
	cout << m.load_factor() << endl; // TODO load_factor > max_load_factor
	cout << m.max_load_factor() << endl;
}

void test4()
{
	_unordered_map<string, int> m;
	vector<pair<int, string>> v;

	for (int i = 0; i < 200; ++i)
	{
		v.push_back({ i, "aaaa" + to_string(i) });
	}

	for (const auto& p : v)
	{
		m[p.second] = p.first;
	}

	for (const auto& p : v)
	{
		_unordered_map<string, int>::iterator it = m.find(p.second);
		assert(it->second == p.first);
	}

	assert(m.find("aaaa200") == m.end());
}

void test5()
{
	_unordered_map<string, int> m1, m2;

	for (int i = 0; i < 20; ++i)
	{
		m1["aaaa" + to_string(i)] = i;
		m2["bbbb" + to_string(i)] = 20 - i;
	}

	for (_unordered_map<string, int>::iterator it = m1.begin(); it != m1.end(); ++it)
	{
		cout << it->first << " : " << it->second << ' ';
	}
	cout << endl << endl;

	for (_unordered_map<string, int>::iterator it = m2.begin(); it != m2.end(); ++it)
	{
		cout << it->first << " : " << it->second << ' ';
	}
	cout << endl << "----------------------------------------------------------------\n\n";

	m1.swap(m2);

	for (_unordered_map<string, int>::iterator it = m1.begin(); it != m1.end(); ++it)
	{
		cout << it->first << " : " << it->second << ' ';
	}
	cout << endl << endl;

	for (_unordered_map<string, int>::iterator it = m2.begin(); it != m2.end(); ++it)
	{
		cout << it->first << " : " << it->second << ' ';
	}
}

void test6()
{
	_unordered_map<string, int> m1;

	for (int i = 0; i < 20; ++i)
	{
		m1["aaaa" + to_string(i)] = i;
	}
	_unordered_map<string, int> m2(m1);

	for (_unordered_map<string, int>::iterator it = m1.begin(); it != m1.end(); ++it)
	{
		cout << it->first << " : " << it->second << ' ';
	}
	cout << endl << endl;

	for (_unordered_map<string, int>::iterator it = m2.begin(); it != m2.end(); ++it)
	{
		cout << it->first << " : " << it->second << ' ';
	}

	//assert(m1 == m2); QUESTION
}

void test7()
{
	_unordered_map<string, int> m1;

	for (int i = 0; i < 20; ++i)
	{
		m1["aaaa" + to_string(i)] = i;
	}
	
	_unordered_map<string, int> m2(move(m1));

	assert(distance(m2.begin(), m2.end()) == 20);

	for (_unordered_map<string, int>::iterator it = m2.begin(); it != m2.end(); ++it)
	{
		cout << it->first << " : " << it->second << ' ';
	}
}

void test8()
{
	_unordered_map<string, int> m1, m2;

	for (int i = 0; i < 20; ++i)
	{
		m1["aaaa" + to_string(i)] = i;
	}
	for (int i = 0; i < 30; ++i)
	{
		m2["bbbb" + to_string(i)] = 30 - i;
	}

	m1 = m2;
	assert(distance(m1.begin(), m1.end()) == 30);
	assert(distance(m2.begin(), m2.end()) == 30);

	for (_unordered_map<string, int>::iterator it = m1.begin(); it != m1.end(); ++it)
	{
		cout << it->first << " : " << it->second << ' ';
	}
	for (_unordered_map<string, int>::iterator it = m2.begin(); it != m2.end(); ++it)
	{
		cout << it->first << " : " << it->second << ' ';
	}
}

void test9()
{
	_unordered_map<string, int> m1, m2;

	for (int i = 0; i < 20; ++i)
	{
		m1["aaaa" + to_string(i)] = i;
	}
	for (int i = 0; i < 30; ++i)
	{
		m2["bbbb" + to_string(i)] = 30 - i;
	}

	m1 = move(m2);
	assert(distance(m1.begin(), m1.end()) == 30);

	for (_unordered_map<string, int>::iterator it = m1.begin(); it != m1.end(); ++it)
	{
		cout << it->first << " : " << it->second << ' ';
	}
}

void test10()
{
	_unordered_map<string, int> m;

	for (int i = 0; i < 200; ++i)
	{
		m["aaaa" + to_string(i)] = i;
	}

	for (_unordered_map<string, int>::iterator it = m.begin(); it != m.end();)
	{
		auto it1(it);
		++it;

		cout << m.size() << " : " << m.load_factor() << endl;
		m.erase(it1);
	}
}