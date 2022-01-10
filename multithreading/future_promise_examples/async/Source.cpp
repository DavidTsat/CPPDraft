#include <iostream>
#include <future>
#include <chrono>

using namespace std;

int find_the_answer_to_ltuae()
{
	cout << "find_the_answer_to_ltuae\n";
	return 7;
}

void do_other_stuff()
{
	cout << "other stuff\n";
}


int main()
{
	future<int> the_answer = async(find_the_answer_to_ltuae);
	//this_thread::sleep_for(chrono::milliseconds(100));

	do_other_stuff();
	cout << "the answer is: " << the_answer.get() << endl;

	return 0;
}