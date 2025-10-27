cmake_minimum_required(VERSION 3.28)
project(polymorph)

set(CMAKE_CXX_STANDARD 17)

add_executable(polymorph main.cpp 
                             shape.h 
                             shape.cpp 
                             rectangle.h 
                             rectangle.cpp 
                             circle.h 
                             circle.cpp)
