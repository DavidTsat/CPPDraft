#include "btree.h"
#include <iostream>

int main() {
	DSTL::btree<double, double, std::greater<double>> b;

	b.insert({ 15, 15 });
	b.insert({ 6,  8  });
	b.insert({ 18, 18 });
	b.insert({ 13, 13 });
	b.insert({ 9,  9  });
	b.insert({ 17, 17 });
	b.insert({ 20, 20 });
	b.insert({ 4,  4  });
	b.insert({ 7,  7  });
	b.insert({ 2,  2  });
	b.insert({ 3,  3 });

	inorder_print(b);
	std::cout << std::endl;
	postorder_print(b);


	
	DSTL::btree<int, int> b2({ {6, 6}, {1, 1}, {5, 5}, {15, 15}, {18, 18}, {45,45}, {0,0} });
	std::cout << std::endl;

	inorder_print(b2);
	std::cout << std::endl;
	postorder_print(b2);

	DSTL::btree<int, int> bi;
	
	return 0;
}