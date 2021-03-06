#include "btree.h"
#include "rbtree.h"
#include <iostream>
#include <map>

template <typename K, typename V, typename C>
void inorder_print(DSTL::btree<K, V, C>& b) {
	b.inorder_traverse([](std::pair<const K, V>& v) {std::cout << v.first << ':' << v.second << ' '; });
}

template <typename K, typename V, typename C>
void postorder_print(DSTL::btree<K, V, C>& b) {
	b.postorder_traverse([](std::pair<const K, V>& v) {std::cout << v.first << ':' << v.second << ' '; });
}

template <typename K, typename V, typename C>
void inorder_print(DSTL::rbtree<K, V, C>& b) {
	b.inorder_traverse([](std::pair<const K, V>& v) {std::cout << v.first << ':' << v.second << ' '; });
}

template <typename K, typename V, typename C>
void postorder_print(DSTL::rbtree<K, V, C>& b) {
	b.postorder_traverse([](std::pair<const K, V>& v) {std::cout << v.first << ':' << v.second << ' '; });
}

int main() {
	
	DSTL::rbtree<double, double, std::less<double>> b;
	
	std::vector<std::pair<int, int>> entries({ {15, 55}, {6, 74}, {18, -45}, {13, 133}, {9,-9}, {17, 0}, {20, 45}, {4, 49}, {7, 78}, {2, 45}, {3, 33} });
	for (const auto& entry : entries) {
		b.insert(entry);
	}

	for (DSTL::rbtree<double, double, std::less<double>>::const_iterator it = b.cbegin(); it != b.cend(); ++it) {
		std::cout << it->first << ":" << it->second << ' ';
	}
	std::cout << std::endl;
	
	//b.delete_entry(7);
	
	for (const auto& entry : entries) {
		b.delete_entry(entry.first);
	}
	

	for (DSTL::rbtree<double, double, std::less<double>>::const_iterator it = b.cbegin(); it != b.cend(); ++it) {
		std::cout << it->first << ":" << it->second << ' ';
	}

	/*
	DSTL::rbtree<double, double, std::less<double>> b2(b);

	postorder_print(b);
	std::cout << std::endl;
	inorder_print(b);
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	for (DSTL::rbtree<double, double, std::less<double>>::const_iterator it = b.cbegin(); it != b.cend(); ++it) {
		std::cout << it->first << ":" << it->second << ' ';
	}

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	postorder_print(b2);
	std::cout << std::endl;
	inorder_print(b2);
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	for (DSTL::rbtree<double, double, std::less<double>>::const_iterator it = b2.cbegin(); it != b2.cend(); ++it) {
		std::cout << it->first << ":" << it->second << ' ';
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << b.get_height() << " " << b.get_size() << " " << b2.get_height() << b2.get_size() << std::endl;
	
	DSTL::rbtree<double, double, std::less<double>> b3(std::move(b2));
	std::cout << "\nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
	postorder_print(b2);
	std::cout << std::endl;
	inorder_print(b2);
	std::cout << "\nVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV\n";
	postorder_print(b3);
	std::cout << std::endl;
	inorder_print(b3);
	std::cout << std::endl;
	std::cout << b2.get_height() << " " << b2.get_size() << " " << b3.get_height() << b3.get_size() << std::endl;


	DSTL::rbtree<double, double> b44 = std::move(b);


	DSTL::rbtree<double, double> b4({ {6,14}, {1,0}, {5,54}, {15,4}, {18,8}, {45,4}, {-10, 0} });
	//b4 = b3;
	b4 = std::move(b3);
	int a = 4;
	//postorder_print(b);
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