cmake_minimum_required (VERSION 3.7)

# 项目信息
project (QQ-Server)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-std=c++11)
    message(STATUS "optional:-std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)

ADD_SUBDIRECTORY(src)