//
// Created by peter on 2020/1/21.
//

#ifndef CMAKEDEMO_BPLUSTREE_H
#define CMAKEDEMO_BPLUSTREE_H

#define M 3 //The minimum degree of this B+ tree
#define KEY_NUM_MAX 2*M - 1//Maximum Key Number
#define KEY_NUM_MIN M - 1//Minimum Key Number
#include<iostream>
#include<queue>

using namespace std;

enum NodeType
{
    NODE_TYPE_INTERNAL,
    NODE_TYPE_LEAF
};

struct User
{
    int id;
    string name;
    unsigned short age;
    unsigned short sex;
    string mobile;
    string address;
    User(int id, string name) : id(id), name(name) {}
};

struct BPlusTreeNode
{
    NodeType node_type = NODE_TYPE_LEAF;
    int count = 0; //内部节点是键数量，叶子节点是数据数量
    BPlusTreeNode* parent = nullptr;
    int parent_index = -1;
};

struct BPlusTreeInternalNode : public BPlusTreeNode
{
    int keys[KEY_NUM_MAX];
    BPlusTreeNode* children[KEY_NUM_MAX + 1] = { nullptr };
    BPlusTreeInternalNode()
    {
        this->node_type = NODE_TYPE_INTERNAL;
    }

    // key小合并大的
    void merge(BPlusTreeInternalNode* other)
    {
        for (int i = 0; i < other->count; ++i)
        {
            this->keys[i + this->count] = other->keys[i];
        }

        for (int i = 0; i < other->count + 1; ++i)
        {
            this->children[i + this->count] = other->children[i];
        }

        this->count += other->count;
    }

    BPlusTreeNode* remove_by_index(int index)
    {
        BPlusTreeInternalNode* parent = static_cast<BPlusTreeInternalNode*>(this->parent);
        if (parent == nullptr && this->count == 1)
        {
            BPlusTreeNode* ret = new BPlusTreeNode;
            ret = this->children[0];
            delete this;
            return ret;
        }

        for (int i = index; i < this->count - 1; ++i)
        {
            this->keys[i] = this->keys[i + 1];
            this->children[i + 1] = this->children[i + 2];
        }

        --this->count;

        if (this->count < KEY_NUM_MIN)
        {
            if (parent != nullptr)
            {
                //先看左孩子
                if (this->parent_index > 1 && parent->children[this->parent_index - 1]->count > KEY_NUM_MIN)
                {

                }
                //查看右孩子
                else if (this->parent_index < parent->count && parent->children[this->parent_index + 1]->count > KEY_NUM_MIN)
                {
                }
                else
                {
                    // 合并
                    if (this->parent_index > 1)
                    {
                    }
                    else if (this->parent_index < parent->count)
                    {
                        this->add_key(parent->keys[this->parent_index]);
                        this->merge(static_cast<BPlusTreeInternalNode*>(parent->children[this->parent_index + 1]));
                        //parent->
                        return parent->remove_by_index(this->parent_index);
                    }
                }
            }
        }
    }

    int add_key(int key)
    {
        // 查找插入的位置
        int i = 0;
        while (this->keys[i] < key && i < this->count)
        {
            ++i;
        }

        if (i == this->count)
        {
            this->keys[this->count] = key;
        }
        else
        {
            int j;
            for (j = this->count; j > i; --j)
            {
                this->keys[j] = this->keys[j - 1];
                this->children[j + 1] = this->children[j];
            }
            this->keys[i] = key;
        }

        ++this->count;

        return i;
    }
};

struct BPlusTreeLeafNode : public BPlusTreeNode
{
    BPlusTreeLeafNode* prev;
    BPlusTreeLeafNode* next;

    User *users[KEY_NUM_MAX];

    // key小合并大的
    void merge(BPlusTreeLeafNode* other)
    {
        for (int i = 0; i < other->count; ++i)
        {
            this->users[i + this->count] = other->users[i];
        }

        this->count += other->count;
    }

    void remove(User *user)
    {
        int i = 0;
        while (i < this->count && users[i]->id != user->id)
        {
            ++i;
        }

        for (int j = i; j < this->count - 1; ++j)
        {
            this->users[j] = this->users[j + 1];
        }

        --this->count;
    }

