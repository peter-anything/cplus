#include<vector>

using namespace std;

class UnionFindSet
{
private:
    vector<int> parents;
    vector<int> ranks;
public:
    UnionFindSet(int n)
    {
        ranks = vector<int>(n + 1, 0);
        parents = vector<int>(n + 1, 0);

        for (int i = 0; i < parents.size(); ++i)
        {
            parents[i] = i;
        }
    }

    bool Union(int u, int v)
    {
        int pu = Find(u);
        int pv = Find(v);

        if (pu == pv) return false;

        if (ranks[pv] < ranks[pu])
        {
            parents[pv] = pu;
        }
        else if (ranks[pu] < ranks[pv])
        {
            parents[pu] = pv;
        }
        else
        {
            parents[pv] = pu;
            ranks[pu] += 1;
        }

        return true;
    }

    int Find(int u)
    {
        if (u != parents[u])
        {
            parents[u] = Find(parents[u]);
        }

        return parents[u];
    }
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        UnionFindSet ufs(edges.size());
        for (auto edge : edges)
        {
            if (!ufs.Union(edge[0], edge[1]))
            { 
                return edge;
            }
        }

        return {};
    }
}; 