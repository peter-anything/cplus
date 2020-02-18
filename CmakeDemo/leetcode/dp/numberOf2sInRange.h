#include<vector>
#include<algorithm>
#include<iostream>

class Solution {
public:
    int numberOf2sInRange(int n) {
        std::vector<int> num_arr;
        while (n > 0)
        {
            num_arr.push_back(n % 10);
            n /= 10;
        }

        std::reverse(num_arr.begin(), num_arr.end());
        
        int num_size = num_arr.size();
        std::vector<std::vector<int>> dp(num_size, std::vector<int>(2));
        dp[0][0] = (int)num_arr[0] > 2;
        dp[0][1] = (int)num_arr[0] == 2;

        int v = num_arr[0];

        for (int i = 1; i < num_size; v = num_arr[i] + 10 * v, ++i)
        {
            dp[i][0] = dp[i][1] = 0;
            for (int j = 0; j < num_arr[i]; ++j)
            {
                dp[i][0] += dp[i - 1][0] + dp[i - 1][1] + (j == 2) * (v + 1);
            }

            dp[i][1] += dp[i - 1][1] + (num_arr[i] == 2);
            for (int j = num_arr[i]; j < 10; ++j)
            {
                dp[i][0] += dp[i - 1][0] + (j == 2) * v;
            }
        }

        return dp[num_size - 1][0] + dp[num_size - 1][1];
    }
};

void test()
{
    Solution solu;
    std::cout << solu.numberOf2sInRange(25);

}