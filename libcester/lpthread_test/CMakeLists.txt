cmake_minimum_required(VERSION 3.10)
project(lpthread_test VERSION 1.0)
add_executable(${PROJECT_NAME} lpthread_test.c)
target_link_libraries(${PROJECT_NAME} -lpthread)

#MINGW => cmake . -G"MinGW Makefiles"