cmake_minimum_required(VERSION 3.13)
project(GOL C)

set(CMAKE_C_STANDARD 99)

add_executable(GOL main.c life.c life.h file_library.c file_library.h)