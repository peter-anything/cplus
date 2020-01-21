#include <iostream>

class Test
{
public:
    int m_a;
public:
    Test(int a = 0) : m_a(a) {}
    ~Test()
    {
        std::cout << "destroy" << std::endl;
    }
};

void Fun(std::auto_ptr<Test> p)
{
    std::cout << p->m_a << std::endl;
}

class B;
class A
{
public:
    A() : m_b() {};
    ~A() {
        std::cout << "delete A" << std::endl;
    }
public:
    std::weak_ptr<B> m_b;
};

class B
{
public:
    B() : m_a(nullptr) {};
    ~B() {
        std::cout << "delete B" << std::endl;
    }
public:
    std::shared_ptr<A> m_a;
};

template<class T>
class Enalbed_Shared_From_This
{
public:
    std::shared_ptr<T> shared_from_this() {
        return std::shared_ptr<T> this;
    }
};

class AA : public std::enable_shared_from_this<AA>
{
public:
    AA()
    {
        std::cout << "new AA" << std::endl;
    }

    ~AA()
    {
        std::cout << "delete AA" << std::endl;
    }
};

int main()
{
    std::shared_ptr<AA> p1(std::make_shared<AA>());
    std::shared_ptr<AA> p2 = p1->shared_from_this();
}
