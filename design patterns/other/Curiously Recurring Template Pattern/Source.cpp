#include <iostream>
#include "crtp.h"

using namespace std;

int main()
{
	FILE* fp;
	writer<console_writer> c = console_writer();
	c.write("David console_writer");

	fopen_s(&fp, "file_.txt", "w+");
	file_writer::mfile = fp;

	writer<file_writer> f = file_writer();
	
	f.write("David file_writer");

	return 0;
}