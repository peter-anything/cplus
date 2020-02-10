#include<vector>
#include<iostream>

using namespace std;

class Solution {
private:
    vector<vector<int>> edges;
    vector<bool> visited;
public:
    void dfs(int i)
    {
        visited[i] = true;
        for (int v : edges[i])
        {
            if (!visited[v])
            {
                dfs(v);
            }
        }
    }

    int makeConnected(int n, vector<vector<int>>& connections) {
        if (connections.size() < n - 1)
        {
            return -1;
        }
        edges.resize(n);
        for (vector<int> & conn : connections)
        {
            edges[conn[0]].push_back(conn[1]);
            edges[conn[1]].push_back(conn[0]);
        }
        visited.resize(n);

        int part = 0;
        for (int i = 0; i < n; ++i)
        {
            
            if (!visited[i])
            {
                ++part;
                dfs(i);
            }
        }

        return part - 1;
    }
};

void test()
{
    int n = 6;
    vector<vector<int>> nums = { {0,1},{0,2},{1,2} };
    Solution solu;
    std::cout << solu.makeConnected(n, nums);

}