    int insert(User *user)
    {
        int i = 0;
        while (i < this->count && users[i]->id < user->id)
        {
            ++i;
        }
        
        if (i == this->count)
        {
            this->users[this->count] = user;
        }
        else
        {
            int j;
            for (j = this->count; j > i; --j)
            {
                this->users[j] = this->users[j - 1];
                this->users[j + 1] = this->users[j];
            }
            this->users[i] = user;
        }

        ++this->count;

        return i;
    }
};

class BPlusTree
{
private:
    BPlusTreeNode* root = nullptr;
    BPlusTreeLeafNode* head = nullptr;
    BPlusTreeLeafNode* tail = nullptr;
public:
    BPlusTree() : head(new BPlusTreeLeafNode), tail(new BPlusTreeLeafNode)
    {
        head->prev = tail;
        head->next = tail;
        tail->prev = head;
        tail->next = head;
    }

    void list_append(BPlusTreeLeafNode* new_list_node)
    {
        tail->prev->next = new_list_node;
        new_list_node->prev = tail->prev;
        new_list_node->next = tail;
        tail->prev = new_list_node;
    }

    void list_insert_after(BPlusTreeLeafNode* iter, BPlusTreeLeafNode* new_list_node)
    {
        new_list_node->prev = iter;
        new_list_node->next = iter->next;
        iter->next->prev = new_list_node;
        iter->next = new_list_node;
    }

    void list_remove(BPlusTreeLeafNode* iter)
    {
        iter->prev->next = iter->next;
        iter->next->prev = iter->prev;

        delete iter;
        iter = nullptr;
    }

    BPlusTreeLeafNode* leaf_search(BPlusTreeNode* node, int key)
    {
        if (node->node_type == NODE_TYPE_LEAF)
        {
            return static_cast<BPlusTreeLeafNode*>(node);
        }
        int i = 0;
        BPlusTreeInternalNode* curr_node = static_cast<BPlusTreeInternalNode*>(node);
        while (curr_node->keys[i] <= key && i < curr_node->count)
        {
            ++i;
        }

        return leaf_search(curr_node->children[i], key);
    }

    void split(BPlusTreeNode* node)
    {
        //分裂

        if (node->node_type == NODE_TYPE_LEAF)
        {
            BPlusTreeLeafNode* curr_node = static_cast<BPlusTreeLeafNode*>(node);
            BPlusTreeLeafNode* new_node = new BPlusTreeLeafNode;
            //复制
            for (int i = 0; i < M; ++i)
            {
                new_node->users[i] = curr_node->users[i + KEY_NUM_MIN];
                curr_node->users[i + KEY_NUM_MIN] = nullptr;
            }

            new_node->count = M;
            curr_node->count = M - 1;
            new_node->node_type = curr_node->node_type;

            list_insert_after(curr_node, new_node);

            if (curr_node->parent == nullptr)
            {
                BPlusTreeInternalNode* new_root = new BPlusTreeInternalNode;
                new_root->children[0] = curr_node;
                new_root->children[1] = new_node;
                new_root->keys[0] = new_node->users[0]->id;
                new_root->count = 1;
                new_node->parent = curr_node->parent = new_root;
                new_node->parent_index = curr_node->parent_index = 0;
                root = new_root;
            }
            else
            {
                new_node->parent = curr_node->parent;
                BPlusTreeInternalNode* parent = static_cast<BPlusTreeInternalNode*>(curr_node->parent);
                int pos = parent->add_key(new_node->users[0]->id);
                parent->children[pos + 1] = new_node;
                new_node->parent_index = pos;

                if (parent->count == KEY_NUM_MAX)
                {
                    split(parent);
                }
            }
        }
        else
        {
            BPlusTreeInternalNode* curr_node = static_cast<BPlusTreeInternalNode*>(node);
            //复制
            BPlusTreeInternalNode* new_node = new BPlusTreeInternalNode;
            //复制后面两个关键字
           for (int i = 0; i < KEY_NUM_MIN; ++i)
           {
               new_node->keys[i] = curr_node->keys[i + KEY_NUM_MIN + 1];
               curr_node->keys[i + KEY_NUM_MIN + 1] = -1;
           }
           //复制后面两个关键字
           int p_index = 0;
           for (int i = 0; i < KEY_NUM_MIN + 1; ++i)
           {
               new_node->children[i] = curr_node->children[i + KEY_NUM_MIN + 1];
               new_node->children[i]->parent = new_node;
               if (i < 2)
               {
                   new_node->children[i]->parent_index = p_index;
               }
               else
               {
                   new_node->children[i]->parent_index = ++p_index;
               }
               
               curr_node->children[i + KEY_NUM_MIN + 1] = nullptr;
           }

            new_node->count = M - 1;
            curr_node->count = M - 1;

            if (curr_node->parent == nullptr)
            {
                BPlusTreeInternalNode* new_root = new BPlusTreeInternalNode;
                new_root->children[0] = curr_node;
                new_root->children[1] = new_node;
                new_root->keys[0] = curr_node->keys[KEY_NUM_MIN];
                new_root->count = 1;
                new_node->parent = curr_node->parent = new_root;
                new_node->parent_index = curr_node->parent_index = 0;
                root = new_root;
            }
            else
            {
                new_node->parent = curr_node->parent;
                BPlusTreeInternalNode* parent = static_cast<BPlusTreeInternalNode*>(curr_node->parent);
                int pos = parent->add_key(new_node->keys[0]);
                parent->children[pos + 1] = new_node;
                new_node->parent_index = pos;
                if (parent->count == KEY_NUM_MAX)
                {
                    split(parent);
                }
            }
            /*BPlusTreeLeafNode* new_list_node = new BPlusTreeLeafNode(new_node);
            list_append(new_list_node);*/
        }
    }

