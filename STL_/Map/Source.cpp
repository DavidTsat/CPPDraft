#include "btree.h"
#include "rbtree.h"
#include <iostream>
#include <map>

template <typename K, typename V, typename C>
void inorder_print(DSTL::btree<K, V, C>& b) {
	b.inorder_traverse(b.begin(), [](std::pair<const K, V>& v) {std::cout << v.first << ':' << v.second << ' '; });
}

template <typename K, typename V, typename C>
void postorder_print(DSTL::btree<K, V, C>& b) {
	b.postorder_traverse(b.begin(), [](std::pair<const K, V>& v) {std::cout << v.first << ':' << v.second << ' '; });
}

int main() {

	DSTL::rbtree<double, double, std::less<double>> b;
	//b.insert(std::make_pair(15, 14));
	b.insert(15);
	b.insert(6);
	b.insert(18);
	b.insert(13);
	b.insert(9);
	b.insert(17);
	b.insert(20);
	b.insert(4);
	b.insert(7);
	b.insert(2);
	b.insert(3);
	/*
	DSTL::btree<double, double, std::less<double>> b;

	b.insert(15);
	b.insert(6);
	b.insert(18);
	b.insert(13);
	b.insert(9);
	b.insert(17);
	b.insert(20);
	b.insert(4);
	b.insert(7);
	b.insert(2);
	b.insert(3);

	inorder_print(b);
	std::cout << std::endl;
	postorder_print(b);

	std::cout << std::endl;
	std::cout << std::endl;
	std::map<int, int, std::less<int>> bstd({ { 15, 15 }, { 6,6 }, { 18,18 }, { 13, 13 }, { 9, 9 }, { 17,17 }, { 20,20 }, { 4,4 }, { 7,7 }, { 2,2 }, { 3,3 } });

	for (std::map<int, int>::const_iterator it = bstd.begin(); it != bstd.end(); ++it) {
		std::cout << it->first << ":" << it->second << ' ';
	}
	std::cout << std::endl;
	std::cout << std::endl;

	DSTL::btree<double, double, std::less<double>>::const_iterator itt = b.begin();
	std::map<int, int>::iterator itt2 = bstd.begin();
	(*itt2).second = 784;
	//(*itt2).first = 7804;
	//(*itt).second = 784;
	//itt->first = 78;
	//itt->second = 778;
	//(*itt).first = 7804;
	std::cout << "AAAA: " << (*itt).first << std::endl;
	
	for (DSTL::btree<double, double, std::less<double>>::const_iterator it = b.begin(); it != b.end(); ++it) {
		std::cout << it->first << ":" << it->second << ' ';
	}
	
	
	b.delete_entry(18);

	std::cout << std::endl;
	std::cout << std::endl;
	inorder_print(b);
	std::cout << std::endl;
	postorder_print(b);
	
	/*
	DSTL::btree<int, int> b2({6, 1, 5, 15, 18, 45, 0});
	std::cout << std::endl;

	inorder_print(b2);
	std::cout << std::endl;
	postorder_print(b2);
	*/
	
	return 0;
}