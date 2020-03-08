#include<vector>
#include<queue>
#include<unordered_set>

using namespace std;

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges)
    {
        if (n == 1)
        {
            return { 0 };
        }

        vector<unordered_set<int>> adjs(n);
        for (auto edge : edges)
        {
            adjs[edge[0]].insert(edge[1]);
            adjs[edge[1]].insert(edge[0]);
        }

        queue<int> Q;
        for (int i = 0; i < n; ++i)
        {
            if (adjs[i].size() == 1)
            {
                Q.push(i);
            }
        }

        while (n > 2)
        {
            int sz = Q.size();
            n -= sz;

            while (size--> 0)
            {
                auto t = Q.front();
                Q.pop();
                for (auto itm : adjs[t]) 
                {
                    adjs[itm].erase(t);
                    if (adjs[itm].size() == 1)
                    {
                        Q.push(itm);
                    }
                }

            }
        }

        vector<int> res;
        while (!Q.empty())
        {
            res.push_back(Q.front());
            Q.pop();
        }

        return res;
    }

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> inDegree(numCourses, 0);

        vector<vector<int>> dirTable(numCourses, vector<int>());
        for (auto v : prerequisites)
        {
            ++inDegree[v[0]];
            dirTable[v[1]].push_back(v[0]);
        }

        queue<int> Q;
        for (int i = 0; i < inDegree.size(); ++i)
        {
            if (inDegree[i] == 0)
            {
                Q.push(i);
            }
        }

        vector<int> res;
        while (!Q.empty())
        {
            auto tmp = Q.front();
            Q.pop();
            res.push_back(tmp);
            for (auto adjnode : dirTable[tmp])
            {
                if (--inDegree[adjnode] == 0)
                {
                    Q.push(adjnode);
                }
            }
        }

        return res.size() == numCourses;
    }
};