cmake_minimum_required(VERSION 3.20)
project(DisjSets)

set(CMAKE_CXX_STANDARD 20)

add_executable(DisjSets main.cpp
        DisjSet.cpp
        DisjSet.h)

find_library(GVC gvc)
if(GVC)
    target_link_libraries(${PROJECT_NAME} PUBLIC cgraph ${GVC})
endif()