cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

project(elliptic-curve-arithmetic)

add_executable(elliptic-curve-arithmetic elliptic-curve-arithmetic.cpp)

install(TARGETS elliptic-curve-arithmetic RUNTIME DESTINATION bin)
