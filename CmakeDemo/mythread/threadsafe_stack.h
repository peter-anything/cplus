#include <exception>
#include <memory>
#include <mutex>
#include <stack>
#include <iostream>

struct empty_stack : std::exception
{
    const char* what() const throw()
    {
        return "empty statck";
    }
};

template<class T>
class threadsafe_stack
{
private:
    std::stack<T> data;
    mutable std::mutex m;

public:
    threadsafe_stack() : data(std::stack<T>()) {}

    threadsafe_stack(const threadsafe_stack& other)
    {
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    }

    threadsafe_stack& operator = (const threadsafe_stack&) = delete;

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push(new_value);
    }

    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
        {
            throw empty_stack();
        }

        std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
        data.pop();

        return res;
    }

    void pop(T& value)
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
        {
            throw empty_stack();
        }

        value = data.top();
        data.pop();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m);

        return data.empty();
    }

    void tranverse()
    {
        std::stack<T> tmp_data = data;
        T data;
        while (!tmp_data.empty())
        {
            data = tmp_data.top();

            std::cout << data << std::endl;
            tmp_data.pop();
        }
    }
};