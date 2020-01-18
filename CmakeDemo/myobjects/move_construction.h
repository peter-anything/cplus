#include <thread>
#include <iostream>

void some_function()
{}

void some_other_function(int)
{}

std::thread f()
{
    void some_function();
    return std::thread(some_function);
}
std::thread g()
{
    void some_other_function(int);
    std::thread t(some_other_function, 42);
    return t;
}

class Person
{
public:
    int* data;
public:
    Person() {
        data = new int[1000];
        for (int i = 0; i < 1000; ++i)
        {
            data[i] = i;
        }

        std::cout << "constructor" << std::endl;
    }
    ~Person() { delete[] data; }
    Person(const Person& other) : data(new int[1000]) {
        std::copy(other.data, other.data + 1000, data);
        std::cout << "copy constructor" << std::endl;
    }
    /*Person(Person && other) : data(other.data)
    {
        other.data = nullptr;

        std::cout << "move constructor" << std::endl;
    }*/
    Person& operator = (const Person& other)
    {
        this->data = new int[1000];
        std::copy(other.data, other.data + 1000, data);

        std::cout << "copy assign" << std::endl;
        return *this;
    }

    Person(Person&& p) : data(p.data) { p.data = nullptr; std::cout << "move constructor" << std::endl; }
};

Person get_person()
{
    Person p;
    return p;
}

void func(Person p)
{
    std::cout << p.data[0];
}

void test_construction()
{
    /*std::thread t1 = f();
    t1.join();
    std::thread t2 = g();
    t2.join();*/
    Person p = get_person();
    Person p2 = p;
    Person p3, p4;
    p3 = p4;
    Person p5;
    Person p6 = std::move(p5);

    Person p7, p8;
    p7 = std::move(p8);

    return 0;
}
