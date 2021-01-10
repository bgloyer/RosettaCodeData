cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

project(jump-anywhere)

add_executable(jump-anywhere jump-anywhere.cpp)

install(TARGETS jump-anywhere DESTINATION bin)

