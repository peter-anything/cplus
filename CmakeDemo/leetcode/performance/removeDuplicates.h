#include<stack>
#include<iostream>
#include<algorithm>

using namespace std;

class Solution {
public:
    string removeDuplicates(string s, int k) {
        stack<pair<char, int>> Q;
        for (char ch : s)
        {
            if (!Q.empty() && Q.top().first == ch)
            {
                ++(Q.top().second);
                if (Q.top().second == k)
                {
                    Q.pop();
                }
            }
            else
            {
                Q.push(make_pair(ch, 1));
            }
        }

        string result;
        while (!Q.empty())
        {
            char c = Q.top().first;
            int cnt = Q.top().second;
            for (int i = 0; i < cnt; ++i)
            {
                result.push_back(c);
            }
            Q.pop();
        }

        reverse(result.begin(), result.end());
        
        return result;
    }
};

void test()
{
    string s = "abcd";
    int k = 2;
    Solution solu;
    cout << solu.removeDuplicates(s, k);
}