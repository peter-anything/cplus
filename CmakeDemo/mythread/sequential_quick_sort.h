//
// Created by peter on 2020/1/19.
//

#ifndef CMAKEDEMO_SEQUENTIAL_QUICK_SORT_H
#define CMAKEDEMO_SEQUENTIAL_QUICK_SORT_H

#include <list>
#include <algorithm>
#include <future>
#include <type_traits>

struct my_data
{
    unsigned bf1:10;
};

template <class T>
std::list<T> sequential_quick_sort(std::list<T> input)
{
    if (input.empty())
    {
        return input;
    }

    std::list<T> result;
    result.splice(result.begin(), input, input.begin());
    T const& pivot = *result.begin();
    auto divide_point = std::partition(input.begin(), input.end(), [&] (T const& t) { return t < pivot; });
    std::list<T> lower_part;
    lower_part.splice(lower_part.end(), input, input.begin(), divide_point);
    auto new_lower(sequential_quick_sort(std::move(lower_part)));
    auto new_higher(sequential_quick_sort(std::move(input)));
    result.splice(result.end(), new_higher);
    result.splice(result.begin(), new_lower);

    return result;
}

#endif //CMAKEDEMO_SEQUENTIAL_QUICK_SORT_H
