cmake_minimum_required(VERSION 3.28)
project(stack_class)

set(CMAKE_CXX_STANDARD 17)

add_executable(stack_class main.cpp
        Stack.cpp
        Stack.h)
