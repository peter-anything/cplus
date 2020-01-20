#ifndef CMAKEDEMO_TREE_H
#define CMAKEDEMO_TREE_H

template <class T>
class BinaryTree {
private:
    struct Node {
        std::shared_ptr<T> data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        Node() : left(), right() {}

        Node(T const &value) : data(std::make_shared<T>(value)) {}
    };

public:
    BinaryTree() {}

    void Insert(T const &value) {
        InnerInsert(value, std::move(root));
    }

private:
    std::unique_ptr<Node> root;

    void InnerInsert(T const &value, std::unique_ptr<Node> root) {
        if (root == nullptr)
        {
            std::unique_ptr<Node> new_node(new Node(value));
            root = std::move(new_node);
        }
        else
        {
            if (value <= *root->data)
            {
                if (root->left == nullptr)
                {
                    std::unique_ptr<Node> new_node(new Node(value));
                    root->left = std::move(new_node);
                }
            }
        }
    }
};

#endif