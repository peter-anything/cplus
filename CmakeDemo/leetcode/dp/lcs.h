//
// Created by peter on 2020/1/22.
//

#ifndef CMAKEDEMO_LCS_H
#define CMAKEDEMO_LCS_H

#include <iostream>
#include <string>

using namespace std;

class LCS {
public:
    int length(const string & str1, const string & str2, vector<vector<int>> &veca)
    {
        int i = 0;
        int j = 0;
        int biggest = 0;

        if (str1 == "" || str2 == "")
        {
            return 0;
        }

        for (j = 0; j <= str2.length(); ++j)
        {
            veca[0][j] = 0;
        }

        for (i = 0; i <= str1.length(); ++i)
        {
            veca[i][0] = 0;
        }

        for (i = 1; i <= str1.length(); ++i)
        {
            for(j = 1; j <= str2.length(); ++j)
            {
                if (str1[i - 1] == str2[j - 1])
                {
                    veca[i][j] = veca[i - 1][j - 1] + 1;
                }
                else
                {
                    veca[i][j] = max(veca[i - 1][j], veca[i][j - 1]);
                }
            }
        }

        return veca[str1.length()][str2.length()];
    }

    void print_all_result(const string & str1, const string & str2, int i, int j, vector<vector<int>> &veca, string lcs_str, vector<string> & results)
    {

        while (i > 0 && j > 0)
        {
            if (str1[i - 1] == str2[j - 1])
            {
                lcs_str = lcs_str + str1[i - 1];
                --i;
                --j;
            }
            else {
                if (veca[i - 1][j] > veca[i][j - 1]) {
                    --i;
                } else if (veca[i - 1][j] < veca[i][j - 1]) {
                    --j;
                } else
                {
                    print_all_result(str1, str2, i, j - 1, veca, lcs_str, results);
                    print_all_result(str1, str2, i - 1, j, veca, lcs_str, results);
                    return;
                }
            }
        }

        cout << lcs_str << endl;
        std::reverse(lcs_str.begin(), lcs_str.end());
        results.push_back(lcs_str);
    }

};

void test()
{
    string s1 = "ABCBDAB";
    string s2 = "BDCABA";
    string lcs_str;
    vector<vector<int>> v(s1.length() + 1, vector<int>(s2.length() + 1));
    LCS lcs;
    lcs.length(s1, s2, v);
    vector<string> results;
    lcs.print_all_result(s1, s2, s1.length(), s2.length(), v, lcs_str, results);
    cout << lcs.length(s1, s2, v);
    cout << "test" << endl;
    cout << max(1, 1) << endl;
}

#endif //CMAKEDEMO_LCS_H
