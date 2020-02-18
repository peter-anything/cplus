#include<string>
#include<algorithm>
#include<vector>

using namespace std;

class Solution {
public:
    vector<string> permutation(string S) {
        string perm_str = S;
        sort(perm_str.begin(), perm_str.end());

        vector<string> res;
        vector<bool> visited(perm_str.size(), false);
        string curr;
        back_track(res, perm_str, visited, curr);

        return res;
    }

    void back_track(vector<string>& res, string& perm_str, vector<bool>& visited, string& curr)
    {
        if (curr.size() == perm_str.size())
        {
            res.push_back(curr);
            return;
        }

        for (int i = 0; i < perm_str.size(); ++i)
        {
            if (visited[i]) continue;
            
            if (i > 0 && perm_str[i] == perm_str[i - 1] && !visited[i - 1])
                continue;
            curr.push_back(perm_str[i]);
            visited[i] = true;

            back_track(res, perm_str, visited, curr);

            visited[i] = false;
            curr.pop_back();
        }
    }
};