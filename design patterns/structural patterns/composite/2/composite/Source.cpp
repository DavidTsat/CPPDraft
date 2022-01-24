#include <iostream>
#include <vector>
#include "conceptual.h"
#include "draw_example.h"

using namespace std;


int main()
{
	group root("root");
	circle c1, c2;
	root.add(&c1);
	group subgroup("sub");
	subgroup.add(&c2);
	root.add(&subgroup);
	root.draw();

	/*
	component* simple = new leaf;
	client_code1(simple);
	cout << endl;

	component* tree = new composite;
	component* branch1 = new composite;
	
	component* leaf_1 = new leaf;
	component* leaf_2 = new leaf;
	component* leaf_3 = new leaf;

	branch1->add(leaf_1);
	branch1->add(leaf_2);
	component* branch2 = new composite;
	branch2->add(leaf_3);
	tree->add(branch1);
	tree->add(branch2);
	client_code1(tree);

	cout << endl;
	client_code2(tree, simple);
	*/
	return 0;
}