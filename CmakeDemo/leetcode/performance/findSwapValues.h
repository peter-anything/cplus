#include<vector>
#include<numeric>
#include<algorithm>

using namespace std;

class Solution {
public:
    vector<int> findSwapValues(vector<int>& array1, vector<int>& array2) {
        int sum1 = accumulate(array1.begin(), array1.end(), 0);
        int sum2 = accumulate(array2.begin(), array2.end(), 0);
        vector<int> result;

        int d = (sum2 - sum1) / 2;
        int i = 0;
        for (int x : array2)
        {
            vector<int>::iterator iter = find(array1.begin(), array1.begin(), x - d);
            if (iter != array1.end())
            {
                int index = distance(array1.begin(), iter);
                result.push_back(index, i);
            }
            ++i;
        }
    }
};