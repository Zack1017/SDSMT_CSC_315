cmake_minimum_required(VERSION 3.29)
project(gen_Tree)

set(CMAKE_CXX_STANDARD 20)

add_executable(gen_Tree main.cpp
        LC_RS_Tree.cpp
        LC_RS_Tree.h)

find_library(GVC gvc)
if(GVC)
    target_link_libraries(${PROJECT_NAME} PUBLIC cgraph ${GVC})
endif()
