//
// Created by peter on 2020/1/19.
//

#ifndef CMAKEDEMO_ASYNC_TEST_H
#define CMAKEDEMO_ASYNC_TEST_H

#include <string>
#include <future>
#include <iostream>

struct X
{
    void foo(int, std::string const &) {
        std::cout << "foo" << std::endl;
    }
    std::string bar(std::string const &) {
        std::cout << "bar" << std::endl;
    }
};

struct Y {
    double operator()(double) {}

    Y()
    {
        std::cout << "constructor" << std::endl;
    }
};

class move_only
{
public:
    move_only() {}
    move_only(move_only &&) {}
    move_only(move_only const&) = delete;
    move_only& operator = (move_only &&) {}
    move_only& operator = (move_only const &) = delete;
    void operator() () {}
};

#endif //CMAKEDEMO_ASYNC_TEST_H
