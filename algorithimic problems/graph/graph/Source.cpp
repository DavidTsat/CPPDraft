#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include <queue>
#include <array>
#include <map>

//#include <unordered_set>

using namespace std;


//template <typename T>
class graph
{
	struct vertex {
		int id;
		vector<unique_ptr<vertex>> adjacents;
		vertex() = default;
		vertex(int id_) : id(id_) {}

		int getid() const { return id; }
	};

	int num_vertices;
	vector<vertex> vertices;

	void bfs_rec(int src, queue<int>&  to_visit, vector<bool>& visited);
	void dfs_rec(int src, vector<bool>& visited);
public:
	graph() = default;
	graph(int);
	void add_edge(int, int);
	void bfs(int src, int dest = -1);

	void bfs_rec(int src, int dest = -1);
	void dfs_rec(int src, int dest = -1);
};


graph::graph(int n) : num_vertices(n), vertices(num_vertices) {

}

void graph::bfs_rec(int src, queue<int>& to_visit, vector<bool>& visited) {

	if (to_visit.empty()) return;

	int c = to_visit.front();
	to_visit.pop();

	cout << c << ' ';

	visited[c] = true;

	for (auto it = vertices[c].adjacents.begin(); it != vertices[c].adjacents.end(); ++it) {
		if (!visited[(*it)->id]) {
			//	visited[(*it)->id] = true;
			to_visit.push((*it)->id);
		}
	}
	bfs_rec(src, to_visit, visited);
}

void graph::bfs_rec(int src, int dest) {
	queue<int> to_visit;
	vector<bool> visited(num_vertices, false);

	to_visit.push(src);

	bfs_rec(src, to_visit, visited);
}

void graph::dfs_rec(int src, vector<bool>& visited) {
	visited[src] = true;
	cout << src << ' ';
	for (auto it = vertices[src].adjacents.begin(); it != vertices[src].adjacents.end(); ++it) {
		if (!visited[(*it)->id]) {
			dfs_rec((*it)->id, visited);
		}
	}
}

void graph::dfs_rec(int src, int dest) {
	vector<bool> visited(num_vertices, false);
	dfs_rec(src, visited);
}

void graph::bfs(int src, int dest) {
	vector<bool> visited(num_vertices, false);
	
	queue<int> q;

	visited[src] = true;
	q.push(src);

	while (!q.empty())
	{
		int c = q.front();
		visited[c] = true;
		q.pop();
		
		cout << c << ' ';
		if (c == dest) {
			cout << "found.finish!\n";
			break;
		}
		for (auto it = vertices[c].adjacents.begin(); it != vertices[c].adjacents.end(); ++it) {
			int dd = (*it)->id;
			if (!visited[(*it)->id]) {
			//	visited[(*it)->id] = true;
				q.push((*it)->id);
			}
		}
	}
	cout <<  endl;
}
void graph::add_edge(int s, int d) {
	if (vertices.size() < max(s, d)) {
		vertices.resize(max(s, d)+1);
	}
	vertices[s].adjacents.push_back(make_unique<vertex>(d));
	vertices[d].adjacents.push_back(make_unique<vertex>(s));
}

class Solution1 {

