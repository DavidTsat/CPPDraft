#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define all(a) a.begin(), a.end()

#define uninitialized_copy_from(begin, end)		\
for (size_t i = 0; i < M; ++i)					\
{												\
	v[i] = new T[N];							\
	uninitialized_copy(begin, end, v[i]);		\
}

template <typename T>
class mat
{
	size_t M;
	size_t N;

	T** v;

	void cover_island_dfs(int i, int j)
	{
		if (i >= M || i < 0 || j >= N || j < 0 || v[i][j] == '0')
			return;

		v[i][j] = '0';

		cover_island_dfs(i + 1, j);
		cover_island_dfs(i - 1, j);
		cover_island_dfs(i, j + 1);
		cover_island_dfs(i, j - 1);
	}
public:
	mat() : M(0), N(0), v(nullptr) {}

	mat(const vector<vector<T>>& v_) : M(v_.size()), N(v_[0].size()), v(new T* [M])
	{
		uninitialized_copy_from(v_[i].cbegin(), v_[i].cend());
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
		uninitialized_copy_from(m2[i], m2[i] + N);
	}

	
	mat(mat<T>&& m2) noexcept : mat()
	{
		swap_(*this, m2);
		cout << "move" << endl;
	}

	mat<T>& operator=(mat<T>&& m2) noexcept
	{
		cout << "move assignment" << endl;

		swap_(*this, m2);
		//	m2.~mat();

		return *this;
	}

	mat<T>& operator=(const mat<T>& m2)
	{
		mat<T> m1(m2);
		swap_(*this, m1);

		return *this;
	}
	
	template <typename F>
	friend void swap_(mat<F>&, mat<F>&);

	~mat()
	{
		if (!v) return;

		for (size_t i = 0; i < M; ++i)
		{
			delete[] v[i];
		}
		delete[] v;

		v = nullptr;
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

	constexpr pair<size_t, size_t> size() const
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
		if (M == 0) return;

		int n = M - 1;
		for (int i = 0; i <= n; ++i)
		{
			int j = n - i;
			for (int k = i; k <= n; ++k)
			{
				std::swap(v[k][i], v[j][k]);
			}
		}

		for (int j = 0; j <= n - 2; ++j)
		{
			for (int i = j + 1; i + j < n; ++i)
			{
				std::swap(v[j][i], v[i][n - j]);
			}
		}
	}

	template <typename F>
	friend ostream& operator<<(ostream& os, const mat<F>& m);

	int max_square() const
	{
		if (std::is_same<T, char>::value)
		{
			int n = 0;
			mat<int> vb(M, N);

			for (int i = 0; i < M; ++i)
			{
				for (int j = 0; j < N; ++j)
				{

					if (i == 0 || j == 0 || v[i][j] == '0')
					{
						vb[i][j] = v[i][j] == '1';
					}
					else
					{
						vb[i][j] = min(min(vb[i - 1][j], vb[i][j - 1]), vb[i - 1][j - 1]) + 1;
					}

					n = max(n, vb[i][j]);
				}
			}

			return n * n;
		}
		else
		{
			throw std::logic_error("incorrect type!");
		}
	}

	int num_islands()
	{
		if (std::is_same<T, char>::value)
		{
			int count = 0;

			for (int i = 0; i < M; ++i)
			{
				for (int j = 0; j < N; ++j)
				{
					if (v[i][j] == '1')
					{
						cover_island_dfs(i, j);
						++count;
					}
				}
			}
			return count;
		}
		else
		{
			throw std::logic_error("incorrect type!");
		}
	}

};

template <typename F>
void swap_(mat<F>& m1, mat<F>& m2)
{
	//std::swap(m1, m2); // QUESTION ?? WHY WE CAN'T CALL THIS
	std::swap(m1.M, m2.M);
	std::swap(m1.N, m2.N);
	std::swap(m1.v, m2.v);
}

template <typename F>
ostream& operator<<(ostream& os, const mat<F>& m)
{
	for_each(m.v, m.v + m.N, [&m](const F* ptr) {
		for_each(ptr, ptr + m.N, [&m](const F& elem) { cout << elem << ' '; });
		cout << endl;
		});
	return os;
}

template <typename T>
mat<T> mat_mul(const mat<T>& m1, const mat<T>& m2)
{
	if (m1.size().second != m2.size().first)
	{
		throw logic_error("Bad shapes!");
	}

	mat<T> r(m1.size().first, m2.size().second);

	for (int i = 0; i < r.size().first; ++i)
	{
		for (int j = 0; j < m2.size().second; ++j)
		{
			for (int k = 0; k < m1.size().second; ++k)
			{
				r[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}
	return r;
}

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