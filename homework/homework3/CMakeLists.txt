cmake_minimum_required(VERSION 3.20)
project(expressionTree VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_GRAPHVIZ "Enable Graphviz" ON)

add_executable(expressionTree main.cpp ExpressionTree.cpp)

if(ENABLE_GRAPHVIZ)
  find_path(GRAPHVIZ_INCLUDE_DIR NAMES graphviz/cgraph.h cgraph.h)
  find_library(GVC_LIB gvc)
  find_library(CGRAPH_LIB cgraph)
  if(GRAPHVIZ_INCLUDE_DIR AND GVC_LIB AND CGRAPH_LIB)
    target_compile_definitions(expressionTree PRIVATE HAVE_GRAPHVIZ=1)
    target_include_directories(expressionTree PRIVATE ${GRAPHVIZ_INCLUDE_DIR})
    target_link_libraries(expressionTree PRIVATE ${GVC_LIB} ${CGRAPH_LIB})
  endif()
endif()
