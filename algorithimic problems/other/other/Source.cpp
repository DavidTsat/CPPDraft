#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
finds all positive numbers in the array that have their opposites in it as well
*/
void f(vector<int>& v)
{
	struct custom_cmp
	{
		bool operator()(int a, int b)
		{
			if (a != b && a != -b)
			{
				return abs(a) < abs(b);
			}
			return a < b;
		}
	};
	sort(v.begin(), v.end(), custom_cmp());
}

int main()
{
	vector<int> v{ 1,-2,-4,-1,3,0,2,-3,7,-2 };
	auto print_vec = [](const vector<int>& vv) { for (int c : vv) cout << c << ' '; cout << endl; };
	print_vec(v);
	f(v);
	print_vec(v);
	return 0;
}