    void insert(User *user)
    {
        if (root == nullptr)
        {
            BPlusTreeLeafNode* new_root = new BPlusTreeLeafNode();
            new_root->count = 1;
            new_root->node_type = NODE_TYPE_LEAF;
            new_root->users[0] = user;
            root = new_root;

            list_append(new_root);

            return;
        }
        else
        {
            BPlusTreeLeafNode* curr_node = leaf_search(root, user->id);
            //// 查找插入的位置
            curr_node->insert(user);
            if (curr_node->count == KEY_NUM_MAX)
            {
                split(curr_node);
            }
        }
    }

    void traverse()
    {
        BPlusTreeLeafNode* curr = head->next;
        while (curr != head)
        {
            /*BPlusTreeNode* leaf = curr->leaf;*/
            for (int i = 0; i < curr->count; ++i)
            {
                std::cout << curr->users[i]->id << std::endl;
            }
            curr = curr->next;
        }
    }

    void test()
    {
        BPlusTreeInternalNode* new_root = static_cast<BPlusTreeInternalNode*>(root);
        queue< BPlusTreeInternalNode*> Q;
        Q.push(new_root);
        for (int i = 0; i < new_root->count; ++i)
        {
            std::cout << new_root->keys[i] << '\t';
        }
        std::cout << std::endl;

        while (!Q.empty())
        {
            BPlusTreeInternalNode* curr_node = Q.front();
            Q.pop();
            
            if (curr_node->node_type == NODE_TYPE_INTERNAL)
            {
                for (int i = 0; i < curr_node->count + 1; ++i)
                {
                    if (curr_node->children[i]->node_type == NODE_TYPE_INTERNAL)
                    {
                        BPlusTreeInternalNode* node = static_cast<BPlusTreeInternalNode*>(curr_node->children[i]);
                        Q.push(node);
                        for (int i = 0; i < node->count; ++i)
                        {
                            std::cout << node->keys[i] << '\t';
                        }
                        std::cout << std::endl;
                    }
                    if (curr_node->children[i]->node_type == NODE_TYPE_LEAF)
                    {
                        BPlusTreeLeafNode* node = static_cast<BPlusTreeLeafNode*>(curr_node->children[i]);
                        //
                        for (int i = 0; i < node->count; ++i)
                        {
                            std::cout << node->users[i]->id << '\t';
                        }
                        std::cout << std::endl;
                    }
                }
            }
        }
        std::cout << std::endl;
    }

