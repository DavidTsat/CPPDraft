#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
Самый простой, но неэффективный подход: перебираем все элементы, на каждом шаге проверяем, если данный элемент
не встречается в новом, результативном массиве, то добавляем, в противном случае идем дальше.
Временная сложность такого подхода будет O(n^2), а пространственная - O(n).
*/
template <typename T>
void unique1(vector<T>& v)
{
	vector<T> r;
	r.reserve(v.size());

	for_each(v.cbegin(), v.cend(), [&r](const T& t) { if (find(r.cbegin(), r.cend(), t) == r.cend()) r.push_back(t); }); // O(n^2)
	v = move(r);
}

/*
Вторый, более эффективный подход. Обьявляем map<T, unsigned> - отоброжение элемент -> индекс в результативном массиве.
Перебираем все элементы входного массива и кладем в мап, если такого элемента нет в нем. O(n) будет сложность цикла 
O(logn) - вставка в мап, т.о. общая сложность этой операции будет O(nlogn). O(n) - инициализация вектора std::vector<T>(m.size())
и так как на этой строке вызывается move assignment operator, сложность перемещения будет O(1). После чего проходимся по всем элементам
мапа и кладем в результативный массив с соответствующим индексом - O(n). Т.о. суммарная временная сложность будет
O(nlogn) + O(n) + O(n), что можно считать как O(nlogn).
*/
template <typename T>
void unique2(vector<T>& v)
{
	map<T, unsigned> m;
	unsigned c = 0;
	for (int i = 0; i < v.size(); ++i) // nlog(n)
	{
		auto p = m.insert({ v[i], c });
		if (p.second) ++c;
	}

	v = std::vector<T>(m.size()); // move; O(n)
	
	for (auto it = m.cbegin(); it != m.cend(); ++it) // O(n)
	{
		v[it->second] = it->first;
	}
}

/*
Третий и на мой взгляд наиболее эффективный подход. Это почти один и тот же алгоритм, что и unique2, но вместо мап, который основан
на бинарном дереве и т.о. у него вставка - O(logn), использую unordered_map<T, int>, для которого вставка в среднем делается за 
константное время - O(1). Т.о, здесь суммарная временная сложность будет O(n) + O(n) + O(n) = O(n), пространственная сложность будет 
O(n) + O(n) + O(n) = O(n) (indices и v2)
*/
template <typename T>
void unique3(vector<T>& v)
{	
	int c = 0;
	unordered_map<T, int> indices(v.size());

	for (int i = 0; i < v.size(); ++i) // O(n)
	{
		auto p = indices.insert({ v[i], c });
		if (p.second) ++c;
	}
	
	v = std::vector<T>(indices.size()); // move; O(n)

	for (auto it = indices.cbegin(); it != indices.cend(); ++it) // O(n)
	{
		v[it->second] = it->first;
	}
}

template <typename T>
void unique3_improved_mem(vector<T>& v)
{
	int c = 0;
	unordered_map<T, int> indices(v.size());

	for (int i = 0; i < v.size(); ++i) // O(n)
	{
		auto p = indices.insert({ v[i], c });
		if (p.second) ++c;
	}

	v.erase(v.begin() + indices.size(), v.end());

	for (auto it = indices.cbegin(); it != indices.cend(); ++it) // O(n)
	{
		v[it->second] = it->first;
	}
}

/*
Можно и четвертый подход предложить, но код не очень ясный и к тому же уступает
в производительности алгоритмам unique2 и unique3. Но-все таки это решение тоже кинул.
Храним индексы элементов, которые будут использованы в результативном массиве - как и прежде
O(n), после чего сортируем массив, в среднем - O(nlogn), и в конце проходимся по всем элементам
отсортированного массива, кладем в результативный массив первое вхождение элемента, а остальные
опускаем - O(n).  Т.о. временная сложность будет O(n) + O(nlogn) + O(n) = O(nlogn), а пространственная -
O(n) + O(n) + memory(sort(v.begin(), v.end())), Последнее слагаемое это пространственная сложность
алгортима std::sort
*/
template <typename T>
void unique4(vector<T>& v)
{
	unordered_map<T, unsigned> indices;
	int i = 0;
	for (const T& t : v)
	{
		if (indices.find(t) == indices.cend())
		{
			indices[t] = i++;
		}
	}
	
	vector<T> r(indices.size());

	sort(v.begin(), v.end());

	auto it = v.cbegin();
	for (auto it2 = next(v.cbegin()); it != v.cend(); ++it2)
	{
		r[indices[*it]] = *it;
		while (it2 != v.cend() && *it2 == *it)
		{
			++it2;
		}
		it = it2;
		if (it2 == v.cend()) break;
	}
	v = move(r);
}

vector<int> generate_vec(int n, int r)
{
	vector<int> vec(n);
	random_device rnd_device;

	mt19937 mersenne_engine{ rnd_device() };  // Generates random integers
	uniform_int_distribution<int> dist{ 1, r };

	auto gen = [&dist, &mersenne_engine]() {
		return dist(mersenne_engine);
	};
	
	generate(begin(vec), end(vec), gen);

	return vec;
}

int main()
{
	auto print_vec = [](const vector<int>& v) { for (int c : v) {
		cout << c << ' ';
	}};

	//vector<int> v({ 1,1,4,0,-5,1,2,3,4,5,7,1 }); // 1,4,0,-5,2,3,5,7
	
	vector<int> v = generate_vec(2500000, 200000);
//\\	print_vec(v);
	//vector<int> v = { 31, 42, 28, 38, 15, 28, 27,8 };
	/*
	for (int c : v)
	{
		cout << c << ' ';
	}
	*/
	cout << endl;
	//unique(v.begin(), v.end());


	auto start_time = std::chrono::high_resolution_clock::now();

	/*
	sort(v.begin(), v.end());
	auto p = unique(v.begin(), v.end());
	v.erase(p, v.end());
	*/

	//auto v2 = v;
	unique3_improved_mem(v);
	//unique2<int>(v);
	//unique4(v);
	//cout << "LLLLL: " << (v2 == v) << endl;
	//cout << "AAAA:  " << (v2 == v) << endl;
	/*
	sort(v.begin(), v.end());
	auto p = unique(v.begin(), v.end());
	cout << "AAAAAAAAAA: " << (p == v.end()) << endl;
	*/
	
	auto end_time = std::chrono::high_resolution_clock::now();
	auto time = end_time - start_time;

	std::cout << time / std::chrono::milliseconds(1) << "ms to run.\n";
	//print_vec(v2);
	cout << endl;
	//print_vec(v);

	/*
	for (int c : v)
	{
		cout << c << ' ';
	}
	*/
	return 0;
}