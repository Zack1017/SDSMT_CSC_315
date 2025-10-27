cmake_minimum_required(VERSION 3.25)
project(AVL)

set(CMAKE_CXX_STANDARD 20)

add_executable(AVL main.cpp
        AVLTree.cpp
        AVLTree.h)

find_library(GVC gvc)
if(GVC)
    target_link_libraries(${PROJECT_NAME} PUBLIC cgraph ${GVC})
endif()
