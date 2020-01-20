#include <threadsafe_stack.h>
#include "tree.h"
#include <iostream>

int main()
{
    BinaryTree<int> tree;
    tree.Insert(10);
    tree.Insert(9);
    std::cout << "hello " << std::endl;
}
