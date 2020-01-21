#include <rbtree.h>
#include <iostream>

using namespace std;

int main()
{
    RBTree<int, string> tree;
    tree.Insert(1, "hello");
    tree.Insert(2, "hello");
    tree.Insert(3, "hello");
    tree.Insert(4, "hello");
    tree.InOrder();
}