#ifndef CMAKEDEMO_TREE_H
#define CMAKEDEMO_TREE_H

#include <iostream>

template <class T>
class BinaryTree {
public:
    struct Node {
        std::shared_ptr<T> data;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        T test_data;

        Node() : left(), right() {}

        Node(T const &value) : data(std::make_shared<T>(value)), test_data(value) {}
    };

public:
    BinaryTree() {}

    void Insert(T const &value) {
        root = InnerInsert(value, root);
    }

    void Traverse()
    {
        InnerTraverse(root);
        std::cout << std::endl;
    }

public:
    std::shared_ptr<Node> root;

    void InnerTraverse(std::shared_ptr<Node> root)
    {
        if (root != nullptr)
        {
            std::cout << *root->data << '\t';

            if (root->left != nullptr)
            {
                InnerTraverse(root->left);
            }

            if (root->right != nullptr)
            {
                InnerTraverse(root->right);
            }
        }
    }

    std::shared_ptr<Node> InnerInsert(T const &value, std::shared_ptr<Node> root) {
        if (root == nullptr)
        {
            std::shared_ptr<Node> new_node(new Node(value));
            root = new_node;
        }
        else
        {
            if (value <= *root->data)
            {
                if (root->left == nullptr)
                {
                    std::shared_ptr<Node> new_node(new Node(value));
                    root->left = new_node;
                }
                else
                {
                    root->left = InnerInsert(value, root->left);
                }
            }
            else
            {
                if (root->right == nullptr)
                {
                    std::shared_ptr<Node> new_node(new Node(value));
                    root->right = new_node;
                }
                else
                {
                    root->right = InnerInsert(value, root->right);
                }
            }
        }

        return root;
    }
};

#endif