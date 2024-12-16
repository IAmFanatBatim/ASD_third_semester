cmake_minimum_required(VERSION 3.26)
project(stack C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(stack
        stack.c
        stack.h)
