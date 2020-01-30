#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1)
        {
            return s;
        }
        vector<string> rows(min(numRows, (int)s.size()));
        int cur_row = 0;
        bool going_down = false;

        /*for (char c: s)
        {
            vector[cur_row] += c;
            if (cur_row == 0 || cur_row == numRows - 1)
            {
                going_down = !going_down;
            }

            cur_row += going_down ? 1 : -1;
        }*/
        int step = 2 * numRows - 2;
        int index = 0;
        int len = s.size();
        int add = 0;
        string ret;
        for (int i = 0; i < numRows; ++i)
        {
            index = i;
            add = i * 2;
            while (index < len)
            {
                ret += s[index];
                add = step - add;
                index += (i == 0 || i == numRows - 1) ? step : add;
            }

        }

        return ret;

        //string ret;
        //for (string str : rows)
        //{
        //    ret += str;
        //}

        //return ret;
    }
};

void test()
{
    Solution s;
    cout << s.convert("LEETCODEISHIRING", 3);
}