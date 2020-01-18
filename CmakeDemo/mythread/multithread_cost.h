#include <thread>
#include <numeric>
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>
#include <chrono>

template<class Iterator, class T>
struct accumulate_block
{
    void operator()(Iterator first, Iterator last, T& result)
    {
        result = std::accumulate(first, last, result);
    }
};

template<class Iterator, class T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    unsigned long const length = std::distance(first, last);

    if (!length)
        return init;

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads =
        (length + min_per_thread - 1) / min_per_thread;

    unsigned long const hardware_threads =
        std::thread::hardware_concurrency();

    unsigned long const num_threads =
        std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

    unsigned long const block_size = length / num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread>  threads(num_threads - 1);

    Iterator block_start = first;
    for (unsigned long i = 0; i < (num_threads - 1); ++i)
    {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(
            accumulate_block<Iterator, T>(),
            block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    }
    accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);

    std::for_each(threads.begin(), threads.end(),
        std::mem_fn(&std::thread::join));

    return std::accumulate(results.begin(), results.end(), init);
}

int test_cost()
{
    std::vector<double> vi;
    for (long i = 0; i < 100000000; i++)
    {
        double d = i + 0.1;
        vi.push_back(d);
    }

    double init = 0;

    auto start = std::chrono::system_clock::now();
    double sum = parallel_accumulate(vi.begin(), vi.end(), init);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << elapsed_seconds.count() << std::endl;
    std::cout << sum << std::endl;

    double test_sum = std::accumulate(vi.begin(), vi.end(), init);
    auto end2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = end2 - end;
    std::cout << elapsed_seconds2.count() << std::endl;
    std::cout << test_sum << std::endl;

    return 0;
}