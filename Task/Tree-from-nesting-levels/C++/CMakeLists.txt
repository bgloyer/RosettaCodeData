cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)

project(tree-from-nesting-levels)

add_executable(tree-from-nesting-levels tree-from-nesting-levels.cpp)

install(TARGETS tree-from-nesting-levels DESTINATION bin)

