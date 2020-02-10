#include<vector>
#include<unordered_map>
#include<algorithm>
#include<iostream>

using namespace std;

class Solution {
public:
    int minSetSize(vector<int>& arr) {
        unordered_map<int, int> mp;
        for (int i = 0; i < arr.size(); ++i)
        {
            ++mp[arr[i]];
        }

        vector<int> t;
        for (auto x : mp)
        {
            t.push_back(x.second);
        }
        sort(t.begin(), t.end());
        int res = 0, len = arr.size();
        for (int i = t.size() - 1; i >= 0; --i)
        {
            len -= t[i];
            ++res;
            if (len <= arr.size() / 2)
            {
                return res;
            }
        }

        return res;
    }
};

void test()
{
    vector<int> arr({ 3,3,3,3,5,5,5,2,2,7 });
    Solution s;
    std::cout << s.minSetSize(arr);
}