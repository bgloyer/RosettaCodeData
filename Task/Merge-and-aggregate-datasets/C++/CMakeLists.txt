cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)

project(merge-and-aggregate-datasets)

add_executable(merge-and-aggregate-datasets merge-and-aggregate-datasets.cpp)

install(TARGETS merge-and-aggregate-datasets DESTINATION bin)

