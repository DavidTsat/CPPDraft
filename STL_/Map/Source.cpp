#include "btree.h"
#include <iostream>

int main() {
	DSTL::btree<double, double, std::greater<double>> b;

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


	DSTL::btree<double> b2({ 6,1,5,15,18,45,0 });
	std::cout << std::endl;
/*
	inorder_print(b2);

	DSTL::btree<int> bi;
	*/
	return 0;
}