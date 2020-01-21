//
// Created by peter on 2020/1/20.
//

#ifndef CMAKEDEMO_THREADSAFE_NOLOCK_LINK_H
#define CMAKEDEMO_THREADSAFE_NOLOCK_LINK_H

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

struct Node
{
    int val;
    Node* next;
};

std::atomic<Node*> list_head(nullptr);

void append(int val)
{
    Node* old_head = list_head;
    Node* newNode = new Node{ val, old_head };
    while (!list_head.compare_exchange_weak(old_head, newNode))
    {
        newNode->next = old_head;
    }
}

void test()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 100; ++i)
    {
        threads.emplace_back(std::thread(append, i));
    }
    for (auto & th : threads)
    {
        th.join();
    }
    for (Node *it = list_head; it != nullptr; it=it->next)
    {
        std::cout << it->val << '\t';
    }
}

#endif //CMAKEDEMO_THREADSAFE_NOLOCK_LINK_H
