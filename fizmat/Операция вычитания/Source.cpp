#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <chrono>

using namespace std;

#define len(a) ((int)((a).size()))
#define all(a) a.begin(), a.end()
#define add push_back
#define mkp make_pair
#define fr first
#define sc second
#define endl '\n'

const long long INF = 1000000000ll * 1000000003ll;
const long long MOD = 1000000007ll;
const int N = 2e5 + 5;

int v[N];

#define test_num "test3.txt"

struct sol
{
	ifstream cin;
	sol()
	{
		cin = ifstream(test_num);
	}
	void f2(size_t sz, int n)
	{
		unordered_set<int> us;
		us.reserve(sz*2);

		for (int i = 0; i < sz; ++i)
		{
			cin >> v[i];
			us.insert(v[i]);
		}

		for (int i = 0; i < sz; ++i)
		{
			if (us.find(v[i] - n) != us.end())
			{
				cout << "YES" << endl;
				return;
			}
		}
		cout << "NO" << endl;
	}

	void solve()
	{
		int t;
		cin >> t;

		auto start = std::chrono::system_clock::now();

		while (t--)
		{
			int n, k;
			cin >> n >> k;
			f2(n, k);
		}

		auto end = std::chrono::system_clock::now();
		auto elapsed = end - start;
		std::cout << "TIME: " << elapsed.count() << '\n';
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin.rdbuf(cin.rdbuf());
	std::cout.rdbuf(cout.rdbuf());

	sol s;
	s.solve();
	
	return 0;
}