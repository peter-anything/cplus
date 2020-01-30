#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        const char* data = s.c_str();
        int len = s.size();
        if (len < 2)
        {
            return len;
        }
        unordered_map<char, int> hash;
        int first = 0, last = 0;
        int max_length = 0;
        while (first < len && last < len)
        {
            char tmp_char = data[last];
            if (hash.find(tmp_char) != hash.end() && hash[tmp_char] >= first)
            {
                first = hash[tmp_char] + 1;
            }
            max_length = max(max_length, last - first + 1);
            hash[tmp_char] = last;
            ++last;
        }

        return max_length;
    }
};


void test()
{
    Solution s;
    cout << s.lengthOfLongestSubstring("abcabcbb");
}