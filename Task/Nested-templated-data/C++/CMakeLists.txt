cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)

project(nested-templated-data)

add_executable(nested-templated-data nested-templated-data.cpp)

target_link_libraries(nested-templated-data ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS nested-templated-data RUNTIME DESTINATION bin)
