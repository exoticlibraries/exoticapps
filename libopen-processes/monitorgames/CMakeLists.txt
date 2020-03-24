cmake_minimum_required(VERSION 3.10)
project(monitorgames VERSION 1.0)
target_link_libraries(monitorgames -lpsapi -lopen-processes -lpthread)
add_executable(monitorgames monitorgames.cpp)