    void remove(User* user)
    {
        if (root == nullptr)
        {
            return;
        }
        BPlusTreeLeafNode* curr_node = leaf_search(root, user->id);
        if (curr_node->count > KEY_NUM_MIN)
        {
            curr_node->remove(user);
        }
        else
        {
            BPlusTreeInternalNode* parent = static_cast<BPlusTreeInternalNode*>(curr_node->parent);
            //如果左右兄弟有大于最小数量，借
            if (curr_node->prev != nullptr && curr_node->prev->parent == parent && curr_node->prev->count > KEY_NUM_MIN)
            {
                User* brother_user = curr_node->prev->users[curr_node->prev->count - 1];
                curr_node->remove(user);
                curr_node->prev->remove(brother_user);
                curr_node->insert(brother_user);
                //更新父亲节点
                parent->keys[curr_node->parent_index] = brother_user->id;
            }
            else if (curr_node->next != nullptr && curr_node->next->parent == parent && curr_node->next->count > KEY_NUM_MIN)
            {
                User* brother_user = curr_node->next->users[0];
                curr_node->remove(user);
                curr_node->next->remove(brother_user);
                curr_node->insert(brother_user);
                //更新父亲节点
                int parent_index = curr_node->parent_index + 1 > parent->count ? curr_node->parent_index : curr_node->parent_index + 1;
                parent->keys[curr_node->parent_index + 1] = curr_node->next->users[0]->id;
            }
            else
            {
                //合并
                if (curr_node->prev != nullptr && curr_node->prev->parent == parent)
                {
                    curr_node->remove(user);
                    curr_node->prev->merge(curr_node);
                    //delete curr_node;
                    list_remove(curr_node);
                    root = parent->remove_by_index(curr_node->parent_index);
                }
                else if (curr_node->next != nullptr && curr_node->next->parent == parent)
                {
                    curr_node->remove(user);
                    curr_node->merge(curr_node->next);
                    //delete curr_node->next;
                    list_remove(curr_node->next);
                    root = parent->remove_by_index(curr_node->parent_index);
                }
            }
        }
    }
};

void test()
{
    BPlusTree bptree;
    //for (int i = 0; i < 100; ++i)
    //{
    //    User* u = new User(i + 1, "peter" + i);
    //    bptree.insert(u);

    //}

    ////bptree.traverse();
    //bptree.test();
    //return;
    User* user1 = new User(10, "peter1");
    User* user2 = new User(20, "peter2");
    User* user3 = new User(30, "peter3");
    User* user4 = new User(40, "peter4");
    User* user5 = new User(50, "peter5");

    User* user6 = new User(60, "peter6");
    User* user7 = new User(70, "peter7");
    User* user8 = new User(80, "peter8");
    User* user9 = new User(90, "peter9");
    User* user10 = new User(100, "peter10");

    User* user11 = new User(110, "peter11");
    User* user12 = new User(120, "peter12");
    User* user13 = new User(71, "peter7.1");
    User* user14 = new User(72, "peter7.2");
    User* user15 = new User(73, "peter7.3");

    bptree.insert(user1);
    bptree.insert(user2);
    bptree.insert(user3);
    bptree.insert(user4);
    bptree.insert(user5);

    bptree.insert(user6);
    bptree.insert(user7);
    bptree.insert(user8);
    bptree.insert(user9);
    bptree.insert(user10);

    bptree.insert(user11);
    bptree.insert(user12);
    bptree.insert(user13);
    bptree.insert(user14);
    bptree.insert(user15);
    //
    bptree.remove(user11);
    bptree.remove(user12);
    bptree.remove(user10);
    bptree.insert(new User(61, "test"));
    bptree.remove(user3);
    bptree.remove(user1);
    bptree.test();
    std::cout << "-------------------------" << std::endl;
    bptree.traverse();
    //bptree.traverse();
  /*  bptree.insert(10);
    bptree.insert(20);
    bptree.insert(30);
    bptree.insert(40);
    bptree.insert(50);
    bptree.insert(60);
    bptree.insert(70);
    bptree.insert(80);
    bptree.insert(90);
    bptree.insert(100);
    bptree.insert(110);
    bptree.insert(120);
    bptree.insert(71);
    bptree.insert(72);
    bptree.insert(73);
    bptree.traverse();*/
}

#endif