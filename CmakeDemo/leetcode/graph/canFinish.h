#include<vector>
#include<queue>

using namespace std;

class Solution {
public:
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