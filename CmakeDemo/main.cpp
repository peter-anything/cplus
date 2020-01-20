#include <threadsafe_stack.h>
#include "tree.h"
#include <iostream>

int main()
{
    BinaryTree<int> tree;
    tree.Insert(10);
    tree.Insert(9);
    tree.Insert(11);
    tree.Insert(8);
    tree.Insert(7);
    tree.Insert(20);
    tree.Traverse();
    std::cout << tree.Height() << std::endl;
    std::cout << tree.IsBalance() << std::endl;

    std::cout << "hello " << std::endl;
}
