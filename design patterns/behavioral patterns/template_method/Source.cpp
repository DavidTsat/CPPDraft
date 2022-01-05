#include "conceptual.h"
#include "game.h"

using namespace std;

int main()
{
	game* c = new chess();
	//game* g;
	
	c->run();
	delete c;

	/*
	concrete_class1* c1 = new concrete_class1;
	client_code(c1);
	concrete_class2* c2 = new concrete_class2;
	client_code(c2);

	delete c1;
	delete c2;
	*/
	return 0;
}