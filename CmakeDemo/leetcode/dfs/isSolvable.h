#include<vector>
#include<string>
#include<unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<char, int> rep;
    unordered_map<char, int> lead_zero;
    bool visited[10];
    int carry[10];
public:
    bool isSolvable(vector<string>& words, string result) {
        memset(visited, false, sizeof(visited));
        memset(carry, 0, sizeof(carry));

        for (string& word : words)
        {
            if (word.size() > result.size())
            {
                return false;
            }

            for (char &ch : word)
            {
                rep[ch] = -1;
                lead_zero[ch] = 0;
            }

            if (word.size() > 1)
            {
                lead_zero[word[0]] = 1;
            }
        }

        for (char& ch : result)
        {
            rep[ch] = -1;
            lead_zero[ch] = 0;
        }

        if (result.size() > 1)
        {
            lead_zero[result[0]] = 1;
        }

        return dfs(words, result, 0, 0, result.size());
    }

    bool dfs(vector<string>& words, string& result, int pos, int id, int len)
    {
        if (pos == len)
        {
            return carry[pos] == 0;
        }
        else if (id < words.size())
        {
            int sz = words[id].size();
            if (sz < pos || rep[words[id][sz - pos - 1]] != -1)
            {
                return dfs(words, result, pos, id + 1, len);
            }
            else
            {
                char ch = words[id][sz - pos - 1];
                for (int i = lead_zero[ch]; i < 10; ++i)
                {
                    if (!visited[i])
                    {
                        visited[i] = true;
                        rep[ch] = i;
                        bool check = dfs(words, result, pos, id + 1, len);
                        rep[ch] = -1;
                        visited[i] = false;
                        if (check)
                        {
                            return true;
                        }
                    }
                }
            }

            return false;
        }
        else
        {
            int left = carry[pos];
            for(const string& word : words)
            {
                if (word.size() > pos)
                {
                    left += rep[word[word.size() - pos - 1]];
                }
            }
            char ch = result[result.size() - pos - 1];
            carry[pos + 1] = left / 10;
            left %= 10;
            if (rep[ch] == left)
            {
                return dfs(words, result, pos + 1, 0, len);
            }
            else if (rep[ch] == -1 && !visited[left] && !(lead_zero[ch] == 1 && left == 0))
            {
                visited[left] = true;
                rep[ch] = left;
                bool check = dfs(words, result, pos + 1, 0, len);
                visited[left] = false;
                rep[ch] = -1;
                return check;
            }
            else
            {
                return false;
            }
        }
    }
};

void test()
{

}