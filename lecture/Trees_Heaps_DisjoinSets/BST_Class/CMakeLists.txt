cmake_minimum_required(VERSION 3.28)
project(BST_Class)

set(CMAKE_CXX_STANDARD 20)

add_executable(BST_Class main.cpp
        BST.cpp
        BST.h)

find_library(GVC gvc)
if(GVC)
    target_link_libraries(${PROJECT_NAME} PUBLIC cgraph ${GVC})
endif()
