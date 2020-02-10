#include<vector>
#include<iostream>

using namespace std;

class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int result = 0;
        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid[0].size(); ++j)
            {
                if (grid[i][j] == 0)
                {
                    int val = 1;
                    dfs(grid, i, j, val);
                    result += val;
                }
            }
        }

        return result;
    }

    void dfs(vector<vector<int>>& grid, int i, int j, int &val) {
        if (i >= grid.size() || j >= grid[0].size())
        {
            val = 0;
            return;
        }

        if (grid[i][j] != 0)
        {
            return;
        }
        grid[i][j] = -1;
        dfs(grid, i + 1, j, val);
        dfs(grid, i - 1, j, val);
        dfs(grid, i, j + 1, val);
        dfs(grid, i, j - 1, val);
    }
};

void test()
{
    vector<vector<int>> grid = { {1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1} };
    Solution solu; 
    cout << solu.closedIsland(grid);
}