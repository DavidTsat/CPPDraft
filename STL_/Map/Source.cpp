#include "btree.h"
#include <iostream>

int main() {
	btree<double> b;

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
	b.insert(3);

	b.inorder_print();

	btree<double> b2({ 6,1,5,15,18,45,0 });
	std::cout << std::endl;
	b2.inorder_print();

	btree<int> bi;
	return 0;
}