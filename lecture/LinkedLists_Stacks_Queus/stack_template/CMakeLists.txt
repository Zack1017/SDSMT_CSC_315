cmake_minimum_required(VERSION 3.29)
project(stack_template)

set(CMAKE_CXX_STANDARD 20)

add_executable(stack_template main.cpp
        Stack.cpp
        Stack.h)
