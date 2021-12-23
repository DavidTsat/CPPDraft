class Solution {
	void visit_dfs(vector<vector<char>>& grid, int i, int j) const
	{
		if (i < 0 || j < 0 || i >= grid.size() || j >= grid[i].size() || grid[i][j] == '0')
		{
			return;
		}
		grid[i][j] = '0';

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