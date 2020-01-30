#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.size();
        if (len < 2)
        {
            return s;
        }

        int start = 0;
        int max = 1;

        vector<vector<int>> dp(len, vector<int>(len));
        for (int i = 0; i < len; ++i)
        {
            dp[i][i] = 1;
            if (i < len - 1 && s[i] == s[i+1])
            {
                dp[i][i + 1] = 1;
                max = 2;
                start = i;
            }
        }

        for (int tmp_len = 3; tmp_len <= len; tmp_len++)
        {
            for (int i = 0; i + tmp_len - 1 < len; ++i)
            {
                int j = i + tmp_len - 1;
                if (s[i] == s[j] && dp[i+1][j - 1] == 1)
                {
                    dp[i][j] = 1;
                    max = tmp_len;
                    start = i;
                }
            }
        }

        return s.substr(start, max);
    }
};

void test()
{
    Solution s;
    cout << s.longestPalindrome("babad");
}