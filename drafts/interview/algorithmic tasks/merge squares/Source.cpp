#include <iostream>
#include <vector>

using namespace std;

/*
Пусть дан некоторый отсортированный в неубывающем порядке вектор целых чисел {-8, -5, -3, 0, 1, 4, 4, 5, 7, 9}
Требуется написать алгоритм, который за линейное время вернет отсортированный вектор квадратов элементов входного вектора:
{-8, -5, -3, 0, 1, 4, 4, 5, 7, 9} -> {0, 1, 9, 16, 16, 25, 25, 49, 64, 81}
*/

class Solution
{
public:
	vector<int> sorted_squares(vector<int>& data)
	{
		vector<int> v;
		int i = 0;
		for (; i < data.size(); ++i)
		{
			if (data[i] >= 0)
			{
				break;
			}
		}

		int j = i - 1;
		while (j >= 0 && i < data.size())
		{
			if (abs(data[j]) <= abs(data[i]))
			{
				v.push_back(data[j] * data[j]);
				--j;
			}
			else
			{
				v.push_back(data[i] * data[i]);
				++i;
			}
		}
		while (j >= 0)
		{
			v.push_back(data[j] * data[j]);
			--j;
		}
		while (i < data.size())
		{
			v.push_back(data[i] * data[i]);
			++i;
		}
		return v;
	}
};

int main()
{
	Solution s;
	vector<int> v1 = { -8, -5, -3, 0, 1, 4, 4, 5, 7, 9 };
	vector<int> v2 = { 0, 1, 4 };
	vector<int> v3 = { -5, -3 };
	vector<int> v4;
	 
	vector<int> v1_answer = { 0, 1, 9, 16, 16, 25, 25, 49, 64, 81 };
	vector<int> v2_answer = { 0, 1, 16 };
	vector<int> v3_answer = { 9, 25};
	vector<int> v4_answer = {};

	vector<int> v1_ = s.sorted_squares(v1);
	vector<int> v2_ = s.sorted_squares(v2);
	vector<int> v3_ = s.sorted_squares(v3);
	vector<int> v4_ = s.sorted_squares(v4);

	cout << boolalpha << (v1_ == v1_answer) << endl;
	cout << boolalpha << (v2_ == v2_answer) << endl;
	cout << boolalpha << (v3_ == v3_answer) << endl;
	cout << boolalpha << (v4_ == v4_answer) << endl;
	return 0;
}