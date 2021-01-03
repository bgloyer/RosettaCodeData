cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

project(deepcopy)

add_executable(deepcopy deepcopy.cpp)

install(TARGETS deepcopy RUNTIME DESTINATION bin)
