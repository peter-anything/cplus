//
// Created by peter on 2020/1/19.
//

#ifndef CMAKEDEMO_NOTIFY_TEST_H
#define CMAKEDEMO_NOTIFY_TEST_H

#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>

#include <iostream>

bool more_data_to_prepare()
{
    return true;
}

struct data_chunk
{

};

data_chunk prepare_data()
{
    return data_chunk();
}

void process(data_chunk &)
{

}

bool is_last_chunk(data_chunk &)
{
    return true;
}

std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

void data_preparation_thread()
{
    std::cout << "more_data_to_prepare" << std::endl;
    data_chunk const data = prepare_data();
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(data);
    data_cond.notify_one();
}

void data_processing_thread()
{
    std::cout << "data_processing" << std::endl;
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [] { return !data_queue.empty(); });
    data_chunk data = data_queue.front();
    data_queue.pop();
    lk.unlock();
    process(data);
}

void test()
{
    std::thread t1(data_preparation_thread);
    std::thread t2(data_processing_thread);

    t1.join();
    t2.join();
}

#endif //CMAKEDEMO_NOTIFY_TEST_H