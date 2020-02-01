#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        vector<int> curr;
        vector<bool> visited(nums.size(), false);

        back_track(res, nums, curr, visited, 0);

        return res;
    }

private:
    void swap(int& a, int& b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    void back_track(vector<vector<int>> &res, vector<int>& nums, vector<int>& curr, vector<bool> visited, int i)
    {
        if (curr.size() == nums.size())
        {
            res.push_back(curr);

            return;
        }

        for (int i = 0; i < nums.size(); ++i)
        {
            if (visited[i]) continue;
            if (i > 0 && !visited[i - 1] && nums[i] == nums[i - 1])
            {
                continue;
            }
            curr.push_back(nums[i]);
            visited[i] = true;
            back_track(res, nums, curr, visited, i + 1);
            visited[i] = false;
            curr.pop_back();
        }
    }
};

void test()
{
    vector<int> nums({1, 1, 2, 2});
    Solution ss;
    vector<vector<int>> res = ss.permuteUnique(nums);
    for (vector<int> & one : res)
    {
        for (int x : one)
        {
            cout << x << '\t';
        }

        cout << endl;
    }
    cout << "test" << endl;
}