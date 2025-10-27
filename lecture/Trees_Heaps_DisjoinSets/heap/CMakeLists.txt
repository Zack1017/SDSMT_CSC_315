cmake_minimum_required(VERSION 3.25)
project(heap)

set(CMAKE_CXX_STANDARD 20)

add_executable(heap main.cpp
        MinHeap.cpp
        MinHeap.h)

find_library(GVC gvc)
if(GVC)
    target_link_libraries(${PROJECT_NAME} PUBLIC cgraph ${GVC})
endif()