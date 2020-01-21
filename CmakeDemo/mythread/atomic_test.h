#include <iostream>
#include <cassert>
#include <vector>
#include <thread>
#include <atomic>

std::atomic<int> cnt = { 0 };
std::atomic<bool> ready{ false };
int data = 0;

void f()
{
    for (int n = 0; n < 1000; ++n)
    {
        cnt.fetch_add(1, std::memory_order_relaxed);
    }
}

void producer()
{
    data = 100;
    ready.store(true, std::memory_order_release);
}

void consumer()
{
    while (!ready.load(std::memory_order_consume));

    assert(data == 100);
}

void test1()
{
    std::vector<std::thread> v;
    for (int i = 0; i < 10; ++i)
    {
        v.emplace_back(f);
    }

    for (auto& t : v)
    {
        t.join();
    }

    assert(cnt == 10000);
}

void test2()
{
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
}

std::atomic<bool> x, y;
std::atomic<int> z;

void write_x_then_y()
{
    x.store(true, std::memory_order_relaxed);
    y.store(true, std::memory_order_relaxed);
}

void read_y_then_x()
{
    while (!y.load(std::memory_order_relaxed))
    {
        if (x.load(std::memory_order_relaxed))
        {
            ++z;
        }
    }
}

void test3()
{
    x = false;
    y = false;
    z = 0;
    std::thread a(write_x_then_y);
    std::thread b(read_y_then_x);

    a.join();
    b.join();

    assert(z.load() != 0);
}

struct X
{
    int i;
    std::string s;
};

std::atomic<X*> p;
std::atomic<int> a;

void create_x()
{
    X* x = new X;
    x->i = 42;
    x->s = "hello";
    a.store(99, std::memory_order_relaxed);
    p.store(x, std::memory_order_relaxed);
}

void use_x()
{
    X* x;
    while (!(x=p.load(std::memory_order_relaxed)))
    {
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }

    assert(x->i == 42);
    assert(x->s == "hello");
    assert(a.load(std::memory_order_relaxed) == 99);
}

void test4()
{
    std::thread t1(create_x);
    std::thread t2(use_x);

    t1.join();
    t2.join();
}