#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <condition_variable>

using namespace std;


bool can_partition(vector<int> & nums)
{
    int sum = 0;
    for (auto x : nums)
    {
        sum += x;
    }

    if (sum % 2 != 0)
    {
        return false;
    }
    else
    {
        sum /= 2;
    }

    int len = nums.size();

    vector<vector<bool>> dp(len + 1, vector<bool>(sum + 1, false));

    for (int i = 0;  i <= len; ++i)
    {
        dp[i][0] = true;
    }

    for (int i = 1; i <= len; ++i)
    {
        for (int j = 1; j <= sum; ++j)
        {
            if (j >= nums[i - 1])
            {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[len][sum];
}

#include <dp/lcs.h>
#include <unordered_map>
#include <map>

int main()
{

    vector<string> req_skills = {"java", "nodejs", "reactjs"};
    vector<vector<string>>  people = {{"java"},{"nodejs"},{"nodejs","reactjs"}};
    int n = req_skills.size();
    int full = 1 << n;
    map<string, int> skills;
    vector<int> dp(full, -1);
    map<int, vector<int>> team;

    for (int i = 0; i < n; ++i)
    {
        skills[req_skills[i]] = i;
    }

    dp[0] = 0;
    team[0] = vector<int>();

    for (int i = 0; i < people.size(); ++i)
    {
        int idx = 0;
        for (auto s : people[i])
        {
            if (skills.count(s))
            {
                idx = idx | (1 << skills[s]);
            }
        }

        for (int j = 0; j < full; ++j)
        {
            if (dp[j] >= 0)
            {
                int x = j | idx;
                if (dp[x] == -1 || dp[x] > dp[j] + 1)
                {
                    dp[x] = dp[j] + 1;
                    team[x] = team[j];
                    team[x].push_back(i);
                }
            }
        }
    }

    std::cout << test;
}