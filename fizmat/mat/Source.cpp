#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define all(a) a.cbegin(), a.cend()

template <typename T>
class mat
{
	size_t M;
	size_t N;

	T** v;
public:

	mat(const vector<vector<T>>& v2) : M(v2.size()), N(v2[0].size()), v(new T* [M])
	{
		for (size_t i = 0; i < M; ++i)
		{
			v[i] = new T[N];
			copy(all(v2[i]), v[i]);
		}
	}

	mat(size_t m, size_t n) : M(m), N(n), v(new T* [M])
	{
		for (size_t i = 0; i < M; ++i)
		{
			v[i] = new T[N]();
		}
	}

	mat(const mat<T>& m2) : M(m2.M), N(m2.N), v(new T* [M])
	{
		for (size_t i = 0; i < M; ++i)
		{
			v[i] = new T[N];
			copy(m2.v[i], m2.v[i] + N, v[i]);
		}
	}

	~mat()
	{
		for (size_t i = 0; i < M; ++i)
		{
			delete[] v[i];
		}
		delete[] v;
	}

	T& get(size_t i, size_t j)
	{
		return v[i][j];
	}

	T*& operator[](size_t i)
	{
		return v[i];
	}

	const T* operator[](size_t i) const
	{
		return v[i];
	}

	pair<size_t, size_t> size() const
	{
		return { M, N };
	}

	vector<vector<T>> to_vec_of_vec() const
	{
		vector<vector<T>> mv(M, vector<T>(N));
		for (size_t i = 0; i < M; ++i)
		{
			for (size_t j = 0; j < N; ++j)
			{
				mv[i][j] = v[i][j];
			}
		}
		return mv;
	}

	vector<int> spiral_order() const
	{
		enum class direction { right, down, left, up };

		int m = M;
		int n = N;

		vector<int> r(m * n);
		int k = 0;
		direction cur_dir = direction::right;

		while (k < r.size())
		{
			int cur_row = (M - m + 1) / 2;
			int cur_col = (N - n + 1) / 2;
			switch (cur_dir)
			{
			case direction::right:
			{
				for (int j = cur_col; j < cur_col + n; ++j)
				{
					r[k++] = v[cur_row][j];
				}
				--m;
				cur_dir = direction::down;
			}
			break;
			case direction::down:
			{
				//int cur_col = n - 1;
				for (int j = cur_row; j < cur_row + m; ++j)
				{
					r[k++] = v[j][N - cur_col - 1];
				}
				--n;
				cur_dir = direction::left;
			}
			break;
			case direction::left:
			{
				for (int j = N - 1 - cur_col; j >= cur_col - 1; --j)
				{
					r[k++] = v[M - cur_row][j];
				}
				--m;
				cur_dir = direction::up;
			}
			break;
			case direction::up:
			{
				for (int j = M - 1 - cur_row; j >= cur_row; --j)
				{
					r[k++] = v[j][cur_col - 1];
				}
				--n;
				cur_dir = direction::right;
			}
			break;
			}
		}
		return r;
	}

	void rotate()
	{
		int n = M - 1;
		for (int i = 0; i <= n; ++i)
		{
			int j = n - i;
			for (int k = i; k <= n; ++k)
			{
				swap(v[k][i], v[j][k]);
			}
		}

		for (int j = 0; j <= n - 2; ++j)
		{
			for (int i = j + 1; i + j < n; ++i)
			{
				swap(v[j][i], v[i][n - j]);
			}
		}
	}

	template <typename T>
	friend ostream& operator<<(ostream& os, const mat<T>& m)
	{
		for (int i = 0; i < m.M; ++i)
		{
			for (int j = 0; j < m.N; ++j)
			{
				os << m[i][j] << ' ';
			}
			os << endl;
		}
		return os;
	}
};

template <typename T>
mat<T> generate_spiral_mat(int n)
{
	mat<int> v(n, n);

	int k = n % 2 == 0 ? n / 2 : n / 2 + 1;
	int c = 1;

	size_t M = v.size().first;

	for (int p = 0; p < k; ++p)
	{
		for (int j = 0; j <= 3; ++j)
		{
			switch (j)
			{
			case 0:
				// row; from left to right
				for (int i = 1; i <= n; ++i)
				{
					if (!v[p][i - 1])
						v[p][i - 1] = c++;
				}
				break;
			case 1:
				// column; from up to bottom
				for (int i = 1; i <= n; ++i)
				{
					if (!v[i - 1][M - 1 - p])
						v[i - 1][M - 1 - p] = c++;
				}
				break;
			case 2:
				// row; from right to left
				for (int i = 1; i <= n; ++i)
				{
					if (!v[M - 1 - p][M - i])
						v[M - 1 - p][M - i] = c++;
				}
				break;
			case 3:
				// column; from bottom to up
				for (int i = 1; i <= n; ++i)
				{
					if (!v[M - i][p])
						v[M - i][p] = c++;
				}
				break;
			}
		}
	}

	return v;
}


void spiral_order_tests()
{
	vector<vector<int>> v1 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	vector<vector<int>> v2 = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} };

	vector<int> v1_answ = { 1, 2, 3, 6, 9, 8, 7, 4, 5 };
	vector<int> v2_answ = { 1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7 };

	vector<vector<vector<int>>> inputs = { v1, v2 };
	vector<vector<int>> outputs = { v1_answ, v2_answ };

	for (int i = 0; i < 2; ++i)
	{
		mat<int> m(inputs[i]);
		vector<int> answ = m.spiral_order();
		cout << boolalpha << (answ == outputs[i]) << endl;
	}
}

void spiral_mat_tests()
{
	int v1 = 3;
	int v2 = 1;

	vector<vector<int>> v1_answ = { {1, 2, 3}, {8, 9, 4}, {7, 6, 5} };
	vector<vector<int>> v2_answ = { {1} };

	vector<int> inputs = { v1, v2 };
	vector<vector<vector<int>>> outputs = { v1_answ, v2_answ };

	for (int i = 0; i < 2; ++i)
	{
		mat<int> m = generate_spiral_mat<int>(inputs[i]); // FOR THIS TO WORK PROPERLY WE MUST HAVE A CORRECTLY IMPLEMENTED COPY CONSTRUCTOR
		vector<vector<int>> answ = m.to_vec_of_vec();
		cout << boolalpha << (answ == outputs[i]) << endl;
	}

}

void rotate_tests()
{
	vector<vector<int>> v1 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	vector<vector<int>> v2 = { {5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16} };
	vector<vector<int>> v3 = { {1} };

	vector<vector<int>> v1_answ = { {7, 4, 1}, {8, 5, 2}, {9, 6, 3} };
	vector<vector<int>> v2_answ = { {15, 13, 2, 5}, {14, 3, 4, 1}, {12, 6, 8, 9}, {16, 7, 10, 11} };
	vector<vector<int>> v3_answ = { {1} };

	vector<vector<vector<int>>> inputs = { v1, v2, v3 };
	vector<vector<vector<int>>> outputs = { v1_answ, v2_answ, v3_answ };

	for (int i = 0; i < 3; ++i)
	{
		mat<int> m(inputs[i]);
		m.rotate();
		vector<vector<int>> answ = m.to_vec_of_vec();
		cout << boolalpha << (answ == outputs[i]) << endl;
	}
}

void run_tests()
{
	cout << "running spiral_order_tests" << endl;
	spiral_order_tests();
	cout << endl << "running spiral_mat_tests " << endl;
	spiral_mat_tests();
	cout << endl << "running rotate_tests" << endl;
	rotate_tests();
}
int main()
{
	run_tests();

	return 0;
}