cmake_minimum_required(VERSION 3.7)
project(CmakeDemo)

find_package(Threads)

#include_directories(./linkedlist)

#include_directories(./datastruct)

#include_directories(./kernel)

include_directories(./leetcode)
include_directories(./utils)
add_subdirectory(./docker-inside)
#add_subdirectory(./raft-demo)

add_executable(CmakeDemo main.cpp docker-inside/cgroup/memory_limit.h)

target_link_libraries(CmakeDemo ${CMAKE_THREAD_LIBS_INIT})