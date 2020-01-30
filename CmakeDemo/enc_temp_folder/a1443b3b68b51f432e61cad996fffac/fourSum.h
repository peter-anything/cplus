#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int len = nums.size();
        int left = 0;
        int right = len - 1;
        int total;
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        for (int k = 0; k < len - 3; ++k)
        {
            if (nums[k] + nums[k + 1] + nums[k + 2] + nums[k + 3] > target
                ||
                nums[k] + nums[len - 3] + nums[len - 2] + nums[len - 1] < target
                )
            {
                continue;
            }
            if (k > 0 && nums[k] == nums[k - 1])
            {
                continue;
            }

            for (int i = k + 1; i < len - 1; ++i)
            {
                if (i > k + 1 && nums[i] == nums[i - 1])
                {
                    continue;
                }

                if (nums[k] + nums[i] + nums[i + 1] + nums[i + 2] > target
                    ||
                    nums[k] + nums[i] + nums[len - 2] + nums[len - 1] < target
                    )
                {
                    continue;
                }
                left = i + 1;
                right = len - 1;

                while (left < right)
                {
                    total = nums[k] + nums[i] + nums[left] + nums[right];
                    if (total == target)
                    {
                        vector<int> arr({nums[k], nums[i], nums[left], nums[right]});
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
                    else if (total > target)
                    {
                        --right;
                    }
                    else
                    {
                        ++left;
                    }
                }
            }
        }

        return res;
    }
};

void test()
{
    /*[1, -2, -5, -4, -3, 3, 3, 5]
    - 11*/
    vector<int> nums({ 1, -2, -5, -4, -3, 3, 3, 5 });
    Solution s;
    vector<vector<int>> res = s.fourSum(nums, -11);
    cout << "test" << endl;
}