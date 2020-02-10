#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

class Solution {
public:
    int maxJumps(vector<int>& arr, int d) {
        vector<int> steps(arr.size(), -1);
        int result = 0;
        for (int i = 0; i < arr.size(); ++i)
        {
            dfs(arr, i, d, steps, result);
        }

        return result;
    }

    void dfs(vector<int>& arr, int pos, int d, vector<int>& steps, int& result)
    {
        if (steps[pos] != -1)
        {
            return;
        }

        int l = max(0, pos - d);
        int r = min((int)arr.size() - 1, pos + d);

        int step = 0;
        for (int direction = -1;  direction <= 1; direction += 2)
        {
            for (int i = direction + pos; i <= r && i >= l; i += direction)
            {
                if (arr[pos] <= arr[i])
                {
                    break;
                }
                dfs(arr, i, d, steps, result);
                step = max(step, steps[i]);
            }
        }
        steps[pos] = step + 1;
        result = max(result, steps[pos]);
        /*int len = arr.size();
        if (pos < 0 || pos > len - 1)
        {
            return 1;
        }

        int max_count = 0;

        for (int next = 0; next < step; ++next)
        {
            if (pos + next < len && arr[pos + next] < arr[pos])
            {
               int count = dfs(arr, pos + next, dp, step);
               if (count + 1 > max_count)
               {
                   max_count = count + 1;
               }
            }

            if (pos - next > -1 && arr[pos - next] < arr[pos])
            {
                int count = dfs(arr, pos - next, dp, step);
                if (count + 1 > max_count)
                {
                    max_count = count + 1;
                }
            }
        }

        return max_count;*/
    }
};

void test()
{
    /*[]
    20*/
    vector<int> arr({ 59,8,74,27,92,36,95,78,73,54,75,37,42,15,59,84,66,25,35,61,97,16,6,52,49,18,22,70,5,59,92,85 });
    Solution solu;
    std::cout << solu.maxJumps(arr, 20);
}