	pair<pair<int, int>, pair<int, int>> extract_islands(vector<vector<char>>& grid, const pair<int, int> p) {
		pair<int, int> p2(p);

		int left_row_id, right_row_id, left_col_id, right_col_id;
		pair<int, int> l, r;

		while (p2.second > 0) {
			if (grid[p.first][p2.second] == '1') {
				--p2.second;
			}
			else {
				++p2.second;
				break;
			}
		}
		
		left_col_id = p2.second;
		p2.second = p.second;

		while (p2.second < grid[p.first].size()) {
			if (grid[p.first][p2.second] == '1') {
				++p2.second;
			}
			else {
				--p2.second;
				break;
			}
		}
		if (p2.second == grid[p.first].size()) {
			--p2.second;
		}

		right_col_id = p2.second;
		p2.second = p.second;


		while (p2.first > 0) {
			if (grid[p2.first][p.second] == '1') {
				--p2.first;
			}
			else {
				++p2.first;
				break;
			}
		}

		left_row_id = p2.first;
		p2.first = p.first;

		while (p2.first < grid.size()) {
			if (grid[p2.first][p.second] == '1') {
				++p2.first;
			}
			else {
				--p2.first;
				break;
			}
		}
		if (p2.first == grid.size()) {
			--p2.first;
		}
		right_row_id = p2.first;
		//p2.first = p.first;

		//auto left_col_id = (int)(distance(grid[p.first].cbegin(), find(grid[p.first].cbegin(), grid[p.first].cend(), '1')));
		//auto right_col_id = (int)(grid[p.first].size() - 1 - distance(grid[p.first].crbegin(), find(grid[p.first].crbegin(), grid[p.first].crend(), '1')));

		/*
		for (int i = 0; i < grid.size(); ++i)
		{
			if (grid[i][left_col_id] == '1')
			{
				left_row_id = i;
				//r.second = make_pair<int,int>(i, i);
				break;
			}
		}
		

		for (int i = grid.size() - 1; i >= 0; --i)
		{
			if (grid[i][right_col_id] == '1')
			{
				right_row_id =  i;
				// r.second = make_pair<int,int>(r.second.first, i);
				break;
			}
		}
		*/

		l = { left_row_id, left_col_id };
		r = { right_row_id, right_col_id };

		//    c = {{left_row_id, p.second}, {right_row_id, p.second}};

		return { l, r };
	}

	bool visited(vector<pair<pair<int, int>, pair<int, int>>>& rects, pair<int, int> p)
	{
		
		for (const pair<pair<int, int>, pair<int, int>>& r : rects)
		{
			if ((p.first >= r.first.first && p.first <= r.second.first ) && (p.second >= r.first.second && p.second <= r.second.second))
			{
				return true;
			}
		}
		
		return false;
	}
public:
	int numIslands(vector<vector<char>>& grid) {
		vector<pair<pair<int, int>, pair<int, int>>> rects; // рассмотренные вершины <левый верхний угол, правый нижний угол>
		int count = 0;

		//if (grid.size())

		for (int i = 0; i < grid.size(); ++i)
		{
			for (int j = 0; j < grid[i].size(); ++j)
			{

				if (grid[i][j] == '1' && !visited(rects, { i, j }))
				{
					pair<pair<int, int>, pair<int, int>> rect = extract_islands(grid, { i, j });
					rects.push_back(rect);
					++count;
				}
			}
		}

		return count;
	}
};

class Solution {

	void visit_bfs(vector<vector<char>>& grid, vector<bool>& visited, int i) const
	{
		if (!visited[i])
		{
			visited[i] = true;
		//	cout << i << ' ';
		}

		queue<int> to_visit;
		to_visit.push(i);

		while (!to_visit.empty())
		{
			int c = to_visit.front();
			to_visit.pop();
			visited[c] = true;

			cout << c << ' ';

			for (int j = 0; j < grid[c].size(); ++j)
			{
				if (grid[c][j] == '1' && !visited[j])
				{
					to_visit.push(j);
				}
			}
		}
		cout << endl;
	}
	void visit(vector<vector<char>>& grid, vector<bool>& visited, int i) const
	{
		visit_bfs(grid, visited, i);
	}
public:
	int numIslands(vector<vector<char>>& grid) {

		if (grid.size() == 1)
		{
			Solution1 s;
			return s.numIslands(grid);
		}


		if (grid.size() != grid[0].size())
		{
			vector<vector<char>> grid2 (max(grid.size(), grid[0].size()), vector<char>(max(grid.size(), grid[0].size()), '0'));
			for (int i = 0; i < grid.size(); ++i)
			{
				for (int j = 0; j < grid[i].size(); ++j)
				{
					grid2[i][j] = grid[i][j];
				}
			}
			grid = move(grid2);
		}

		int count = 0;


		vector<bool> visited(max(grid.size(), grid[0].size())); // рассмотренные вершины
		for (int i = 0; i < grid.size(); ++i)
		{
			for (int j = 0; j < grid[i].size(); ++j)
			{
				bool vv = false;
				array<pair<int, int>, 5> adj{ {{i,j}, {i - 1,j}, {i + 1,j}, {i, j - 1}, {i, j + 1} } };
				for (pair<int, int> v : adj)
				{
					if (v.first >= 0 && v.first < grid.size() && v.second >=0 && v.second < grid[0].size()) {
						if (!visited[v.first] && grid[v.first][v.second] == '1') {
							visit(grid, visited, v.first);
							vv = true;
						}
					}
				}
				if (vv) ++count;
	
			}
		}
		

		return count;
	}
};

