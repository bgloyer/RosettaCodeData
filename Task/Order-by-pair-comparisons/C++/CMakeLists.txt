cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project(order-by-pair-comparison LANGUAGES CXX)

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
