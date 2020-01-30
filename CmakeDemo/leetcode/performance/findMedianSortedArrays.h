#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        //找前n大,如果是奇数7， 找出第四个即可（3）
        //如果是偶数8， 找出第四和第五（3， 4）
        int len1 = nums1.size();
        int len2 = nums2.size();
        int left = (len1 + len2 + 1) / 2;
        int right = (len1 + len2 + 2) / 2;

        int m = get_k_th(nums1, 0, len1 - 1, nums2, 0, len2 - 1, left);
        int n = get_k_th(nums1, 0, len1 - 1, nums2, 0, len2 - 1, right);
        return (get_k_th(nums1, 0, len1 - 1, nums2, 0, len2 - 1, left) + get_k_th(nums1, 0, len1 - 1, nums2, 0, len2 - 1, right)) / 2.0;
    }

private:
    int get_k_th(vector<int>& nums1, int start1, int end1, vector<int>& nums2, int start2, int end2, int k)
    {
        int len1 = end1 - start1 + 1;
        int len2 = end2 - start2 + 1;

        if (len1 > len2)
        {
            return get_k_th(nums2, start2, end2, nums1, start1, end1, k);
        }

        if (len1 == 0)
        {
            return nums2[start2 + k - 1];
        }

        if (k == 1)
        {
            return min(nums1[start1], nums2[start2]);
        }

        int i = start1 + min(len1, (k) / 2) - 1;
        int j = start2 + min(len2, (k) / 2) - 1;

        if (nums1[i] > nums2[j])
        {
            return get_k_th(nums1, start1, end1, nums2, j + 1, end2, k - (j - start2 + 1));
        }
        else
        {
            return get_k_th(nums1, i + 1, end1, nums2, start2, end2, k - (i - start1 + 1));
        }
    }
};

void test()
{
    vector<int> a({ 1, 2 });
    vector<int> b({ -1, 3 });

    Solution s;
    cout << s.findMedianSortedArrays(a, b);
}