cmake_minimum_required(VERSION 3.20)
project(list_class)

set(CMAKE_CXX_STANDARD 20)

add_executable(list_class main.cpp
        linklist.h
        linklist.cpp)
