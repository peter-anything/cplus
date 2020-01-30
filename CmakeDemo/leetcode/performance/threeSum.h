#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        cout << "test" << endl;
        int len = nums.size();
        int left = 0, right = 0;
        vector<vector<int>> res;

        for (int i = 0; i < nums.size(); ++i)
        {
            left = i + 1;

            if (nums[i] > 0)
            {
                return res;
            }

            if (left == len - 1)
            {
                return res;
            }

            if (i > 0 && nums[i] == nums[i - 1])
            {
                continue;
            }
            right = len - 1;
            int total = 0;
            while (left < right)
            {
                total = nums[i] + nums[left] + nums[right];
                if (total == 0)
                {
                    vector<int> arr({nums[i], nums[left], nums[right]});
                    res.push_back(arr);
                    while (left < right && nums[left] == nums[left + 1])
                    {
                        ++left;
                    }
                    while (left < right && nums[right] == nums[right - 1])
                    {
                        --right;
                    }
                    ++left;
                    --right;
                }
                else if(total > 0)
                {
                    --right;
                }
                else
                {
                    ++left;
                }
            }
        }
        
        return res;
    }
};

void test()
{
    vector<int> nums({ -1, 0, 1, 2, -1, -4 });
    Solution s;
    vector<vector<int>> res = s.threeSum(nums);



    cout << "Test" << endl;
}