//
// Created by peter on 2020/1/21.
//

#ifndef CMAKEDEMO_BGTREE_H
#define CMAKEDEMO_BGTREE_H

#include <iostream>

enum RBTreeColor
{
    RED,
    BLACK
};

template<class K, class V>
class RBTreeNode
{
public:
    RBTreeColor color;
    K key;
    V value;
    RBTreeNode<K, V> *left;
    RBTreeNode<K, V> *right;
    RBTreeNode<K, V> *parent;

    RBTreeNode(const K& key = K(), const V& value = V(), const RBTreeColor& color = RED) :
        left(nullptr),
        right(nullptr),
        parent(nullptr),
        key(key),
        value(value),
        color(color)
    {}
};

template<class K, class V>
class RBTree
{
    typedef RBTreeNode<K, V> Node;
private:
    Node* m_root;
    void left_rotate(Node * parent) {
        Node *subR = parent->right;
        Node *subRL = subR->left;

        parent->right = subRL;
        if (subRL) {
            subRL->parent = parent;
        }
        subR->left = parent;
        Node *g_parent = parent->parent;
        parent->parent = subR;
        subR->parent = g_parent;

        if (g_parent == nullptr) {
            m_root = subR;
        } else if (g_parent->left == parent) {
            g_parent->left = subR;
        } else
        {
            g_parent->right = subR;
        }
    }

    void right_rotate(Node * parent) {
        Node *subL = parent->left;
        Node *subLR = subL->right;

        parent->left = subLR;
        if (subLR) {
            subLR->parent = parent;
        }
        subL->right = parent;
        Node *g_parent = parent->parent;
        parent->parent = subL;
        subL->parent = g_parent;

        if (g_parent == nullptr) {
            m_root = subL;
        } else if (g_parent->left == parent) {
            g_parent->left = subL;
        } else
        {
            g_parent->right = subL;
        }
    }
public:
    void InOrder()
    {
        _InOrder(m_root);
    }

    void _InOrder(Node* root)
    {
        if (root)
        {
            std::cout << root->key << " " << root->color << '\t'<< std::endl;
            _InOrder(root->left);
            _InOrder(root->right);
        }
    }

    RBTree() : m_root(nullptr) {}
    ~RBTree() {}
    void Insert(const K& key, const V& value)
    {
        if (m_root == nullptr)
        {
            m_root = new Node(key, value);
            m_root->color = BLACK;

            return;
        }

        Node* p_cur = m_root;
        Node* parent = nullptr;

        while (p_cur)
        {
            if (key < p_cur->key)
            {
                parent = p_cur;
                p_cur = p_cur->left;
            }
            else if (key > p_cur->key)
            {
                parent = p_cur;
                p_cur = p_cur->right;
            }
            else
            {
                return ;
            }
        }

        p_cur = new Node(key, value);
        if (key < parent->key)
        {
            parent->left = p_cur;
        }
        else
        {
            parent->right = p_cur;
        }

        p_cur->parent = parent;

        while (m_root != p_cur && p_cur->parent->color == RED)
        {
            Node *gf = parent->parent;
            if (gf->left == parent)
            {
                Node* uncle = gf->right;
                if (uncle && uncle->color == RED)
                {
                    parent->color = BLACK;
                    uncle->color = BLACK;

                    p_cur = gf;
                    parent = p_cur->parent;
                }
                else {
                    if (parent->right == p_cur)
                    {
                        // 左旋
                        left_rotate(parent);
                        std::swap(parent, p_cur);
                    }
                    gf->color = RED;
                    parent->color = BLACK;
                    // 右旋
                    right_rotate(gf);
                }
            }
            else
            {
                Node *uncle = gf->left;
                if (uncle && uncle->color == RED)
                {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    gf->color = RED;

                    p_cur = gf;
                    parent = p_cur->parent;
                }
                else
                {
                    if (parent->left == p_cur)
                    {
                        // 右旋
                        right_rotate(parent);
                        std::swap(parent, p_cur);
                    }
                    gf->color = RED;
                    parent->color = BLACK;
                    // 左旋
                    left_rotate(gf);
                }
            }
        }
        m_root->color = BLACK;
    }
};

#endif //CMAKEDEMO_BGTREE_H
