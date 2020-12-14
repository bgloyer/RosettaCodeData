cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project(dining-philosophers)


find_package( Threads REQUIRED )

add_executable(dining-philosophers dining-philosophers-2.cpp)

target_link_libraries(dining-philosophers ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS dining-philosophers RUNTIME DESTINATION bin)
