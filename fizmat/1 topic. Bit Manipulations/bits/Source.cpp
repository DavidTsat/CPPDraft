#include <iostream>
#include <string>

using namespace std;

/*
Пусть дано целочисленное значение short x, требуется возвращать его бинарное представление в std::string (порядок - big endian).
Алгоритм должен использовать битовые операции.
Предполагается, что sizeof(short) = 2 (то есть длина результативной строки должа быть равной 2*8 = 16)
Примеры
0   -> "0000000000000000"
1   -> "0000000000000001"
7   -> "0000000000000111"
777 -> "0000001100001001"
513 -> "0000001000000001"
*/

string short_to_binary_string(short x)
{
	string s;
	for (int i = 0; i < sizeof(x) * 8; ++i)
	{
		s = to_string((x & 1) == 1) + s;
		x = x >> 1;
	}
	return s;
}

unsigned binary_string_to_int(string s)
{
	unsigned x = 0;
	for (int i = 0; i < s.size(); ++i)
	{
		x = x << 1;
		char c = s[i];
		int cc = c - '0';
		x = x | cc;
	}
	return x;
}

bool get_bit(int num, int i)
{
	return (num & (1 << i)) != 0;
}

int set_bit(int num, int i)
{
	return num | (1 << i);
}

int clear_bit(int num, int i)
{
	return num & ~(1 << i);
}

int clear_bits_MSB_through_i(int num, int i)
{
	int mask = (1 << i) - 1;
	int mask2 = -1 >> i; // problem with this mask; implementation defined 
	return num & mask;
}

int clear_bits_i_through_zero(int num, int i)
{
	int mask = -1 << i;
	return num & mask;
}

int update_bit(int num, int i, bool b)
{
	int clear_mask = ~(1 << i);
	int set_mask = (b ? 1 : 0) << i;

	return (num & clear_mask) | set_mask;
}

int main()
{
	cout << short_to_binary_string(0) << endl;
	cout << short_to_binary_string(1) << endl;
	cout << short_to_binary_string(7) << endl;
	cout << short_to_binary_string(777) << endl;
	cout << short_to_binary_string(513) << endl;
	cout << short_to_binary_string(-7) << endl;

	cout << boolalpha << (short_to_binary_string(0)   == "0000000000000000") << endl;
	cout << boolalpha << (short_to_binary_string(1)   == "0000000000000001") << endl;
	cout << boolalpha << (short_to_binary_string(7)   == "0000000000000111") << endl;
	cout << boolalpha << (short_to_binary_string(777) == "0000001100001001") << endl;
	cout << boolalpha << (short_to_binary_string(513) == "0000001000000001") << endl;
	cout << boolalpha << (short_to_binary_string(-7)  == "1111111111111001") << endl;

	cout << endl;

	cout << (short_to_binary_string(update_bit(set_bit(513, 2), 2, 0))) << endl;
	cout << (short_to_binary_string(clear_bits_MSB_through_i(-7, 7))) << endl;
	cout << (short_to_binary_string(clear_bits_i_through_zero(-7, 7))) << endl;

	cout << binary_string_to_int("1000") <<endl;

	cout << short_to_binary_string(1 << (((sizeof(int) * 8) - 1))) << endl;

	cout << (1 << (((sizeof(int) * 8) - 1))) << endl;
//	cout << short_to_binary_string(-1) << endl;
	/*
	string s;
	short x = 7; //7
	char* c = (char*)&x;
	char a = *(c);
	cout << (int)a << endl;
	cout << int_to_binary_string(512) << endl;
	*/
	//cout << binary_string_to_int(int_to_binary_string(1)) <<endl;
	return 0;
}