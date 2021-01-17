cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)

project(ascii-art-diagram-converter)

add_executable(ascii-art-diagram-converter ascii-art-diagram-converter.cpp)

install(TARGETS ascii-art-diagram-converter DESTINATION bin)

