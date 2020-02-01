#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        back_track(res, nums, 0);

        return res;
    }

private:
    void swap(int& a, int& b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    void back_track(vector<vector<int>> &res, vector<int>& nums, int i)
    {
        if (i == nums.size() - 1)
        {
            res.push_back(nums);

            return;
        }

        for (int j = i; j < nums.size(); ++j)
        {
            if (i == j)
            {
                back_track(res, nums, i + 1);
                continue;
            }

            int k;
            for (k = j - 1; k >= i; --k)
            {
                if (nums[k] == nums[j])
                {
                    break;
                }
            }

            if (k != i - 1)
            {
                continue;
            }
            swap(nums[i], nums[j]);
            back_track(res, nums, i + 1);
            swap(nums[i], nums[j]);
        }
    }
};

void test()
{
    vector<int> nums({1, 1, 2, 2});
    Solution ss;
    vector<vector<int>> res = ss.permute(nums);
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