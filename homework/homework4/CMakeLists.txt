cmake_minimum_required(VERSION 3.20)
project(RBTree VERSION 0.1.0 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional: toggle Graphviz linkage (not required for writing DOT files)
option(ENABLE_GRAPHVIZ "Enable Graphviz (link to gvc/cgraph)" OFF)

# Sources
add_executable(
    RBTree
    main.cpp
    rbtree.cpp
)

target_include_directories(RBTree PRIVATE src)

# Nice warnings
if(MSVC)
  target_compile_options(RBTree PRIVATE /W4 /permissive-)
else()
  target_compile_options(RBTree PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Optional Graphviz linking (only needed if you add code that calls libgvc/cgraph APIs)
if(ENABLE_GRAPHVIZ)
  find_path(GRAPHVIZ_INCLUDE_DIR NAMES graphviz/cgraph.h cgraph.h)
  find_library(GVC_LIB gvc)
  find_library(CGRAPH_LIB cgraph)
  if(GRAPHVIZ_INCLUDE_DIR AND GVC_LIB AND CGRAPH_LIB)
    target_compile_definitions(RBTree PRIVATE HAVE_GRAPHVIZ=1)
    target_include_directories(RBTree PRIVATE ${GRAPHVIZ_INCLUDE_DIR})
    target_link_libraries(RBTree PRIVATE ${GVC_LIB} ${CGRAPH_LIB})
  endif()
endif()