class Solution_last {
	void visit_dfs(vector<vector<char>>& grid, int i, int j) const
	{
		if (i < 0 || j < 0 || i >= grid.size() || j >= grid[i].size() || grid[i][j] == '0')
		{
			return;
		}
		grid[i][j] = '0';

	//	visit_dfs(grid, i, j);
		visit_dfs(grid, i - 1, j);
		visit_dfs(grid, i + 1, j);
		visit_dfs(grid, i, j - 1);
		visit_dfs(grid, i, j + 1);
	}
	void visit(vector<vector<char>>& grid, int i, int j) const
	{
		visit_dfs(grid, i, j);
	}
public:
	int numIslands(vector<vector<char>>& grid) {
		int count = 0;

		for (int i = 0; i < grid.size(); ++i)
		{
			for (int j = 0; j < grid[i].size(); ++j)
			{
				if (grid[i][j] == '1')
				{
					visit(grid, i, j);
					++count;
				}
			}
		}
		return count;
	}
};



 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solutiont {

	/*
	void dfs(TreeNode* t, vector<int>& depths, int& d)
	{
		if (t == nullptr)
		{
			//depths.push_back(d);
			//d = 0;
			//--d;
			return;
		}
		
		++d;
		dfs(t->left, depths, d);
		
		dfs(t->right, depths, d);
		
	}
	*/

	void bfs(TreeNode* t, queue<pair<TreeNode*, pair<bool, int>>>& q,  int& d)
	{
		if (t == nullptr)
		{
			return;
		}
		
		q.push({ t, { true, d } });

		q.push({ t->left,  {false, d + 1} });
		q.push({ t->right, {false, d + 1} });

		while (!q.empty())
		{
			pair<TreeNode*, pair<bool, int>>p = q.front();
			q.pop();

			if (p.second.first == false)
			{
				d = p.second.second;

				bfs(p.first, q, d);
			}
		//	++d;
		}
	}

	int max_subtree_len(TreeNode* t)
	{
		int max_d = 0;
		int depth = 0;
		vector<int> depths;
		queue<pair<TreeNode*, pair<bool, int>>> q;

		bfs(t, q, depth);
		//dfs(t, depths, depth);
//		for_each(depths.cbegin(), depths.cend(), [&max_d](int c) {max_d = max(c, max_d); });
		max_d = depth;
		return max_d;
	}
public:
	bool isBalanced(TreeNode* root) {
		if (root == nullptr) return true;

		int left_max_depth = 1;
		int right_max_depth = 1;

		if (root->left)
		{
			left_max_depth += max_subtree_len(root->left);
		}

		if (root->right)
		{

			right_max_depth += max_subtree_len(root->right);
		}

		int diff = abs(left_max_depth - right_max_depth);

		return diff <= 1;
	}
};

class Solution_sym {

	int is_symmetric(TreeNode* root, map<int, vector<pair<int, bool>>>& level_values, int& d, bool b)
	{
		if (root == nullptr)
		{
			//(level_values[d]).push_back({ INT16_MIN, b });
			return 0;
		}

		///     vector<int> level_values;

		/*
		if (d > 0) {
			if (root->left == nullptr) (level_values[d - 1]).push_back({ INT16_MIN, 1 });

			if (root->right == nullptr) (level_values[d - 1]).push_back({ INT16_MIN, 0 });
		}
		*/
		int l = is_symmetric(root->left,  level_values, d, 1);
		int r = is_symmetric(root->right, level_values, d, 0);


		int level_height = max(l, r) + 1;

		d = level_height;

		(level_values[level_height]).push_back({root->val, b});

		return level_height;
		//  level_values.push_back(root->val);

		 // return l && r;
	}

