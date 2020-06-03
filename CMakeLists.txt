cmake_minimum_required(VERSION 3.15)
project(OS_ex4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS -pthread)

add_executable(OS_ex4 test.c osqueue.c osqueue.h threadPool.h threadPool.c)