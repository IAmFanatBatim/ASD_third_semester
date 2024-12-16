cmake_minimum_required(VERSION 3.26)
project(fifo C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(fifo
        fifo.c
        fifo.h)