	bool isSymmetric2(TreeNode* root) {
		if (root == nullptr) return true;

		int d = 0;
		map<int, vector<pair<int, bool>>> level_values;
		is_symmetric(root, level_values, d, 1);


		for (const pair<int, vector<pair<int, bool>>>& v : level_values)
		{
			if (v.second.size() > 1)
			{
				auto itb = v.second.cbegin();
				auto ite = itb + v.second.size() / 2;

				//	auto ite = --v.second.cend();

				while (ite != v.second.cend())
				{
					if (itb->first != ite->first) return false;
					++itb;
					++ite;
					//if (*itb++ != *ite++) return false;
					/*
					if (itb->first != ite->second || itb->second == ite->second)
					{
						return false;
					}
					++itb;
					++ite;
					*/
					//if (*itb++ != *--ite) return false;
				}
			}
		}

		return true;
	}

public:
	bool isSymmetric(TreeNode* root) {
		if (root == nullptr) return true;
		bool b = isSymmetric2(root);
		

		return b;
	}
};


class Solution_sol {

	bool traverse_level(TreeNode* t, vector<int>& v, int l)
	{
		if (t == nullptr) {
			if (l == 1) {
				v.push_back(-1918126);
			}
			return false;
		}

		if (l == 1)
		{
			v.push_back(t->val);
			return true;
		}

		int bl = traverse_level(t->left, v, l - 1);
		int br = traverse_level(t->right, v, l - 1);

		return bl || br;
	}

public:
	bool isSymmetric(TreeNode* root) {
		if (!root) return true;

		int l = 2;

		vector<int> v;
		while (traverse_level(root, v, l++)) {
			int i = (v.size() / 2)-1;
			int j = v.size() / 2;
			
			while (i >= 0 && j < v.size())
			{
			//	if (itb == v.cbegin() && *itb != *ite++) return false;
				if (v[i--] != v[j++]) return false;
			}
			v.clear();
		}

		return true;
	}
};


class Solution_same {

	void level_order(TreeNode* p, vector<pair<int, bool>>& v, bool b)
	{
		if (p == nullptr)
		{

			return;
		}

		level_order(p->left, v, 1);
		level_order(p->right, v, 0);

		v.push_back({ p->val, b });
	}

	void traverse(TreeNode* p, vector<pair<int, bool>>& v)
	{
		level_order(p, v, 0);
	}

public:
	bool isSameTree(TreeNode* p, TreeNode* q) {
		vector<pair<int, bool>> v1;
		vector<pair<int, bool>> v2;

		traverse(p, v1);
		traverse(q, v2);

		return v1 == v2;
	}
};

/*
class Solution_same {

	bool level_order(TreeNode* p, vector<int>& v, int l, bool b)
	{
		if (p == nullptr)
		{
			return false;
		}
		if (l == 1)
		{
			v.push_back(p->val + b);
			return true;
		}


		bool bl = level_order(p->left, v, l-1, 0);

		bool br = level_order(p->right, v, l-1, 1);

		return bl || br;
		//cout << p->val << endl;
	//	v.push_back(i);
		
	}



public:
	bool isSameTree(TreeNode* p, TreeNode* q) {

		int l = 1;

		while (true)
		{
			vector<int> v1;
			vector<int> v2;

			bool b1 = level_order(p, v1, l, 0);
			bool b2 = level_order(p, v2, l, 0);

			if (b1 != b2) return false;
			if (v1 != v2) return false;
			if (b1 == false && b2 == false) break;
			++l;
		}
		return true;
	}
};
*/

