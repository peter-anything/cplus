#include<iostream>
#include<vector>

using namespace std;

struct TrieNode
{
    TrieNode()
    {
    }

    TrieNode* links[26] = { nullptr };

    void put(char key, TrieNode *node)
    {
        links[key - 'a'] = node;
    }

    bool is_one_children()
    {
        int i = 0;
        for (auto link : links)
        {
            if (link != nullptr)
            {
                ++i;
            }

            if (i == 2)
            {
                return false;
            }
        }

        return i == 1;
    }

    bool contains(char key)
    {
        return links[key - 'a'] != nullptr;
    }

    TrieNode* get(char key)
    {
        return links[key - 'a'];
    }

    bool end;
};

class Trie
{
private:
    TrieNode* root = nullptr;
public:
    Trie()
    {
        root = new TrieNode();
    }

    void insert(string word)
    {
        TrieNode* current_node = root;
        for (char ch : word)
        {
            if (!current_node->contains(ch))
            {
                current_node->put(ch, new TrieNode);
            }

            current_node = current_node->get(ch);
        }

        current_node->end = true;
    }

    bool search(string key)
    {
        TrieNode* current_node = root;

        for (char c : key)
        {
            if (current_node->contains(c))
            {
                current_node = current_node->get(c);
            }
            else
            {
                return false;
            }
        }

        return true;
    }

    void get_loggest_common_str(string &ret, string &key)
    {
        TrieNode* current_node = root;
        for (char ch : key)
        {
            if (current_node->contains(ch) && current_node->is_one_children())
            {
                ret += ch;
                current_node = current_node->get(ch);
            }
            else
            {
                return;
            }
        }
    }
};

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        Trie t;
        for (string str : strs)
        {
            t.insert(str);
        }

        string ret;
        t.get_loggest_common_str(ret, strs[0]);

        return ret;
    }
};

void test()
{
    Trie t;
    vector<string> v;
    v.push_back("hello");

    t.insert("hello");
    Solution s;
    cout << s.longestCommonPrefix(v) << endl;
}