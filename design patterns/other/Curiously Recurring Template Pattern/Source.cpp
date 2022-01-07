#include <iostream>
#include "crtp.h"
#include "ex1.h"
#include "counter.h"
#include "crtp_singleton.h"

using namespace std;

int main()
{

	test_singl* t = test_singl::get_instance();
	t->set_s("David");
	cout << t->get_s() << endl;
	test_singl* t2 = test_singl::get_instance();
	t2->set_s("David2");
	cout << t->get_s() << endl;

	A a;
	A a2;
	B b;

	{
		A a3;
	}
	cout << A::objects_created << endl;
	cout << B::objects_created << endl;


	cout << A::objects_alive << endl;
	cout << B::objects_alive << endl;
	

	/*
	derived1 d1; 
	derived2 d2;

	base<derived1>* b1 = &d1;
	base<derived2>* b2 = &d2;

	b1->foo();
	b2->foo();

	base<derived1> b11 = d1;
	base<derived2> b22 = d2;

	b11.foo();
	b22.foo();
	
	FILE* fp;
	fopen_s(&fp, "file_2.txt", "w+");

	writer<file_writer2>* f = new file_writer2(fp);
	f->write("OOOOOOOOOO");
	delete f;

//	writer<file_writer2> ff = file_writer2(fp);
//	ff.write("YYY");
	*/
	/*
	FILE* fp;
	writer<console_writer> c = console_writer();
	c.write("David console_writer");

	fopen_s(&fp, "file_.txt", "w+");
	file_writer::mfile = fp;

	writer<file_writer> f = file_writer();
	
	f.write("David file_writer");
	*/

	return 0;
}