class Solutiondd{
public:
	int maxProfit(vector<int>& prices) {
		int m = 0;
		auto b = prices.begin();
		auto it = b;
		//  ++it;

		  //vector<int>::iterator max_ind = max_element(it, prices.end());
		auto max_ind = max_element(it, prices.end());

		while (max_ind != prices.end())
		{
			while (it != max_ind) {
				m = max(m, *max_ind - *it);
				++it;
			}
			it = max_ind+1;
			max_ind = max_element(it, prices.end());
			// it = max_ind;
		}

		/*
		for (; it != prices.cend(); ++it)
		{
		 //   int max_ = 0;
			int buy = *b;

			auto max_ind = max_element(it, prices.cend());

			if (max_ind != prices.end()) {
				m = max(m, *max_ind - buy);
			}
			++b;
		}
		*/
		return m;

	}
};
int main() {

	TreeNode n1, n2;
	n1.val = 1;
	n1.left = nullptr;
	n1.right = new TreeNode(2, nullptr, nullptr);

	n2.val = 1;
	n2.left = new TreeNode(2, nullptr, nullptr);
	n2.right = nullptr;

	vector<int> vv({ 7,1,5,3,6,4 });
	Solutiondd d;
	cout << d.maxProfit(vv) << endl;
	//[1,2,2,3,null,null,3,4,null,null,4]
	//[3, 9, 20, null, null, 15, 7]

	//[1, 2, 2, 3, 4, 4, 3]
	//[1, 2, 2, null, 3, null, 3]
	
	
	/*
	n.val = 1;
	n.left  = new TreeNode(2, new TreeNode(3, nullptr, nullptr), new TreeNode(4, nullptr, nullptr));
	n.right = new TreeNode(2, new TreeNode(4, nullptr, nullptr), new TreeNode(3, nullptr, nullptr));
	*/
	
	/*
	n.val = 1;
	n.left = new TreeNode(1,nullptr, nullptr);
	n.right = nullptr;
	*/
	
	/*
	n.val = 1;
	n.left  = new  TreeNode(2, nullptr, new TreeNode(3, nullptr, nullptr));
	n.right = new TreeNode(2, nullptr, new TreeNode(3, nullptr, nullptr));
	*/
	
	/*
	n.val = 3;
	n.left  = new TreeNode(9, nullptr, nullptr);
	n.right = new TreeNode(20, new TreeNode(15, nullptr, nullptr), new TreeNode(7, nullptr, nullptr));
	*/
	
	/*
	n.val = 1;
	n.left = nullptr;
	n.right = new TreeNode(2, nullptr, nullptr);
	*/

	/*
	n.val = 1;
	n.left = nullptr;
	n.right = new TreeNode(2, nullptr, new TreeNode(3, nullptr, nullptr));
	*/


	/*
	Solution_same t;
	cout << t.isSameTree(&n1, &n2) << endl;
	*/
	/*

	vector < vector<char>> g1({ {'1', '1', '1', '1', '0'},{'1', '1', '0', '1', '0'},{'1', '1', '0', '0', '0'},{'0', '0', '0', '0', '0'} });
	vector < vector<char>> g2({ {'1', '1', '0', '0', '0'},{'1', '1', '0', '0', '0'},{'0', '0', '1', '0', '0'},{'0', '0', '0', '1', '1'} });

	vector < vector<char>> g3({ { '1', '0', '1', '1', '0', '1', '1'} });

	vector < vector<char>> g4({ { '1', '1', '1'}, {'0', '1', '0'},{'0', '1', '0'} });

	vector < vector<char>> g5({{'1'}, {'1'}});
	Solution1 s;
	Solution ss;
	//cout << s.numIslands(g1) << endl;
	cout <<"NUMBER: " << ss.numIslands(g3) << endl;
	//cout << s.numIslands(g3) << endl;

	/*
	graph g(10);
	g.add_edge(0, 1);
	g.add_edge(0, 3);
	g.add_edge(1, 2);
	g.add_edge(2, 4);
	g.add_edge(4, 5);
	g.add_edge(3, 6);
	/*
	g.add_edge(0, 1);
	g.add_edge(0, 2);
	g.add_edge(1, 2);
//	g.add_edge(2, 0);
	g.add_edge(2, 3);
	g.add_edge(3, 3);
	*/
	/*
	g.bfs(0);
	g.dfs_rec(0);
	*/
	return 0;
}