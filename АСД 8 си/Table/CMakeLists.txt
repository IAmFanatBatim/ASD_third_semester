cmake_minimum_required(VERSION 3.25)
project(Table C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Table
        Table.c
        Table.h
        Task.c Table_test.c)
