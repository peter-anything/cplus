#include<iostream>
#include<queue>
#include<stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Tree
{
public:
    Tree() {}
public:
    TreeNode* root = NULL;
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if (root == NULL)
        {
            return root;
        }

        if (root == p || root == q)
        {
            return root;
        }

        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if (left != NULL && right != NULL)
        {
            return root;
        }
        else if (left != NULL)
        {
            return left;
        }
        else if (root != NULL)
        {
            return right;
        }

        return NULL;
    }

    bool isCompleteTree(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        TreeNode* node;
        while (!q.empty())
        {
            node = q.front();
            q.pop();
            
            if (node == NULL)
            {
                while (!q.empty())
                {
                    node = q.front();
                    q.pop();
                    if (node != NULL)
                    {
                        return false;
                    }
                }
                return true;
            }

            q.push(node->left);
            q.push(node->right);

        }

        return true;
    }

    vector<int> postorderTraversal(TreeNode* root) {
        if (root == NULL)
        {
            return {};
        }
        stack<TreeNode*> stack;
        stack.push(root);
        vector<int> res;
        while (!stack.empty())
        {
            TreeNode* curr = stack.top();
            stack.pop();
            res.push_back(curr->val);

            if (curr->left != NULL)
            {
                stack.push(curr->left);
            }
            if (curr->right != NULL)
            {
                stack.push(curr->right);
            }
        }

        reverse(res.begin(), res.end());
        return res;
    }

    vector<int> inorderTraversal(TreeNode* root) {
        if (root == NULL)
        {
            return {};
        }

        stack<TreeNode*> stack;
        vector<int> res;
        TreeNode* curr = root;

        while (curr != NULL || !stack.empty())
        {
            if (curr)
            {
                if (curr->left != NULL)
                {
                    stack.push(curr);
                    curr = curr->left;
                }  
                else
                {
                    res.push_back(curr->val);
                    curr = curr->right;
                }
            }
            else
            {
                if (!stack.empty())
                {
                    curr = stack.top();
                    res.push_back(curr->val);
                    stack.pop();
                }

                curr = curr->right;
            }
        }

        return res;
    }
};

void test()
{
    Tree t;
    t.root = new TreeNode(3);
    t.root->left = new TreeNode(1);
    t.root->right = new TreeNode(2);
    Solution solu;
    solu.inorderTraversal(t.root);
}