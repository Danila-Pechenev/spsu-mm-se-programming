cmake_minimum_required(VERSION 3.20)
project(Task_2__Hash_map_ C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Task_2__Hash_map_
        list.c
        list.h
        hashtable.c
        hashtable.h
        main.c)
