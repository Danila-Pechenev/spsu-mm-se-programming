cmake_minimum_required(VERSION 3.20)
project(task4 C)

set(CMAKE_C_STANDARD 11)

add_executable(task4 main.c)
target_link_libraries(task4 m)