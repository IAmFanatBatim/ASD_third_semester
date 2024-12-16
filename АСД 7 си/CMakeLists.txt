cmake_minimum_required(VERSION 3.26)
project(_7_ C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(_7_
        tree.c
        tree.h)
