#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic<bool> ready(false);
std::atomic_flag winner = ATOMIC_FLAG_INIT;

void cout(int m)
{
    while (!ready)
    {
        std::this_thread::yield();
    }

    for (int i = 0; i < 1000000; ++i)
    {

    }
    std::cout << "winner" << m;
}

void test()
{
    std::vector<std::thread> threads;
    for (int i = 0; i <= 10; ++i)
    {
        threads.push_back(std::move(std::thread(cout, i)));
    }
    ready = true;

    for (auto & th : threads)
    {
        th.join();
    }
}

