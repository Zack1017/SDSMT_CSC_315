cmake_minimum_required(VERSION 3.20)
project(SubsetSum VERSION 0.1.0 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Sources
add_executable(
    SubsetSum
    main.cpp
    SubsetSum.cpp
)

# Include path for headers (adjust if you place headers in a different folder)
target_include_directories(SubsetSum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
