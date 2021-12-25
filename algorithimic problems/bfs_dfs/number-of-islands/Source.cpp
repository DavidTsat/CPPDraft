class Solution {
    void dfs(vector<vector<char>>& grid, int i, int j)
    {
        if (i >= grid.size() || i < 0 || j >= grid[0].size() || j < 0 || grid[i][j] == '0')
            return;

        grid[i][j] = '1';


    }

    void cover_island_dfs(vector<vector<char>>& grid, int i, int j)
    {
        if (i >= grid.size() || i < 0 || j >= grid[0].size() || j < 0 || grid[i][j] == '0')
            return;

        grid[i][j] = '0';

        cover_island_dfs(grid, i + 1, j);
        cover_island_dfs(grid, i - 1, j);
        cover_island_dfs(grid, i, j + 1);
        cover_island_dfs(grid, i, j - 1);
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int count = 0;

        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid[0].size(); ++j)
            {
                if (grid[i][j] == '1')
                {
                    cover_island_dfs(grid, i, j);
                    ++count;
                }
            }
        }
        return count;
    }
};
