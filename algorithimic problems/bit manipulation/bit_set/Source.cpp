#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>
#include <sstream>
#include <assert.h>

using namespace std;

string short_to_binary_string(short x)
{
	bitset<sizeof(x)*8> b(x);
	return b.to_string();
}

unsigned binary_string_to_int(string s)
{
	bitset<sizeof(unsigned)*8> b(s);
	return b.to_ulong();
}

class bset
{
	vector<char> v;


	vector<char> unsigned_to_vchar(unsigned x) const
	{
		vector<char> r;
		for (int i = 0; i < sizeof(x) * 8 - 1; ++i)
		{
			r.push_back('0' + ((x & 1) == 1));
			x = x >> 1;
		}
		reverse(r.begin(), r.end());
		return r;
	}
public:
	bset() = default;
	bset(unsigned x)
	{
		v = unsigned_to_vchar(x);
	}

	bset(string s)
	{
		std::copy(s.cbegin(), s.cend(), back_inserter(v));
	}

	unsigned to_unsigned() const
	{
		unsigned x = 0;
		for (vector<char>::const_reverse_iterator it = v.crbegin(); it != v.crend(); ++it)
		{
			x = x | (*it - '0') << distance(v.crbegin(), it);
		}
		return x;
	}

	string to_string() const
	{
		stringstream ss;

		for_each(v.cbegin(), v.cend(), [&ss](char c) {ss << c; });
		return ss.str();
	}

	char& operator[](unsigned i)
	{
		return v[v.size() - i - 1];
	}

	const char& operator[](unsigned i) const
	{
		return v[v.size() - i - 1];
	}

	bool operator==(const bset& b) const
	{
		return v == b.v;
	}
	bool any() const
	{
		for (char c : v)
		{
			if (c == '1')
				return true;
		}
		return false;
	}

	bool all() const
	{
		for (char c : v)
		{
			if (c == '0')
				return false;
		}
		return true;
	}

	size_t count() const
	{
		size_t c = 0;
		for (char c : v)
		{
			if (c == '1')
				++c;
		}
		return c;
	}

	size_t size() const
	{
		return v.size();
	}

	friend ostream& operator<<(ostream& os, const bset& b);

	/*
	* logical operators
	*/

	bset& operator&=(const bset& b)
	{
		assert(size() == b.size());

		for (int i = 0; i < size(); ++i)
		{
			v[i] = '0' + ((v[i] - '0') & (b.v[i] - '0'));
		}
		return *this;
	}

	bset& operator|=(const bset& b)
	{

	}
	bset& operator^=(const bset& b)
	{

	}
	bset& operator~()
	{

	}

	bset operator<<(std::size_t pos) const
	{
		unsigned d = this->to_unsigned();
		d <<= pos;
		//*this = d;
		return d;
	}

	bset& operator>>=(std::size_t pos)
	{
		unsigned d = this->to_unsigned();
		d >>= pos;
		v = unsigned_to_vchar(d);
		return *this;
	}
};

ostream& operator<<(ostream& os, const bset& b)
{
	for (char c : b.v)
	{
		os << c;
	}
	os << endl;

	return os;
}

bset operator^(const bset& b1, const bset& b2)
{
//	assert(b1.size() == b2.size());
	//stringstream ss;
	string s;
	for (int i = 0; i < min(b1.size(), b2.size()); ++i)
	{
		s = (char)('0' + ((b1[i] - '0') ^ (b2[i] - '0'))) + s;
	}

	return s;
}

int main()
{
	bset b("01011101");

	cout << b << endl;
	cout << b.to_unsigned() << endl;
	cout << b[1] << endl;
	cout << b.to_string() << endl;
	cout << endl;
	cout << "AAAA:::: " << bset(b.to_string()).to_unsigned() << endl;
	
	bset b2("11000101");

	cout << b2 << endl;
	cout << (b &= b2) << endl;
	cout << endl;
	cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";

	cout << short_to_binary_string(145) << endl;
	cout << binary_string_to_int(short_to_binary_string(145)) << endl;
	

	cout << "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n";

	cout << b2 << endl;
	cout << (b2 << 2) << endl;
	cout << b2 << endl;
	cout << (b2 >>= 1) << endl;

	cout << "b1 = " << b << " : " << "b2 = " << b2 << endl;
	cout << "b1^b2 = " << (b ^ b2) << endl;
	/*
	bitset<10> s1{0b0011};
	cout << s1 << endl;
	cout << s1.to_ulong() << endl;

	s1.set(3, 1);
	cout << s1 << " " << s1.count() << endl;
	cout << (s1 &= 0b0011) << endl;
	cout << s1.to_string() << endl;
	cout << (s1 & bitset <10>(s1)) << endl;
	cout << s1[0] << endl;
	*/

	//cout << (s1 + s1) << endl;
	return 0;
}