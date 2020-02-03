#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty())
        {
            return s.empty();
        }

        int s_len = s.size();
        int p_len = p.size();

        vector<vector<bool>> dp(s_len + 1, vector<bool>(p_len + 1, false));
        dp[0][0] = true; 
        for (int i = 2; i <= p_len; ++i)
        {
            dp[0][i] = dp[0][i - 2] && p[i - 1] == '*';
        }
        for (int i = 1; i <= s_len; ++i)
        {
            for (int j = 1; j <= p_len; ++j)
            {
                if (s[i - 1] == p[j - 1] || p[j - 1] == '.')
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                
                if (p[j - 1] == '*')
                {
                    dp[i][j] = dp[i][j - 2] ||
                        dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.');
                }
            }
        }
        return dp[s.size()][p.size()];
    }

    bool testMatch(string str, string pattern)
    {
        if (str.empty() && pattern.empty())
        {
            return true;
        }

        bool isMatchMany = pattern.size() > 1 && pattern.at(1) == '*';
        if (str.empty() && !pattern.empty())
        {
            if (isMatchMany)
            {
                return testMatch(str, pattern.substr(2));
            }
            return false;
        }

        if (!str.empty() && pattern.empty())
        {
            return false;
        }

        bool first_match = (str.at(0) == pattern.at(0) || pattern.at(0) == '.');

        if (isMatchMany)
        {
            return testMatch(str, pattern.substr(2)) || (first_match && testMatch(str.substr(1), pattern));
        }

        return first_match && testMatch(str.substr(1), pattern.substr(1));
    }
};

void test()
{
    string str1 = "ab";
    string str2 = "c*a*b";

    Solution s;
    cout << s.isMatch(str1, str2);
}