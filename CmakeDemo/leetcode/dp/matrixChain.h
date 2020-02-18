#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int matrixChain(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> s(n, vector<int>(n));
        vector<vector<int>> m(n, vector<int>(n));
        return dp(m, s, nums);
    }

    int dp(vector<vector<int>> m, vector<vector<int>> s, vector<int>& nums)
    {
        for (int i = 0; i < m.size(); ++i)
        {
            m[i][i] = 0;
        }

        for (int r = 2; r < m.size(); ++r)
        {
            for (int i = 1; i < m.size() - r + 1; ++i)
            {
                int j = i + r - 1;
                m[i][j] = m[i + 1][j] + nums[i - 1] * nums[i] * nums[j];
                s[i][j] = i;

                for (int k = i + 1; k < j; ++k)
                {
                    int t = m[i][k] + m[k + 1][j] + nums[i - 1] * nums[k] * nums[j];
                    if (t < m[i][j])
                    {
                        m[i][j] = t;
                        s[i][j] = k;
                    }
                }
            }
        }

        return m[1][m.size() - 1];
    }

    int backtrack(int i, int j, vector<vector<int>>& m, vector<vector<int>>& s, vector<int>& nums)
    {
        if (m[i][j] > 0)
        {
            return m[i][j];
        }

        if (i == j)
        {
            return 0;
        }

        int u = backtrack(i, i, m, s, nums) + backtrack(i + 1, j, m, s, nums) + nums[i - 1] * nums[i] * nums[j];
        s[i][j] = i;

        for (int k = i + 1; k < j; ++k)
        {
            int t = backtrack(i, k, m, s, nums) + backtrack(k + 1, j, m, s, nums) + nums[i - 1] * nums[k] * nums[j];

            if (t < u)
            {
                u = t;
                s[i][j] = k;
            }
        }

        m[i][j] = u;
        return u;
    }
};

void test()
{
    vector<int> nums = { 30,35,15,5,10,20,25 };
    Solution solu;
    cout << solu.matrixChain(nums);
}