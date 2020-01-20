cmake_minimum_required(VERSION 3.13)
project(CmakeDemo)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)

include_directories(./linkedlist)

include_directories(./mythread)

include_directories(./datastruct)

add_executable(CmakeDemo main.cpp)

target_link_libraries(CmakeDemo ${CMAKE_THREAD_LIBS_INIT})